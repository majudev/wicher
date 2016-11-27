#include "ListsManager.h"

bool Wicher::ListsManager::refresh_types(){
    this->type_list->clear();
    this->type_map.clear();

    json_error_t error;
    json_t * root = json_loads(Database::getSingleton().run(Database::Query::get_types()).c_str(), 0, &error);
    if(!root){
        Toolkit::log(std::string("JSON error when refreshing types:") + std::string(error.text));
        Toolkit::log(std::string("\tSource:") + std::string(error.source));
        Toolkit::log(std::string("\tLine:") + Toolkit::itostr(error.line));
        Toolkit::log(std::string("\tColumn:") + Toolkit::itostr(error.column));
        Toolkit::log(std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position));
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            std::string response(response_str);
            if(response == std::string("ok")){
                json_t * array = json_object_get(root, "types");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        const char * id_str = json_string_value(json_object_get(obj, "id"));
                        const char * name_str = json_string_value(json_object_get(obj, "name"));
                        int unavailable = json_integer_value(json_object_get(obj, "unavailable"));
                        int total = json_integer_value(json_object_get(obj, "total"));
                        const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                        if(id_str && name_str && comment_str){
                            std::string id(id_str);
                            std::string name(name_str);
                            std::string comment(comment_str);

                            Gtk::TreeModel::iterator iter = this->type_list->append();
                            Gtk::TreeModel::Row row = *iter;
                            row[type_columns.id] = id.c_str();
                            row[type_columns.name] = name.c_str();
                            row[type_columns.available] = total-unavailable;
                            row[type_columns.unavailable] = unavailable;
                            row[type_columns.total] = total;
                            row[type_columns.comment] = comment.c_str();
                            type_map[row[type_columns.name]] = id;
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else Toolkit::log(std::string("Error when refreshing types. Server's response: ") + response);
        }
    }

    free(root);
    return false;
}

bool Wicher::ListsManager::refresh_lists(){
    int pages = this->state_notepad->get_n_pages();
    int x = 1;
    while(x != pages){
        this->state_notepad->remove_page(1);
        ++x;
    }

    Gtk::TreeModel::Children children = this->type_list->children();
    Gtk::TreeModel::Children::iterator iter = children.begin();
    while(iter != children.end()){
        Gtk::TreeModel::Row row = *iter;
        Glib::ustring type_id = row[type_columns.id];
        Glib::ustring name = row[type_columns.name];
        Glib::RefPtr<Gtk::ListStore> list = Gtk::ListStore::create(entry_columns);

        json_error_t error;
        json_t * root = json_loads(Database::getSingleton().run(Database::Query::get_items(std::string(type_id))).c_str(), 0, &error);
        if(!root){
            Toolkit::log(std::string("JSON error when refreshing ") + std::string(type_id) + std::string(" items:") + std::string(error.text));
            Toolkit::log(std::string("\tSource:") + std::string(error.source));
            Toolkit::log(std::string("\tLine:") + Toolkit::itostr(error.line));
            Toolkit::log(std::string("\tColumn:") + Toolkit::itostr(error.column));
            Toolkit::log(std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position));
        }else{
            const char * response_str = json_string_value(json_object_get(root, "response"));
            if(response_str){
                std::string response(response_str);
                if(response == std::string("ok")){
                    json_t * array = json_object_get(root, "items");
                    if(array){
                        size_t size = json_array_size(array);
                        size_t x = 0;
                        while(x != size){
                            json_t * obj = json_array_get(array, x);
                            int id = json_integer_value(json_object_get(obj, "id"));
                            bool available = json_boolean_value(json_object_get(obj, "available"));
                            int wz_id = json_integer_value(json_object_get(obj, "wz_id"));
                            const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                            if(comment_str){
                                std::string comment(comment_str);

                                Gtk::TreeModel::iterator iter = list->append();
                                Gtk::TreeModel::Row row = *iter;
                                row[entry_columns.id] = id;
                                row[entry_columns.available] = available;
                                if(available){
                                    row[entry_columns.wz_id] = "";
                                }else{
                                    row[entry_columns.wz_id] = Toolkit::itostr(wz_id).c_str();
                                }
                                row[entry_columns.comment] = comment.c_str();
                                row[entry_columns.checkbox] = false;
                                row[entry_columns.type] = this->type_map[name];
                            }
                            ++x;
                        }
                    }
                }else Toolkit::log(std::string("Error when refreshing ") + std::string(type_id) + std::string(" items. Server's response:") + response);
            }
        }
        free(root);

        Gtk::TreeView * view = Gtk::manage(new Gtk::TreeView());
        Gtk::Label * label = Gtk::manage(new Gtk::Label(name));
        view->set_model(list);
        view->append_column("ID", entry_columns.id);
        view->append_column("Dostępność", entry_columns.available);
        view->append_column("ID Wydania", entry_columns.wz_id);
        view->append_column("Komentarz", entry_columns.comment);
        view->append_column("Do WZ", entry_columns.checkbox);

        //view->get_column(0)->set_min_width(100);
        view->get_column(0)->set_expand(true);
        //view->get_column(1)->set_expand(true);
        view->get_column(2)->set_expand(true);
        view->get_column(3)->set_expand(true);
        view->get_column(4)->set_expand(false);

        Gtk::CellRendererText * renderer = static_cast<Gtk::CellRendererText*>(view->get_column(3)->get_first_cell());
        renderer->property_editable() = true;
        renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_item_comment_edited) );

        Gtk::CellRendererToggle * trenderer = static_cast<Gtk::CellRendererToggle*>(view->get_column(4)->get_first_cell());
        trenderer->property_activatable() = true;
        trenderer->signal_toggled().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_item_checkbox_toggled) );

        view->signal_row_activated().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_info_item_window) );

        view->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

        Gtk::Box * box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        Gtk::Button * button = Gtk::manage(new Gtk::Button("Dodaj"));
        button->signal_clicked().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_create_item_window) );
        box->pack_start(*view, true, true, 0);
        box->pack_start(*button, false, false, 0);

        this->state_notepad->append_page(*box, *label);

        ++iter;
    }
    this->state_notepad->show_all();
    return true;
}

