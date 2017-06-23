#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_create_type_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(new_type_window), "visible", &val);
    return val;
}

void signalwindows_show_create_type_window(){
    if(!signalwindows_is_shown_create_type_window()){
        gtk_entry_set_text(new_type_name_entry, "");
        gtk_entry_set_text(new_type_id_entry, "");
        gtk_entry_set_text(new_type_comment_entry, "");
        gtk_widget_show_all(GTK_WIDGET(new_type_window));
    }else show_dialog_creating_already_shown(new_type_window);
}

void signalwindows_on_new_type_ok_button_clicked(){
    wicherlog("running on_new_type_ok_button_clicked");
    if(signalwindows_is_shown_create_type_window()){
        wicherlog("running on_new_type_ok_button_clicked - 2");
        const char * name = gtk_entry_get_text(new_type_name_entry);
        const char * id = gtk_entry_get_text(new_type_id_entry);
        const char * comment = gtk_entry_get_text(new_type_comment_entry);
        wicherlog("running on_new_type_ok_button_clicked - 3");
        if(name[0] && id[0]){
            char * response = database_run(database_query_register_type(id, name, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(new_type_window, root);
                }
            }else{
                show_dialog_response_error(new_type_window, error);
            }
            free(root);
            if(!(listsmanager_refresh_types() && listsmanager_refresh_lists() && listsmanager_refresh_history())){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(new_type_window));
        }else show_dialog_empty_entries(new_type_window);
    }
}
