#ifndef SPLASH_H
#define SPLASH_H
#include <gtkmm.h>
#include <cstdio>
#include <string>
#include "Toolkit.h"
#include "Database.h"
#include "Dialogger.h"

namespace Wicher{
class Splash{
    public:
        Splash(int argc, char * argv[]);
        bool show();

    private:
        bool run_server();
        void on_connect();
        void on_run();
        std::string host;
        int port;
        std::string username;
        std::string password;
        bool flag;
        Glib::RefPtr<Gtk::Application> app;
        Glib::RefPtr<Gtk::Builder> builder;
        Gtk::Window * window;
        Gtk::Entry * username_entry;
        Gtk::Entry * password_entry;
        Gtk::Button * connect;
        Gtk::Button * run;
};
}

#endif // SPLASH_H
