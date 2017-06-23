#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
//#include "PDF.h"

bool signalwindows_is_shown_info_wz_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(info_wz_window), "visible", &val);
    return val;
}

void signalwindows_show_info_wz_window(GtkTreeView * view, GtkTreePath * path, GtkTreeViewColumn * column, gpointer user_data){
    if(!signalwindows_is_shown_info_wz_window()){
        GtkTreeModel * list = gtk_tree_view_get_model(view);
        GtkTreeIter iter;
        bool res = gtk_tree_model_get_iter(list, &iter, path);
        if(res){
            gint id;
            gchararray person;
            gchararray date;
            gchararray return_date;
            gchararray comment;
            gtk_tree_model_get(list, &iter,
                               WZ_COLUMNS_ID, &id,
                               WZ_COLUMNS_PERSON, &person,
                               WZ_COLUMNS_DATE, &date,
                               WZ_COLUMNS_RETURN_DATE, &return_date,
                               WZ_COLUMNS_COMMENT, &comment, -1);
            char buffer[10];
            sprintf(buffer, "%d", id);
            gtk_entry_set_text(info_wz_id_entry, buffer);
            gtk_entry_set_text(info_wz_date_entry, date);
            gtk_entry_set_text(info_wz_person_entry, person);
            gtk_entry_set_text(info_wz_comment_entry, comment);

            gtk_list_store_clear(info_wz_items_list);
            json_error_t error;
            json_t * root = json_loads(database_run(database_query_get_wz_items(id)), 0, &error);
            if(!root){
                show_dialog_response_error(info_wz_window, error);
            }else{
                const char * response_str = json_string_value(json_object_get(root, "response"));
                if(response_str){
                    if(!strcmp(response_str, "ok")){
                        json_t * array = json_object_get(root, "items");
                        if(array){
                            size_t size = json_array_size(array);
                            size_t x = 0;
                            while(x != size){
                                json_t * obj = json_array_get(array, x);
                                int item_id = json_integer_value(json_object_get(obj, "id"));
                                const char * item_type = json_string_value(json_object_get(obj, "type"));
                                json_t * items_array = json_object_get(root, "types");
                                for(unsigned int i = 0; i < json_array_size(items_array); ++i){
                                    json_t * item_obj = json_array_get(items_array, i);
                                    const char * type_id = json_string_value(json_object_get(item_obj, "id"));
                                    if(type_id && item_type && strcmp(type_id, item_type) == 0){
                                        const char * type_name = json_string_value(json_object_get(item_obj, "name"));
                                        GtkTreeIter iter2;
                                        gtk_list_store_append(info_wz_items_list, &iter2);
                                        gtk_list_store_set (info_wz_items_list, &iter2,
                                                            ITEMS_LIST_COLUMNS_ID, item_id,
                                                            ITEMS_LIST_COLUMNS_TYPE, item_type,
                                                            ITEMS_LIST_COLUMNS_TYPE_NAME, type_name, -1);
                                        break;
                                    }
                                }
                                ++x;
                            }
                        }
                    }else show_dialog_query_error(info_wz_window, root);
                }
                free(root);
            }

            gtk_widget_show_all(GTK_WIDGET(info_wz_window));

            int tmp;
            if(strlen(return_date) == 10 && return_date[2] == '/' && return_date[5] == '/' && sscanf(return_date, "%d/%d/%d", &tmp, &tmp, &tmp) != EOF){
                gtk_entry_set_text(info_wz_return_date_entry, return_date);
                gtk_widget_show_all(GTK_WIDGET(info_wz_return_date_box));
            }else{
                gtk_widget_hide(GTK_WIDGET(info_wz_return_date_box));
            }
        }
    }else show_dialog_creating_already_shown(info_wz_window);
}

void signalwindows_on_info_wz_ok_button_clicked(){
    /*if(!Wicher::Config::getSingleton().get_unsafe_mode()){
        this->info_wz_window->close();
        return;
    }*/
    if(signalwindows_is_shown_info_wz_window()){
        const char * id = gtk_entry_get_text(info_wz_id_entry);
        const char * person = gtk_entry_get_text(info_wz_person_entry);
        const char * date = gtk_entry_get_text(info_wz_date_entry);
        const char * comment = gtk_entry_get_text(info_wz_comment_entry);
        if(id[0]){
            //std::string response;
            //if(Wicher::Config::getSingleton().get_unsafe_mode()) response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_wz(Toolkit::strtoi(id), date, person, true, comment));
            //else response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_wz(Toolkit::strtoi(id), std::string(), std::string(), true, comment));
            int id_i;
            sscanf(id, "%d", &id_i);
            char * response = database_run(database_query_change_wz(id_i, date, person, true, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_wz_window, root);
                }
            }else{
                show_dialog_response_error(info_wz_window, error);
            }
            free(root);
            if(!listsmanager_refresh_all()){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_wz_window));
        }else show_dialog_empty_entries(info_wz_window);
    }
}

void signalwindows_on_info_wz_pz_button_clicked(){
    const char * id_str = gtk_entry_get_text(info_wz_id_entry);
    int id;
    sscanf(id_str, "%d", &id);
    gboolean val = false;
    g_object_get(G_OBJECT(info_wz_return_date_box), "visible", &val);
    if(val){
        GtkTreeIter iter;
        bool valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(pz_list), &iter);
        while(valid){
            int id_tmp;
            gtk_tree_model_get (GTK_TREE_MODEL(pz_list), &iter,
                                PZ_COLUMNS_ID, &id_tmp, -1);
            if(id == id_tmp){
                signalwindows_show_info_pz_window_h(&iter);
                break;
            }
            valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(pz_list), &iter);
        }
        gtk_widget_hide(GTK_WIDGET(info_wz_window));
    }else{
        signalwindows_show_create_pz_window(id);
        gtk_widget_hide(GTK_WIDGET(info_wz_window));
    }
}

void signalwindows_on_info_wz_print_button_clicked(){
    /*Gtk::FileChooserDialog dialog("Zapisz plik", Gtk::FILE_CHOOSER_ACTION_SAVE);
    //dialog.set_transient_for(*this);
    
    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
    filter->set_name("Plik PDF");
    filter->add_pattern("*.pdf");
    dialog.add_filter(filter);

    //Add response buttons the the dialog:
    dialog.add_button("_Anuluj", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Zapisz", Gtk::RESPONSE_OK);

    int result = dialog.run();

    switch(result){
        case(Gtk::RESPONSE_OK):
            Glib::ustring id = info_wz_id_entry->get_text();
            Glib::ustring person = info_wz_person_entry->get_text();
            Glib::ustring date = info_wz_date_entry->get_text();
            Glib::ustring comment = info_wz_comment_entry->get_text();
            
            Wicher::PDF::EntryGen gen;
            Gtk::TreeModel::Children children = this->info_wz_items_list->children();
            for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter){
                Gtk::TreeModel::Row row = *iter;
                int id = row[wz_items_list_columns.id];
                Glib::ustring type = row[wz_items_list_columns.type];
                Glib::ustring name = row[wz_items_list_columns.type_name];
                gen.append(id, name, type);
            }
            
            if(PDF::generate_wz(dialog.get_filename(), id, "Nobody at all", person, date, "Purpose", "", false, gen.get_entries())) Dialogger::pdf_ok(this->info_wz_window, dialog.get_filename());
            else Dialogger::pdf_error(this->info_wz_window, dialog.get_filename());
    }
    this->info_wz_window->close();*/
    show_dialog_info(info_pz_window, "Ta funkcja nie jest jeszcze aktywna!", "Pracujemy nad tym.");
}
