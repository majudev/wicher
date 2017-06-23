#include "ui.h"
#include <string.h>
#include <jansson.h>

void show_dialog_error(GtkWindow * parent, char * primary, char * secondary){
    GtkWidget * dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, primary);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), secondary);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_dialog_info(GtkWindow * parent, char * primary, char * secondary){
    GtkWidget * dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, primary);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), secondary);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_dialog_query_error(GtkWindow * parent, json_t * root){
    char first[128];
    char secondary[128];
    strcpy(first, "Błąd w odpowiedzi serwera");
    strcpy(secondary, "Nie można uzyskać szczegółów.");
    if(root){
        if(json_is_object(root)){
            json_t * resp = json_object_get(root, "response");
            if(json_is_string(resp)){
                const char * response = json_string_value(resp);
                if(!strcmp(response, "ok")){
                    strcpy(first, "Podczas wykonywania żądania wystąpił błąd");
                    json_t * errorid = json_object_get(root, "errorid");
                    json_t * longtext = json_object_get(root, "longtext");
                    if(!strcmp(response, "error") && json_is_integer(errorid)){
                        sprintf(secondary, "Numer błędu: %d", json_integer_value(errorid));
                    }else if(!strcmp(response, "error") && json_is_string(longtext)){
                        sprintf(secondary, "Opis (z serwera): %s", json_string_value(longtext));
                    }else{
                        sprintf(secondary, "Odpowiedź serwera: %s", response);
                    }
                }else{
                    strcpy(first, "Błędny błąd");
                    strcpy(secondary, "Wszystko wydaje się być w porządku. Mimo tego na twoim miejscu skontaktowałbym się z autorem (email znajduje się pod przyciskiem \"Informacje o wersji\")");
                }
            }else{
                strcpy(first, "Odpowiedź serwera nie zawiera pola 'response'");
                strcpy(secondary, "Pole to jest wynikiem operacji przeprowadzanej na serwerze.");
            }
        }else{
            strcpy(first, "Odpowiedź serwera nie zawiera głównego obiektu");
            strcpy(secondary, "W obiekcie głównym znajdują się wszystkie informacje o odpowiedzi serwera.");
        }
    }
    show_dialog_error(parent, first, secondary);
}

void show_dialog_response_error(GtkWindow * parent, json_error_t error){
    char secondary[256];
    sprintf(secondary, "JSON error when parsing server's response: %s\n\tSource: %s\n\tLine: %d\n\t%Column: %d\n\tPosition [bytes]: %d", error.text, error.source, error.line, error.column, error.position);
    show_dialog_error(parent, "Błąd przy odczytywaniu odpowiedzi serwera", secondary);
}

void show_dialog_local_server_error(GtkWindow * parent){
    show_dialog_error(parent, "Błąd", "Nie można uruchomić serwera lokalnego");
}

void show_dialog_connection_error(GtkWindow * parent){
    show_dialog_error(parent, "Błąd", "Nie można połączyć się z serwerem");
}

void show_dialog_login_data_error(GtkWindow * parent){
    show_dialog_info(parent, "Błąd", "Podano błędny login lub hasło");
}

void show_dialog_refresh_error(){
    show_dialog_error(NULL, "Błąd", "Nie można odświeżyć list");
}

void show_dialog_update_error(){
    show_dialog_error(NULL, "Błąd", "Nie można zaktualizować");
}

void show_dialog_creating_already_shown(GtkWindow * parent){
    show_dialog_info(parent, "Jedno okienko tworzenia jest już wyświetlone", "Przed otwarciem kolejnego zamknij poprzednie.");
}

void show_dialog_info_already_shown(GtkWindow * parent){
    show_dialog_info(parent, "Jedno okienko szczegółów jest już wyświetlone", "Przed otwarciem kolejnego zamknij poprzednie.");
}

void show_dialog_empty_entries(GtkWindow * parent){
    show_dialog_info(parent, "Uzupełnij wszystkie pola", "Nie wszystkie pola obowiązkowe zostały uzupełnione.");
}

/*void show_dialog_pdf_ok(Gtk::Window * parent, std::string path){
    show_dialog_info(parent, "Tworzenie dokumentu zakończone sukcesem", "Zapisano do " + path);
}

void show_dialog_pdf_error(Gtk::Window * parent, std::string path){
    show_dialog_error(parent, "Błąd przy tworzeniu dokumentu", "Błąd zapisu " + path);
}*/