#ifndef SIGNALWINDOWS_H
#define SIGNALWINDOWS_H
#include "Toolkit.h"
#include "Database.h"
#include "Dialogger.h"
#include "Builder.h"
#include "ColumnModels.h"
#include "Config.h"

namespace Wicher{
class WZItemsListColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        WZItemsListColumns();
        Gtk::TreeModelColumn<int> id;
        Gtk::TreeModelColumn<Glib::ustring> type;
        Gtk::TreeModelColumn<Glib::ustring> type_name;
};

class SignalWindows{
    public:
        SignalWindows();
        void show_create_type_window();
        void show_create_item_window();
        void show_create_wz_window();
        void show_create_pz_window(int wz_id);

        void show_info_type_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void show_add_items_window(Glib::ustring type_name, Glib::ustring type);
        void show_info_item_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void show_info_wz_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        void show_info_pz_window(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

    private:
        bool is_shown_create_type_window();
        bool is_shown_create_item_window();
        bool is_shown_create_wz_window();
        bool is_shown_create_pz_window();

        bool is_shown_info_type_window();
        bool is_shown_add_items_window();
        bool is_shown_info_item_window();
        bool is_shown_info_wz_window();
        bool is_shown_info_pz_window();

        void on_new_type_ok_button_clicked();
        void on_new_item_ok_button_clicked();
        void on_new_wz_ok_button_clicked();
        void on_new_pz_ok_button_clicked();

        void on_info_type_delete_button_clicked();
        void on_info_type_add_button_clicked();
        void on_info_type_close_button_clicked();
        void on_add_items_ok_button_clicked();
        void on_info_item_delete_button_clicked();
        void on_info_item_copy_button_clicked();
        void on_info_item_close_button_clicked();
        void on_info_wz_pz_button_clicked();
        void on_info_wz_print_button_clicked();
        void on_info_wz_ok_button_clicked();
        void on_info_pz_print_button_clicked();
        void on_info_pz_ok_button_clicked();

        Glib::RefPtr<Gtk::Builder> builder;
        Gtk::Notebook * state_notepad;

        ColumnModels::EntryColumns entry_columns;
        ColumnModels::TypeColumns type_columns;
        Gtk::TreeView * type_tree;
        Glib::RefPtr<Gtk::ListStore> type_list;

        ColumnModels::WZColumns wz_columns;
        ColumnModels::PZColumns pz_columns;
        WZItemsListColumns wz_items_list_columns;

        Gtk::TreeView * pz_tree;
        Glib::RefPtr<Gtk::ListStore> pz_list;

        Gtk::Window * new_type_window;
        Gtk::Entry * new_type_name_entry;
        Gtk::Entry * new_type_id_entry;
        Gtk::Entry * new_type_comment_entry;
        Gtk::Button * new_type_ok_button;

        Gtk::Window * new_item_window;
        Gtk::Entry * new_item_type_name_entry;
        Gtk::Entry * new_item_type_entry;
        Gtk::Entry * new_item_comment_entry;
        Gtk::Button * new_item_ok_button;

        Gtk::Window * new_wz_window;
        Gtk::Entry * new_wz_person_entry;
        Gtk::Calendar * new_wz_date_entry;
        Gtk::Entry * new_wz_comment_entry;
        Gtk::Button * new_wz_ok_button;

        Gtk::Window * new_pz_window;
        Gtk::Entry * new_pz_wz_id_entry;
        Gtk::Entry * new_pz_person_entry;
        Gtk::Calendar * new_pz_date_entry;
        Gtk::Entry * new_pz_comment_entry;
        Gtk::Button * new_pz_ok_button;

        Gtk::Window * info_type_window;
        Gtk::Entry * info_type_name_entry;
        Gtk::Entry * info_type_id_entry;
        Gtk::Entry * info_type_available_entry;
        Gtk::Entry * info_type_unavailable_entry;
        Gtk::Entry * info_type_total_entry;
        Gtk::Entry * info_type_comment_entry;
        Gtk::Button * info_type_delete_button;
        Gtk::Button * info_type_add_button;
        Gtk::Button * info_type_close_button;

        Gtk::Window * add_items_window;
        Gtk::Entry * add_items_type_name_entry;
        Gtk::Entry * add_items_type_entry;
        Gtk::SpinButton * add_items_count_spin;
        Gtk::Entry * add_items_comment_entry;
        Gtk::Button * add_items_ok_button;

        Gtk::Window * info_item_window;
        Gtk::Entry * info_item_id_entry;
        Gtk::Entry * info_item_type_name_entry;
        Gtk::Entry * info_item_type_entry;
        Gtk::Entry * info_item_comment_entry;
        Gtk::Button * info_item_delete_button;
        Gtk::Button * info_item_copy_button;
        Gtk::Button * info_item_close_button;

        Gtk::Window * info_wz_window;
        Gtk::Entry * info_wz_id_entry;
        Gtk::Entry * info_wz_person_entry;
        Gtk::Entry * info_wz_date_entry;
        Gtk::Box * info_wz_return_date_box;
        Gtk::Entry * info_wz_return_date_entry;
        Gtk::Entry * info_wz_comment_entry;
        Gtk::TreeView * info_wz_items_tree;
        Glib::RefPtr<Gtk::ListStore> info_wz_items_list;
        Gtk::Button * info_wz_pz_button;
        Gtk::Button * info_wz_print_button;
        Gtk::Button * info_wz_ok_button;

        Gtk::Window * info_pz_window;
        Gtk::Entry * info_pz_id_entry;
        Gtk::Entry * info_pz_wz_id_entry;
        Gtk::Entry * info_pz_person_entry;
        Gtk::Entry * info_pz_date_entry;
        Gtk::Entry * info_pz_comment_entry;
        Gtk::TreeView * info_pz_items_tree;
        Glib::RefPtr<Gtk::ListStore> info_pz_items_list;
        Gtk::Button * info_pz_print_button;
        Gtk::Button * info_pz_ok_button;
};
}

#endif // SIGNALWINDOWS_H
