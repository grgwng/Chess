#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <iostream>
#include <string>

using namespace std;

class Xwindow {
    shared_ptr<Display> d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];

public:
    Xwindow(int width=500, int height=500);  
    ~Xwindow();      
                           
    enum {White=0, Black, Grey, TileLight, TileDark};

    void fillRectangle(int x, int y, int width, int height, int colour=Black);
    void drawString(int x, int y, string msg, int colour, int fontSize);
};

#endif
