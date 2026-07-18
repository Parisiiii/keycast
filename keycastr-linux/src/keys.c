#include "keys.h"
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <string.h>

static int shift = 0;
static int ctrl = 0;
static int alt = 0;

static Display *dpy = NULL;

void init_keys(Display *display) {
    dpy = display;
}

const char* get_key_name(int keycode) {
    KeySym ks = XkbKeycodeToKeysym(dpy, keycode, 0, 0);
    return XKeysymToString(ks);
}

void print_combo(const char *key) {
    char buffer[256] = "";

    if (ctrl) strcat(buffer, "Ctrl + ");
    if (shift) strcat(buffer, "Shift + ");
    if (alt) strcat(buffer, "Alt + ");

    strcat(buffer, key);

    printf("%s\n", buffer);
    fflush(stdout);
}

void handle_key_event(int keycode, int is_press) {
    const char *key = get_key_name(keycode);
    if (!key) return;

    // Track modifiers
    if (strcmp(key, "Shift_L") == 0 || strcmp(key, "Shift_R") == 0)
        shift = is_press;
    else if (strcmp(key, "Control_L") == 0 || strcmp(key, "Control_R") == 0)
        ctrl = is_press;
    else if (strcmp(key, "Alt_L") == 0 || strcmp(key, "Alt_R") == 0)
        alt = is_press;

    if (is_press) {
        print_combo(key);
    }
}