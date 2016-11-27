#ifndef WICHERTOOLKIT_H_INCLUDED
#define WICHERTOOLKIT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <gtkmm.h>

namespace Wicher{
class Toolkit{
    public:
        static void log(std::string str);
        static std::string itostr(int i);
        static int strtoi(std::string str);
        static std::string time();
        static void set_icon(Gtk::Window * w);
        static bool date_extract(Glib::ustring date, int * day, int * month, int * year);
        static bool date_is_valid(Glib::ustring date);
};
class Logger{
    public:
        Logger();
        Logger(const Logger& );
        Logger& operator<< (const std::string& msg);
        static Logger & getLogger();
};
Logger log(void);
}

#endif // UTILS_H_INCLUDED
