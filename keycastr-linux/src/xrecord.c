#include "xrecord.h"
#include "keys.h"
#include <X11/Xlib.h>
#include <X11/extensions/record.h>
#include <stdio.h>

static Display *dpy, *dpy_data;

void callback(XPointer priv, XRecordInterceptData *hook) {
    if (hook->category != XRecordFromServer) {
        XRecordFreeData(hook);
        return;
    }

    unsigned char *data = hook->data;
    int event_type = data[0] & 0x7F;
    int keycode = data[1];

    if (event_type == KeyPress) {
        handle_key_event(keycode, 1);
    } else if (event_type == KeyRelease) {
        handle_key_event(keycode, 0);
    }

    XRecordFreeData(hook);
}

void start_xrecord() {
    dpy = XOpenDisplay(NULL);
    dpy_data = XOpenDisplay(NULL);

    if (!dpy || !dpy_data) {
        printf("Cannot open display\n");
        return;
    }

    init_keys(dpy);

    XRecordRange *range = XRecordAllocRange();
    range->device_events.first = KeyPress;
    range->device_events.last = KeyRelease;

    XRecordClientSpec clients = XRecordAllClients;

    XRecordContext ctx = XRecordCreateContext(
        dpy, 0, &clients, 1, &range, 1
    );

    XRecordEnableContextAsync(dpy_data, ctx, callback, NULL);

    while (1) {
        XRecordProcessReplies(dpy_data);
    }
}