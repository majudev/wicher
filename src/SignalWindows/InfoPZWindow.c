#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
//#include "PDF.h"

bool signalwindows_is_shown_info_pz_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(info_pz_window), "visible", &val);
    return val;
}

void signalwindows_show_info_pz_window_h(GtkTreeIter * iter){
    if(!signalwindows_is_shown_info_pz_window()){
        gint id;
        gint wz_id;
        gchararray person;
        gchararray date;
        gchararray comment;
        gtk_tree_model_get(GTK_TREE_MODEL(pz_list), iter,
                           PZ_COLUMNS_ID, &id,
                           PZ_COLUMNS_WZ_ID, &wz_id,
                           PZ_COLUMNS_PERSON, &person,
                           PZ_COLUMNS_DATE, &date,
                           PZ_COLUMNS_COMMENT, &comment, -1);
        char buffer[10];
        sprintf(buffer, "%d", id);
        gtk_entry_set_text(info_pz_id_entry, buffer);
        sprintf(buffer, "%d", wz_id);
        gtk_entry_set_text(info_pz_wz_id_entry, buffer);
        gtk_entry_set_text(info_pz_date_entry, date);
        gtk_entry_set_text(info_pz_person_entry, person);
        gtk_entry_set_text(info_pz_comment_entry, comment);

        gtk_list_store_clear(info_pz_items_list);
        json_error_t error;
        json_t * root = json_loads(database_run(database_query_get_wz_items(wz_id)), 0, &error);
        if(!root){
            show_dialog_response_error(info_pz_window, error);
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
                                    gtk_list_store_append(info_pz_items_list, &iter2);
                                    gtk_list_store_set (info_pz_items_list, &iter2,
                                                        ITEMS_LIST_COLUMNS_ID, item_id,
                                                        ITEMS_LIST_COLUMNS_TYPE, item_type,
                                                        ITEMS_LIST_COLUMNS_TYPE_NAME, type_name, -1);
                                    break;
                                }
                            }
                            ++x;
                        }
                    }
                }else show_dialog_query_error(info_pz_window, root);
            }
            free(root);
        }
 
        gtk_widget_show_all(GTK_WIDGET(info_pz_window));
    }else show_dialog_creating_already_shown(info_pz_window);
}

void signalwindows_show_info_pz_window(GtkTreeView * view, GtkTreePath * path, GtkTreeViewColumn * column, gpointer user_data){
    if(!signalwindows_is_shown_info_pz_window()){
        GtkTreeModel * list = gtk_tree_view_get_model(view);
        GtkTreeIter iter;
        bool res = gtk_tree_model_get_iter(list, &iter, path);
        if(res) signalwindows_show_info_pz_window_h(&iter);
    }else show_dialog_creating_already_shown(info_pz_window);
}

void signalwindows_on_info_pz_ok_button_clicked(){
    /*if(!Wicher::Config::getSingleton().get_unsafe_mode()){
        this->info_pz_window->close();
        return;
    }*/
    if(signalwindows_is_shown_info_pz_window()){
        const char * id = gtk_entry_get_text(info_pz_id_entry);
        const char * wz_id = gtk_entry_get_text(info_pz_wz_id_entry);
        const char * person = gtk_entry_get_text(info_pz_person_entry);
        const char * date = gtk_entry_get_text(info_pz_date_entry);
        const char * comment = gtk_entry_get_text(info_pz_comment_entry);
        if(id[0]){
            //std::string response;
            //if(Wicher::Config::getSingleton().get_unsafe_mode()) response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_pz(Toolkit::strtoi(id), date, person, true, comment));
            //else response = Wicher::Database::getSingleton().run(Wicher::Database::Query::change_pz(Toolkit::strtoi(id), std::string(), std::string(), true, comment));
            int id_i;
            sscanf(id, "%d", &id_i);
            char * response = database_run(database_query_change_pz(id_i, date, person, true, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_pz_window, root);
                }
            }else{
                show_dialog_response_error(info_pz_window, error);
            }
            free(root);
            if(!listsmanager_refresh_all()){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_pz_window));
        }else show_dialog_empty_entries(new_pz_window);
    }
}

void signalwindows_on_info_pz_print_button_clicked(){
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
            Glib::ustring id = info_pz_id_entry->get_text();
            Glib::ustring wz_id = info_pz_wz_id_entry->get_text();
            Glib::ustring person = info_pz_person_entry->get_text();
            Glib::ustring date = info_pz_date_entry->get_text();
            Glib::ustring comment = info_pz_comment_entry->get_text();
            
            Wicher::PDF::EntryGen gen;
            Gtk::TreeModel::Children children = this->info_wz_items_list->children();
            for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter){
                Gtk::TreeModel::Row row = *iter;
                int id = row[wz_items_list_columns.id];
                Glib::ustring type = row[wz_items_list_columns.type];
                Glib::ustring name = row[wz_items_list_columns.type_name];
                gen.append(id, name, type);
            }
            
            if(PDF::generate_pz(dialog.get_filename(), id, wz_id, "Nobody at all", person, date, false, gen.get_entries())) Dialogger::pdf_ok(this->info_pz_window, dialog.get_filename());
            else Dialogger::pdf_error(this->info_pz_window, dialog.get_filename());
    }
    this->info_pz_window->close();*/
    show_dialog_info(info_pz_window, "Ta funkcja nie jest jeszcze aktywna!", "Pracujemy nad tym.");
}
