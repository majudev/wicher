#include "Builder.h"

Wicher::Builder::Builder(const Builder &) {}

Wicher::Builder::Builder(){
    builder = Gtk::Builder::create();
    try{
        builder->add_from_file("share/wicher/gui/gui.ui");

        builder->add_from_file("share/wicher/gui/create_type.ui");
        builder->add_from_file("share/wicher/gui/create_item.ui");
        builder->add_from_file("share/wicher/gui/create_wz.ui");
        builder->add_from_file("share/wicher/gui/create_pz.ui");

        builder->add_from_file("share/wicher/gui/info_type.ui");
        builder->add_from_file("share/wicher/gui/info_item.ui");
        builder->add_from_file("share/wicher/gui/info_wz.ui");
        builder->add_from_file("share/wicher/gui/info_pz.ui");

        builder->add_from_file("share/wicher/gui/options_window.ui");
        builder->add_from_file("share/wicher/gui/info_window.ui");
    }catch(const Gtk::BuilderError &e){
        Toolkit::log(std::string("Gtk::BuilderError: ") + std::string(e.what()));
    }catch(const Glib::MarkupError &e){
        Toolkit::log(std::string("Glib::MarkupError: ") + std::string(e.what()));
    }catch(const Glib::FileError &e){
        Toolkit::log(std::string("Glib::FileError: ") + std::string(e.what()));
    }catch(Gdk::PixbufError &e){
        Toolkit::log(std::string("Gdk::PixbufError: ") + std::string(e.what()));
    }
}

Wicher::Builder & Wicher::Builder::getSingleton(){
    static Builder b;
    return b;
}

Glib::RefPtr<Gtk::Builder> Wicher::Builder::getBuilder(){
    return builder;
}
