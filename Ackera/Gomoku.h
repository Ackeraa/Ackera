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
    Acker A;
    Gomoku(int argc, char *argv[]);
    GdkPixbuf *create_pixbuf(const gchar *filename);
    void setBackground(GtkWidget *widget, int w, int h);
    void placePiece(gdouble x, gdouble y, const gchar *path);
    gboolean mousePress(GtkWidget *widget, GdkEventButton *event, gpointer data);
};

#endif /* Gomoku_h */
