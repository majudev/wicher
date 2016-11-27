#ifndef MAIN_H
#define MAIN_H
#include <gtkmm.h>
#include <string>
#include "Toolkit.h"
#include "Database.h"
#include "Builder.h"
#include "ListsManager.h"
#include "ToolbarOptions.h"
#include "ToolbarInfo.h"

namespace Wicher{
class Main{
    public:
        Main(int argc, char * argv[]);
        ~Main();
        void run();

    private:
        Glib::RefPtr<Gtk::Application> app;
        Glib::RefPtr<Gtk::Builder> builder;

        ListsManager * lists_manager;

        ToolbarOptions * options_window;
        ToolbarInfo * info_window;

        Gtk::Window * window;
        Gtk::Button * toolbar_options;
        Gtk::Button * toolbar_refresh;
        Gtk::Button * toolbar_info;
};
}

#endif // MAIN_H
