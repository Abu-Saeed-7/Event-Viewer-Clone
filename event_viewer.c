#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *button_name = (const gchar *)data;
    g_print("Button clicked: %s\n", button_name);
}

static void on_menu_item_selected(GtkWidget *widget, gpointer data) {
    const gchar *item_name = (const gchar *)data;
    g_print("Selected: %s\n", item_name);
}

static void toggle_side_bar(GtkWidget *widget, gpointer data) {
    GtkWidget *sidebar = (GtkWidget *)data;
    gboolean visible = gtk_widget_get_visible(sidebar);
    gtk_widget_set_visible(sidebar, !visible);
    
    if (visible) {
        g_print("Menu bar hidden\n");
    } else {
        g_print("Menu bar shown\n");
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Event Viewer Clone");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
    
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), main_box);
    
    GtkWidget *menu_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(menu_bar, 5);
    gtk_widget_set_margin_end(menu_bar, 5);
    gtk_box_append(GTK_BOX(main_box), menu_bar);
    
    GtkWidget *file_btn = gtk_button_new_with_label("File");
    GtkWidget *action_btn = gtk_button_new_with_label("Action");
    GtkWidget *view_btn = gtk_button_new_with_label("View");
    GtkWidget *help_btn = gtk_button_new_with_label("Help");
    
    gtk_box_append(GTK_BOX(menu_bar), file_btn);
    gtk_box_append(GTK_BOX(menu_bar), action_btn);
    gtk_box_append(GTK_BOX(menu_bar), view_btn);
    gtk_box_append(GTK_BOX(menu_bar), help_btn);

    g_signal_connect(file_btn, "clicked", G_CALLBACK(on_menu_item_selected), "File");
    g_signal_connect(action_btn, "clicked", G_CALLBACK(on_menu_item_selected), "Action");
    g_signal_connect(view_btn, "clicked", G_CALLBACK(on_menu_item_selected), "View");
    g_signal_connect(help_btn, "clicked", G_CALLBACK(on_menu_item_selected), "Help");
    
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX(main_box), separator);

    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(toolbar, 5);
    gtk_widget_set_margin_end(toolbar, 5);
    gtk_widget_set_margin_top(toolbar, 5);
    gtk_widget_set_margin_bottom(toolbar, 5);
    gtk_box_append(GTK_BOX(main_box), toolbar);
    
    GtkWidget *back_btn = gtk_button_new_with_label("Back");
    GtkWidget *forward_btn = gtk_button_new_with_label("Forward");
    GtkWidget *find_btn = gtk_button_new_with_label("Find");
    GtkWidget *toggle_sidebar_btn = gtk_button_new_with_label("Show/Hide sidebar");
    
    gtk_box_append(GTK_BOX(toolbar), back_btn);
    gtk_box_append(GTK_BOX(toolbar), forward_btn);
    gtk_box_append(GTK_BOX(toolbar), find_btn);
    gtk_box_append(GTK_BOX(toolbar), toggle_sidebar_btn);
    
    g_signal_connect(back_btn, "clicked", G_CALLBACK(on_button_clicked), "Back");
    g_signal_connect(forward_btn, "clicked", G_CALLBACK(on_button_clicked), "Forward");
    g_signal_connect(find_btn, "clicked", G_CALLBACK(on_button_clicked), "Find");
    
    
    GtkWidget *content_pane = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX(main_box), content_pane);
    
    GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(sidebar, 200, -1);
    gtk_widget_set_margin_start(sidebar, 5);
    gtk_widget_set_margin_top(sidebar, 5);
    gtk_widget_set_margin_bottom(sidebar, 5);
   // gtk_widget_set_visible(sidebar, TRUE);

    g_signal_connect(toggle_sidebar_btn, "clicked", G_CALLBACK(toggle_side_bar), sidebar);
    
    GtkWidget *app_btn = gtk_button_new_with_label("Application");
    GtkWidget *security_btn = gtk_button_new_with_label("Security");
    GtkWidget *system_btn = gtk_button_new_with_label("System");
    
    gtk_widget_set_halign(app_btn, GTK_ALIGN_START);
    gtk_widget_set_halign(security_btn, GTK_ALIGN_START);
    gtk_widget_set_halign(system_btn, GTK_ALIGN_START);
    
    gtk_box_append(GTK_BOX(sidebar), app_btn);
    gtk_box_append(GTK_BOX(sidebar), security_btn);
    gtk_box_append(GTK_BOX(sidebar), system_btn);
    
    g_signal_connect(app_btn, "clicked", G_CALLBACK(on_menu_item_selected), "Application Logs");
    g_signal_connect(security_btn, "clicked", G_CALLBACK(on_menu_item_selected), "Security Logs");
    g_signal_connect(system_btn, "clicked", G_CALLBACK(on_menu_item_selected), "System Logs");
    
    GtkWidget *content = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(content), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(content), GTK_WRAP_WORD);
    
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(content));
    gtk_text_buffer_set_text(buffer, "Welcome to Event Viewer!\n\n"
                            "This is a simple GTK4 application designed for learning.", -1);
    
    gtk_paned_set_start_child(GTK_PANED(content_pane), sidebar);
    gtk_paned_set_end_child(GTK_PANED(content_pane), content);
    
    gtk_paned_set_position(GTK_PANED(content_pane), 200);
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.eventviewer", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}