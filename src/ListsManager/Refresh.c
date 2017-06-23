#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool listsmanager_refresh_wz(){
    gtk_list_store_clear(wz_list);

    json_error_t error;
    json_t * root = json_loads(database_run(database_query_get_wzs()), 0, &error);
    if(!root){
        wicherlog("JSON error when refreshing WZs: %s", error.text);
        wicherlog("\tSource: %s", error.source);
        wicherlog("\tLine: %d", error.line);
        wicherlog("\tColumn: %d", error.column);
        wicherlog("\tPosition [bytes]: %d", error.position);
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            if(!strcmp(response_str, "ok")){
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
                            GtkTreeIter iter;
                            gtk_list_store_append(wz_list, &iter);
                            gtk_list_store_set(wz_list, &iter, WZ_COLUMNS_ID, id,
                                               WZ_COLUMNS_DATE, date_str,
                                               WZ_COLUMNS_PERSON, person_str,
                                               WZ_COLUMNS_RETURN_DATE, return_date_str,
                                               WZ_COLUMNS_COMMENT, comment_str, -1);
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else wicherlog("Error when refreshing WZs. Server's response: %s", response_str);
        }
    }

    free(root);
    return false;
}

bool listsmanager_refresh_pz(){
    gtk_list_store_clear(pz_list);

    json_error_t error;
    json_t * root = json_loads(database_run(database_query_get_pzs()), 0, &error);
    if(!root){
        wicherlog("JSON error when refreshing PZs: %s", error.text);
        wicherlog("\tSource: %s", error.source);
        wicherlog("\tLine: %d", error.line);
        wicherlog("\tColumn: %d", error.column);
        wicherlog("\tPosition [bytes]: %d", error.position);
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            if(!strcmp(response_str, "ok")){
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
                            GtkTreeIter iter;
                            gtk_list_store_append(pz_list, &iter);
                            gtk_list_store_set(pz_list, &iter, PZ_COLUMNS_ID, id,
                                               PZ_COLUMNS_WZ_ID, wz_id,
                                               PZ_COLUMNS_DATE, date_str,
                                               PZ_COLUMNS_PERSON, person_str,
                                               PZ_COLUMNS_COMMENT, comment_str, -1);
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else wicherlog("Error when refreshing PZs. Server's response: %s", response_str);
        }
    }

    free(root);
    return false;
}

bool listsmanager_refresh_history(){
    gtk_list_store_clear(history_list);

    json_error_t error;
    json_t * root = json_loads(database_run(database_query_get_history()), 0, &error);
    if(!root){
        wicherlog("JSON error when refreshing history: %s", error.text);
        wicherlog("\tSource: %s", error.source);
        wicherlog("\tLine: %d", error.line);
        wicherlog("\tColumn: %d", error.column);
        wicherlog("\tPosition [bytes]: %d", error.position);
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            if(!strcmp(response_str, "ok")){
                json_t * array = json_object_get(root, "history");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        int id = json_integer_value(json_object_get(obj, "id"));
                        const char * data_str = json_string_value(json_object_get(obj, "data"));
                        if(data_str){
                            GtkTreeIter iter;
                            gtk_list_store_append(history_list, &iter);
                            gtk_list_store_set(history_list, &iter, HISTORY_COLUMNS_ID, id,
                                               HISTORY_COLUMNS_DATA, data_str, -1);
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else wicherlog("Error when refreshing history. Server's response: %s", response_str);
        }
    }

    free(root);
    return false;
}

bool listsmanager_refresh_all(){
    bool res = true;
    if(!listsmanager_refresh_types()){
        res = false;
        wicherlog("Failed to refresh types list.");
    }
    if(!listsmanager_refresh_lists()){
        res = false;
        wicherlog("Failed to refresh items lists.");
    }
    if(!listsmanager_refresh_wz()){
        res = false;
        wicherlog("Failed to refresh WZs list.");
    }
    if(!listsmanager_refresh_pz()){
        res = false;
        wicherlog("Failed to refresh PZs list.");
    }
    if(!listsmanager_refresh_history()){
        res = false;
        wicherlog("Failed to refresh history.");
    }
    return res;
}

void listsmanager_refresh_all_void(){
    if(!listsmanager_refresh_all()){
        show_dialog_refresh_error();
    }
}
