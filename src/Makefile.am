AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = wicher
#wicher_SOURCES = Toolkit.cpp \
#	Config.cpp \
#	Dialogger.cpp \
#	Splash/RunServer.cpp \
#	Splash/Splash.cpp \
#	Database.cpp \
#	DatabaseQuery.cpp \
#	sha256.cpp \
#	Main/Builder.cpp \
#	Toolbar/ToolbarOptions.cpp \
#	Toolbar/ToolbarInfo.cpp \
#	SignalWindows/CreateTypeWindow.cpp \
#	SignalWindows/CreateItemWindow.cpp \
#	SignalWindows/CreateWZWindow.cpp \
#	SignalWindows/CreatePZWindow.cpp \
#	SignalWindows/InfoTypeWindow.cpp \
#	SignalWindows/AddItemsWindow.cpp \
#	SignalWindows/InfoItemWindow.cpp \
#	SignalWindows/InfoWZWindow.cpp \
#	SignalWindows/InfoPZWindow.cpp \
#	SignalWindows/SignalWindows.cpp \
#	ListsManager/StateManager.cpp \
#	ListsManager/Refresh.cpp \
#	ListsManager/ColumnModels.cpp \
#	ListsManager/Constructor.cpp \
#	ListsManager/ListsSignals.cpp \
#	ListsManager/ListsEditSignals.cpp \
#	PDF/entry_gen.cpp \
#	PDF/wz_gen.cpp \
#	PDF/pz_gen.cpp \
#	Main/Main.cpp \
#	main.cpp
wicher_SOURCES = \
	sha256.c \
	Toolkit.c \
	Dialogger.c \
	Database.c \
	DatabaseQuery.c \
	Splash/Splash.c \
	Splash/RunServer.c \
	Main/Main.c \
	Toolbar/ToolbarInfo.c \
	Toolbar/ToolbarOptions.c \
	ListsManager/Constructor.c \
	ListsManager/Refresh.c \
	ListsManager/StateManager.c \
	SignalWindows/SignalWindows.c \
	SignalWindows/AddItemsWindow.c \
	SignalWindows/CreateItemWindow.c \
	SignalWindows/CreatePZWindow.c \
	SignalWindows/CreateWZWindow.c \
	SignalWindows/CreateTypeWindow.c \
	SignalWindows/InfoTypeWindow.c \
	SignalWindows/InfoPZWindow.c \
	SignalWindows/InfoWZWindow.c \
	SignalWindows/InfoItemWindow.c \
	main.c
wicher_CPPFLAGS = $(gtk3_CFLAGS) $(jansson_CFLAGS) $(AM_CPPFLAGS)
#wicher_LDFLAGS = -rdynamic
wicher_LDADD = $(gtk3_LIBS) $(jansson_LIBS) -lhpdf
if USE_WINSOCK
	wicher_LDADD += -lws2_32
endif
