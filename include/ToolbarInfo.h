#ifndef TOOLBARINFO_H
#define TOOLBARINFO_H
#include <gtkmm.h>
#include <string>
#include "Toolkit.h"
#include "Builder.h"

namespace Wicher{
class ToolbarInfo{
    public:
        ToolbarInfo(Glib::RefPtr<Gtk::Window> parent);
        void show();

    private:
        void on_ok_click();
        Glib::RefPtr<Gtk::Builder> builder;
        Glib::RefPtr<Gtk::Window> parent;
        Gtk::Window * window;
        Gtk::Button * ok_button;
};
}

#endif // SPLASH_H
