#include "SignalWindows.h"

void Wicher::SignalWindows::show_create_wz_window(){
    if(!is_shown_create_wz_window()){
        //new_wz_name_entry->set_text("");
        //new_wz_id_entry->set_text("");
        //new_wz_comment_entry->set_text("");
        this->new_wz_window->show_all();
    }else Dialogger::creating_already_shown(new_wz_window);
}

void Wicher::SignalWindows::on_new_wz_ok_button_clicked(){
    if(is_shown_create_wz_window()){
        Glib::ustring person = new_wz_person_entry->get_text();
        Glib::Date date;
        new_wz_date_entry->get_date(date);
        Glib::ustring comment = new_wz_comment_entry->get_text();
        if(!person.empty()){
            std::vector<int> item_ids;
            std::vector<std::string> item_types;

            int x = 1;
            while(x != state_notepad->get_n_pages()){
                Gtk::Widget * widget_ptr = this->state_notepad->get_nth_page(x);
                Gtk::Box * box = static_cast<Gtk::Box *>(widget_ptr);
                Gtk::Widget * tree_widget = box->get_children()[0];
                if(Gtk::TreeView * view_ptr = dynamic_cast<Gtk::TreeView*>(tree_widget)){
                    Glib::RefPtr<Gtk::ListStore> list_ptr = Glib::RefPtr<Gtk::ListStore>::cast_static(view_ptr->get_model());
                    Gtk::TreeModel::Children children = list_ptr->children();
                    Gtk::TreeModel::Children::iterator iterc = children.begin();
                    while(iterc != children.end()){
                        Gtk::TreeModel::Row row = *iterc;
                        int id = row[entry_columns.id];
                        Glib::ustring type = row[entry_columns.type];
                        bool to_wz = row[entry_columns.checkbox];
                        if(to_wz){
                            item_ids.push_back(id);
                            item_types.push_back(type);
                        }
                        ++iterc;
                    }
                }
                ++x;
            }

            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_wz(date.format_string("%d/%m/%Y"), person, comment, item_ids, item_types));
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
            this->new_wz_window->close();
        }else Dialogger::empty_entries(new_wz_window);
    }
}

bool Wicher::SignalWindows::is_shown_create_wz_window(){
    return this->new_wz_window->is_visible();
}
