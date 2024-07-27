#include "Window.h"
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

Xwindow::Xwindow(int width, int height) {
    auto displayDeleter = [](Display* d) { 
        if (d) {
            XCloseDisplay(d);
        }
    };

    d = shared_ptr<Display>(XOpenDisplay(NULL), displayDeleter);
    if (!d) {
        cerr << "Cannot open display" << endl;
        exit(1);   
    }
    s = DefaultScreen(d.get());
    w = XCreateSimpleWindow(d.get(), RootWindow(d.get(), s), 10, 10, width, height, 1,
                            BlackPixel(d.get(), s), WhitePixel(d.get(), s));
    XSelectInput(d.get(), w, ExposureMask | KeyPressMask);
    XMapRaised(d.get(), w);

    Pixmap pix = XCreatePixmap(d.get(), w, width, height, DefaultDepth(d.get(), DefaultScreen(d.get())));
    gc = XCreateGC(d.get(), pix, 0, (XGCValues *)0);

    XFlush(d.get());
    XFlush(d.get());

    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10] = {"white", "black", "grey", "burlywood", "sienna4"};

    cmap = DefaultColormap(d.get(), DefaultScreen(d.get()));
    for (int i = 0; i < 5; ++i) {
        XParseColor(d.get(), cmap, color_vals[i], &xcolour);
        XAllocColor(d.get(), cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(d.get(), gc, colours[Black]);

    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d.get(), w, &hints);

    XSynchronize(d.get(), True);

    usleep(1000);

    XEvent ev;
    while (1) {
        XNextEvent(d.get(), &ev);
        if (ev.type == Expose) break;
    }
}

Xwindow::~Xwindow() {
    XFreeGC(d.get(), gc);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d.get(), gc, colours[colour]);
    XFillRectangle(d.get(), w, gc, x, y, width, height);
    XSetForeground(d.get(), gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour, int fontSize) {
    XSetForeground(d.get(), gc, colours[colour]);

    // Load the font
    string fontName = "-*-helvetica-*-r-*-*-" + to_string(fontSize) + "-*-*-*-*-*-*-*";
    XFontStruct* font = XLoadQueryFont(d.get(), fontName.c_str());
    if (!font) {
        cerr << "Cannot load font " << fontName << endl;
        font = XLoadQueryFont(d.get(), "fixed");
    }

    XSetFont(d.get(), gc, font->fid);
    XDrawString(d.get(), w, gc, x, y, msg.c_str(), msg.length());
    XFreeFont(d.get(), font);
}
