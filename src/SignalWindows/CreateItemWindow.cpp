#include "SignalWindows.h"

void Wicher::SignalWindows::show_create_item_window(){
    if(!is_shown_create_item_window()){
        int pagenum = state_notepad->get_current_page();
        Gtk::Widget * child = state_notepad->get_nth_page(pagenum);
        Glib::ustring label = state_notepad->get_tab_label_text(*child);
        Glib::ustring id;
        Gtk::TreeModel::Children children = this->type_list->children();
        Gtk::TreeModel::Children::iterator iter = children.begin();
        while(iter != children.end()){
            Gtk::TreeModel::Row row = *iter;
            Glib::ustring rlabel = row[type_columns.name];
            if(label == rlabel){
                id = row[type_columns.id];
                break;
            }
            ++iter;
        }
        new_item_type_name_entry->set_text(label);
        new_item_type_entry->set_text(id);
        new_item_comment_entry->set_text("");
        this->new_item_window->show_all();
    }else Dialogger::creating_already_shown(new_item_window);
}

void Wicher::SignalWindows::on_new_item_ok_button_clicked(){
    if(is_shown_create_item_window()){
        Glib::ustring type = new_item_type_entry->get_text();
        Glib::ustring comment = new_item_comment_entry->get_text();
        if(!type.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item(std::string(type), std::string(comment)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(new_item_window, root);
                }
            }else{
                Dialogger::response_error(new_item_window, error);
            }
            free(root);
            this->new_item_window->close();
        }else Dialogger::empty_entries(new_item_window);
    }
}

bool Wicher::SignalWindows::is_shown_create_item_window(){
    return this->new_item_window->is_visible();
}
