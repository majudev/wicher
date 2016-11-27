#include "ToolbarOptions.h"

Wicher::ToolbarOptions::ToolbarOptions(Glib::RefPtr<Gtk::Window> parent) : parent(parent) {
    Toolkit::log("Preparing Info window... (net.majudev.wicher.gtk.main)");
    builder = Wicher::Builder::getSingleton().getBuilder();

    builder->get_widget("options_window", window);
    builder->get_widget("wz_tree", wz_tree);
    builder->get_widget("pz_tree", pz_tree);
    builder->get_widget("info_wz_person_entry", info_wz_person_entry);
    builder->get_widget("info_wz_date_entry", info_wz_date_entry);
    builder->get_widget("info_pz_person_entry", info_pz_person_entry);
    builder->get_widget("info_pz_date_entry", info_pz_date_entry);
    builder->get_widget("options_safety_switch", options_safety_switch);
    this->options_safety_switch->signal_state_set().connect_notify( sigc::mem_fun(this, &Wicher::ToolbarOptions::on_switch_state_set) );
	std::flush(std::cerr);
    if(window){
        Wicher::Toolkit::set_icon(window);
    }
}

void Wicher::ToolbarOptions::show(){
    window->show_all();
}

void Wicher::ToolbarOptions::on_switch_state_set(bool state){
	std::flush(std::cerr);
    Gtk::CellRendererText * renderer = static_cast<Gtk::CellRendererText*>(wz_tree->get_column(1)->get_first_cell());
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
    info_pz_date_entry->set_editable(state);
}
