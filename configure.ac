AC_PREREQ([2.69])
AC_INIT([xfce4-tabmanager-plugin], [0.1.0], [your-email@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])

# Define package and locale directory
AC_DEFINE([PACKAGE], ["xfce4-tabmanager-plugin"], [Name of package])
AC_DEFINE([LOCALEDIR], ["${datadir}/locale"], [Locale directory])

# NLS support
XDT_I18N

# Programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT

# Check for required packages
PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.24.0])
PKG_CHECK_MODULES([XFCE4PANEL], [libxfce4panel-2.0 >= 4.14.0])
PKG_CHECK_MODULES([XFCE4UI], [libxfce4ui-2 >= 4.14.0])
PKG_CHECK_MODULES([XFCE4UTIL], [libxfce4util-1.0 >= 4.14.0])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    data/Makefile
])
AC_OUTPUT 