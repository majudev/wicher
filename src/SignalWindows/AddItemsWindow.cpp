#include "SignalWindows.h"

void Wicher::SignalWindows::show_add_items_window(Glib::ustring type_name, Glib::ustring type){
    if(!is_shown_add_items_window()){
        this->add_items_type_name_entry->set_text(type_name);
        this->add_items_type_entry->set_text(type);
        this->add_items_count_spin->get_adjustment()->set_value(10.0);
        this->add_items_comment_entry->set_text("");
        this->add_items_window->show_all();
    }else Dialogger::creating_already_shown(add_items_window);
}

void Wicher::SignalWindows::on_add_items_ok_button_clicked(){
    if(is_shown_add_items_window()){
        Glib::ustring type = add_items_type_entry->get_text();
        Glib::ustring comment = add_items_comment_entry->get_text();
        if(!type.empty()){
            int x = 0;
            int max = this->add_items_count_spin->get_adjustment()->get_value();
            while(x != max){
                std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item(std::string(type), std::string(comment)));
                json_error_t error;
                json_t * root = json_loads(response.c_str(), 0, &error);
                json_t * resp = json_object_get(root, "response");
                if(root){
                    if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                        Dialogger::query_error(add_items_window, root);
                    }
                }else{
                    Dialogger::response_error(add_items_window, error);
                }
                free(root);
                this->new_item_window->close();
                ++x;
            }
        }else Dialogger::empty_entries(add_items_window);
        this->add_items_window->close();
    }
}

bool Wicher::SignalWindows::is_shown_add_items_window(){
    return this->add_items_window->is_visible();
}
