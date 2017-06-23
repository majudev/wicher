#include "ui.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

//void listsmanager_on_type_name_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data);
//void listsmanager_on_type_comment_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data);
void listsmanager_on_item_comment_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data);
void listsmanager_on_item_checkbox_toggled(GtkCellRendererToggle * cell_renderer, gchar * path_string, gpointer user_data);

bool listsmanager_refresh_types(){
    gtk_list_store_clear(type_list);

    json_error_t error;
    json_t * root = json_loads(database_run(database_query_get_types()), 0, &error);
    if(!root){
        wicherlog("JSON error when refreshing types: %s", error.text);
        wicherlog("\tSource: %s", error.source);
        wicherlog("\tLine: %d", error.line);
        wicherlog("\tColumn: %d", error.column);
        wicherlog("\tPosition [bytes]: %d", error.position);
    }else{
        const char * response_str = json_string_value(json_object_get(root, "response"));
        if(response_str){
            if(!strcmp(response_str, "ok")){
                json_t * array = json_object_get(root, "types");
                if(array){
                    size_t size = json_array_size(array);
                    size_t x = 0;
                    while(x != size){
                        json_t * obj = json_array_get(array, x);
                        const char * id_str = json_string_value(json_object_get(obj, "id"));
                        const char * name_str = json_string_value(json_object_get(obj, "name"));
                        int unavailable = json_integer_value(json_object_get(obj, "unavailable"));
                        int total = json_integer_value(json_object_get(obj, "total"));
                        const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                        if(id_str && name_str && comment_str){
                            GtkTreeIter iter;
                            gtk_list_store_append(type_list, &iter);
                            gtk_list_store_set(type_list, &iter, TYPE_COLUMNS_ID, id_str,
                                              TYPE_COLUMNS_NAME, name_str,
                                              TYPE_COLUMNS_AVAILABLE, total-unavailable,
                                              TYPE_COLUMNS_UNAVAILABLE, unavailable,
                                              TYPE_COLUMNS_TOTAL, total,
                                              TYPE_COLUMNS_COMMENT, comment_str,
                                              TYPE_COLUMNS_EDITABLE, true, -1);
                        }
                        ++x;
                    }
                    free(root);
                    return true;
                }
            }else wicherlog("Error when refreshing types. Server's response: %s", response_str);
        }
    }

    free(root);
    return false;
}

