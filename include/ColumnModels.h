#ifndef COLUMNMODELS_H_INCLUDED
#define COLUMNMODELS_H_INCLUDED

namespace Wicher{
class ColumnModels{
    public:
        class WZColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                WZColumns();
                Gtk::TreeModelColumn<int> id;
                Gtk::TreeModelColumn<Glib::ustring> date;
                Gtk::TreeModelColumn<Glib::ustring> person;
                Gtk::TreeModelColumn<Glib::ustring> return_date;
                Gtk::TreeModelColumn<Glib::ustring> comment;
        };
        class PZColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                PZColumns();
                Gtk::TreeModelColumn<int> id;
                Gtk::TreeModelColumn<int> wz_id;
                Gtk::TreeModelColumn<Glib::ustring> date;
                Gtk::TreeModelColumn<Glib::ustring> person;
                Gtk::TreeModelColumn<Glib::ustring> comment;
        };
        class HistoryColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                HistoryColumns();
                Gtk::TreeModelColumn<int> id;
                Gtk::TreeModelColumn<Glib::ustring> data;
        };
        class TypeColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                TypeColumns();
                Gtk::TreeModelColumn<Glib::ustring> id;
                Gtk::TreeModelColumn<Glib::ustring> name;
                Gtk::TreeModelColumn<int> available;
                Gtk::TreeModelColumn<int> unavailable;
                Gtk::TreeModelColumn<int> total;
                Gtk::TreeModelColumn<Glib::ustring> comment;
        };
        class EntryColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                EntryColumns();
                Gtk::TreeModelColumn<int> id;
                Gtk::TreeModelColumn<bool> available;
                Gtk::TreeModelColumn<Glib::ustring> wz_id;
                Gtk::TreeModelColumn<Glib::ustring> comment;
                Gtk::TreeModelColumn<bool> checkbox;
                Gtk::TreeModelColumn<Glib::ustring> type;
        };
};
}

#endif // COLUMNMODELS_H_INCLUDED
