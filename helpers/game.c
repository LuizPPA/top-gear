#include "game.h"
#include "car.h"

float position;
float moviment_speed = 22.0;
float street_width = 1300.0;
float street_length = 500.0;
float view_angle = 16.0;
CAR player;

float max(float a, float b){
  if(a > b) return a;
  return b;
}

void draw_track(){
  // Street center
  // al_draw_filled_circle(position, sh-60, 1, BLUE);
  // Sky
  al_draw_filled_rectangle(0, 0, sw, sh-street_length, LIGHT_BLUE);
  // Left strret border
  al_draw_line(position-(street_width/2), sh, position-((street_width/view_angle)/2), sh-street_length, YELLOW, 1);
  // Right street border
  al_draw_line(position+(street_width/2), sh, position+((street_width/view_angle)/2), sh-street_length, YELLOW, 1);
  al_draw_line(0, sh-street_length, sw, sh-street_length, YELLOW, 1);
}

void draw_car(){
  al_draw_bitmap(player.texture, (sw/2)-(player.width/2), (sh)-(20+player.height), 0);
  al_draw_rectangle((sw/2)-(player.width/2), sh-(player.height+20), (sw/2)+(player.width/2), sh-20.0, RED, 1);
  al_draw_filled_circle(sw/2, sh-(20+(player.height/2)), 1, RED);
}

void draw_hud(){
  char gear[10];
  char speed[20];
  sprintf(gear, "%d", player.gear);
  sprintf(speed, "%.0f Km/h", player.speed);
  draw_text(DISKUN_FONT, 60, BLUE, 30, sh-140, ALLEGRO_ALIGN_LEFT, "GEAR", false);
  draw_text(DISKUN_FONT, 80, BLUE, 30, sh-80, ALLEGRO_ALIGN_LEFT, gear, false);
  draw_text(DISKUN_FONT, 60, BLUE, sw-30, sh-140, ALLEGRO_ALIGN_RIGHT, "SPEED", false);
  draw_text(DISKUN_FONT, 80, BLUE, sw-30, sh-80, ALLEGRO_ALIGN_RIGHT, speed, false);
}

void redraw_game(){
  al_clear_to_color(GREY);
  draw_track();
  draw_car();
  draw_hud();
  al_flip_display();
}

bool is_car_on_track(){
  return (position-(player.width/2) >= (sw-street_width)/2 && position+(player.width/2) <= sw-((sw-street_width)/2));
}

int update(){
  al_get_keyboard_state(&key_state);
  if(is_car_on_track()){
    moviment_speed = 22.0;
  }
  else{
    moviment_speed = 10.0;
    if(player.speed - GRASS_SLOW_EFFECT > 0) player.speed -= GRASS_SLOW_EFFECT;
    else player.speed = 0;
  }
  if (al_key_down(&key_state, ALLEGRO_KEY_A)) {
    if(position < max(sw, street_width)+player.width) position += moviment_speed;
  }
  if (al_key_down(&key_state, ALLEGRO_KEY_D)){
    if(position > 0-player.width) position -= moviment_speed;
  }
  if (al_key_down(&key_state, ALLEGRO_KEY_W)){
    if(player.speed+speed_increase(player.gear, player.speed) < 8.6/10.0*max_speed(player.gear)) {
      player.speed += speed_increase(player.gear, player.speed);
    }
    else {
      player.speed += speed_increase(player.gear, player.speed)/8;
    }
  }
  else {
    if(player.speed > NO_ACCELERATE_EFFECT) player.speed -= NO_ACCELERATE_EFFECT;
    else player.speed = 0;
  }
  redraw_game();
  return 0;
}

int play(){
  stop_music(music);
  music = set_music(LAS_VEGAS_MUSIC);
  start_music(music, true);
  position = (sw/2);
  player = new_car(GAME_CAR_BITMAP);
  redraw_game();
  while (true) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    // Return to menu
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return -1;
      // Gear up
      else if(ev.keyboard.keycode == ALLEGRO_KEY_E && player.gear < 6) player.gear++;
      // Gear down
      else if(ev.keyboard.keycode == ALLEGRO_KEY_Q && player.gear > 1) player.gear--;
    }
    // Quit game
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return 4;
    // Each 1/fps seconds
    if(ev.type == ALLEGRO_EVENT_TIMER) {
      if(update() == -1){
        return -1;
      }
    }
  }
  return 0;
}
