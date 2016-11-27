#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Toolkit.h"
#include "sha256.h"

#include <vector>
#include <jansson.h>

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#include <Windows.h>
#include <io.h>
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#define WIN
#elif defined(__unix__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define UNI
#endif

namespace Wicher{
class Database{
    public:
        static Database & getSingleton();
        bool conn(std::string address, int port);
        bool login(std::string login, std::string password);
        bool connected();
        std::string run(std::string msg);

        ~Database();

        class Query{
            public:
                static std::string login(std::string login, std::string password);

                static std::string register_item(std::string type, std::string comment);
                static std::string register_type(std::string id, std::string name, std::string comment);
                static std::string register_wz(std::string date, std::string person, std::string comment, std::vector<int> item_ids, std::vector<std::string> item_types);
                static std::string register_pz(int wz_id, std::string date, std::string person, std::string comment);

                static std::string change_item(int id, std::string type, std::string new_comment);
                static std::string change_type(std::string id, std::string new_name, bool change_comment, std::string new_comment);
                static std::string change_wz(int id, std::string new_date, std::string new_person, bool change_comment, std::string new_comment/*, std::vector<int> new_item_ids, std::vector<std::string> new_item_types*/);
                static std::string change_pz(int id, std::string new_date, std::string new_person, bool change_comment, std::string new_comment);

                static std::string drop_item(int id, std::string type);
                static std::string drop_type(std::string id);
                static std::string drop_wz(int id);
                static std::string drop_pz(int id);

                static std::string get_items(std::string type);
                static std::string get_types();
                static std::string get_wzs();
                static std::string get_pzs();
                static std::string get_history();
                static std::string get_wz_items(int id);
        };

    private:
        bool c;
        int sock;
        Database();
        Database(const Database&);
        bool send(std::string msg);
        std::string recv();
};
}

#endif // DATABASE_H
