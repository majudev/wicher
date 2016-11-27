#include "SignalWindows.h"

void Wicher::SignalWindows::show_info_type_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
    if(!is_shown_info_type_window()){
        Gtk::TreeView * view = column->get_tree_view();
        Gtk::TreeModel::iterator iter = view->get_model()->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            Glib::ustring id = row[type_columns.id];
            Glib::ustring name = row[type_columns.name];
            int available = row[type_columns.available];
            int unavailable = row[type_columns.unavailable];
            int total = row[type_columns.total];
            Glib::ustring comment = row[type_columns.comment];
            this->info_type_id_entry->set_text(id);
            this->info_type_name_entry->set_text(name);
            this->info_type_available_entry->set_text(Toolkit::itostr(available));
            this->info_type_unavailable_entry->set_text(Toolkit::itostr(unavailable));
            this->info_type_total_entry->set_text(Toolkit::itostr(total));
            this->info_type_comment_entry->set_text(comment);
            this->info_type_window->show_all();
        }
    }else Dialogger::creating_already_shown(info_type_window);
}

void Wicher::SignalWindows::on_info_type_close_button_clicked(){
    if(is_shown_info_type_window()){
        Glib::ustring id = info_type_id_entry->get_text();
        Glib::ustring name = info_type_name_entry->get_text();
        Glib::ustring comment = info_type_comment_entry->get_text();
        if(!id.empty() && !name.empty() && !comment.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_type(std::string(id), std::string(name), true, std::string(comment)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(info_type_window, root);
                }
            }else{
                Dialogger::response_error(info_type_window, error);
            }
            free(root);
            this->info_type_window->close();
        }else Dialogger::empty_entries(new_item_window);
    }
}

void Wicher::SignalWindows::on_info_type_delete_button_clicked(){
    if(is_shown_info_type_window()){
        Glib::ustring id = info_type_id_entry->get_text();
        if(!id.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_type(std::string(id)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(info_type_window, root);
                }
            }else{
                Dialogger::response_error(info_type_window, error);
            }
            free(root);
            this->info_type_window->close();
        }else Dialogger::empty_entries(new_item_window);
    }
}

void Wicher::SignalWindows::on_info_type_add_button_clicked(){
    this->show_add_items_window(this->info_type_name_entry->get_text(), this->info_type_id_entry->get_text());
}

bool Wicher::SignalWindows::is_shown_info_type_window(){
    return this->info_type_window->is_visible();
}
