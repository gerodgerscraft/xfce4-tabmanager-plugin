#ifndef TABMANAGER_HPP
#define TABMANAGER_HPP

#include <gtk/gtk.h>
#include <memory>
#include <string>
#include "Theme.hpp"

// Forward declarations
namespace TabManager {
    void onTabActivated(class Tab* tab);
    void onTabDeactivated(class Tab* tab);
    void updateTabStyle(class Tab* tab);
    void drawTabIndicator(class Tab* tab, cairo_t* cr);
    void applyThemeToTab(class Tab* tab);
}

namespace TabManager {

class Tab {
public:
    Tab(const std::string& id, const std::string& name);
    ~Tab();
    void activate();
    void deactivate();
    void updateStyle();
    GtkWidget* getWidget() { return mWidget; }
    
    bool mActive;
    std::string mId;
    std::string mName;
    GtkWidget* mWidget;
    GdkRGBA mColor;
    
private:
    void onDraw(cairo_t* cr);
    static gboolean onDrawCallback(GtkWidget* widget, cairo_t* cr, Tab* tab);

    bool mNeedsAttention;

    friend void onTabActivated(Tab* tab);
    friend void onTabDeactivated(Tab* tab);
    friend void updateTabStyle(Tab* tab);
    friend void drawTabIndicator(Tab* tab, cairo_t* cr);
    friend void applyThemeToTab(Tab* tab);
};

void onTabActivated(Tab* tab);
void onTabDeactivated(Tab* tab);
void updateTabStyle(Tab* tab);
void drawTabIndicator(Tab* tab, cairo_t* cr);
void applyThemeToTab(Tab* tab);

// Shared with docklike
extern GtkWidget* mBox;
extern GtkWidget* mFullBar;
extern gint mFullBarHeight;
extern bool mFullBarVisible;
extern GdkRGBA mFullBarColor;
extern GtkWidget* mFullBarWindow;

void init();
void updateFullBarPosition();
void updateFullBarColor(const GdkRGBA* color);
void showFullBar();
void hideFullBar();
gboolean onFullBarDraw(GtkWidget* widget, cairo_t* cr, gpointer data);

// Theme integration
GdkRGBA getTabColor(const std::string& tabId, const std::string& tabName);

} // namespace TabManager

#endif // TABMANAGER_HPP 