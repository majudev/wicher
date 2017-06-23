#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_info_item_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(info_item_window), "visible", &val);
    return val;
}

void signalwindows_show_info_item_window(GtkTreeView * view, GtkTreePath * path, GtkTreeViewColumn * column, gpointer user_data){
    if(!signalwindows_is_shown_info_item_window()){
        GtkTreeModel * list = gtk_tree_view_get_model(view);
        GtkTreeIter iter;
        bool res = gtk_tree_model_get_iter(list, &iter, path);
        if(res){
            gint id;
            const char * comment;
            gtk_tree_model_get (list, &iter,
                                ENTRY_COLUMNS_ID, &id,
                                ENTRY_COLUMNS_COMMENT, &comment, -1);

            int pagenum = gtk_notebook_get_current_page(state_notepad);
            
            const char * label = gtk_notebook_get_tab_label_text(state_notepad, gtk_notebook_get_nth_page(state_notepad, pagenum));
            
            char * type;
            GtkTreeIter iter2;
            bool valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(type_list), &iter2);
            while(valid){
                char * rlabel;
                char * rid;
                gtk_tree_model_get (GTK_TREE_MODEL(type_list), &iter2,
                                    TYPE_COLUMNS_ID, &rid,
                                    TYPE_COLUMNS_NAME, &rlabel, -1);
                if(!strcmp(label, rlabel)){
                    type = rid;
                    break;
                }
                valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(type_list), &iter2);
            }
            char buffer[10];
            sprintf(buffer, "%d", id);
            gtk_entry_set_text(info_item_id_entry, buffer);
            gtk_entry_set_text(info_item_type_name_entry, label);
            gtk_entry_set_text(info_item_type_entry, type);
            gtk_entry_set_text(info_item_comment_entry, comment);
            gtk_widget_show_all(GTK_WIDGET(info_item_window));
        }
    }else show_dialog_creating_already_shown(info_item_window);
}

void signalwindows_on_info_item_close_button_clicked(){
    if(signalwindows_is_shown_info_item_window()){
        const char * id = gtk_entry_get_text(info_item_id_entry);
        const char * type = gtk_entry_get_text(info_item_type_entry);
        const char * comment = gtk_entry_get_text(info_item_comment_entry);
        if(id[0] && type[0]){
            int id_i;
            sscanf(id, "%d", &id_i);
            char * response = database_run(database_query_change_item(id_i, type, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_item_window, root);
                }
            }else{
                show_dialog_response_error(info_item_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_item_window));
        }else show_dialog_empty_entries(info_item_window);
    }
}

void signalwindows_on_info_item_delete_button_clicked(){
    if(signalwindows_is_shown_info_item_window()){
        const char * id = gtk_entry_get_text(info_item_id_entry);
        const char * type = gtk_entry_get_text(info_item_type_entry);
        if(id[0] && type[0]){
            int id_i;
            sscanf(id, "%d", &id_i);
            char * response = database_run(database_query_drop_item(id_i, type));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_item_window, root);
                }
            }else{
                show_dialog_response_error(info_item_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_item_window));
        }else show_dialog_empty_entries(info_item_window);
    }
}

void signalwindows_on_info_item_copy_button_clicked(){
    if(signalwindows_is_shown_info_item_window()){
        const char * type = gtk_entry_get_text(info_item_type_entry);
        const char * comment = gtk_entry_get_text(info_item_comment_entry);
        if(type[0]){
            char * response = database_run(database_query_register_item(type, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_item_window, root);
                }
            }else{
                show_dialog_response_error(info_item_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_item_window));
        }else show_dialog_empty_entries(info_item_window);
    }
}
