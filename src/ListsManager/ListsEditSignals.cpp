#include "ListsManager.h"

void Wicher::ListsManager::on_wz_date_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    if(!Wicher::Config::getSingleton().get_unsafe_mode()) return;
    if(new_text.empty()) return;
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->wz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[wz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_wz(id, std::string(new_text), "", false, ""));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[wz_columns.date] = new_text;
        }
        free(root);
    }
}
void Wicher::ListsManager::on_wz_person_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    if(!Wicher::Config::getSingleton().get_unsafe_mode()) return;
    if(new_text.empty()) return;
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->wz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[wz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_wz(id, "", std::string(new_text), false, ""));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[wz_columns.person] = new_text;
        }
        free(root);
    }
}
void Wicher::ListsManager::on_wz_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->wz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[wz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_wz(id, "", "", true, std::string(new_text)));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[wz_columns.comment] = new_text;
        }
        free(root);
    }
}

void Wicher::ListsManager::on_pz_date_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    if(!Wicher::Config::getSingleton().get_unsafe_mode()) return;
    if(new_text.empty()) return;
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->pz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[pz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_pz(id, std::string(new_text), "", false, ""));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[pz_columns.date] = new_text;
        }
        free(root);
    }
}
void Wicher::ListsManager::on_pz_person_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    if(!Wicher::Config::getSingleton().get_unsafe_mode()) return;
    if(new_text.empty()) return;
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->pz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[pz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_pz(id, "", std::string(new_text), false, ""));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[pz_columns.person] = new_text;
        }
        free(root);
    }
}
void Wicher::ListsManager::on_pz_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->pz_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        int id = row[pz_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_pz(id, "", "", true, std::string(new_text)));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!(json_is_string(r) && std::string(json_string_value(r)) == std::string("ok"))){
            Wicher::Dialogger::update_error();
        }else{
            row[pz_columns.comment] = new_text;
        }
        free(root);
    }
}
