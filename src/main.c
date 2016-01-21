#include <pebble.h>
#include "main.h"

Window *s_window;
TextLayer *s_text;
TextLayer *s_date;

int main(void){
  init();
  app_event_loop();
  deinit();
}

void init(void){
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload
  });
  window_stack_push(s_window, true);
  
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  update_time(tick_time);
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}
void deinit(void){
  window_destroy(s_window);
}

void window_load(Window *window){
  Layer *layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(layer);
  
  s_text = text_layer_create(GRect(0, bounds.size.h, bounds.size.w, (bounds.size.h / 3) * 2));
  text_layer_set_font(s_text, fonts_get_system_font(FONT_KEY_LECO_38_BOLD_NUMBERS));
  text_layer_set_text_alignment(s_text, GTextAlignmentCenter);
  layer_add_child(layer, text_layer_get_layer(s_text));
  
  s_date = text_layer_create(GRect(0, (bounds.size.h / 3), bounds.size.w, 0));
  text_layer_set_font(s_date, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(s_text, GTextAlignmentCenter);
  layer_add_child(layer, text_layer_get_layer(s_date));
}
void window_unload(Window *window){
  text_layer_destroy(s_text);
  text_layer_destroy(s_date);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time(tick_time);
}
void update_time(struct tm *tick_time){ 
  static char time_buffer[5];
  if(clock_is_24h_style()){
    strftime(time_buffer, sizeof(time_buffer), "%H:%M", tick_time);
  }else{
    strftime(time_buffer, sizeof(time_buffer), "%I:%M", tick_time);
  }
  text_layer_set_text(s_text, time_buffer);
  
  static char date_buffer[6];
  strftime(date_buffer, sizeof(date_buffer), "%b %d", tick_time);
  text_layer_set_text(s_date, date_buffer);
}