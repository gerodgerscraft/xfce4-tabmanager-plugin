plugindir = $(libdir)/xfce4/panel/plugins
plugin_LTLIBRARIES = libtabmanager.la

libtabmanager_la_SOURCES = \
    Plugin.cpp \
    TabManager.cpp \
    TabManager.hpp \
    Theme.cpp \
    Theme.hpp \
    Tab.cpp

libtabmanager_la_CPPFLAGS = \
    -I$(top_srcdir) \
    $(GTK_CFLAGS) \
    $(XFCE4PANEL_CFLAGS) \
    $(XFCE4UI_CFLAGS) \
    $(XFCE4UTIL_CFLAGS)

libtabmanager_la_LIBADD = \
    $(GTK_LIBS) \
    $(XFCE4PANEL_LIBS) \
    $(XFCE4UI_LIBS) \
    $(XFCE4UTIL_LIBS)

libtabmanager_la_LDFLAGS = \
    -avoid-version \
    -module \
    -no-undefined \
    -export-symbols-regex '^construct' 