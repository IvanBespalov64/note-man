#include <gtk/gtk.h>
#include <stdio.h>

/*Clear button's callback*/
static void clear_callback(GtkWidget* widget, GtkTextBuffer* buffer){
	gtk_text_buffer_set_text(buffer, "", 0);
}

const char* ICON_NAME = "icon.png";

int main (int argc, char *argv[])
{
    GtkWidget *window;
	GtkWidget *text_view;
	GtkWidget *scrolled_window;
	GtkWidget *vbox;
	GtkWidget *clear_button;

	GtkTextBuffer *buffer;

	GdkPixbuf *icon;

	gtk_init (&argc, &argv);

	/*Init window*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Note Man");
	gtk_widget_set_size_request(GTK_WINDOW (window), 300, 400);
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	icon = gdk_pixbuf_new_from_file(ICON_NAME, NULL);
	gtk_window_set_icon(GTK_WINDOW (window), icon);

	/*Init buffer*/
	buffer = gtk_text_buffer_new(NULL);

	/*Init textview*/
	text_view = gtk_text_view_new_with_buffer(buffer);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (text_view), GTK_WRAP_WORD);

	/*Init vertical box*/
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER (window), vbox);

	/*Init scrolled window*/
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window),
								   GTK_POLICY_AUTOMATIC,
								   GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER (scrolled_window), text_view);
	gtk_container_set_border_width(GTK_CONTAINER (scrolled_window), 5);

	gtk_container_add(GTK_CONTAINER (vbox), scrolled_window);

	/*Init button*/
	clear_button = gtk_button_new();
	gtk_button_set_label(clear_button, "Clear");
	g_signal_connect(clear_button, "clicked",
					 G_CALLBACK(clear_callback), buffer);
	gtk_widget_set_size_request(clear_button, NULL, 50);
	gtk_box_pack_start(GTK_BOX(vbox), clear_button, FALSE, TRUE, 0);

	gtk_widget_show_all(window);

    gtk_main ();
    return 0;
}
