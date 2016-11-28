AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = wicher
wicher_SOURCES = Toolkit.cpp \
	Config.cpp \
	Dialogger.cpp \
	Splash/RunServer.cpp \
	Splash/Splash.cpp \
	Database.cpp \
	DatabaseQuery.cpp \
	sha256.cpp \
	Main/Builder.cpp \
	Toolbar/ToolbarOptions.cpp \
	Toolbar/ToolbarInfo.cpp \
	SignalWindows/CreateTypeWindow.cpp \
	SignalWindows/CreateItemWindow.cpp \
	SignalWindows/CreateWZWindow.cpp \
	SignalWindows/CreatePZWindow.cpp \
	SignalWindows/InfoTypeWindow.cpp \
	SignalWindows/AddItemsWindow.cpp \
	SignalWindows/InfoItemWindow.cpp \
	SignalWindows/InfoWZWindow.cpp \
	SignalWindows/InfoPZWindow.cpp \
	SignalWindows/SignalWindows.cpp \
	ListsManager/StateManager.cpp \
	ListsManager/Refresh.cpp \
	ListsManager/ColumnModels.cpp \
	ListsManager/Constructor.cpp \
	ListsManager/ListsSignals.cpp \
	ListsManager/ListsEditSignals.cpp \
	PDF/entry_gen.cpp \
	PDF/wz_gen.cpp \
	PDF/pz_gen.cpp \
	Main/Main.cpp \
	main.cpp
wicher_CPPFLAGS = $(gtkmm3_CFLAGS) $(jansson_CFLAGS) $(BOOST_CPPFLAGS) $(AM_CPPFLAGS)
wicher_LDADD = $(gtkmm3_LIBS) $(jansson_LIBS) $(BOOST_LDFLAGS) $(BOOST_THREAD_LIB) $(BOOST_SYSTEM_LIB) -lhpdf
if USE_WINSOCK
	wicher_LDADD += -lws2_32
endif
