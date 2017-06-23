#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_add_items_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(add_items_window), "visible", &val);
    return val;
}

void signalwindows_show_add_items_window(const char * type_name, const char * type){
    if(!signalwindows_is_shown_add_items_window()){
        gtk_entry_set_text(add_items_type_name_entry, type_name);
        gtk_entry_set_text(add_items_type_entry, type);
        gtk_adjustment_set_value(gtk_spin_button_get_adjustment(add_items_count_spin), 10.0);
        gtk_entry_set_text(add_items_comment_entry, "");
        gtk_widget_show_all(GTK_WIDGET(add_items_window));
    }else show_dialog_creating_already_shown(add_items_window);
}

void signalwindows_on_add_items_ok_button_clicked(){
    if(signalwindows_is_shown_add_items_window()){
        const char * type = gtk_entry_get_text(add_items_type_entry);
        const char * comment = gtk_entry_get_text(add_items_comment_entry);
        if(type[0]){
            int x = 0;
            int max = gtk_adjustment_get_value(gtk_spin_button_get_adjustment(add_items_count_spin));
            while(x != max){
                char * response = database_run(database_query_register_item(type, comment));
                json_error_t error;
                json_t * root = json_loads(response, 0, &error);
                json_t * resp = json_object_get(root, "response");
                if(root){
                    if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                        show_dialog_query_error(add_items_window, root);
                    }
                }else{
                    show_dialog_response_error(add_items_window, error);
                }
                free(root);
                ++x;
            }
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(add_items_window));
        }else show_dialog_empty_entries(add_items_window);
    }
}
