#include "ui.h"

GtkTreeView * type_tree;
GtkTreeView * wz_tree;
GtkTreeView * pz_tree;
GtkTreeView * history_tree;
GtkListStore * type_list;
GtkListStore * wz_list;
GtkListStore * pz_list;
GtkListStore * history_list;
GtkNotebook * state_notepad;

bool listsmanager_init(){
    if(!signalwindows_init()) return false;

    /*builder->get_widget("type_create_button", create_type_button);
    builder->get_widget("wz_create_button", create_wz_button);*/

    type_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "type_tree"));
    state_notepad = GTK_NOTEBOOK(gtk_builder_get_object(builder, "state_notepad"));
    type_list = GTK_LIST_STORE(gtk_tree_view_get_model(type_tree));

    wz_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "wz_tree"));
    wz_list = GTK_LIST_STORE(gtk_tree_view_get_model(wz_tree));

    pz_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "pz_tree"));
    pz_list = GTK_LIST_STORE(gtk_tree_view_get_model(pz_tree));

    history_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "history_tree"));
    history_list = GTK_LIST_STORE(gtk_tree_view_get_model(history_tree));

    /*builder->get_widget("new_type_ok_button", new_type_ok_button);
    builder->get_widget("new_item_ok_button", new_item_ok_button);
    builder->get_widget("new_wz_ok_button", new_wz_ok_button);
    builder->get_widget("new_pz_ok_button", new_pz_ok_button);
    builder->get_widget("info_type_close_button", info_type_close_button);
    builder->get_widget("info_type_delete_button", info_type_delete_button);
    builder->get_widget("info_item_close_button", info_item_close_button);
    builder->get_widget("info_item_copy_button", info_item_copy_button);
    builder->get_widget("info_item_delete_button", info_item_delete_button);
    builder->get_widget("info_wz_ok_button", info_wz_ok_button);
    builder->get_widget("info_pz_ok_button", info_pz_ok_button);
    new_type_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_new_type_ok_button_clicked) );
    new_item_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_new_item_ok_button_clicked) );
    new_wz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_new_wz_ok_button_clicked) );
    new_pz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_new_pz_ok_button_clicked) );
    info_type_close_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_type_close_delete_button_clicked) );
    info_type_delete_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_type_close_delete_button_clicked) );
    info_item_close_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_item_close_copy_delete_button_clicked) );
    info_item_copy_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_item_close_copy_delete_button_clicked) );
    info_item_delete_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_item_close_copy_delete_button_clicked) );
    info_wz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_wz_close_button_clicked) );
    info_pz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_info_pz_close_button_clicked) );

    create_type_button->signal_clicked().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_create_type_window) );
    create_wz_button->signal_clicked().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_create_wz_window) );

    Gtk::CellRendererText * renderer = static_cast<Gtk::CellRendererText*>(type_tree->get_column(5)->get_first_cell());
    renderer->property_editable() = true;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_type_comment_edited) );
    renderer = static_cast<Gtk::CellRendererText*>(type_tree->get_column(0)->get_first_cell());
    renderer->property_editable() = true;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_type_name_edited) );

    renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(1)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_wz_date_edited) );
    renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(2)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_wz_person_edited) );
    renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(4)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_wz_comment_edited) );

    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(2)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_pz_date_edited) );
    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(3)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_pz_person_edited) );
    renderer = static_cast<Gtk::CellRendererText*>(pz_tree->get_column(4)->get_first_cell());
    renderer->property_editable() = false;
    renderer->signal_edited().connect( sigc::mem_fun(this, &Wicher::ListsManager::on_pz_comment_edited) );

    this->type_tree->signal_row_activated().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_info_type_window) );
    this->wz_tree->signal_row_activated().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_info_wz_window) );
    this->pz_tree->signal_row_activated().connect( sigc::mem_fun(sw, &Wicher::SignalWindows::show_info_pz_window) );*/
    
    if(!type_tree || !type_list || !wz_tree || !wz_list || !pz_tree || !pz_list || !history_tree || !history_list || !state_notepad){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }

    return true;
}
