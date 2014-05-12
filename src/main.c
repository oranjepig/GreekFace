#include <pebble.h>
#include <string.h>

Window *my_window;
TextLayer *top_layer;
TextLayer *bottom_layer;

static char time_as_text[60];
static char minutes_as_text[60];

char *texthours[13] = {"dwdeka","mia","duo","treiv","tessereiv","pente","exi","epta","oktw","ennea","deka","enteka","dwdeka"};

char *mindecs[6] = {"","deka","eikosi","trianta","saranta","penhnta"};

char *minsingles[10] = {"","ena","duo","tria","tessera","pente","exi","epta","oktw","ennia"};


static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  
  char *timestring = "00:00";
  strftime(timestring, 86, "%I:%M", tick_time); //put the time into a string
  
  int hours;
  hours = tick_time->tm_hour;  // get hour as integer
  if(hours>12)
  {    hours = hours - 12;  };
  
    
  memset(&time_as_text[0], 0, sizeof(time_as_text)); 
  strcat(time_as_text, texthours[hours]);
  
  int mins;
  mins = tick_time->tm_min;
  
  char *minutetext ="";
  char *minmon = "";
  
  if(mins==15)
  {    minutetext ="tetarto";  }
    else if(mins==30)
    {    minutetext="mish";}
      else if(mins==11)
      {   minutetext="enteka";}
        else if(mins==12)
       {   minutetext="dwdeka";}
      else
      {  minutetext = mindecs[mins/10];
         minmon = minsingles[mins%10];
      };
  
  memset(&minutes_as_text[0], 0, sizeof(minutes_as_text));
  
  if(mins>0)
  { 
         strcat(minutes_as_text, "kai ");
         strcat(minutes_as_text, minutetext);
         strcat(minutes_as_text, " ");
         strcat(minutes_as_text, minmon);    
   
  } else strcat(minutes_as_text, "akribwv");

  text_layer_set_text(top_layer, time_as_text);
  text_layer_set_text(bottom_layer, minutes_as_text);  
 }

void handle_init(void) {
    my_window = window_create();
    window_stack_push(my_window, true);
    window_set_background_color(my_window, GColorBlack);  
  
    top_layer = text_layer_create(GRect(0, 10, 144, 40));
    text_layer_set_text_alignment(top_layer, GTextAlignmentLeft);
    text_layer_set_background_color(top_layer, GColorBlack);
    text_layer_set_text_color(top_layer, GColorWhite);
    text_layer_set_font(top_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NAXOS_BOLD_34)));

  
    bottom_layer = text_layer_create(GRect(0, 56, 144, 110));
    text_layer_set_text_alignment(bottom_layer, GTextAlignmentLeft);
    text_layer_set_background_color(bottom_layer, GColorBlack);
    text_layer_set_text_color(bottom_layer, GColorWhite);
    text_layer_set_font(bottom_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NAXOS_REG_34)));

  
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(top_layer));
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(bottom_layer));
    tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  } 


void handle_deinit(void) {
	  tick_timer_service_unsubscribe();
    text_layer_destroy(top_layer);
    text_layer_destroy(bottom_layer);
	  window_destroy(my_window);
  
}

int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}