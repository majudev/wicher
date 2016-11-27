#include "SignalWindows.h"

void Wicher::SignalWindows::show_create_pz_window(int wz_id){
    if(!is_shown_create_pz_window()){
        this->new_pz_wz_id_entry->set_text(Wicher::Toolkit::itostr(wz_id));
        this->new_pz_person_entry->set_text("");
        this->new_pz_comment_entry->set_text("");

        this->new_pz_window->show_all();
    }else Dialogger::creating_already_shown(new_pz_window);
}

void Wicher::SignalWindows::on_new_pz_ok_button_clicked(){
    if(is_shown_create_pz_window()){
        Glib::ustring person = new_pz_person_entry->get_text();
        Glib::Date date;
        new_pz_date_entry->get_date(date);
        Glib::ustring wz_id = new_pz_wz_id_entry->get_text();
        Glib::ustring comment = new_pz_comment_entry->get_text();
        if(!person.empty() && !wz_id.empty()){
            std::string response = Wicher::Database::getSingleton().run(Wicher::Database::Query::register_pz(Wicher::Toolkit::strtoi(wz_id), date.format_string("%d/%m/%Y"), person, comment));
            json_error_t error;
            json_t * root = json_loads(response.c_str(), 0, &error);
            json_t * resp = json_object_get(root, "response");
            if(root){
                if(!json_is_string(resp) || std::string(json_string_value(resp)) != std::string("ok")){
                    Dialogger::query_error(new_pz_window, root);
                }
            }else{
                Dialogger::response_error(new_pz_window, error);
            }
            free(root);
        }else Dialogger::empty_entries(new_pz_window);
        this->new_pz_window->close();
    }
}

bool Wicher::SignalWindows::is_shown_create_pz_window(){
    return this->new_pz_window->is_visible();
}
