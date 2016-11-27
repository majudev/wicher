#include "Toolkit.h"

void Wicher::Toolkit::log(std::string str){
    time_t rawtime;
    struct tm * timeinfo;

    std::time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[20];
    strftime(buffer, 20, "%H:%M:%S", timeinfo);
    std::cout << "[WICHER][" << buffer << "] " << str << std::endl;
}

std::string Wicher::Toolkit::itostr(int i){
    char ch[10];
    sprintf(ch, "%d", i);
    return std::string(ch);
}

int Wicher::Toolkit::strtoi(std::string str){
    int i;
    sscanf(str.c_str(), "%d", &i);
    return i;
}

std::string Wicher::Toolkit::time(){
    time_t rawtime;
    struct tm * timeinfo;

    std::time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[30];
    strftime(buffer, 20, "%d-%m-%Y %H:%M:%S", timeinfo);
    return std::string(buffer);
}

void Wicher::Toolkit::set_icon(Gtk::Window * w){
    std::vector< Glib::RefPtr<Gdk::Pixbuf> > icons;
    try{
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon16.png"));
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon32.png"));
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon64.png"));
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon128.png"));
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon256.png"));
        icons.push_back(Gdk::Pixbuf::create_from_file("share/wicher/icons/icon512.png"));
    }catch(const Glib::FileError &e){
        Toolkit::log(std::string("Glib::FileError: ") + std::string(e.what()));
    }catch(Gdk::PixbufError &e){
        Toolkit::log(std::string("Gdk::PixbufError: ") + std::string(e.what()));
    }
    w->set_icon_list(icons);
}

bool Wicher::Toolkit::date_extract(Glib::ustring date, int * day, int * month, int * year){
    if(date.size() == 10 && date[2] == '/' && date[5] == '/' && sscanf(date.c_str(), "%d/%d/%d", day, month, year) != EOF){
        return true;
    }
    return false;
}
bool Wicher::Toolkit::date_is_valid(Glib::ustring date){
    int i;
    return date_extract(date, &i, &i, &i);
}

Wicher::Logger::Logger(){}
Wicher::Logger::Logger(const Wicher::Logger& ){}

Wicher::Logger Wicher::log(){
    return Logger::getLogger();
}

Wicher::Logger & Wicher::Logger::getLogger(){
    static Logger l;
    return l;
}

Wicher::Logger& Wicher::Logger::operator<< (const std::string& msg){
    Wicher::Toolkit::log(msg);
    return *this;
}
