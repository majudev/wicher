#include "Dialogger.h"

void Wicher::Dialogger::error(Gtk::Window * parent, std::string primary, std::string secondary){
    if(!parent){
        Gtk::MessageDialog dialog(primary.c_str());
        dialog.set_secondary_text(secondary.c_str());
        dialog.run();
    }else{
        Gtk::MessageDialog dialog(*parent, primary.c_str());
        dialog.set_secondary_text(secondary.c_str());
        dialog.run();
    }
}

void Wicher::Dialogger::info(Gtk::Window * parent, std::string primary, std::string secondary){
    if(!parent){
        Gtk::MessageDialog dialog(primary.c_str());
        dialog.set_secondary_text(secondary.c_str());
        dialog.run();
    }else{
        Gtk::MessageDialog dialog(*parent, primary.c_str());
        dialog.set_secondary_text(secondary.c_str());
        dialog.run();
    }
}

void Wicher::Dialogger::test(Gtk::Window * parent){
    error(parent, "First text", "No explaination D:");
}

void Wicher::Dialogger::query_error(Gtk::Window * parent, json_t * root){
    std::string first("Błąd w odpowiedzi serwera");
    std::string secondary("Nie można uzyskać szczegółów.");
    if(root){
        if(json_is_object(root)){
            json_t * resp = json_object_get(root, "response");
            if(json_is_string(resp)){
                std::string response(json_string_value(resp));
                if(response != std::string("ok")){
                    first = "Podczas wykonywania żądania wystąpił błąd";
                    json_t * errorid = json_object_get(root, "errorid");
                    json_t * longtext = json_object_get(root, "longtext");
                    if(response == std::string("error") && json_is_integer(errorid)){
                        secondary = std::string("Numer błędu: ") + Toolkit::itostr(json_integer_value(errorid));
                    }else if(response == std::string("error") && json_is_string(longtext)){
                        secondary = std::string("Opis (z serwera): ") + std::string(json_string_value(longtext));
                    }else{
                        secondary = std::string("Odpowiedź serwera: ") + response;
                    }
                }else{
                    first = "Błędny błąd";
                    secondary = "Wszystko wydaje się być w porządku. Mimo tego na twoim miejscu skontaktowałbym się z autorem (email znajduje się pod przyciskiem \"Informacje o wersji\")";
                }
            }else{
                first = "Odpowiedź serwera nie zawiera pola 'response'";
                secondary = "Pole to jest wynikiem operacji przeprowadzanej na serwerze.";
            }
        }else{
            first = "Odpowiedź serwera nie zawiera głównego obiektu";
            secondary = "W obiekcie głównym znajdują się wszystkie informacje o odpowiedzi serwera.";
        }
    }
    error(parent, first, secondary);
}

void Wicher::Dialogger::query_error(json_t * root){
    query_error(nullptr, root);
}

void Wicher::Dialogger::response_error(Gtk::Window * parent, json_error_t error){
    std::string secondary =
        std::string("JSON error when parsing server's response: ") + std::string(error.text) + std::string("\n") +
        std::string("\tSource:") + std::string(error.source) + std::string("\n") +
        std::string("\tLine:") + Toolkit::itostr(error.line) + std::string("\n") +
        std::string("\tColumn:") + Toolkit::itostr(error.column) + std::string("\n") +
        std::string("\tPosition [bytes]:") + Toolkit::itostr(error.position);
    Wicher::Dialogger::error(parent, "Błąd przy odczytywaniu odpowiedzi serwera", secondary);
}

void Wicher::Dialogger::response_error(json_error_t error){
    response_error(nullptr, error);
}

void Wicher::Dialogger::local_server_error(Gtk::Window * parent){
    error(parent, "Błąd", "Nie można uruchomić serwera lokalnego");
}

void Wicher::Dialogger::connection_error(Gtk::Window * parent){
    error(parent, "Błąd", "Nie można połączyć się z serwerem");
}

void Wicher::Dialogger::login_data_error(Gtk::Window * parent){
    error(parent, "Błąd", "Podano błędny login lub hasło");
}

void Wicher::Dialogger::refresh_error(){
    error(nullptr, "Błąd", "Nie można odświeżyć list");
}

void Wicher::Dialogger::update_error(){
    error(nullptr, "Błąd", "Nie można zaktualizować");
}

void Wicher::Dialogger::creating_already_shown(Gtk::Window * parent){
    info(parent, "Jedno okienko tworzenia jest już wyświetlone", "Przed otwarciem kolejnego zamknij poprzednie.");
}

void Wicher::Dialogger::info_already_shown(Gtk::Window * parent){
    info(parent, "Jedno okienko szczegółów jest już wyświetlone", "Przed otwarciem kolejnego zamknij poprzednie.");
}

void Wicher::Dialogger::empty_entries(Gtk::Window * parent){
    info(parent, "Uzupełnij wszystkie pola", "Nie wszystkie pola obowiązkowe zostały uzupełnione.");
}

void Wicher::Dialogger::pdf_ok(Gtk::Window * parent, std::string path){
    info(parent, "Tworzenie dokumentu zakończone sukcesem", "Zapisano do " + path);
}

void Wicher::Dialogger::pdf_error(Gtk::Window * parent, std::string path){
    error(parent, "Błąd przy tworzeniu dokumentu", "Błąd zapisu " + path);
}