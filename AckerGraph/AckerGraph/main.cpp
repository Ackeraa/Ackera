#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *layout;

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
    GdkPixbuf *src = create_pixbuf(path);
    
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, w, h, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    gtk_layout_put(GTK_LAYOUT(layout), image, 40, 50);
    
    g_object_unref(src);
    g_object_unref(dst);
    
}

void placePiece(gdouble x, gdouble y, const gchar *path)
{
    GdkPixbuf *src = create_pixbuf(path);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, 30, 30, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    gtk_layout_put(GTK_LAYOUT(layout), image, x - 15, y - 15);
    
    gtk_widget_show_all(window);
}

gboolean mousePress(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    const gchar *path = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/black2.png";
    switch(event->button)
    {
        case 1:
            printf("Left Button!!\n");
            break;
        case 2:
            printf("Middle Button!!\n");
            break;
        case 3:
            printf("Right Button!!\n");
            break;
        default:
            printf("Unknown Button!!\n");
    }
    
    if (event->type == GDK_2BUTTON_PRESS)
    {
        printf("double click\n");
    }
    
    gdouble x = event->x;
    gdouble y = event->y;
    gdouble posX = gint((x - 92) / 41) * 41.3 + 112.0;
    gdouble posY = gint((y - 80) / 41) * 41.3 + 100.0;

    if (abs(gint(x - posX)) <= 10 && abs(gint(y - posY)) <= 10)
    {
        placePiece(posX, posY, path);
        
    }
    printf("(%.1lf, %.1lf) (%.1lf, %.1lf)\n", (double)x, (double)y, posX, posY);
    return true;
}

int main (int argc, char *argv[])
{


    const gchar *path = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/board.png";
    
   // while (1)
    //{
        gtk_init(&argc, &argv);

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Acker");
        gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        
        layout = gtk_layout_new(NULL, NULL);
        gtk_container_add(GTK_CONTAINER(window), layout);
        gtk_widget_show(layout);
        
        setBackground(window, 700, 700, path);
        
        gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_MOTION_MASK);
        

        
        g_signal_connect(window, "button-press-event", G_CALLBACK(mousePress), NULL);
        
        gtk_widget_show_all(window);
        gtk_main();

    //}

    
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
   return 0;
}
