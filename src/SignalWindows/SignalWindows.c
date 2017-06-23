#include "ui.h"

GtkWindow * new_type_window;
GtkEntry * new_type_name_entry;
GtkEntry * new_type_id_entry;
GtkEntry * new_type_comment_entry;
GtkButton * new_type_ok_button;

GtkWindow * new_item_window;
GtkEntry * new_item_type_name_entry;
GtkEntry * new_item_type_entry;
GtkEntry * new_item_comment_entry;
GtkButton * new_item_ok_button;

GtkWindow * new_wz_window;
GtkEntry * new_wz_person_entry;
GtkCalendar * new_wz_date_entry;
GtkEntry * new_wz_comment_entry;
GtkButton * new_wz_ok_button;

GtkWindow * new_pz_window;
GtkEntry * new_pz_wz_id_entry;
GtkEntry * new_pz_person_entry;
GtkCalendar * new_pz_date_entry;
GtkEntry * new_pz_comment_entry;
GtkButton * new_pz_ok_button;

GtkWindow * info_type_window;
GtkEntry * info_type_name_entry;
GtkEntry * info_type_id_entry;
GtkEntry * info_type_available_entry;
GtkEntry * info_type_unavailable_entry;
GtkEntry * info_type_total_entry;
GtkEntry * info_type_comment_entry;
GtkButton * info_type_delete_button;
GtkButton * info_type_add_button;
GtkButton * info_type_close_button;

GtkWindow * add_items_window;
GtkEntry * add_items_type_name_entry;
GtkEntry * add_items_type_entry;
GtkSpinButton * add_items_count_spin;
GtkEntry * add_items_comment_entry;
GtkButton * add_items_ok_button;

GtkWindow * info_item_window;
GtkEntry * info_item_id_entry;
GtkEntry * info_item_type_entry;
GtkEntry * info_item_type_name_entry;
GtkEntry * info_item_comment_entry;
GtkButton * info_item_delete_button;
GtkButton * info_item_copy_button;
GtkButton * info_item_close_button;

GtkWindow * info_wz_window;
GtkEntry * info_wz_id_entry;
GtkEntry * info_wz_person_entry;
GtkBox * info_wz_return_date_box;
GtkEntry * info_wz_return_date_entry;
GtkEntry * info_wz_date_entry;
GtkEntry * info_wz_comment_entry;
GtkTreeView * info_wz_items_tree;
GtkListStore * info_wz_items_list;
GtkButton * info_wz_pz_button;
GtkButton * info_wz_print_button;
GtkButton * info_wz_ok_button;

GtkWindow * info_pz_window;
GtkEntry * info_pz_id_entry;
GtkEntry * info_pz_wz_id_entry;
GtkEntry * info_pz_person_entry;
GtkEntry * info_pz_date_entry;
GtkEntry * info_pz_comment_entry;
GtkTreeView * info_pz_items_tree;
GtkListStore * info_pz_items_list;
GtkButton * info_pz_print_button;
GtkButton * info_pz_ok_button;

