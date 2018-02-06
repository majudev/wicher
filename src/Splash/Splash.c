#include "ui.h"
#include "db.h"

GtkWindow * splash_window = NULL;
GtkEntry * splash_username_entry = NULL;
GtkEntry * splash_password_entry = NULL;
GtkButton * splash_connect_button = NULL;
GtkButton * splash_run_button = NULL;

void splash_on_connect(){
    const char * h_string = "majudev.net";
    int p_int = 63431;
    const char * un_string = gtk_entry_get_text(splash_username_entry);
    const char * ps_string = gtk_entry_get_text(splash_password_entry);
    if(un_string[0] && ps_string[0]){
        wicherlog("Setting login credentials:");
        wicherlog("\tHOST: %s", h_string);
        wicherlog("\tPORT: %d", p_int);
        wicherlog("\tUSERNAME: %s", un_string);
        wicherlog("\tPASSWORD: ****");
        wicherlog("Connecting...");
        if(database_connect(h_string, p_int)){
            wicherlog("OK.");
            wicherlog("Logging in...");
            if(database_login(un_string, ps_string)){
                wicherlog("OK.");
                gtk_widget_hide(GTK_WIDGET(splash_window));
                main_run();
            }else show_dialog_login_data_error(splash_window);
        }else show_dialog_connection_error(splash_window);
    }else show_dialog_login_data_error(splash_window);
}

void splash_on_run(){
    const char * h_string = "localhost";
    int p_int = 63431;
    const char * un_string = "null";
    const char * ps_string = "null";
    wicherlog("Setting login credentials:");
    wicherlog("\tHOST: %s", h_string);
    wicherlog("\tPORT: %d", p_int);
    wicherlog("\tUSERNAME: %s", un_string);
    wicherlog("\tPASSWORD: ****");
    wicherlog("Running local server...");
    if(splash_run_server()){
        wicherlog("OK.");
        wicherlog("Connecting...");
        if(database_connect(h_string, p_int)){
            wicherlog("OK.");
            wicherlog("Logging in...");
            if(database_login(un_string, ps_string)){
                wicherlog("OK.");
                gtk_widget_hide(GTK_WIDGET(splash_window));
                main_run();
            }else show_dialog_login_data_error(splash_window);
        }else show_dialog_connection_error(splash_window);
    }else show_dialog_local_server_error(splash_window);
}

bool splash_init(){
    wicherlog("Preparing login splash...");
    GError * error = NULL;
    if(!gtk_builder_add_from_file(builder, "share/wicher/gui/splash.ui", &error)){
        wicherlog_err("Couldn't read GtkBuilder file: %s", error->message);
        g_error_free(error);
        return false;
    }
    splash_window = GTK_WINDOW(gtk_builder_get_object(builder, "window1"));
    splash_username_entry = GTK_ENTRY(gtk_builder_get_object(builder, "username"));
    splash_password_entry = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    splash_connect_button = GTK_BUTTON(gtk_builder_get_object(builder, "connect"));
    splash_run_button = GTK_BUTTON(gtk_builder_get_object(builder, "run"));
    if(!splash_window || !splash_username_entry || !splash_password_entry || !splash_connect_button || !splash_run_button){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }else return true;
}

bool splash_show(){
    wicherlog("Running login splash...");
    gtk_widget_show(GTK_WIDGET(splash_window));
    return true;
}
