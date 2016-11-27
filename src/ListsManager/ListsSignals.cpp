#include "ListsManager.h"

void Wicher::ListsManager::on_new_type_ok_button_clicked(){
    if(!(this->refresh_types() && this->refresh_lists() && this->refresh_history())){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_new_item_ok_button_clicked(){
    if(!(this->refresh_types() && this->refresh_lists() && this->refresh_history())){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_add_items_ok_button_clicked(){
    if(!(this->refresh_types() && this->refresh_lists() && this->refresh_history())){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_new_wz_ok_button_clicked(){
    if(!this->refresh_all()){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_new_pz_ok_button_clicked(){
    if(!this->refresh_all()){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_info_type_close_delete_button_clicked(){
    if(!(this->refresh_types() && this->refresh_lists() && this->refresh_history())){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_info_item_close_copy_delete_button_clicked(){
    if(!(this->refresh_types() && this->refresh_lists() && this->refresh_history())){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_info_wz_close_button_clicked(){
    if(!this->refresh_all()){
        Dialogger::refresh_error();
    }
}

void Wicher::ListsManager::on_info_pz_close_button_clicked(){
    if(!this->refresh_all()){
        Dialogger::refresh_error();
    }
}
