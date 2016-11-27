#include "Database.h"
#include <jansson.h>

std::string Wicher::Database::Query::login(std::string login, std::string password){
    SHA256 sha256;
    std::string passwd = sha256(password);
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("login"));
    json_object_set_new(root, "login", json_string(login.c_str()));
    json_object_set_new(root, "password", json_string(passwd.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::register_item(std::string type, std::string comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "type", json_string(type.c_str()));
    json_object_set_new(root, "comment", json_string(comment.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::register_type(std::string id, std::string name, std::string comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id.c_str()));
    json_object_set_new(root, "name", json_string(name.c_str()));
    json_object_set_new(root, "comment", json_string(comment.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::register_wz(std::string date, std::string person, std::string comment, std::vector<int> item_ids, std::vector<std::string> item_types){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "date", json_string(date.c_str()));
    json_object_set_new(root, "person", json_string(person.c_str()));
    json_object_set_new(root, "comment", json_string(comment.c_str()));
    json_t * items = json_array();
    unsigned int x = 0;
    while(x != item_ids.size()){
        json_t * obj = json_object();
        json_object_set_new(obj, "id", json_integer(item_ids[x]));
        json_object_set_new(obj, "type", json_string(item_types[x].c_str()));
        json_array_append_new(items, obj);
        ++x;
    }
    json_object_set_new(root, "items", items);
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::register_pz(int wz_id, std::string date, std::string person, std::string comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "wz_id", json_integer(wz_id));
    json_object_set_new(root, "date", json_string(date.c_str()));
    json_object_set_new(root, "person", json_string(person.c_str()));
    json_object_set_new(root, "comment", json_string(comment.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::change_item(int id, std::string type, std::string new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "id", json_integer(id));
    json_object_set_new(root, "type", json_string(type.c_str()));
    if(!new_comment.empty()){
        json_object_set_new(root, "new_comment", json_string(new_comment.c_str()));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::change_type(std::string id, std::string new_name, bool change_comment, std::string new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id.c_str()));
    if(!new_name.empty()){
        json_object_set_new(root, "new_name", json_string(new_name.c_str()));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment.c_str()));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::change_wz(int id, std::string new_date, std::string new_person, bool change_comment, std::string new_comment/*, std::vector<int> new_item_ids, std::vector<std::string> new_item_types*/){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "id", json_integer(id));
    if(!new_date.empty()){
        json_object_set_new(root, "new_date", json_string(new_date.c_str()));
    }
    if(!new_person.empty()){
        json_object_set_new(root, "new_person", json_string(new_person.c_str()));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment.c_str()));
    }
    /*if(!new_item_ids.empty()){
        json_t * items = json_array();
        unsigned int x = 0;
        while(x != new_item_ids.size()){
            json_t * obj = json_object();
            json_object_set_new(obj, "id", json_integer(new_item_ids[x]));
            json_object_set_new(obj, "type", json_string(new_item_types[x].c_str()));
            json_array_append_new(items, obj);
            ++x;
        }
        json_object_set_new(root, "new_items", items);
    }*/
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::change_pz(int id, std::string new_date, std::string new_person, bool change_comment, std::string new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "id", json_integer(id));
    if(!new_date.empty()){
        json_object_set_new(root, "new_date", json_string(new_date.c_str()));
    }
    if(!new_person.empty()){
        json_object_set_new(root, "new_person", json_string(new_person.c_str()));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment.c_str()));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::drop_item(int id, std::string type){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "id", json_integer(id));
    json_object_set_new(root, "type", json_string(type.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::drop_type(std::string id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::drop_wz(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
std::string Wicher::Database::Query::drop_pz(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_items(std::string type){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("items"));
    json_object_set_new(root, "type", json_string(type.c_str()));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_types(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("types"));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_wzs(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("wzs"));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_pzs(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("pzs"));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_history(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("history"));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}

std::string Wicher::Database::Query::get_wz_items(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("wz_items"));
    json_object_set_new(root, "wz_id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    std::string tr(str);
    free(str);
    free(root);
    return tr;
}
