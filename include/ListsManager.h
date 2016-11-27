#ifndef LISTSMANAGER_H
#define LISTSMANAGER_H
#include <gtkmm.h>
#include <string>
#include <vector>
#include "SignalWindows.h"
#include "Toolkit.h"
#include "Database.h"
#include "Dialogger.h"
#include "Builder.h"
#include "Config.h"
#include "ColumnModels.h"

namespace Wicher{
class ListsManager{
    public:
        ListsManager();
        ~ListsManager();
        bool refresh_types();
        bool refresh_lists();
        bool refresh_wz();
        bool refresh_pz();
        bool refresh_history();
        bool refresh_all();
        void refresh_all_void();

    private:
        void on_new_type_ok_button_clicked();
        void on_new_item_ok_button_clicked();
        void on_add_items_ok_button_clicked();
        void on_new_wz_ok_button_clicked();
        void on_new_pz_ok_button_clicked();
        void on_info_type_close_delete_button_clicked();
        void on_info_item_close_copy_delete_button_clicked();
        void on_info_wz_close_button_clicked();
        void on_info_pz_close_button_clicked();

        void on_wz_date_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_wz_person_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_wz_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_pz_date_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_pz_person_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_pz_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);

        void on_type_name_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_type_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_item_comment_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_item_checkbox_toggled(const Glib::ustring& path);

        Glib::RefPtr<Gtk::Builder> builder;
        SignalWindows * sw;
        Gtk::Button * new_type_ok_button;
        Gtk::Button * new_item_ok_button;
        Gtk::Button * new_wz_ok_button;
        Gtk::Button * new_pz_ok_button;
        Gtk::Button * info_type_close_button;
        Gtk::Button * info_type_delete_button;
        Gtk::Button * info_item_close_button;
        Gtk::Button * info_item_copy_button;
        Gtk::Button * info_item_delete_button;
        Gtk::Button * info_wz_ok_button;
        Gtk::Button * info_pz_ok_button;

        Gtk::Notebook * state_notepad;
        Gtk::Button * create_type_button;
        Gtk::Button * create_wz_button;

        ColumnModels::WZColumns wz_columns;
        Gtk::TreeView * wz_tree;
        Glib::RefPtr<Gtk::ListStore> wz_list;

        ColumnModels::PZColumns pz_columns;
        Gtk::TreeView * pz_tree;
        Glib::RefPtr<Gtk::ListStore> pz_list;

        ColumnModels::HistoryColumns history_columns;
        Gtk::TreeView * history_tree;
        Glib::RefPtr<Gtk::ListStore> history_list;

        ColumnModels::TypeColumns type_columns;
        Gtk::TreeView * type_tree;
        Glib::RefPtr<Gtk::ListStore> type_list;

        std::map<Glib::ustring, std::string> type_map;

        ColumnModels::EntryColumns entry_columns;
};
}

#endif // SPLASH_H
