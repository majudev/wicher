#ifndef DATABASE_H
#define DATABASE_H
#include <stdbool.h>
#include "toolkit.h"

#ifdef WIN
#include <winsock2.h>
#include <Windows.h>
#include <io.h>
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#elif defined(UNI)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

extern char * database_query_login(const const char * login, const const char * password);
extern char * database_query_register_item(const char * type, const char * comment);
extern char * database_query_register_type(const char * id, const char * name, const char * comment);
extern char * database_query_register_wz(const char * date, const char * person, const char * comment, size_t items_count, int * item_ids, char ** item_types);
extern char * database_query_register_pz(int wz_id, const char * date, const char * person, const char * comment);
extern char * database_query_change_item(int id, const char * type, const char * new_comment);
extern char * database_query_change_type(const char * id, const char * new_name, bool change_comment, const char * new_comment);
extern char * database_query_change_wz(int id, const char * new_date, const char * new_person, bool change_comment, const char * new_comment);
extern char * database_query_change_pz(int id, const char * new_date, const char * new_person, bool change_comment, const char * new_comment);
extern char * database_query_drop_item(int id, const char * type);
extern char * database_query_drop_type(const char * id);
extern char * database_query_drop_wz(int id);
extern char * database_query_drop_pz(int id);
extern char * database_query_get_items(const char * type);
extern char * database_query_get_types();
extern char * database_query_get_wzs();
extern char * database_query_get_pzs();
extern char * database_query_get_history();
extern char * database_query_get_wz_items(int id);

extern bool database_connect(const char * address, int port);
extern bool database_send(char * msg);
extern char * database_recv();
extern char * database_run(char * msg);
extern bool database_login(const char * login, const char * password);
extern void database_cleanup();

#endif