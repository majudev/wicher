#ifndef UI_H
#define UI_H
#include <gtk/gtk.h>
#include <stdbool.h>
#include <jansson.h>

#include "toolkit.h"
#include "sw.h"

typedef enum { HISTORY_COLUMNS_ID = 0, HISTORY_COLUMNS_DATA = 1 } history_columns;
typedef enum { WZ_COLUMNS_ID = 0, WZ_COLUMNS_DATE = 1, WZ_COLUMNS_PERSON = 2, WZ_COLUMNS_RETURN_DATE = 3, WZ_COLUMNS_COMMENT = 4 } wz_columns;
typedef enum { PZ_COLUMNS_ID = 0, PZ_COLUMNS_WZ_ID = 1, PZ_COLUMNS_DATE = 2, PZ_COLUMNS_PERSON = 3, PZ_COLUMNS_COMMENT = 4 } pz_columns;
typedef enum { TYPE_COLUMNS_ID = 0, TYPE_COLUMNS_NAME = 1, TYPE_COLUMNS_AVAILABLE = 2, TYPE_COLUMNS_UNAVAILABLE = 3, TYPE_COLUMNS_TOTAL = 4, TYPE_COLUMNS_COMMENT = 5, TYPE_COLUMNS_EDITABLE = 6 } type_columns;
typedef enum { ENTRY_COLUMNS_ID = 0, ENTRY_COLUMNS_AVAILABLE = 1, ENTRY_COLUMNS_WZ_ID = 2, ENTRY_COLUMNS_COMMENT = 3, ENTRY_COLUMNS_CHECKBOX = 4, ENTRY_COLUMNS_TYPE = 5 } entry_columns;

extern GtkBuilder * builder;

extern GtkWindow * main_window;

extern GtkTreeView * type_tree;
extern GtkTreeView * wz_tree;
extern GtkTreeView * pz_tree;
extern GtkTreeView * history_tree;
extern GtkListStore * type_list;
extern GtkListStore * wz_list;
extern GtkListStore * pz_list;
extern GtkListStore * history_list;
extern GtkNotebook * state_notepad;

extern void show_dialog_error(GtkWindow * parent, char * primary, char * secondary);
extern void show_dialog_info(GtkWindow * parent, char * primary, char * secondary);
extern void show_dialog_query_error(GtkWindow * parent, json_t * root);
extern void show_dialog_response_error(GtkWindow * parent, json_error_t error);
extern void show_dialog_local_server_error(GtkWindow * parent);
extern void show_dialog_connection_error(GtkWindow * parent);
extern void show_dialog_login_data_error(GtkWindow * parent);
extern void show_dialog_refresh_error();
extern void show_dialog_update_error();
extern void show_dialog_creating_already_shown(GtkWindow * parent);
extern void show_dialog_info_already_shown(GtkWindow * parent);
extern void show_dialog_empty_entries(GtkWindow * parent);

extern bool splash_init();
extern bool splash_show();
extern bool splash_run_server();

extern bool main_init();
extern void main_run();

extern bool options_window_init();
extern bool info_window_init();

extern bool listsmanager_init();
extern bool listsmanager_refresh_types();
extern bool listsmanager_refresh_lists();
extern bool listsmanager_refresh_wz();
extern bool listsmanager_refresh_pz();
extern bool listsmanager_refresh_history();
extern bool listsmanager_refresh_all();

extern void window_set_default_icons();

#endif