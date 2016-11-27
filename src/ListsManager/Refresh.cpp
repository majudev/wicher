#include "ListsManager.h"

bool Wicher::ListsManager::refresh_wz(){
    this->wz_list->clear();

    json_error_t error;
    json_t * root = json_loads(Database::getSingleton().run(Database::Query::get_wzs()).c_str(), 0, &error);
    if(!root){
        Toolkit::log(std::string("JSON error when refreshing WZs:") + std::string(error.text));
        Toolkit::log(std::string("\tSource:") + std::string(error.source));
        Toolkit::log(std::string("\tLine:") + Toolkit::itostr(error.line));
        Toolkit::log(std::string("\tColumn:") + Toolkit::itostr(error.column));
        Toolkit::log(std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position));
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            std::string response(response_str);
            if(response == std::string("ok")){
                json_t * array = json_object_get(root, "wzs");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        int id = json_integer_value(json_object_get(obj, "id"));
                        const char * date_str = json_string_value(json_object_get(obj, "date"));
                        const char * person_str = json_string_value(json_object_get(obj, "person"));
                        const char * return_date_str = json_string_value(json_object_get(obj, "return_date"));
                        const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                        if(date_str && person_str && return_date_str && comment_str){
                            std::string date(date_str);
                            std::string person(person_str);
                            std::string return_date(return_date_str);
                            std::string comment(comment_str);

                            Gtk::TreeModel::iterator iter = this->wz_list->append();
                            Gtk::TreeModel::Row row = *iter;
                            row[wz_columns.id] = id;
                            row[wz_columns.date] = date.c_str();
                            row[wz_columns.person] = person.c_str();
                            row[wz_columns.return_date] = return_date.c_str();
                            row[wz_columns.comment] = comment.c_str();
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else Toolkit::log(std::string("Error when refreshing WZs. Server's response: ") + response);
        }
    }

    free(root);
    return false;
}

bool Wicher::ListsManager::refresh_pz(){
    this->pz_list->clear();

    json_error_t error;
    json_t * root = json_loads(Database::getSingleton().run(Database::Query::get_pzs()).c_str(), 0, &error);
    if(!root){
        Toolkit::log(std::string("JSON error when refreshing PZs:") + std::string(error.text));
        Toolkit::log(std::string("\tSource:") + std::string(error.source));
        Toolkit::log(std::string("\tLine:") + Toolkit::itostr(error.line));
        Toolkit::log(std::string("\tColumn:") + Toolkit::itostr(error.column));
        Toolkit::log(std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position));
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            std::string response(response_str);
            if(response == std::string("ok")){
                json_t * array = json_object_get(root, "pzs");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        int id = json_integer_value(json_object_get(obj, "id"));
                        int wz_id = json_integer_value(json_object_get(obj, "wz_id"));
                        const char * date_str = json_string_value(json_object_get(obj, "date"));
                        const char * person_str = json_string_value(json_object_get(obj, "person"));
                        const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                        if(date_str && person_str && comment_str){
                            std::string date(date_str);
                            std::string person(person_str);
                            std::string comment(comment_str);

                            Gtk::TreeModel::iterator iter = this->pz_list->append();
                            Gtk::TreeModel::Row row = *iter;
                            row[pz_columns.id] = id;
                            row[pz_columns.wz_id] = wz_id;
                            row[pz_columns.date] = date.c_str();
                            row[pz_columns.person] = person.c_str();
                            row[pz_columns.comment] = comment.c_str();
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else Toolkit::log(std::string("Error when refreshing PZs. Server's response: ") + response);
        }
    }

    free(root);
    return false;
}

bool Wicher::ListsManager::refresh_history(){
    this->history_list->clear();

    json_error_t error;
    json_t * root = json_loads(Database::getSingleton().run(Database::Query::get_history()).c_str(), 0, &error);
    if(!root){
        Toolkit::log(std::string("JSON error when refreshing history:") + std::string(error.text));
        Toolkit::log(std::string("\tSource:") + std::string(error.source));
        Toolkit::log(std::string("\tLine:") + Toolkit::itostr(error.line));
        Toolkit::log(std::string("\tColumn:") + Toolkit::itostr(error.column));
        Toolkit::log(std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position));
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            std::string response(response_str);
            if(response == std::string("ok")){
                json_t * array = json_object_get(root, "history");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        int id = json_integer_value(json_object_get(obj, "id"));
                        const char * data_str = json_string_value(json_object_get(obj, "data"));
                        if(data_str){
                            std::string data(data_str);

                            Gtk::TreeModel::iterator iter = this->history_list->append();
                            Gtk::TreeModel::Row row = *iter;
                            row[history_columns.id] = id;
                            row[history_columns.data] = data.c_str();
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else Toolkit::log(std::string("Error when refreshing history. Server's response: ") + response);
        }
    }

    free(root);
    return false;
}

bool Wicher::ListsManager::refresh_all(){
    bool res = true;
    if(!this->refresh_types()){
        res = false;
        Toolkit::log("Failed to refresh types list.");
    }
    if(!this->refresh_lists()){
        res = false;
        Toolkit::log("Failed to refresh items lists.");
    }
    if(!this->refresh_wz()){
        res = false;
        Toolkit::log("Failed to refresh WZs list.");
    }
    if(!this->refresh_pz()){
        res = false;
        Toolkit::log("Failed to refresh PZs list.");
    }
    if(!this->refresh_history()){
        res = false;
        Toolkit::log("Failed to refresh history.");
    }
    return res;
}

void Wicher::ListsManager::refresh_all_void(){
    if(!this->refresh_all()){
        Dialogger::refresh_error();
    }
}
