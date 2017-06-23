#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_info_type_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(info_type_window), "visible", &val);
    return val;
}

void signalwindows_show_info_type_window(GtkTreeView * view, GtkTreePath * path, GtkTreeViewColumn * column, gpointer user_data){
    if(!signalwindows_is_shown_info_type_window()){
        GtkTreeModel * list = gtk_tree_view_get_model(view);
        GtkTreeIter iter;
        bool res = gtk_tree_model_get_iter(list, &iter, path);
        if(res){
            const char * id;
            const char * name;
            gint available;
            gint unavailable;
            gint total;
            const char * comment;
            gtk_tree_model_get(list, &iter,
                               TYPE_COLUMNS_ID, &id,
                               TYPE_COLUMNS_NAME, &name,
                               TYPE_COLUMNS_AVAILABLE, &available,
                               TYPE_COLUMNS_UNAVAILABLE, &unavailable,
                               TYPE_COLUMNS_TOTAL, &total,
                               TYPE_COLUMNS_COMMENT, &comment, -1);
            char buffer[10];
            gtk_entry_set_text(info_type_id_entry, id);
            gtk_entry_set_text(info_type_name_entry, name);
            sprintf(buffer, "%d", available);
            gtk_entry_set_text(info_type_available_entry, buffer);
            sprintf(buffer, "%d", unavailable);
            gtk_entry_set_text(info_type_unavailable_entry, buffer);
            sprintf(buffer, "%d", total);
            gtk_entry_set_text(info_type_total_entry, buffer);
            gtk_entry_set_text(info_type_comment_entry, comment);
            gtk_widget_show_all(GTK_WIDGET(info_type_window));
        }
    }else show_dialog_creating_already_shown(info_type_window);
}

void signalwindows_on_info_type_close_button_clicked(){
    if(signalwindows_is_shown_info_type_window()){
        const char * id = gtk_entry_get_text(info_type_id_entry);
        const char * name = gtk_entry_get_text(info_type_name_entry);
        const char * comment = gtk_entry_get_text(info_type_comment_entry);
        if(id[0] && name[0]){
            char * response = database_run(database_query_change_type(id, name, comment[0], comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_type_window, root);
                }
            }else{
                show_dialog_response_error(info_type_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_type_window));
        }else show_dialog_empty_entries(info_type_window);
    }
}

void signalwindows_on_info_type_delete_button_clicked(){
    if(signalwindows_is_shown_info_type_window()){
        const char * id = gtk_entry_get_text(info_type_id_entry);
        if(id[0]){
            char * response = database_run(database_query_drop_type(id));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(info_type_window, root);
                }
            }else{
                show_dialog_response_error(info_type_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(info_type_window));
        }else show_dialog_empty_entries(info_type_window);
    }
}

void signalwindows_on_info_type_add_button_clicked(){
    signalwindows_show_add_items_window(gtk_entry_get_text(info_type_name_entry), gtk_entry_get_text(info_type_id_entry));
}
