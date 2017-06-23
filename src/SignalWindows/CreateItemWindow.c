#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_create_item_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(new_item_window), "visible", &val);
    return val;
}

void signalwindows_show_create_item_window(){
    if(!signalwindows_is_shown_create_item_window()){
        int pagenum = gtk_notebook_get_current_page(state_notepad);
        GtkWidget * child = gtk_notebook_get_nth_page(state_notepad, pagenum);
        const char * label = gtk_notebook_get_tab_label_text(state_notepad, child);
        const char * id;
        GtkTreeIter iter;
        bool valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(type_list), &iter);
        while(valid){
            const char * rlabel;
            gtk_tree_model_get (GTK_TREE_MODEL(type_list), &iter,
                                TYPE_COLUMNS_NAME, &rlabel,
                                TYPE_COLUMNS_ID, &id, -1);
            if(!strcmp(label, rlabel)) break;
            valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(type_list), &iter);
        }
        gtk_entry_set_text(new_item_type_name_entry, label);
        gtk_entry_set_text(new_item_type_entry, id);
        gtk_entry_set_text(new_item_comment_entry, "");
        gtk_widget_show_all(GTK_WIDGET(new_item_window));
    }else show_dialog_creating_already_shown(new_item_window);
}

void signalwindows_on_new_item_ok_button_clicked(){
    if(signalwindows_is_shown_create_item_window()){
        const char * type = gtk_entry_get_text(new_item_type_entry);
        const char * comment = gtk_entry_get_text(new_item_comment_entry);
        if(type[0]){
            char * response = database_run(database_query_register_item(type, comment));
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
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(new_item_window));
        }else show_dialog_empty_entries(new_item_window);
    }
}
