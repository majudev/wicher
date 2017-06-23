#include "db.h"
#include <string.h>
#include <errno.h>
#include <jansson.h>

#define MAX_BUFF 65535

bool database_connected = false;
int database_sock = -1;

bool database_connect(const char * address, int port){
    if(database_connected){
        return true;
    }
#ifdef WIN
    wicherlog("Initializing Winsock2...");
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if(error){
        wicherlog_err("Error when initializing Winsock2. Will now halt.\n");
        wicherlog_err("Error: %s", strerror(errno));
        return false;
    }

    if(wsadata.wVersion != 0x0202){
        wicherlog_err("Error. Cannot get 0x0202 version of Winsock. Will now halt.\n");
        WSACleanup();
        return false;
    }
#endif
    wicherlog("Creating socket...");
    database_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(database_sock < 0){
            wicherlog_err("Error when creating socket: %s", strerror(errno));
            return false;
    }
    struct hostent * server = gethostbyname(address);
    if(server == NULL){
            wicherlog_err("Error: wrong hostname!");
            return false;
    }
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);
    wicherlog("Connecting to %s:%d", address, port);
    if(connect(database_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
            wicherlog_err("Error when connecting: %s", strerror(errno));
            return false;
    }else{
            wicherlog("Got connection!");
            database_connected = true;
            return true;
    }
}

bool database_send(char * msg){
    uint16_t msize = strlen(msg) + 1;
    if(msize+1 > MAX_BUFF){
        wicherlog("Failed to send message (message too big)");
        return false;
    }
#ifdef WIN
    int res = send(database_sock, (char*) &msize, 2, 0);
#else
    int res = send(database_sock, &msize, 2, 0);
#endif
    if(res != 2){
        wicherlog("Failed to send message (cannot send msg size)");
        return false;
    }
	res = 0;
    while(res < msize){
        int res_tmp = send(database_sock, msg, msize, 0);
        if(res_tmp < 0){
            wicherlog("Failed to send message (error when sending content)");
            break;
        }//else std::cerr << "Sent: " << msg << std::endl;
        res += res_tmp;
    }
	return res == msize;
}

char * database_recv(){
    uint16_t msize;
#ifdef WIN
    int res = recv(database_sock, (char*) &msize, 2, 0);
#else
    int res = recv(database_sock, &msize, 2, 0);
#endif
    if(res != 2){
        wicherlog("Failed to recv message (cannot recv msg size)");
        return "";
    }
    char * tr = realloc(NULL, 1); tr[0] = '\0';
	char buffer[1025];
    res = 0;
    while(res < msize){
        int res_tmp = recv(database_sock, buffer, 1024, 0);
        if(res_tmp < 0){
            wicherlog("Failed to recv message (error when receiving content)");
            break;
        }
        buffer[1024] = '\0';
        res += res_tmp;
        tr = realloc(tr, res);
        strcat(tr, buffer);
    }
    if(res == msize){
        return tr;
    }else return "";
}

char * database_run(char * msg){
    if(!database_connected) return strdup("NOT_CONNECTED");
    if(!database_send(msg)){
        return strdup("SEND_FAILED");
    }
    char * r = database_recv();
    if(!r[0]){
        return strdup("RECV_FAILED");
    }
    return r;
}

bool database_login(const char * login, const char * password){
    char * resp = database_run(database_query_login(login, password));
    json_t * root = json_loads(resp, 0, 0);
    json_t * response = json_object_get(root, "response");
    const char * response_str = json_string_value(response);
    if(!response_str){
        wicherlog("Cannot read server's response. Auth failed.");
        return false;
    }
    bool r = !strcmp(response_str, "ok");
    free(root);
    return r;
}

void database_cleanup(){
    database_send("BYE");
	wicherlog("Closing connection...");
#ifdef WIN
    closesocket(database_sock);
    wicherlog("Cleaning up Winsock2...");
    WSACleanup();
#elif defined(UNI)
    close(database_sock);
#endif
}
