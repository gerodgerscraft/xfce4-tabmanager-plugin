#include "TabManager.hpp"
#include "Theme.hpp"
#include <gdk/gdkx.h>

namespace TabManager
{
    GtkWidget* mBox = nullptr;
    GtkWidget* mFullBar = nullptr;
    gint mFullBarHeight = 900;
    bool mFullBarVisible = false;
    GdkRGBA mFullBarColor = {0, 0, 0, 1};
    GtkWidget* mFullBarWindow = nullptr;

    void init()
    {
        // Create main container box
        mBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_show(mBox);

        // Initialize full bar window
        mFullBarWindow = gtk_window_new(GTK_WINDOW_POPUP);
        gtk_window_set_decorated(GTK_WINDOW(mFullBarWindow), FALSE);
        gtk_window_set_skip_taskbar_hint(GTK_WINDOW(mFullBarWindow), TRUE);
        gtk_window_set_skip_pager_hint(GTK_WINDOW(mFullBarWindow), TRUE);
        gtk_window_set_keep_above(GTK_WINDOW(mFullBarWindow), TRUE);
        gtk_widget_set_size_request(mFullBarWindow, 10, mFullBarHeight);

        // Create drawing area for full bar
        mFullBar = gtk_drawing_area_new();
        gtk_container_add(GTK_CONTAINER(mFullBarWindow), mFullBar);
        g_signal_connect(G_OBJECT(mFullBar), "draw",
            G_CALLBACK(onFullBarDraw), nullptr);

        // Initialize theme
        Theme::init();
    }

    void updateFullBarPosition()
    {
        if (!mFullBarVisible || !mFullBarWindow)
            return;

        GdkScreen* screen = gdk_screen_get_default();
        GdkWindow* root = gdk_screen_get_root_window(screen);
        gint x, y;
        gdk_window_get_position(root, &x, &y);
        gtk_window_move(GTK_WINDOW(mFullBarWindow), x, y);
    }

    void updateFullBarColor(const GdkRGBA* color)
    {
        if (color)
            mFullBarColor = *color;
        if (mFullBar)
            gtk_widget_queue_draw(mFullBar);
    }

    void showFullBar()
    {
        if (!mFullBarVisible && mFullBarWindow)
        {
            gtk_widget_show_all(mFullBarWindow);
            mFullBarVisible = true;
            updateFullBarPosition();
        }
    }

    void hideFullBar()
    {
        if (mFullBarVisible && mFullBarWindow)
        {
            gtk_widget_hide(mFullBarWindow);
            mFullBarVisible = false;
        }
    }

    gboolean onFullBarDraw(GtkWidget* widget, cairo_t* cr, gpointer data)
    {
        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);

        // Draw the full bar with current color
        cairo_set_source_rgba(cr, 
            mFullBarColor.red,
            mFullBarColor.green,
            mFullBarColor.blue,
            mFullBarColor.alpha);
        cairo_rectangle(cr, 0, 0, allocation.width, allocation.height);
        cairo_fill(cr);

        return FALSE;
    }

    void onTabActivated(Tab* tab)
    {
        if (tab)
        {
            updateFullBarColor(&tab->mColor);
            showFullBar();
        }
    }

    void onTabDeactivated(Tab* tab)
    {
        hideFullBar();
    }

    void updateTabStyle(Tab* tab)
    {
        if (tab)
            tab->updateStyle();
    }

    void drawTabIndicator(Tab* tab, cairo_t* cr)
    {
        if (tab && tab->mActive)
        {
            GtkAllocation allocation;
            gtk_widget_get_allocation(tab->mWidget, &allocation);
            
            cairo_set_source_rgba(cr, 
                tab->mColor.red,
                tab->mColor.green,
                tab->mColor.blue,
                tab->mColor.alpha);
            cairo_rectangle(cr, 0, 0, allocation.width, 2);
            cairo_fill(cr);
        }
    }

    GdkRGBA getTabColor(const std::string& tabId, const std::string& tabName)
    {
        // For now, use theme's indicator color
        return *Theme::getIndicatorColor();
    }

    void applyThemeToTab(Tab* tab)
    {
        if (tab)
        {
            tab->mColor = getTabColor(tab->mId, tab->mName);
            updateTabStyle(tab);
        }
    }
} 