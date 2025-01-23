#include "TabManager.hpp"

namespace TabManager {

Tab::Tab(const std::string& id, const std::string& name)
    : mActive(false)
    , mId(id)
    , mName(name)
    , mWidget(nullptr)
    , mNeedsAttention(false)
{
    // Create tab widget
    mWidget = gtk_drawing_area_new();
    gtk_widget_set_size_request(mWidget, 200, 30); // Default size
    
    // Connect draw signal
    g_signal_connect(G_OBJECT(mWidget), "draw",
        G_CALLBACK(onDrawCallback), this);
        
    // Show the widget
    gtk_widget_show(mWidget);
    
    // Get initial color from theme
    applyThemeToTab(this);
}

Tab::~Tab()
{
    if (mWidget)
    {
        gtk_widget_destroy(mWidget);
        mWidget = nullptr;
    }
}

void Tab::activate()
{
    if (!mActive)
    {
        mActive = true;
        onTabActivated(this);
    }
}

void Tab::deactivate()
{
    if (mActive)
    {
        mActive = false;
        onTabDeactivated(this);
    }
}

void Tab::updateStyle()
{
    if (mWidget)
        gtk_widget_queue_draw(mWidget);
}

void Tab::onDraw(cairo_t* cr)
{
    drawTabIndicator(this, cr);
}

gboolean Tab::onDrawCallback(GtkWidget* widget, cairo_t* cr, Tab* tab)
{
    if (tab)
        tab->onDraw(cr);
    return FALSE;
}

} // namespace TabManager 