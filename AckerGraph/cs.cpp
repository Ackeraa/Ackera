//
//  Gomoku.h
//  Ackera
//
//  Created by 高善勋 on 2019/12/22.
//  Copyright © 2019 高善勋. All rights reserved.
//

#ifndef Gomoku_h
#define Gomoku_h

#include <gtk/gtk.h>
#include "Acker.h"

class Gomoku
{
private:
    GtkWidget *window;
    GtkWidget *layout;
    const gchar *imgPath = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/board.png";
    const gchar *blackPath = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/black.png";
    const gchar *whitePath = "/Users/gsx/MyProgram/C++/Ackera/AckerGraph/AckerGraph/white.png";
public:
    Gomoku(int argv, char *argc[]);
    GdkPixbuf *create_pixbuf(const gchar *filename);
    void setBackground(GtkWidget *widget, int w, int h);
    void placePiece(gdouble x, gdouble y);
    gboolean mousePress(GtkWidget *widget, GdkEventButton *event, gpointer data);
}

#endif /* Gomoku_h */



//
//  Gomoku.cpp
//  Ackera
//
//  Created by 高善勋 on 2019/12/22.
//  Copyright © 2019 高善勋. All rights reserved.
//

#include "Gomoku.h"

Gomoku::Gomoku(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Acker");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout);
    gtk_widget_show(layout);

    setBackground(window, 700, 700);

    pair<int, int> pos = A.Move();
    gdouble yy = (15 - pos.first) * 41.3 + 100.0;
    gdouble xx = (pos.second - 1) * 41.3 + 112.0;
    placePiece(xx, yy, blackPath);

    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

    g_signal_connect(window, "button-press-event", G_CALLBACK(mousePress),NULL);

    gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
}

GdkPixbuf Gomoku:: *create_pixbuf(const gchar *filename)
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

void Gomoku::setBackground(GtkWidget *widget, int w, int h)
{
    GdkPixbuf *src = create_pixbuf(imgPath);

    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, w, h, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    gtk_layout_put(GTK_LAYOUT(layout), image, 40, 50);

    g_object_unref(src);
    g_object_unref(dst);

}

void Gomoku::placePiece(gdouble x, gdouble y, const gchar *path)
{
    GdkPixbuf *src = create_pixbuf(path);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, 30, 30, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(dst);
    gtk_layout_put(GTK_LAYOUT(layout), image, x - 15, y - 15);

    gtk_widget_show_all(window);
    g_object_unref(src);
    g_object_unref(dst);

}

gboolean Gomoku::mousePress(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    switch(event->button)
    {
        case 1:
        {
            //printf("Left Button!!\n");
            gdouble x = event->x;
            gdouble y = event->y;
            gdouble posX = gint((x - 92) / 41) * 41.3 + 112.0;
            gdouble posY = gint((y - 80) / 41) * 41.3 + 100.0;

            if (abs(gint(x - posX)) <= 10 && abs(gint(y - posY)) <= 10)
            {
                placePiece(posX, posY, whitePath);

                int yd = gint((x - 92) / 41) + 1;
                int xd = gint((y - 80)) / 41 + 1;
                A.Move(xd, yd);
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

    pair<int, int> pos = A.Move();
    gdouble yy = (pos.first - 1) * 41.3 + 100.0;
    gdouble xx = (pos.second - 1) * 41.3 + 112.0;
    placePiece(xx, yy, blackPath);

    return true;
}