bool signalwindows_init(){
    new_type_window = GTK_WINDOW(gtk_builder_get_object(builder, "new_type_window"));
    new_type_name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_type_name_entry"));
    new_type_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_type_id_entry"));
    new_type_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_type_comment_entry"));
    new_type_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "new_type_ok_button"));
    
    new_item_window = GTK_WINDOW(gtk_builder_get_object(builder, "new_item_window"));
    new_item_type_name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_item_type_name_entry"));
    new_item_type_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_item_type_entry"));
    new_item_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_item_comment_entry"));
    new_item_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "new_item_ok_button"));
    
    new_wz_window = GTK_WINDOW(gtk_builder_get_object(builder, "new_wz_window"));
    new_wz_person_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_wz_person_entry"));
    new_wz_date_entry = GTK_CALENDAR(gtk_builder_get_object(builder, "new_wz_date_entry"));
    new_wz_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_wz_comment_entry"));
    new_wz_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "new_wz_ok_button"));
    
    new_pz_window = GTK_WINDOW(gtk_builder_get_object(builder, "new_pz_window"));
    new_pz_wz_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_pz_wz_id_entry"));
    new_pz_person_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_pz_person_entry"));
    new_pz_date_entry = GTK_CALENDAR(gtk_builder_get_object(builder, "new_pz_date_entry"));
    new_pz_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "new_pz_comment_entry"));
    new_pz_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "new_pz_ok_button"));
    
    info_type_window = GTK_WINDOW(gtk_builder_get_object(builder, "info_type_window"));
    info_type_name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_name_entry"));
    info_type_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_id_entry"));
    info_type_available_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_available_entry"));
    info_type_unavailable_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_unavailable_entry"));
    info_type_total_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_total_entry"));
    info_type_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_type_comment_entry"));
    info_type_delete_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_type_delete_button"));
    info_type_add_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_type_add_button"));
    info_type_close_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_type_close_button"));
    
    add_items_window = GTK_WINDOW(gtk_builder_get_object(builder, "add_items_window"));
    add_items_type_name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "add_items_type_name_entry"));
    add_items_type_entry = GTK_ENTRY(gtk_builder_get_object(builder, "add_items_type_entry"));
    add_items_count_spin = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "add_items_count_spin"));
    add_items_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "add_items_comment_entry"));
    add_items_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "add_items_ok_button"));
    
    info_item_window = GTK_WINDOW(gtk_builder_get_object(builder, "info_item_window"));
    info_item_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_item_id_entry"));
    info_item_type_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_item_type_entry"));
    info_item_type_name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_item_type_name_entry"));
    info_item_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_item_comment_entry"));
    info_item_delete_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_item_delete_button"));
    info_item_copy_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_item_copy_button"));
    info_item_close_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_item_close_button"));
    
    info_wz_window = GTK_WINDOW(gtk_builder_get_object(builder, "info_wz_window"));
    info_wz_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_wz_id_entry"));
    info_wz_person_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_wz_person_entry"));
    info_wz_return_date_box = GTK_BOX(gtk_builder_get_object(builder, "info_wz_return_date_box"));
    info_wz_return_date_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_wz_return_date_entry"));
    info_wz_date_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_wz_date_entry"));
    info_wz_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_wz_comment_entry"));
    info_wz_items_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "info_wz_items_tree"));
    info_wz_items_list = GTK_LIST_STORE(gtk_builder_get_object(builder, "info_wz_items_list"));
    info_wz_pz_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_wz_pz_button"));
    info_wz_print_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_wz_print_button"));
    info_wz_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_wz_ok_button"));
    
    info_pz_window = GTK_WINDOW(gtk_builder_get_object(builder, "info_pz_window"));
    info_pz_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_pz_id_entry"));
    info_pz_wz_id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_pz_wz_id_entry"));
    info_pz_person_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_pz_person_entry"));
    info_pz_date_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_pz_date_entry"));
    info_pz_comment_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info_pz_comment_entry"));
    info_pz_items_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder, "info_pz_items_tree"));
    info_pz_items_list = GTK_LIST_STORE(gtk_builder_get_object(builder, "info_pz_items_list"));
    info_pz_print_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_pz_print_button"));
    info_pz_ok_button = GTK_BUTTON(gtk_builder_get_object(builder, "info_pz_ok_button"));

    info_wz_items_list = GTK_LIST_STORE(gtk_tree_view_get_model(info_wz_items_tree));
    info_pz_items_list = GTK_LIST_STORE(gtk_tree_view_get_model(info_pz_items_tree));
    
    if(!new_type_window || 
        !new_type_name_entry || !new_type_id_entry || !new_type_comment_entry || !new_type_ok_button || !new_item_window || 
        !new_item_type_name_entry || !new_item_type_entry || !new_item_comment_entry || !new_item_ok_button || !new_wz_window || 
        !new_wz_person_entry || !new_wz_date_entry || !new_wz_comment_entry || !new_wz_ok_button || !new_pz_window || 
        !new_pz_person_entry || !new_pz_date_entry || !new_pz_comment_entry || !new_pz_ok_button || !info_type_window || 
        !info_type_name_entry || !info_type_id_entry || !info_type_available_entry || !info_type_unavailable_entry || !info_type_total_entry || 
        !info_type_comment_entry || !info_type_delete_button || !info_type_add_button || !info_type_close_button || !add_items_window || 
        !add_items_type_name_entry || !add_items_type_entry || !add_items_count_spin || !add_items_comment_entry || !add_items_ok_button || 
        !info_item_window || !info_item_id_entry || !info_item_type_entry || !info_item_type_name_entry || !info_item_comment_entry || 
        !info_item_delete_button || !info_item_copy_button || !info_item_close_button || !info_wz_window || !info_wz_id_entry || 
        !info_wz_person_entry || !info_wz_return_date_box || !info_wz_return_date_entry || !info_wz_date_entry || !info_wz_comment_entry || 
        !info_wz_items_tree || !info_wz_items_list || !info_wz_pz_button || !info_wz_print_button || !info_wz_ok_button || 
        !info_pz_window || !info_pz_id_entry || !info_pz_wz_id_entry || !info_pz_person_entry || !info_pz_date_entry || 
        !info_pz_comment_entry || !info_pz_items_tree || !info_pz_items_list || !info_pz_print_button || !info_pz_ok_button ||
        !info_wz_items_list || !info_pz_items_list){
        wicherlog_err("Wrong GtkBuilder file!");
        return false;
    }
    return true;
}
