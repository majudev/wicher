#ifndef DIALOGGER_H
#define DIALOGGER_H
#include <gtkmm.h>
#include <jansson.h>
#include "Toolkit.h"

namespace Wicher{
class Dialogger{
    public:
        ///Test
        static void test(Gtk::Window * parent);

        ///Database
        static void response_error(Gtk::Window * parent, json_error_t error);
        static void response_error(json_error_t error);
        static void query_error(Gtk::Window * parent, json_t * root);
        static void query_error(json_t * root);

        ///Splash errors
        static void local_server_error(Gtk::Window * parent);
        static void connection_error(Gtk::Window * parent);
        static void login_data_error(Gtk::Window * parent);

        ///GUI
        static void refresh_error();
        static void update_error();

        ///Windows
        static void creating_already_shown(Gtk::Window * parent);
        static void info_already_shown(Gtk::Window * parent);
        static void empty_entries(Gtk::Window * parent);
    
        //PDF
        static void pdf_ok(Gtk::Window * parent, std::string path);
        static void pdf_error(Gtk::Window * parent, std::string path);

    private:
        static void info(Gtk::Window * parent, std::string primary, std::string secondary);
        static void error(Gtk::Window * parent, std::string primary, std::string secondary);
};
}

#endif // DIALOGGER_H
