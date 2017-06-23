#include "ui.h"
#include <stdio.h>

#ifdef WIN
#include <windows.h>
bool splash_run_server(){
    return ((int)ShellExecute(NULL, "open", ".\\bin\\wicher_local_server.exe", NULL, NULL, SW_SHOW)) > 32;
}
#elif defined(UNI)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
bool splash_run_server(){
    pid_t pid = fork();
    if(pid < 0){
        wicherlog_err("Cannot fork, error code: %d", errno);
        return false;
    }else if(pid == 0){
        system("bin/wicher_local_server");
        exit(0);
    }else if(pid > 0){
        usleep(1000);
        int wstatus;
        waitpid(pid, &wstatus, WNOHANG);
        if(WIFEXITED(wstatus)){
            wicherlog("Server process hasn't correctly, ignoring.");
	    }else wicherlog("Server process started correctly.");
        return true;
    }
}
#endif