bool listsmanager_refresh_lists(){
    int pages = gtk_notebook_get_n_pages(state_notepad);
    int x = 1;
    while(x != pages){
        gtk_notebook_remove_page(state_notepad, 1);
        ++x;
    }

    GtkTreeIter iter;
    bool valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(type_list), &iter);
    while(valid){
        const char * type_id;
        const char * name;
        gtk_tree_model_get (GTK_TREE_MODEL(type_list), &iter,
                            TYPE_COLUMNS_ID, &type_id,
                            TYPE_COLUMNS_NAME, &name, -1);
        GtkListStore * list = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_STRING);

        json_error_t error;
        json_t * root = json_loads(database_run(database_query_get_items(type_id)), 0, &error);
        if(!root){
            wicherlog("JSON error when refreshing types: %s", error.text);
            wicherlog("\tSource: %s", error.source);
            wicherlog("\tLine: %d", error.line);
            wicherlog("\tColumn: %d", error.column);
            wicherlog("\tPosition [bytes]: %d", error.position);
        }else{
            const char * response_str = json_string_value(json_object_get(root, "response"));
            if(response_str){
                if(!strcmp(response_str, "ok")){
                    json_t * array = json_object_get(root, "items");
                    if(array){
                        size_t size = json_array_size(array);
                        size_t x = 0;
                        while(x != size){
                            json_t * obj = json_array_get(array, x);
                            int id = json_integer_value(json_object_get(obj, "id"));
                            bool available = json_boolean_value(json_object_get(obj, "available"));
                            int wz_id = json_integer_value(json_object_get(obj, "wz_id"));
                            const char * comment_str = json_string_value(json_object_get(obj, "comment"));
                            if(comment_str){
                                GtkTreeIter iter2;
                                gtk_list_store_append(list, &iter2);
                                gtk_list_store_set(list, &iter2, ENTRY_COLUMNS_ID, id,
                                                   ENTRY_COLUMNS_AVAILABLE, (gboolean)available,
                                                   ENTRY_COLUMNS_COMMENT, comment_str,
                                                   ENTRY_COLUMNS_CHECKBOX, (gboolean)false,
                                                   ENTRY_COLUMNS_TYPE, type_id, -1);
                                if(available){
                                    gtk_list_store_set(list, &iter2, ENTRY_COLUMNS_WZ_ID, "", -1);
                                }else{
                                    char wz_id_str[10];
                                    sprintf(wz_id_str, "%d", wz_id);
                                    gtk_list_store_set(list, &iter2, ENTRY_COLUMNS_WZ_ID, wz_id_str, -1);
                                }
                            }
                            ++x;
                        }
                    }
                }else wicherlog("Error when refreshing %s items. Server's response: %s", type_id, response_str);
            }
        }
        free(root);

        GtkTreeView * view = GTK_TREE_VIEW(gtk_tree_view_new_with_model(GTK_TREE_MODEL(list)));
        GtkWidget * label = gtk_label_new(name);
        
        GtkCellRenderer * renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn * column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ENTRY_COLUMNS_ID, NULL);
        gtk_tree_view_column_set_expand(column, true);
        g_object_set(G_OBJECT(renderer), "editable", false);
        gtk_tree_view_append_column (GTK_TREE_VIEW (view), column);
        
        renderer = gtk_cell_renderer_toggle_new();
        column = gtk_tree_view_column_new_with_attributes("Dostępność", renderer, "active", ENTRY_COLUMNS_AVAILABLE, NULL);
        gtk_tree_view_column_set_expand(column, false);
        g_object_set(G_OBJECT(renderer), "activatable", false);
        g_signal_connect(renderer, "toggled", G_CALLBACK(listsmanager_on_item_checkbox_toggled), NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (view), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID Wydania", renderer, "text", ENTRY_COLUMNS_WZ_ID, NULL);
        gtk_tree_view_column_set_expand(column, true);
        g_object_set(G_OBJECT(renderer), "editable", false);
        gtk_tree_view_append_column (GTK_TREE_VIEW (view), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Komentarz", renderer, "text", ENTRY_COLUMNS_COMMENT, NULL);
        gtk_tree_view_column_set_expand(column, true);
        g_object_set(G_OBJECT(renderer), "editable", true);
        g_signal_connect(renderer, "edited", G_CALLBACK(listsmanager_on_item_comment_edited), NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (view), column);
        
        renderer = gtk_cell_renderer_toggle_new();
        column = gtk_tree_view_column_new_with_attributes("Do WZ", renderer, "active", ENTRY_COLUMNS_CHECKBOX, "activatable", ENTRY_COLUMNS_AVAILABLE, NULL);
        gtk_tree_view_column_set_expand(column, false);
        g_signal_connect(renderer, "toggled", G_CALLBACK(listsmanager_on_item_checkbox_toggled), NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (view), column);
        
        g_signal_connect(view, "row-activated", G_CALLBACK(signalwindows_show_info_item_window), NULL);

        gtk_tree_view_set_grid_lines(view, GTK_TREE_VIEW_GRID_LINES_BOTH);

        GtkWidget * box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        GtkWidget * button = gtk_button_new_with_label("Dodaj");
        g_signal_connect(button, "clicked", G_CALLBACK(signalwindows_show_create_item_window), NULL);

        GtkWidget * scrolled_win = gtk_scrolled_window_new(NULL, NULL);
        gtk_container_add(GTK_CONTAINER(scrolled_win), GTK_WIDGET(view));
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled_win), GTK_SHADOW_NONE);

        gtk_box_pack_start(GTK_BOX(box), scrolled_win, true, true, 0);
        gtk_box_pack_start(GTK_BOX(box), button, false, false, 0);

        gtk_notebook_append_page(state_notepad, box, label);
        
        valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(type_list), &iter);
    }
    gtk_widget_show_all(GTK_WIDGET(state_notepad));
    return true;
}

void listsmanager_on_type_name_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data){
    if(new_text[0]) return;
    GtkTreePath * path = gtk_tree_path_new_from_string(path_string);
    GtkTreeIter iter;
    bool res = gtk_tree_model_get_iter(GTK_TREE_MODEL(type_list), &iter, path);
    gtk_tree_path_free(path);
    if(res){
        const char * id;
        gtk_tree_model_get (GTK_TREE_MODEL(type_list), &iter,
                            TYPE_COLUMNS_ID, &id, -1);
        char * response = database_run(database_query_change_type(id, new_text, false, ""));
        json_error_t error;
        json_t * root = json_loads(response, 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!json_is_string(r) || strcmp(json_string_value(r), "ok")){
            show_dialog_update_error();
        }else{
            gtk_list_store_set(type_list, &iter,
                               TYPE_COLUMNS_NAME, new_text, -1);
            if(!listsmanager_refresh_lists()) show_dialog_refresh_error();
        }
        free(root);
    }
}