void Wicher::ListsManager::on_type_name_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    if(new_text.empty()) return;
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->type_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        Glib::ustring id = row[type_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_type(std::string(id), std::string(new_text), false, std::string()));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!json_is_string(r) || std::string(json_string_value(r)) != std::string("ok")){
            Wicher::Dialogger::update_error();
        }else{
            row[type_columns.name] = new_text;
            if(!this->refresh_lists()) Wicher::Dialogger::refresh_error();
        }
        free(root);
    }
}

void Wicher::ListsManager::on_type_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    Gtk::TreePath path(path_string);
    Gtk::TreeModel::iterator iter = this->type_list->get_iter(path);
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        Glib::ustring id = row[type_columns.id];
        std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_type(std::string(id), "", true, std::string(new_text)));
        json_error_t error;
        json_t * root = json_loads(response.c_str(), 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!json_is_string(r) || json_string_value(r) != std::string("ok")){
            Wicher::Dialogger::update_error();
        }else{
            row[type_columns.comment] = new_text;
            if(!this->refresh_lists()) Wicher::Dialogger::refresh_error();
        }
        free(root);
    }
}

void Wicher::ListsManager::on_item_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text){
    Gtk::TreePath path(path_string);
    Glib::ustring label = this->state_notepad->get_tab_label_text(*this->state_notepad->get_nth_page(this->state_notepad->get_current_page()));
    Gtk::Widget * widget_ptr = this->state_notepad->get_nth_page(this->state_notepad->get_current_page());
    Gtk::Box * box = static_cast<Gtk::Box *>(widget_ptr);
    Gtk::Widget * tree_widget = box->get_children()[0];
    if(Gtk::TreeView * view_ptr = dynamic_cast<Gtk::TreeView*>(tree_widget)){
        Glib::RefPtr<Gtk::ListStore> list_ptr = Glib::RefPtr<Gtk::ListStore>::cast_static(view_ptr->get_model());
        Gtk::TreeModel::iterator iter = list_ptr->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            int id = row[entry_columns.id];
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_item(id, this->type_map[label], std::string(new_text)));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * r = json_object_get(root, "response");
            if(!json_is_string(r) || std::string(json_string_value(r)) != std::string("ok")){
                Wicher::Dialogger::update_error();
            }else{
                row[entry_columns.comment] = new_text;
            }
            free(root);
        }
    }
}

void Wicher::ListsManager::on_item_checkbox_toggled(const Glib::ustring& path){
    Glib::ustring label = this->state_notepad->get_tab_label_text(*this->state_notepad->get_nth_page(this->state_notepad->get_current_page()));
    Gtk::Widget * widget_ptr = this->state_notepad->get_nth_page(this->state_notepad->get_current_page());
    Gtk::Box * box = static_cast<Gtk::Box *>(widget_ptr);
    Gtk::Widget * tree_widget = box->get_children()[0];
    if(Gtk::TreeView * view_ptr = dynamic_cast<Gtk::TreeView*>(tree_widget)){
        Glib::RefPtr<Gtk::ListStore> list_ptr = Glib::RefPtr<Gtk::ListStore>::cast_static(view_ptr->get_model());
        Gtk::TreeModel::iterator iter = list_ptr->get_iter(path);
        if(iter){
            Gtk::TreeModel::Row row = *iter;
            if(row[entry_columns.available]){
                row[entry_columns.checkbox] = !row[entry_columns.checkbox];
            }
        }
    }
}
