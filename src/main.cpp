#include <iostream>
#include <gtkmm.h>
#include "Splash.h"
#include "Main.h"
#include "Database.h"

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
#define ChangeCurrentDir(x) chdir(x)
int GetCurrentDir(char * path, size_t path_size){
	char tmp[256];
	sprintf(tmp, "/proc/%d/exe", getpid());
	ssize_t path_len = path_size - 1;
	int bytes = std::min(readlink(tmp, path, path_size), path_len);
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

int main(int argc, char * argv[]){
    char home_dir[4096];
    if(!GetCurrentDir(home_dir, 4096)){
        std::cout << "Cannot get program directory!" << std::endl;
        return -1;
    }else if(ChangeCurrentDir(home_dir)){
        std::cout << "Cannot chdir to program directory!" << std::endl;
        return -1;
    }
    Wicher::Splash * splash = new Wicher::Splash(argc, argv);
    if(splash->show()){
        delete splash;
        Wicher::Main main(argc, argv);
        main.run();
        return 0;
    }
    delete splash;
    return -1;
}

