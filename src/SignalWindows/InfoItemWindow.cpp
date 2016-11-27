#include "SignalWindows.h"

void Wicher::SignalWindows::show_info_item_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
    if(!is_shown_info_item_window()){
        Gtk::TreeView * view = column->get_tree_view();
        Gtk::TreeModel::iterator iter = view->get_model()->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            int id = row[entry_columns.id];
            Glib::ustring comment = row[entry_columns.comment];

            int pagenum = state_notepad->get_current_page();
            Gtk::Widget * child = state_notepad->get_nth_page(pagenum);
            Glib::ustring label = state_notepad->get_tab_label_text(*child);
            Glib::ustring type;
            Gtk::TreeModel::Children children = this->type_list->children();
            Gtk::TreeModel::iterator iter0 = children.begin();
            while(iter0 != children.end()){
                Gtk::TreeModel::Row row0 = *iter0;
                Glib::ustring rlabel = row0[type_columns.name];
                if(label == rlabel){
                    type = row0[type_columns.id];
                    break;
                }
                ++iter0;
            }
            info_item_id_entry->set_text(Toolkit::itostr(id));
            info_item_type_name_entry->set_text(label);
            info_item_type_entry->set_text(type);
            info_item_comment_entry->set_text(comment);
            this->info_item_window->show_all();
        }
    }else Dialogger::creating_already_shown(info_item_window);
}

void Wicher::SignalWindows::on_info_item_close_button_clicked(){
    if(is_shown_info_item_window()){
        Glib::ustring id = info_item_id_entry->get_text();
        Glib::ustring type = info_item_type_entry->get_text();
        Glib::ustring comment = info_item_comment_entry->get_text();
        if(!id.empty() && !type.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_item(Toolkit::strtoi(std::string(id)), std::string(type), std::string(comment)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(info_item_window, root);
                }
            }else{
                Dialogger::response_error(info_item_window, error);
            }
            free(root);
            this->info_item_window->close();
        }else Dialogger::empty_entries(info_item_window);
    }
}

void Wicher::SignalWindows::on_info_item_delete_button_clicked(){
    if(is_shown_info_item_window()){
        Glib::ustring id = info_item_id_entry->get_text();
        Glib::ustring type = info_item_type_entry->get_text();
        if(!id.empty() && !type.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_item(Toolkit::strtoi(std::string(id)), std::string(type)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(info_item_window, root);
                }
            }else{
                Dialogger::response_error(info_item_window, error);
            }
            free(root);
            this->info_item_window->close();
        }else Dialogger::empty_entries(info_item_window);
    }
}

void Wicher::SignalWindows::on_info_item_copy_button_clicked(){
    if(is_shown_info_item_window()){
        Glib::ustring type = info_item_type_entry->get_text();
        Glib::ustring comment = info_item_comment_entry->get_text();
        if(!type.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item(std::string(type), std::string(comment)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(info_item_window, root);
                }
            }else{
                Dialogger::response_error(info_item_window, error);
            }
            free(root);
            this->info_item_window->close();
        }else Dialogger::empty_entries(info_item_window);
    }
}

bool Wicher::SignalWindows::is_shown_info_item_window(){
    return this->info_item_window->is_visible();
}
