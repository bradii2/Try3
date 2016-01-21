#pragma once
void init(void);
void deinit(void);
void window_load(Window *window);
void window_unload(Window *window);
void update_time(struct tm *tick_time);
void tick_handler(struct tm *tick_time, TimeUnits units_changed);
