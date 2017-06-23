#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "ui.h"
#include "db.h"

#if defined(_WIN32) || defined(WIN32)
#include <direct.h>
#define ChangeCurrentDir(x) _chdir(x)
int GetCurrentDir(char * ownPth, size_t ownPth_size){
	// Will contain exe path
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL){
		// When passing NULL to GetModuleHandle, it returns handle of exe itself
		GetModuleFileName(hModule,ownPth, ownPth_size);
		int x = strlen(ownPth);
		bool found_before = false;
		while(x != 0){
			if(ownPth[x] == '\\'){
				ownPth[x] = '\0';
				if(found_before) break;
				found_before = true;
			}
			--x;
		}
		return 1;
	}else{
		return 0;
	}
}
#elif defined(__unix__)
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
#define ChangeCurrentDir(x) chdir(x)
int GetCurrentDir(char * path, size_t path_size){
	char tmp[256];
	sprintf(tmp, "/proc/%d/exe", getpid());
	ssize_t path_len = path_size - 1;
	int bytes = min(readlink(tmp, path, path_size), path_len);
	if(bytes > 0){
		path[bytes] = '\0';
		if(realpath(path, tmp)){
			strcpy(path, tmp);
		}
		bool found_before = false;
		int x = strlen(path);
                while(x != 0){
                        if(path[x] == '/'){
                                path[x] = '\0';
                                if(found_before) break;
				found_before = true;
                        }
                        --x;
                }

		return bytes;
	}
	return 0;
}
#endif

GtkBuilder * builder;

int main(int argc, char * argv[]){
    char home_dir[4096];
    if(!GetCurrentDir(home_dir, 4096)){
        wicherlog_err("Cannot get program directory!");
        return -1;
    }else if(ChangeCurrentDir(home_dir)){
        wicherlog_err("Cannot chdir to program directory!");
        return -1;
    }
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    void window_set_default_icons();
    if(!splash_init()){
        wicherlog_err("Splash screen error. Exiting.");
        return -1;
    }
    if(!main_init()){
        wicherlog_err("Main window error. Exiting.");
        return -1;
    }
    gtk_builder_connect_signals( builder, NULL );
    splash_show(); //here starts the app
    gtk_main();
    database_cleanup();
    return 0;
}

