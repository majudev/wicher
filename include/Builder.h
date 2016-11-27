#ifndef BUILDER_H
#define BUILDER_H
#include <gtkmm.h>
#include <string>
#include "Toolkit.h"

namespace Wicher{
class Builder{
    public:
        static Builder & getSingleton();
        Glib::RefPtr<Gtk::Builder> getBuilder();

    private:
        Builder();
        Builder(const Builder&);
        Glib::RefPtr<Gtk::Builder> builder;
};
}

#endif // BUILDER_H
