#include "Main.h"

Wicher::Main::Main(int argc, char * argv[]){
    Toolkit::log("Preparing GUI... (net.majudev.wicher.gtk.main)");
    app = Gtk::Application::create(argc, argv, "net.majudev.wicher.gtk.main");

    builder = Wicher::Builder::getSingleton().getBuilder();

    builder->get_widget("main_window", window);
    builder->get_widget("toolbar_options", toolbar_options);
    builder->get_widget("toolbar_refresh", toolbar_refresh);
    builder->get_widget("toolbar_info", toolbar_info);

    lists_manager = new ListsManager();

    options_window = new ToolbarOptions(Glib::RefPtr<Gtk::Window>(window));
    info_window = new ToolbarInfo(Glib::RefPtr<Gtk::Window>(window));

    window->maximize();

    if(window){
        Wicher::Toolkit::set_icon(window);
        if(toolbar_options){
            toolbar_options->signal_clicked().connect( sigc::mem_fun(options_window, &Wicher::ToolbarOptions::show) );
        }
        if(toolbar_refresh){
            toolbar_refresh->signal_clicked().connect( sigc::mem_fun(lists_manager, &Wicher::ListsManager::refresh_all_void) );
        }
        if(toolbar_info){
            toolbar_info->signal_clicked().connect( sigc::mem_fun(info_window, &Wicher::ToolbarInfo::show) );
        }
    }

    Toolkit::log("Done.");
}

void Wicher::Main::run(){
    Toolkit::log("Running GUI...");
    app->run(*window);
    Toolkit::log("GUI ended. (net.majudev.wicher.gtk.main)");
}

Wicher::Main::~Main(){
    delete options_window;
    delete info_window;
}
