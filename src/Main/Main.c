#include "ui.h"
#include "buildconfig.h"

GtkWindow * main_window;
GtkButton * toolbar_options;
GtkButton * toolbar_refresh;
GtkButton * toolbar_info;

bool main_init(){
    wicherlog("Preparing GUI...");
    
    bool flag = true;
    GError * error;
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/gui.ui", &error);

    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/create_type.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/create_item.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/create_wz.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/create_pz.ui", &error);

    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/info_type.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/info_item.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/info_wz.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/info_pz.ui", &error);

    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/options_window.ui", &error);
    flag = flag && gtk_builder_add_from_file(builder, "share/wicher/gui/info_window.ui", &error);
    
    if(!flag){
        wicherlog_err("Couldn't read GtkBuilder file: %s", error->message);
        g_error_free(error);
        return false;
    }
    
    main_window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
    toolbar_options = GTK_BUTTON(gtk_builder_get_object(builder, "toolbar_options"));
    toolbar_refresh = GTK_BUTTON(gtk_builder_get_object(builder, "toolbar_refresh"));
    toolbar_info = GTK_BUTTON(gtk_builder_get_object(builder, "toolbar_info"));

    if(!listsmanager_init()) return false;

    if(!options_window_init()) return false;
    if(!info_window_init()) return false;

    gtk_window_maximize(main_window);
	gtk_window_set_title(main_window, PACKAGE_STRING);

    if(!main_window || !toolbar_options || !toolbar_refresh || !toolbar_info){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }

    wicherlog("Done.");
    return true;
}

void main_run(){
    wicherlog("Running GUI...");
    listsmanager_refresh_all();
    gtk_widget_show(GTK_WIDGET(main_window));
}
