#include "ui.h"

GtkWindow * info_window;

void info_window_on_ok_click(){
    gtk_widget_hide(GTK_WIDGET(info_window));
}

bool info_window_init(){
    wicherlog("Preparing info window...");
    info_window = GTK_WINDOW(gtk_builder_get_object(builder, "info_window"));
    if(!info_window){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }
    gtk_window_set_transient_for(info_window, main_window);
    return true;
}

void info_window_show(){
    wicherlog("Showing info window");
    gtk_widget_show(GTK_WIDGET(info_window));
}
