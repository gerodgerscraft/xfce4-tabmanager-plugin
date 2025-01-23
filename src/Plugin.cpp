#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "TabManager.hpp"
#include <libxfce4panel/xfce-panel-plugin.h>
#include <libxfce4util/libxfce4util.h>

extern "C" {
    void construct(XfcePanelPlugin* plugin)
    {
        xfce_textdomain(PACKAGE, LOCALEDIR, "UTF-8");
        
        // Initialize the tab manager
        TabManager::init();
        
        // Add to panel
        gtk_container_add(GTK_CONTAINER(plugin), TabManager::mBox);
        
        // Show configure menu
        xfce_panel_plugin_menu_show_configure(plugin);
        
        // Connect signals
        g_signal_connect(G_OBJECT(plugin), "size-changed",
            G_CALLBACK(+[](XfcePanelPlugin* plugin, gint size) {
                // Update size of the plugin
                gtk_widget_set_size_request(TabManager::mBox, size, size);
                TabManager::updateFullBarPosition();
                return TRUE;
            }), nullptr);
            
        g_signal_connect(G_OBJECT(plugin), "orientation-changed",
            G_CALLBACK(+[](XfcePanelPlugin* plugin, GtkOrientation orientation) {
                // Update orientation of the box
                gtk_orientable_set_orientation(GTK_ORIENTABLE(TabManager::mBox), orientation);
                TabManager::updateFullBarPosition();
            }), nullptr);
            
        g_signal_connect(G_OBJECT(plugin), "free-data",
            G_CALLBACK(+[](XfcePanelPlugin* plugin) {
                // Hide full bar before cleanup
                TabManager::hideFullBar();
                
                // Cleanup widgets
                if (TabManager::mFullBarWindow) {
                    gtk_widget_destroy(TabManager::mFullBarWindow);
                    TabManager::mFullBarWindow = nullptr;
                }
                
                if (TabManager::mBox) {
                    gtk_widget_destroy(TabManager::mBox);
                    TabManager::mBox = nullptr;
                }
            }), nullptr);
            
        // Show all widgets
        gtk_widget_show_all(GTK_WIDGET(plugin));
    }
} 