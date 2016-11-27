#include "SignalWindows.h"

void Wicher::SignalWindows::show_create_type_window(){
    if(!is_shown_create_type_window()){
        new_type_name_entry->set_text("");
        new_type_id_entry->set_text("");
        new_type_comment_entry->set_text("");
        this->new_type_window->show_all();
    }else Dialogger::creating_already_shown(new_type_window);
}

void Wicher::SignalWindows::on_new_type_ok_button_clicked(){
    if(is_shown_create_type_window()){
        Glib::ustring name = new_type_name_entry->get_text();
        Glib::ustring id = new_type_id_entry->get_text();
        Glib::ustring comment = new_type_comment_entry->get_text();
        if(!name.empty() && !id.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_type(std::string(id), std::string(name), std::string(comment)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(new_type_window, root);
                }
            }else{
                Dialogger::response_error(new_type_window, error);
            }
            free(root);
            this->new_type_window->close();
        }else Dialogger::empty_entries(new_type_window);
    }
}

bool Wicher::SignalWindows::is_shown_create_type_window(){
    return this->new_type_window->is_visible();
}
