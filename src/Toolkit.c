#include "ui.h"
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void __wicherlog(FILE * stream, char * format, va_list * arg){
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[13 + strlen(format)];
    strftime(buffer, 12, "[%H:%M:%S] ", timeinfo);
    strcat(buffer, format);
    strcat(buffer, "\n");

    vfprintf(stream, buffer, *arg);
}
void wicherlog(char * format, ...){
    va_list arg;
    va_start (arg, format);
    __wicherlog(stdout, format, &arg);
    va_end (arg);
}
void wicherlog_err(char * format, ...){
    va_list arg;
    va_start (arg, format);
    __wicherlog(stderr, format, &arg);
    va_end (arg);
}

/*char * itostr(int i){
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
}*/

void window_set_default_icons(){
    GList * iconlist = NULL;
    GError * error;
    GdkPixbuf * pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon16.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon32.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon64.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon128.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon256.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    pixbuf = gdk_pixbuf_new_from_file("share/wicher/icons/icon512.png", &error);
    if(pixbuf) iconlist = g_list_append(iconlist, pixbuf);
    gtk_window_set_default_icon_list(iconlist);
}

/*bool Wicher::Toolkit::date_extract(Glib::ustring date, int * day, int * month, int * year){
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
}*/
