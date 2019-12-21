#include <gtk/gtk.h>

GdkPixbuf *create_pixbuf(const gchar *filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    
    if (!pixbuf)
    {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

void print_msg(GtkWidget *widget, gpointer window)
{
    g_print("Button clicked\n");
}

void setBackground(GtkWidget *widget, int w, int h, const gchar *path)
{

    GtkWidget *board = gtk_hbox_new(TRUE, 10);
    gtk_container_add(GTK_CONTAINER(widget), board);
    
    GdkPixbuf *src = create_pixbuf(path);
    
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, w, h, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    gtk_container_add(GTK_CONTAINER(board), image);
    
    g_object_unref(src);
    g_object_unref(dst);
    
}
int main (int argc, char *argv[])
{

    GtkWidget *window;
    const gchar *path = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/board.png";
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Acker");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    setBackground(window, 700, 700, path);
    
    gtk_widget_show_all(window);

    gtk_main();
    
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
   return 0;
}
