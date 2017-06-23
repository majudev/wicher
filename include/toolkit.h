#ifndef TOOLKIT_H
#define TOOLKIT_H

#if defined(_WIN32) || defined(WIN32)
#define WIN
#elif defined(__unix__)
#define UNI
#endif

extern void wicherlog(char * format, ...);
extern void wicherlog_err(char * format, ...);

#endif