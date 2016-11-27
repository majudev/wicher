#include "Database.h"
#define MAX_BUFF 65535

Wicher::Database::Database() : c(false){
    Toolkit::log("Creating Database() singleton...");
}

Wicher::Database & Wicher::Database::getSingleton(){
    static Database db;
    return db;
}

bool Wicher::Database::conn(std::string address, int port){
    if(this->connected()){
        return true;
    }
#ifdef WIN
    Toolkit::log("Initializing Winsock2...");
    WSADATA wsadata;
    int error = WSAStartup(0x0202, &wsadata);
    if(error){
        Toolkit::log("Error when initializing Winsock2. Will now halt.\n");
        perror("Error");
        return false;
    }

    if(wsadata.wVersion != 0x0202){
        Toolkit::log("Error. Cannot get 0x0202 version of Winsock. Will now halt.\n");
        WSACleanup();
        return false;
    }
#endif
    Toolkit::log("Creating socket...");
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
            perror("Error when creating socket");
            return false;
    }
    struct hostent * server = gethostbyname(address.c_str());
    if(server == NULL){
            Toolkit::log("Error: wrong hostname!");
            return false;
    }
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);
    Toolkit::log("Connecting to " + address + ":" + Toolkit::itostr(port));
    if(connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
            perror("Error when connecting");
            return false;
    }else{
            Toolkit::log("Got connection!");
            this->c = true;
            return true;
    }
}

bool Wicher::Database::connected(){ return this->c; }

std::string Wicher::Database::run(std::string msg){
    if(!connected()) return std::string("NOT_CONNECTED");
    if(!this->send(msg)){
        return std::string("SEND_FAILED");
    }
    std::string r = this->recv();
    if(r == std::string("")){
        return std::string("RECV_FAILED");
    }
    return r;
}

bool Wicher::Database::login(std::string login, std::string password){
    std::string resp = this->run(Query::login(login, password));
    json_t * root = json_loads(resp.c_str(), 0, 0);
    json_t * response = json_object_get(root, "response");
    const char * response_str = json_string_value(response);
    if(!response_str){
        Toolkit::log("Cannot read server's response. Auth failed.");
        return false;
    }
    std::string r(response_str);
    free(root);
    return r == std::string("ok");
}

static bool send_msg(std::string msg, int sock){
    if(msg.size()+1 > MAX_BUFF){
        Wicher::Toolkit::log("Failed to send message (message too big)");
        return false;
    }
    uint16_t msize = msg.size() + 1;
    int res = send(sock, &msize, 2, 0);
    if(res != 2){
        Wicher::Toolkit::log("Failed to send message (cannot send msg size)");
        return false;
    }
	res = 0;
    while(res < msize){
        int res_tmp = send(sock, msg.c_str(), msize, 0);
        if(res_tmp < 0){
            Wicher::Toolkit::log("Failed to send message (error when sending content)");
            break;
        }//else std::cerr << "Sent: " << msg << std::endl;
        res += res_tmp;
    }
	return res == msize;
}

bool Wicher::Database::send(std::string msg){
	return send_msg(msg, this->sock);
}

static std::string recv_msg(int sock){
    uint16_t msize;
    int res = recv(sock, &msize, 2, 0);
    if(res != 2){
        Wicher::Toolkit::log("Failed to recv message (cannot recv msg size)");
        return std::string();
    }
    std::string tr;
	char buffer[1025];
    res = 0;
    while(res < msize){
        int res_tmp = recv(sock, buffer, 1024, 0);
        if(res_tmp < 0){
            Wicher::Toolkit::log("Failed to recv message (error when receiving content)");
            break;
        }
        buffer[1024] = '\0';
        res += res_tmp;
        tr += buffer;
    }
    if(res == msize){
        return tr;
    }else return std::string();
}

std::string Wicher::Database::recv(){
	return recv_msg(this->sock);
}

Wicher::Database::~Database(){
    send("BYE");
	Toolkit::log("Closing connection...");
#ifdef WIN
    closesocket(this->sock);
    Toolkit::log("Cleaning up Winsock2...");
    WSACleanup();
#elif defined(UNI)
    close(this->sock);
#endif
}
