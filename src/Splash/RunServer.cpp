#include "Splash.h"
#include <boost/thread.hpp>
#define __NOISY

FILE * f;

static void server_thread(){
    char buffer[1024];
    while(fgets(buffer, 1024, f)){
#ifdef __NOISY
        std::cout << buffer;
#endif
    }
}

bool Wicher::Splash::run_server(){
#ifdef WIN
    f = popen(".\\bin\\wicher_local_server.exe", "r");
#elif defined(UNI)
    f = popen("bin/wicher_local_server", "r");
#endif
    if(!f){
        pclose(f);
        return false;
    }
    boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    boost::thread t(&server_thread);
    return true;
}
