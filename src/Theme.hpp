#ifndef THEME_HPP
#define THEME_HPP

#include <gtk/gtk.h>
#include <string>

namespace TabManager {

class Theme {
public:
    static void init();
    static void cleanup();
    static GdkRGBA* getIndicatorColor();
    static void updateFromSettings();

private:
    static GdkRGBA mIndicatorColor;
    static bool mIndicatorColorFromTheme;
    static std::string mIndicatorColorString;
};

} // namespace TabManager

#endif // THEME_HPP 