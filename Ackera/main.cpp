//
//  main.cpp
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//
#include "Acker.h"
//#include <iostream>
#include <gtk/gtk.h>

#define BLACK 0
#define WHITE 1
#define inf 1e8

//using namespace std;

GtkWidget *window;
GtkWidget *layout;
Acker A(0, 1);

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
    g_object_unref(src);
    g_object_unref(dst);
    
}

gboolean mousePress(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    const gchar *path1 = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/black2.png";
    const gchar *path2 = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/white2.png";
    

     
    switch(event->button)
    {
        case 1:
        {
            printf("Left Button!!\n");
            gdouble x = event->x;
            gdouble y = event->y;
            gdouble posX = gint((x - 92) / 41) * 41.3 + 112.0;
            gdouble posY = gint((y - 80) / 41) * 41.3 + 100.0;

            if (abs(gint(x - posX)) <= 10 && abs(gint(y - posY)) <= 10)
            {
                placePiece(posX, posY, path2);
               // gtk_widget_show(layout);
                
                int yd = gint((x - 92) / 41) + 1;
                int xd = gint((y - 80)) / 41 + 1;
                printf("%d %d\n", xd, yd);
                A.Move(xd, yd);
                printf("*********************\n");
                sleep(100);
            }
        }
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
    
    pair<int, int> pos = A.Move();
    gdouble yy = (pos.first - 1) * 41.3 + 100.0;
    gdouble xx = (pos.second - 1) * 41.3 + 112.0;
    //  printf("%d %d\n", pos.first, pos.second);
    placePiece(xx, yy, path1);

    return true;
}

gboolean mousePress2(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    const gchar *path1 = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/black2.png";
    const gchar *path2 = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/white2.png";
    pair<int, int> pos = A.Move();
    gdouble yy = (pos.first - 1) * 41.3 + 100.0;
    gdouble xx = (pos.second - 1) * 41.3 + 112.0;
    //  printf("%d %d\n", pos.first, pos.second);
    placePiece(xx, yy, path1);
    return true;
}

int main(int argc, char *argv[])
{

    const gchar *path = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/board.png";
    const gchar *path2 = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/black.png";
    
    gtk_init(&argc, &argv);

    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Acker");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout);
    gtk_widget_show(layout);
    
    setBackground(window, 700, 700, path);
    
    pair<int, int> pos = A.Move();
    gdouble yy = (15 - pos.first) * 41.3 + 100.0;
    gdouble xx = (pos.second - 1) * 41.3 + 112.0;
    printf("%d %d %.1lf %.1lf\n", pos.first, pos.second, xx, yy);
    placePiece(xx, yy, path2);

    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);
   
    g_signal_connect(window, "button-press-event", G_CALLBACK(mousePress),NULL);
    g_signal_connect(window, "button-press-event2", G_CALLBACK(mousePress2),NULL);
    
  //  g_signalconn
    gtk_widget_show_all(window);
    printf("9999999999999999\n");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_main();


    return 0;
}