void listsmanager_on_type_comment_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data){
    GtkTreePath * path = gtk_tree_path_new_from_string(path_string);
    GtkTreeIter iter;
    bool res = gtk_tree_model_get_iter(GTK_TREE_MODEL(type_list), &iter, path);
    gtk_tree_path_free(path);
    if(res){
        const char * id;
        gtk_tree_model_get (GTK_TREE_MODEL(type_list), &iter,
                            TYPE_COLUMNS_ID, &id, -1);
        char * response = database_run(database_query_change_type(id, "", true, new_text));
        json_error_t error;
        json_t * root = json_loads(response, 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!json_is_string(r) || strcmp(json_string_value(r), "ok")){
            show_dialog_update_error();
        }else{
            gtk_list_store_set(type_list, &iter,
                               TYPE_COLUMNS_COMMENT, new_text, -1);
            if(!listsmanager_refresh_lists()) show_dialog_refresh_error();
        }
        free(root);
    }
}

void listsmanager_on_item_comment_edited(GtkCellRendererText * renderer, gchar * path_string, gchar * new_text, gpointer user_data){
    GtkTreePath * path = gtk_tree_path_new_from_string(path_string);
    const char * label = gtk_notebook_get_tab_label_text(state_notepad, gtk_notebook_get_nth_page(state_notepad, gtk_notebook_get_current_page(state_notepad)));
    GtkWidget * box = gtk_notebook_get_nth_page(state_notepad, gtk_notebook_get_current_page(state_notepad));
    GList * box_children = gtk_container_get_children(GTK_CONTAINER(box));
    GtkScrolledWindow * swin_widget = GTK_SCROLLED_WINDOW(g_list_nth_data(box_children, 0));
    g_list_free(box_children);
    GList * swin_children = gtk_container_get_children(GTK_CONTAINER(swin_widget));
    GtkTreeView * tree_widget = GTK_TREE_VIEW(g_list_nth_data(swin_children, 0));
    g_list_free(swin_children);
    GtkListStore * list = GTK_LIST_STORE(gtk_tree_view_get_model(tree_widget));
    GtkTreeIter iter;
    bool res = gtk_tree_model_get_iter(GTK_TREE_MODEL(list), &iter, path);
    gtk_tree_path_free(path);
    if(res){
        int id;
        const char * type;
        gtk_tree_model_get (GTK_TREE_MODEL(list), &iter,
                            ENTRY_COLUMNS_ID, &id, 
                            ENTRY_COLUMNS_TYPE, &type, -1);
        char * response = database_run(database_query_change_item(id, type, new_text));
        json_error_t error;
        json_t * root = json_loads(response, 0, &error);
        json_t * r = json_object_get(root, "response");
        if(!json_is_string(r) || strcmp(json_string_value(r), "ok")){
            show_dialog_update_error();
        }else{
            gtk_list_store_set(list, &iter,
                               ENTRY_COLUMNS_COMMENT, new_text, -1);
        }
        free(root);
    }
}

void listsmanager_on_item_checkbox_toggled(GtkCellRendererToggle * cell_renderer, gchar * path_string, gpointer user_data){
    GtkTreePath * path = gtk_tree_path_new_from_string(path_string);
    const char * label = gtk_notebook_get_tab_label_text(state_notepad, gtk_notebook_get_nth_page(state_notepad, gtk_notebook_get_current_page(state_notepad)));
    GtkWidget * box = gtk_notebook_get_nth_page(state_notepad, gtk_notebook_get_current_page(state_notepad));
    GList * box_children = gtk_container_get_children(GTK_CONTAINER(box));
    GtkScrolledWindow * swin_widget = GTK_SCROLLED_WINDOW(g_list_nth_data(box_children, 0));
    g_list_free(box_children);
    GList * swin_children = gtk_container_get_children(GTK_CONTAINER(swin_widget));
    GtkTreeView * tree_widget = GTK_TREE_VIEW(g_list_nth_data(swin_children, 0));
    g_list_free(swin_children);
    GtkListStore * list = GTK_LIST_STORE(gtk_tree_view_get_model(tree_widget));
    GtkTreeIter iter;
    bool res = gtk_tree_model_get_iter(GTK_TREE_MODEL(list), &iter, path);
    gtk_tree_path_free(path);
    if(res){
        gboolean available;
        gboolean checkbox;
        gtk_tree_model_get (GTK_TREE_MODEL(list), &iter,
                            ENTRY_COLUMNS_AVAILABLE, &available,
                            ENTRY_COLUMNS_CHECKBOX, &checkbox, -1);
        if(available){
            gtk_list_store_set(list, &iter, ENTRY_COLUMNS_CHECKBOX, !checkbox, -1);
        }
    }
}
