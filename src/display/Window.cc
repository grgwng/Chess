#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "Window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);   
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,
          height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10]={"white", "black", "grey", "burlywood", "sienna4"};

    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 5; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    XSetForeground(d,gc,colours[Black]);

    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);

    XEvent ev;
    while(1) {
        XNextEvent(d, &ev);
        if(ev.type == Expose) break;
    }
}   

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour, int fontSize) {
    // Set the text color
    XSetForeground(d, gc, colours[colour]);

    // Load the font
    string fontName = "-*-helvetica-*-r-*-*-" + to_string(fontSize) + "-*-*-*-*-*-*-*";
    XFontStruct* font = XLoadQueryFont(d, fontName.c_str());
    if (!font) {
        cerr << "Cannot load font " << fontName << endl;
        font = XLoadQueryFont(d, "fixed");
    }

    XSetFont(d, gc, font->fid);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XFreeFont(d, font);
}
