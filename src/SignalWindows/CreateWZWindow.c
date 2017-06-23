#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "kvec.h"

bool signalwindows_is_shown_create_wz_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(new_wz_window), "visible", &val);
    return val;
}

void signalwindows_show_create_wz_window(){
    if(!signalwindows_is_shown_create_wz_window()){
        gtk_entry_set_text(new_wz_person_entry, "");
        gtk_entry_set_text(new_wz_comment_entry, "");
        gtk_widget_show_all(GTK_WIDGET(new_wz_window));
    }else show_dialog_creating_already_shown(new_wz_window);
}

void signalwindows_on_new_wz_ok_button_clicked(){
    if(signalwindows_is_shown_create_wz_window()){
        const char * person = gtk_entry_get_text(new_wz_person_entry);
        int year, month, day;
        gtk_calendar_get_date(new_wz_date_entry, &year, &month, &day);
        const char * comment = gtk_entry_get_text(new_wz_comment_entry);
        if(person[0]){
            kvec_t(int) item_ids;
            kvec_t(char*) item_types;
            kv_init(item_ids);
            kv_init(item_types);

            int x = 1;
            while(x != gtk_notebook_get_n_pages(state_notepad)){
                GtkWidget * box = gtk_notebook_get_nth_page(state_notepad, x);
                GList * box_children = gtk_container_get_children(GTK_CONTAINER(box));
                GtkScrolledWindow * swin_widget = GTK_SCROLLED_WINDOW(g_list_nth_data(box_children, 0));
                g_list_free(box_children);
                GList * swin_children = gtk_container_get_children(GTK_CONTAINER(swin_widget));
                GtkTreeView * tree_widget = GTK_TREE_VIEW(g_list_nth_data(swin_children, 0));
                g_list_free(swin_children);
                GtkListStore * list = GTK_LIST_STORE(gtk_tree_view_get_model(tree_widget));
                
                GtkTreeIter iter;
                bool valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(list), &iter);
                while(valid){
                    gint id;
                    gchar * type;
                    gboolean to_wz;
                    gtk_tree_model_get (GTK_TREE_MODEL(list), &iter,
                                        ENTRY_COLUMNS_ID, &id,
                                        ENTRY_COLUMNS_TYPE, &type,
                                        ENTRY_COLUMNS_CHECKBOX, &to_wz, -1);
                    if(to_wz){
                        kv_push(int, item_ids, id);
                        kv_push(char *, item_types, type);
                    }
                    valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(list), &iter);
                }
                ++x;
            }

            char buffer[32];
            sprintf(buffer, "%02d/%02d/%04d", day, month, year);
            char * response = database_run(database_query_register_wz(buffer, person, comment, kv_size(item_ids), item_ids.a, item_types.a));
            kv_destroy(item_ids);
            kv_destroy(item_types);
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(new_item_window, root);
                }
            }else{
                show_dialog_response_error(new_item_window, error);
            }
            free(root);
            if(!listsmanager_refresh_all()){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(new_wz_window));
        }else show_dialog_empty_entries(new_wz_window);
    }
}
