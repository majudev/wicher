AM_CPPFLAGS = -I$(top_srcdir)/include/server
bin_PROGRAMS = wicher_local_server
wicher_local_server_SOURCES = ConnectionManager.cpp \
	DatabaseCreator.cpp \
	DatabaseDropper.cpp \
	DatabaseGetter.cpp \
	DatabaseHelper.cpp \
	DatabaseManager.cpp \
	DatabaseUpdater.cpp \
	Log.cpp \
	_main.cpp \
	Main.cpp \
	Makefile.am \
	MessageParser.cpp \
	Toolkit.cpp
wicher_local_server_CPPFLAGS = $(jansson_CFLAGS) $(AM_CPPFLAGS)
wicher_local_server_LDADD = $(jansson_LIBS)
if USE_WINSOCK
        wicher_local_server_LDADD += -lws2_32
endif
