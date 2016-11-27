#include "Splash.h"

void Wicher::Splash::on_connect(){
    std::string h_string("majudev.net");
    int p_int = 9;
    std::string un_string(username_entry->get_text());
    std::string ps_string(password_entry->get_text());
    if(!un_string.empty() && !ps_string.empty()){
        Wicher::Toolkit::log("Setting data:");
        Wicher::Toolkit::log(std::string("\tHOST: ") + h_string);
        Wicher::Toolkit::log(std::string("\tPORT: ") + Wicher::Toolkit::itostr(p_int));
        Wicher::Toolkit::log(std::string("\tUSERNAME: ") + un_string);
        Wicher::Toolkit::log(std::string("\tPASSWORD: ****"));
        host = h_string;
        port = p_int;
        username = un_string;
        password = ps_string;
        Wicher::Toolkit::log("OK.");
        Wicher::Toolkit::log("Connecting...");
        if(Wicher::Database::getSingleton().conn(host, port)){
            Wicher::Toolkit::log("OK.");
            Wicher::Toolkit::log("Logging in...");
            if(Wicher::Database::getSingleton().login(username, password)){
                Wicher::Toolkit::log("OK.");
                flag = true;
                window->close();
            }else Wicher::Dialogger::login_data_error(window);
        }else Wicher::Dialogger::connection_error(window);
    }else Wicher::Dialogger::login_data_error(window);
}

void Wicher::Splash::on_run(){
    std::string h_string("localhost");
    int p_int = 63431;
    std::string un_string("null");
    std::string ps_string("null");
    Wicher::Toolkit::log("Setting data:");
    Wicher::Toolkit::log(std::string("\tHOST: ") + h_string);
    Wicher::Toolkit::log(std::string("\tPORT: ") + Wicher::Toolkit::itostr(p_int));
    Wicher::Toolkit::log(std::string("\tUSERNAME: ") + un_string);
    Wicher::Toolkit::log(std::string("\tPASSWORD: ****"));
    host = h_string;
    port = p_int;
    username = un_string;
    password = ps_string;
    Wicher::Toolkit::log("OK.");
    Wicher::Toolkit::log("Running local server...");
    if(this->run_server()){
        Wicher::Toolkit::log("OK.");
        Wicher::Toolkit::log("Connecting...");
        if(Wicher::Database::getSingleton().conn(host, port)){
            Wicher::Toolkit::log("OK.");
            Wicher::Toolkit::log("Logging in...");
            if(Wicher::Database::getSingleton().login(username, password)){
                Wicher::Toolkit::log("OK.");
                flag = true;
                window->close();
            }else Wicher::Dialogger::login_data_error(window);
        }else Wicher::Dialogger::connection_error(window);
    }else Wicher::Dialogger::local_server_error(window);
}

Wicher::Splash::Splash(int argc, char * argv[]) : flag(false){
    Toolkit::log("Preparing login splash... (net.majudev.wicher.gtk.splash)");
    app = Gtk::Application::create(argc, argv, "net.majudev.wicher.gtk.splash");
    builder = Gtk::Builder::create();
    try{
        builder->add_from_file("share/wicher/gui/splash.ui");
        builder->get_widget("window1", window);
        builder->get_widget("username", username_entry);
        builder->get_widget("password", password_entry);
        builder->get_widget("connect", connect);
        builder->get_widget("run", run);
        if(window){
            Wicher::Toolkit::set_icon(window);
            if(connect){
                connect->signal_clicked().connect( sigc::mem_fun(this, &Wicher::Splash::on_connect) );
            }
            if(run){
                run->signal_clicked().connect( sigc::mem_fun(this, &Wicher::Splash::on_run) );
            }
        }
    }catch(const Gtk::BuilderError &e){
        Toolkit::log(std::string("Gtk::BuilderError: ") + std::string(e.what()));
    }catch(const Glib::MarkupError &e){
        Toolkit::log(std::string("Glib::MarkupError: ") + std::string(e.what()));
    }catch(const Glib::FileError &e){
        Toolkit::log(std::string("Glib::FileError: ") + std::string(e.what()));
    }
}

bool Wicher::Splash::show(){
    Toolkit::log("Running login splash...");
    app->run(*window);
    Toolkit::log("Login splash ended. (net.majudev.wicher.gtk.splash)");
    return flag;
}
