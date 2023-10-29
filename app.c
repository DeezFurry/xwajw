#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdbool.h>

bool isDragging = false;
bool isMouseLocked = false;
int offsetX, offsetY;

void handleButtonPress(XEvent *event, Display *display, Window window) {
    if (event->xbutton.button == Button1) {
        offsetX = event->xbutton.x;
        offsetY = event->xbutton.y;
        isDragging = true;
    }
}

void handleButtonRelease() {
    isDragging = false;
}

void handleMotion(XEvent *event, Display *display, Window window) {
    if (isDragging) {
        XMoveWindow(display, window, event->xmotion.x_root - offsetX, event->xmotion.y_root - offsetY);
    }
}

void toggleMouseLock(Display *display, Window window) {
    if (isMouseLocked) {
        XUngrabPointer(display, CurrentTime);
    } else {
        XGrabPointer(display, window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    }
    isMouseLocked = !isMouseLocked;
}

int main() {
    Display *display;
    Window window;
    XEvent event;

    // Open a connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    // Create a window
    window = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, 200, 100, 1, BlackPixel(display, 0), WhitePixel(display, 0));

    // Select events to monitor
    XSelectInput(display, window, ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask);

    // Map the window on the screen
    XMapWindow(display, window);

    // Main event loop
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XDrawString(display, window, DefaultGC(display, 0), 10, 40, "Hi", 2);
        } else if (event.type == ButtonPress) {
            handleButtonPress(&event, display, window);
        } else if (event.type == ButtonRelease) {
            handleButtonRelease();
        } else if (event.type == MotionNotify) {
            handleMotion(&event, display, window);
        } else if (event.type == KeyPress) {
            if (event.xkey.keycode == XKeysymToKeycode(display, XK_Shift_L) &&
                event.xkey.state & ControlMask) {
                toggleMouseLock(display, window);
            }
        }
    }

    // Close the window and X server connection
    XCloseDisplay(display);

    return 0;
}
