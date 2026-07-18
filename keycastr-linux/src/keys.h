#ifndef KEYS_H
#define KEYS_H
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

void handle_key_event(int keycode, int is_press);
void init_keys(Display *display);
#endif