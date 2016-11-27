#ifndef CONFIG_H
#define CONFIG_H
#include <gtkmm.h>
#include <string>
#include "Builder.h"

namespace Wicher{
class Config{
    public:
        static Config & getSingleton();
        bool get_unsafe_mode();

    private:
        Config();
        Config(const Config&);
        Glib::RefPtr<Gtk::Builder> builder;
        Gtk::Switch * options_safety_switch;
};
}

#endif // CONFIG_H
