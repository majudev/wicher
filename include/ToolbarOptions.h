#ifndef TOOLBAROPTIONS_H
#define TOOLBAROPTIONS_H
#include <gtkmm.h>
#include <string>
#include "Toolkit.h"
#include "Builder.h"
#include "Config.h"

namespace Wicher{
class ToolbarOptions{
    public:
        ToolbarOptions(Glib::RefPtr<Gtk::Window> parent);
        void show();

    private:
        Glib::RefPtr<Gtk::Builder> builder;
        Glib::RefPtr<Gtk::Window> parent;
        Gtk::Window * window;
        Gtk::Switch * options_safety_switch;
        void on_switch_state_set(bool state);

        Gtk::TreeView * wz_tree;
        Gtk::TreeView * pz_tree;
        Gtk::Entry * info_wz_person_entry;
        Gtk::Entry * info_wz_date_entry;
        Gtk::Entry * info_pz_person_entry;
        Gtk::Entry * info_pz_date_entry;
};
}

#endif // SPLASH_H
