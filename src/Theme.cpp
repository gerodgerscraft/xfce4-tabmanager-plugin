#include "Theme.hpp"

namespace TabManager {

// Initialize static members
GdkRGBA Theme::mIndicatorColor = {0.2, 0.4, 0.8, 1.0}; // Default blue color
bool Theme::mIndicatorColorFromTheme = true;
std::string Theme::mIndicatorColorString = "";

void Theme::init()
{
    // Set default indicator color
    updateFromSettings();
}

void Theme::cleanup()
{
    // Nothing to clean up for now
}

GdkRGBA* Theme::getIndicatorColor()
{
    if (mIndicatorColorFromTheme) {
        // Try to get color from current GTK theme
        GtkStyleContext* context = gtk_style_context_new();
        GtkWidgetPath* path = gtk_widget_path_new();
        gtk_widget_path_append_type(path, GTK_TYPE_WINDOW);
        gtk_style_context_set_path(context, path);
        
        GdkRGBA color;
        gtk_style_context_get_color(context, GTK_STATE_FLAG_SELECTED, &color);
        mIndicatorColor = color;
        
        gtk_widget_path_free(path);
        g_object_unref(context);
    }
    else if (!mIndicatorColorString.empty()) {
        // Parse color from string
        gdk_rgba_parse(&mIndicatorColor, mIndicatorColorString.c_str());
    }
    
    return &mIndicatorColor;
}

void Theme::updateFromSettings()
{
    // For now, just use default theme color
    mIndicatorColorFromTheme = true;
    getIndicatorColor();
}

} // namespace TabManager 