#include "ui.h"

GtkWindow * options_window;
GtkSwitch * options_safety_switch;
bool options_window_init(){
    wicherlog("Preparing info window...");
    options_window = GTK_WINDOW(gtk_builder_get_object(builder, "options_window"));
    options_safety_switch = GTK_SWITCH(gtk_builder_get_object(builder, "options_safety_switch"));
    
    if(!options_window || !options_safety_switch){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }
    gtk_window_set_transient_for(options_window, main_window);
    return true;
}

void options_window_show(){
    gtk_widget_show_all(GTK_WIDGET(options_window));
}

void options_window_on_ok_click(){
    gtk_widget_hide(GTK_WIDGET(options_window));
}

void options_window_on_switch_state_set(bool state){
    /*Gtk::CellRendererText * renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(1)->get_first_cell());
    renderer->property_editable() = state;
    renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(2)->get_first_cell());
    renderer->property_editable() = state;
    renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(4)->get_first_cell());
    renderer->property_editable() = state;

    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(2)->get_first_cell());
    renderer->property_editable() = state;
    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(3)->get_first_cell());
    renderer->property_editable() = state;
    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(4)->get_first_cell());
    renderer->property_editable() = state;

    info_wz_person_entry->set_editable(state);
    info_wz_date_entry->set_editable(state);
    info_pz_person_entry->set_editable(state);
    info_pz_date_entry->set_editable(state);*/
}
