#include "db.h"
#include <string.h>
#include <jansson.h>
#include "sha256.h"

char * database_query_login(const char * login, const char * password){
    SHA256_BYTE buffer[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    sha256_init(&ctx);
	sha256_update(&ctx, password, strlen(password));
    sha256_final(&ctx, buffer);
    char password_hash[SHA256_BLOCK_SIZE*2+1];
    for(int i = 0; i < SHA256_BLOCK_SIZE; ++i){
        sprintf(password_hash + 2*i, "%02x", buffer[i]);
    }
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("login"));
    json_object_set_new(root, "login", json_string(login));
    json_object_set_new(root, "password", json_string(password_hash));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_register_item(const char * type, const char * comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "type", json_string(type));
    json_object_set_new(root, "comment", json_string(comment));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_register_type(const char * id, const char * name, const char * comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id));
    json_object_set_new(root, "name", json_string(name));
    json_object_set_new(root, "comment", json_string(comment));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_register_wz(const char * date, const char * person, const char * comment, size_t items_count, int * item_ids, char ** item_types){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "date", json_string(date));
    json_object_set_new(root, "person", json_string(person));
    json_object_set_new(root, "comment", json_string(comment));
    json_t * items = json_array();
    size_t x = 0;
    while(x < items_count){
        json_t * obj = json_object();
        json_object_set_new(obj, "id", json_integer(item_ids[x]));
        json_object_set_new(obj, "type", json_string(item_types[x]));
        json_array_append_new(items, obj);
        ++x;
    }
    json_object_set_new(root, "items", items);
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_register_pz(int wz_id, const char * date, const char * person, const char * comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("register"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "wz_id", json_integer(wz_id));
    json_object_set_new(root, "date", json_string(date));
    json_object_set_new(root, "person", json_string(person));
    json_object_set_new(root, "comment", json_string(comment));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_change_item(int id, const char * type, const char * new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "id", json_integer(id));
    json_object_set_new(root, "type", json_string(type));
    if(new_comment[0]){
        json_object_set_new(root, "new_comment", json_string(new_comment));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_change_type(const char * id, const char * new_name, bool change_comment, const char * new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id));
    if(new_name[0]){
        json_object_set_new(root, "new_name", json_string(new_name));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_change_wz(int id, const char * new_date, const char * new_person, bool change_comment, const char * new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "id", json_integer(id));
    if(new_date[0]){
        json_object_set_new(root, "new_date", json_string(new_date));
    }
    if(new_person[0]){
        json_object_set_new(root, "new_person", json_string(new_person));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_change_pz(int id, const char * new_date, const char * new_person, bool change_comment, const char * new_comment){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("change"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "id", json_integer(id));
    if(new_date[0]){
        json_object_set_new(root, "new_date", json_string(new_date));
    }
    if(new_person[0]){
        json_object_set_new(root, "new_person", json_string(new_person));
    }
    if(change_comment){
        json_object_set_new(root, "new_comment", json_string(new_comment));
    }
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_drop_item(int id, const char * type){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("item"));
    json_object_set_new(root, "id", json_integer(id));
    json_object_set_new(root, "type", json_string(type));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_drop_type(const char * id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("type"));
    json_object_set_new(root, "id", json_string(id));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_drop_wz(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("wz"));
    json_object_set_new(root, "id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
char * database_query_drop_pz(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("drop"));
    json_object_set_new(root, "request_type", json_string("pz"));
    json_object_set_new(root, "id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_items(const char * type){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("items"));
    json_object_set_new(root, "type", json_string(type));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_types(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("types"));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_wzs(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("wzs"));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_pzs(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("pzs"));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_history(){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("history"));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}

char * database_query_get_wz_items(int id){
    json_t * root = json_object();
    json_object_set_new(root, "request", json_string("get"));
    json_object_set_new(root, "request_type", json_string("wz_items"));
    json_object_set_new(root, "wz_id", json_integer(id));
    char * str = json_dumps(root, JSON_COMPACT);
    char * tr = strdup(str);
    free(str);
    free(root);
    return tr;
}
