#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

bool signalwindows_is_shown_create_pz_window(){
    gboolean val = false;
    g_object_get(G_OBJECT(new_pz_window), "visible", &val);
    return val;
}

void signalwindows_show_create_pz_window(int wz_id){
    if(!signalwindows_is_shown_create_pz_window()){
        char buffer[10];
        sprintf(buffer, "%d", wz_id);
        gtk_entry_set_text(new_pz_wz_id_entry, buffer);
        gtk_entry_set_text(new_pz_person_entry, "");
        gtk_entry_set_text(new_pz_comment_entry, "");
        gtk_widget_show_all(GTK_WIDGET(new_pz_window));
    }else show_dialog_creating_already_shown(new_pz_window);
}

void signalwindows_on_new_pz_ok_button_clicked(){
    if(signalwindows_is_shown_create_pz_window()){
        const char * person = gtk_entry_get_text(new_pz_person_entry);
        int year, month, day;
        gtk_calendar_get_date(new_pz_date_entry, &year, &month, &day);
        const char * wz_id = gtk_entry_get_text(new_pz_wz_id_entry);
        const char * comment = gtk_entry_get_text(new_pz_comment_entry);
        if(person[0] && wz_id[0]){
            char buffer[32];
            sprintf(buffer, "%02d/%02d/%04d", day, month, year);
            int wz_id_i;
            sscanf(wz_id, "%d", &wz_id_i);
            const char * response = database_run(database_query_register_pz(wz_id_i, buffer, person, comment));
            json_error_t error;
            json_t * root = json_loads(response, 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || strcmp(json_string_value(resp), "ok")){
                    show_dialog_query_error(new_pz_window, root);
                }
            }else{
                show_dialog_response_error(new_pz_window, error);
            }
            free(root);
            if(!listsmanager_refresh_all()){
                show_dialog_refresh_error();
            }
            gtk_widget_hide(GTK_WIDGET(new_pz_window));
        }else show_dialog_empty_entries(new_pz_window);
    }
}
