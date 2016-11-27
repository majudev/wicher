#include "SignalWindows.h"

Wicher::SignalWindows::SignalWindows(){
    builder = Builder::getSingleton().getBuilder();

    builder->get_widget("type_tree", type_tree);
    builder->get_widget("pz_tree", pz_tree);
    builder->get_widget("state_notepad", state_notepad);
    type_list = Glib::RefPtr<Gtk::ListStore>::cast_static(type_tree->get_model());
    pz_list = Glib::RefPtr<Gtk::ListStore>::cast_static(pz_tree->get_model());

    builder->get_widget("new_type_window", new_type_window);
    builder->get_widget("new_type_name_entry", new_type_name_entry);
    builder->get_widget("new_type_id_entry", new_type_id_entry);
    builder->get_widget("new_type_comment_entry", new_type_comment_entry);
    builder->get_widget("new_type_ok_button", new_type_ok_button);
    new_type_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_new_type_ok_button_clicked) );

    builder->get_widget("new_item_window", new_item_window);
    builder->get_widget("new_item_type_name_entry", new_item_type_name_entry);
    builder->get_widget("new_item_type_entry", new_item_type_entry);
    builder->get_widget("new_item_comment_entry", new_item_comment_entry);
    builder->get_widget("new_item_ok_button", new_item_ok_button);
    new_item_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_new_item_ok_button_clicked) );

    builder->get_widget("new_wz_window", new_wz_window);
    builder->get_widget("new_wz_person_entry", new_wz_person_entry);
    builder->get_widget("new_wz_date_entry", new_wz_date_entry);
    builder->get_widget("new_wz_comment_entry", new_wz_comment_entry);
    builder->get_widget("new_wz_ok_button", new_wz_ok_button);
    new_wz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_new_wz_ok_button_clicked) );

    builder->get_widget("new_pz_window", new_pz_window);
    builder->get_widget("new_pz_wz_id_entry", new_pz_wz_id_entry);
    builder->get_widget("new_pz_person_entry", new_pz_person_entry);
    builder->get_widget("new_pz_date_entry", new_pz_date_entry);
    builder->get_widget("new_pz_comment_entry", new_pz_comment_entry);
    builder->get_widget("new_pz_ok_button", new_pz_ok_button);
    new_pz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_new_pz_ok_button_clicked) );

    builder->get_widget("info_type_window", info_type_window);
    builder->get_widget("info_type_name_entry", info_type_name_entry);
    builder->get_widget("info_type_id_entry", info_type_id_entry);
    builder->get_widget("info_type_available_entry", info_type_available_entry);
    builder->get_widget("info_type_unavailable_entry", info_type_unavailable_entry);
    builder->get_widget("info_type_total_entry", info_type_total_entry);
    builder->get_widget("info_type_comment_entry", info_type_comment_entry);
    builder->get_widget("info_type_delete_button", info_type_delete_button);
    builder->get_widget("info_type_add_button", info_type_add_button);
    builder->get_widget("info_type_close_button", info_type_close_button);
    info_type_delete_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_type_delete_button_clicked) );
    info_type_add_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_type_add_button_clicked) );
    info_type_close_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_type_close_button_clicked) );

    builder->get_widget("add_items_window", add_items_window);
    builder->get_widget("add_items_type_name_entry", add_items_type_name_entry);
    builder->get_widget("add_items_type_entry", add_items_type_entry);
    builder->get_widget("add_items_count_spin", add_items_count_spin);
    builder->get_widget("add_items_comment_entry", add_items_comment_entry);
    builder->get_widget("add_items_ok_button", add_items_ok_button);
    add_items_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_add_items_ok_button_clicked) );

    builder->get_widget("info_item_window", info_item_window);
    builder->get_widget("info_item_id_entry", info_item_id_entry);
    builder->get_widget("info_item_type_entry", info_item_type_entry);
    builder->get_widget("info_item_type_name_entry", info_item_type_name_entry);
    builder->get_widget("info_item_comment_entry", info_item_comment_entry);
    builder->get_widget("info_item_delete_button", info_item_delete_button);
    builder->get_widget("info_item_copy_button", info_item_copy_button);
    builder->get_widget("info_item_close_button", info_item_close_button);
    info_item_delete_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_item_delete_button_clicked) );
    info_item_copy_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_item_copy_button_clicked) );
    info_item_close_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_item_close_button_clicked) );

    builder->get_widget("info_wz_window", info_wz_window);
    builder->get_widget("info_wz_id_entry", info_wz_id_entry);
    builder->get_widget("info_wz_person_entry", info_wz_person_entry);
    builder->get_widget("info_wz_return_date_box", info_wz_return_date_box);
    builder->get_widget("info_wz_return_date_entry", info_wz_return_date_entry);
    builder->get_widget("info_wz_date_entry", info_wz_date_entry);
    builder->get_widget("info_wz_comment_entry", info_wz_comment_entry);
    builder->get_widget("info_wz_items_tree", info_wz_items_tree);
    info_wz_items_list = Glib::RefPtr<Gtk::ListStore>::cast_static(info_wz_items_tree->get_model());
    builder->get_widget("info_wz_pz_button", info_wz_pz_button);
    builder->get_widget("info_wz_print_button", info_wz_print_button);
    builder->get_widget("info_wz_ok_button", info_wz_ok_button);
    info_wz_pz_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_wz_pz_button_clicked) );
    info_wz_print_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_wz_print_button_clicked) );
    info_wz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_wz_ok_button_clicked) );

    builder->get_widget("info_pz_window", info_pz_window);
    builder->get_widget("info_pz_id_entry", info_pz_id_entry);
    builder->get_widget("info_pz_wz_id_entry", info_pz_wz_id_entry);
    builder->get_widget("info_pz_person_entry", info_pz_person_entry);
    builder->get_widget("info_pz_date_entry", info_pz_date_entry);
    builder->get_widget("info_pz_comment_entry", info_pz_comment_entry);
    builder->get_widget("info_pz_items_tree", info_pz_items_tree);
    info_pz_items_list = Glib::RefPtr<Gtk::ListStore>::cast_static(info_pz_items_tree->get_model());
    builder->get_widget("info_pz_print_button", info_pz_print_button);
    builder->get_widget("info_pz_ok_button", info_pz_ok_button);
    info_pz_print_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_pz_print_button_clicked) );
    info_pz_ok_button->signal_clicked().connect( sigc::mem_fun(this, &Wicher::SignalWindows::on_info_pz_ok_button_clicked) );

    Wicher::Toolkit::set_icon(new_type_window);
    Wicher::Toolkit::set_icon(new_item_window);
    Wicher::Toolkit::set_icon(new_wz_window);
    Wicher::Toolkit::set_icon(new_pz_window);

    Wicher::Toolkit::set_icon(info_type_window);
    Wicher::Toolkit::set_icon(info_item_window);
    Wicher::Toolkit::set_icon(info_wz_window);
    Wicher::Toolkit::set_icon(info_pz_window);
}
