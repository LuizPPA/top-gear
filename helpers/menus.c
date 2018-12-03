#include "menus.h"
#include "game.h"
#include "sounds.h"
#include "environment.h"

ALLEGRO_COLOR colors[7];

// Updates menu on screen
int redraw_main_menu(int op){
  clear_display(BLUE, false);
  al_draw_bitmap(GAME_TITLE, (sw/2)-203, (sh/2)-250, 0);
  draw_text(PIXEL_28, colors[0], sw/2, (sh/2)-35, ALLEGRO_ALIGN_CENTRE, "PLAY", false);
  draw_text(PIXEL_28, colors[1], sw/2, (sh/2)+5, ALLEGRO_ALIGN_CENTRE, "OPTIONS", false);
  draw_text(PIXEL_28, colors[2], sw/2, (sh/2)+45, ALLEGRO_ALIGN_CENTRE, "CREDITS", false);
  draw_text(PIXEL_28, colors[3], sw/2, (sh/2)+85, ALLEGRO_ALIGN_CENTRE, "EXIT", true);
}

int options_menu();
int mode_selection();

// Runs main menu
int main_menu(){
  int op = 1;
  // Selected option = WHITE
  colors[0] = WHITE;
  colors[1] = YELLOW;
  colors[2] = YELLOW;
  colors[3] = YELLOW;
  colors[4] = YELLOW;
  // Update screen
  redraw_main_menu(op);
  while (true) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    // Quit game
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return 4;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      // Return to title
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        play_sample(MENU_BACK_SOUND);
        return -1;
      }
      switch (ev.keyboard.keycode) {
        // Selection UP
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
          if(op > 1){
            colors[op-1] = YELLOW;
            op--;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            // Update screen
            redraw_main_menu(op);
          }
          break;
        // Selection DOWN
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
          if(op < 4){
            colors[op-1] = YELLOW;
            op++;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            // Update screen
            redraw_main_menu(op);
          }
          break;
        // Confirm selection
        case ALLEGRO_KEY_ENTER:
          play_sample(MENU_SELECT_SOUND);
          switch (op) {
            // Select game mode
            case 1:
              op = mode_selection();
              break;
            // Configure options
            case 2:
              op = options_menu(set_music(TITLE_MUSIC));
              break;

          }
          if(op != -1) return op;
          op = 1;
          colors[0] = WHITE;
          colors[1] = YELLOW;
          colors[2] = YELLOW;
          colors[3] = YELLOW;
          redraw_main_menu(op);
      }
    }
  }
  draw_title();
  return 0;
}

// Update options screen
void redraw_options_menu(int op){
  clear_display(BLUE, false);

  // Music
  draw_text(PIXEL_28, colors[0], (sw/2)-80, 200+(1*35), ALLEGRO_ALIGN_RIGHT, "Music", false);
  if(music_on) draw_text(PIXEL_28, colors[0], (sw/2)+80, 200+(1*35), ALLEGRO_ALIGN_LEFT, "ON", false);
  else draw_text(PIXEL_28, colors[0], (sw/2)+80, 200+(1*35), ALLEGRO_ALIGN_LEFT, "OFF", false);

  // Sounds
  draw_text(PIXEL_28, colors[1], (sw/2)-80, 200+(2*35), ALLEGRO_ALIGN_RIGHT, "Sounds", false);
  if(sounds_on) draw_text(PIXEL_28, colors[1], (sw/2)+80, 200+(2*35), ALLEGRO_ALIGN_LEFT, "ON", false);
  else draw_text(PIXEL_28, colors[1], (sw/2)+80, 200+(2*35), ALLEGRO_ALIGN_LEFT, "OFF", false);

  // Collisions
  draw_text(PIXEL_28, colors[2], (sw/2)-80, 200+(3*35), ALLEGRO_ALIGN_RIGHT, "Collisions", false);
  if(collisions) draw_text(PIXEL_28, colors[2], (sw/2)+80, 200+(3*35), ALLEGRO_ALIGN_LEFT, "ON", false);
  else draw_text(PIXEL_28, colors[2], (sw/2)+80, 200+(3*35), ALLEGRO_ALIGN_LEFT, "OFF", false);

  // Debug
  draw_text(PIXEL_28, colors[3], (sw/2)-80, 200+(4*35), ALLEGRO_ALIGN_RIGHT, "Debug", false);
  if(debug) draw_text(PIXEL_28, colors[3], (sw/2)+80, 200+(4*35), ALLEGRO_ALIGN_LEFT, "ON", false);
  else draw_text(PIXEL_28, colors[3], (sw/2)+80, 200+(4*35), ALLEGRO_ALIGN_LEFT, "OFF", false);

  al_flip_display();
}

// Configure options
int options_menu(){
  int op = 1;
  colors[0] = WHITE;
  colors[1] = YELLOW;
  colors[2] = YELLOW;
  colors[3] = YELLOW;
  while (true) {
    redraw_options_menu(op);
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return 4;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        play_sample(MENU_BACK_SOUND);
        return -1;
      }
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
          if(op > 1){
            colors[op-1] = YELLOW;
            op--;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
          }
          break;
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
          if(op < 4){
            colors[op-1] = YELLOW;
            op++;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
          }
          break;
        case ALLEGRO_KEY_ENTER:
          switch (op) {
            case 1:
              if(music_on){
                turn_of_music(music);
              }
              else{
                turn_on_music(music);
              }
              break;
            case 2:
              sounds_on = !sounds_on;
              break;
            case 3:
              collisions = !collisions;
              break;
            case 4:
              debug = !debug;
              break;
          }
          play_sample(MENU_SELECT_SOUND);
          break;
      }
    }
  }
}

// Update mode selection screen
void redraw_mode_selection(int op){
  float square_side = 250.0;
  clear_display(BLUE, false);
  draw_text(PIXEL_32, YELLOW, sw/2, 35, ALLEGRO_ALIGN_CENTRE, "GAME MODE", false);
  al_draw_rounded_rectangle((sw/2)-25-square_side, (sh/2)-(square_side/2), (sw/2)-25, (sh/2)+(square_side/2), 0, 0, colors[0], 5);
  draw_text(PIXEL_28, colors[0], (sw/2)-25-(square_side/2), (sh/2)-14, ALLEGRO_ALIGN_CENTRE, "QUICK PLAY", false);
  al_draw_rounded_rectangle((sw/2)+25, (sh/2)-(square_side/2), (sw/2)+25+square_side, (sh/2)+(square_side/2), 0, 0, colors[1], 5);
  draw_text(PIXEL_28, colors[1], (sw/2)+25+(square_side/2), (sh/2)-14, ALLEGRO_ALIGN_CENTRE, "TOURNAMENT", false);
  switch (op) {
    case 1:
      draw_text(PIXEL_22, WHITE, 30, sh-37, ALLEGRO_ALIGN_LEFT, "A single race to test your skills", true);
      break;
    case 2:
      draw_text(PIXEL_22, WHITE, 30, sh-37, ALLEGRO_ALIGN_LEFT, "Join a series of races and make your way to the top!", true);
      break;
  }
}

int* car_selection();
int color_selection();
int map_selection();

// Select gamemode
int mode_selection(){
  int op = 1, *car, map;
  colors[0] = WHITE;
  colors[1] = YELLOW;
  while (true) {
    redraw_mode_selection(op);
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return 4;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        play_sample(MENU_BACK_SOUND);
        return -1;
      }
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
          if(op < 2){
            colors[op-1] = YELLOW;
            op++;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
          }
          break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
          if(op > 1){
            colors[op-1] = YELLOW;
            op--;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
          }
          break;
        case ALLEGRO_KEY_ENTER:
          play_sample(MENU_SELECT_SOUND);
          switch (op) {
            // Start race
            case 1: // Single race
              car = car_selection();
              if(car[0] == 5) return 4;
              if(car[0] == -1) return -1;
              map = map_selection();
              if(map == 4 || map == -1) return map;
              op = play(get_car(car[0], car[1]), NULL, 11, map, true);
              stop_music(music);
              music = set_music(TITLE_MUSIC);
              start_music(music, true);
              break;
            case 2: // Tournament
              car = car_selection();
              if(car[0] == 5) return 4;
              if(car[0] == -1) return -1;
              op = tournament(get_car(car[0], car[1]), 11);
              stop_music(music);
              music = set_music(TITLE_MUSIC);
              start_music(music, true);
              break;
          }
          return op;
      }
    }
  }
  return 0;
}

// Update car selection screen
void redraw_car_selection(int op){
  float square_width = 340.0, square_height = 220;
  float dominus_w = get_bitmap_width(DOMINUS_GT_ICON_BITMAP), dominus_h = get_bitmap_height(DOMINUS_GT_ICON_BITMAP);
  float octane_w = get_bitmap_width(OCTANE_ZSR_ICON_BITMAP), octane_h = get_bitmap_height(OCTANE_ZSR_ICON_BITMAP);
  float roadhog_w = get_bitmap_width(ROADHOG_ICON_BITMAP), roadhog_h = get_bitmap_height(ROADHOG_ICON_BITMAP);
  float maverick_w = get_bitmap_width(MAVERICK_ICON_BITMAP), maverick_h = get_bitmap_height(MAVERICK_ICON_BITMAP);
  clear_display(BLUE, false);
  // Dominus
  al_draw_rectangle((sw/2)-25-square_width, (sh/2)-25-square_height, (sw/2)-25, (sh/2)-25, colors[0], 5);
  draw_text(PIXEL_22, colors[0], (sw/2)-25-(square_width/2), (sh/2)-25-square_height+12, ALLEGRO_ALIGN_CENTRE, "Dominus GT", false);
  al_draw_bitmap(DOMINUS_GT_ICON_BITMAP, (sw/2)-25-((square_width-dominus_w)/2)-dominus_w, (sh/2)-25-35-dominus_h, 0);

  // Octane
  al_draw_rectangle((sw/2)+25, (sh/2)-25-square_height, (sw/2)+25+square_width, (sh/2)-25, colors[1], 5);
  draw_text(PIXEL_28, colors[1], (sw/2)+25+(square_width/2), (sh/2)-25-square_height+12, ALLEGRO_ALIGN_CENTRE, "Octane ZSR", false);
  al_draw_bitmap(OCTANE_ZSR_ICON_BITMAP, (sw/2)+25+((square_width-octane_w)/2), (sh/2)-25-35-octane_h, 0);

  // Roadhog
  al_draw_rectangle((sw/2)-25-square_width, (sh/2)+25, (sw/2)-25, (sh/2)+25+square_height, colors[2], 5);
  draw_text(PIXEL_28, colors[2], (sw/2)-25-(square_width/2), (sh/2)+25+12, ALLEGRO_ALIGN_CENTRE, "Roadhog", false);
  al_draw_bitmap(ROADHOG_ICON_BITMAP, (sw/2)-25-(square_width/2)-(roadhog_w/2), (sh/2)+25+square_height-35-roadhog_h, 0);

  // Maverick
  al_draw_rectangle((sw/2)+25, (sh/2)+25, (sw/2)+25+square_width, (sh/2)+25+square_height, colors[3], 5);
  draw_text(PIXEL_28, colors[3], (sw/2)+25+(square_width/2), (sh/2)+25+12, ALLEGRO_ALIGN_CENTRE, "Maverick", false);
  al_draw_bitmap(MAVERICK_ICON_BITMAP, (sw/2)+25+(square_width/2)-(maverick_w/2), (sh/2)+25+square_height-35-maverick_h, 0);

  draw_text(PIXEL_32, YELLOW, (sw/2), 30, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR VEICHLE", true);
}

// Select car
int* car_selection(){
  int op = 1, *res = (int*) calloc(2, sizeof(int)), color;
  colors[0] = WHITE;
  colors[1] = YELLOW;
  colors[2] = YELLOW;
  colors[3] = YELLOW;
  redraw_car_selection(op);
  while (true) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      res[0] = 5;
      return res;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        play_sample(MENU_BACK_SOUND);
        res[0] = -1;
        return res;
      }
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
          if(op == 1 || op == 3){
            colors[op-1] = YELLOW;
            op++;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_car_selection(op);
          }
          break;
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_S:
          if(op < 3){
            colors[op-1] = YELLOW;
            op += 2;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_car_selection(op);
          }
          break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
          if(op == 2 || op == 4){
            colors[op-1] = YELLOW;
            op--;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_car_selection(op);
          }
          break;
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_W:
          if(op > 2){
            colors[op-1] = YELLOW;
            op -= 2;
            colors[op-1] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_car_selection(op);
          }
          break;
        case ALLEGRO_KEY_ENTER:
          play_sample(MENU_SELECT_SOUND);
          res[0] = op;
          color = color_selection();
          if(color == 7) res[0] = 5;
          if(color == -1) res[0] = -1;
          res[1] = color;
          return res;
      }
    }
  }
  res[0] = 0;
  return res;
}

// Update color selection screen
void redraw_color_selection(int op){
  float block_size = 150.0;
  ALLEGRO_COLOR options[7] = {rgb(255, 0, 0), rgb(0, 0, 255), rgb(0, 255, 0), rgb(100, 100, 100), rgb(170, 0, 240), rgb(247, 165, 0), rgb(0, 0, 0)};
  clear_display(BLUE, false);
  draw_text(PIXEL_32, YELLOW, (sw/2), 35, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR COLOR", false);
  for(int i = -3; i < 4; i++){
    al_draw_filled_rounded_rectangle((sw/2)+(i*(block_size+25.0))-(block_size/2), (sh/2)-(block_size/2), (sw/2)+(i*(block_size+25))+(block_size/2), (sh/2)+(block_size/2), 0, 0, options[i+3]);
    al_draw_rounded_rectangle((sw/2)+(i*(block_size+25.0))-(block_size/2), (sh/2)-(block_size/2), (sw/2)+(i*(block_size+25))+(block_size/2), (sh/2)+(block_size/2), 0, 0, colors[i+3], 5);
  }
  al_flip_display();
}

// Select car color
int color_selection(){
  int op = 0;
  // Selected option = WHITE
  colors[0] = WHITE;
  colors[1] = YELLOW;
  colors[2] = YELLOW;
  colors[3] = YELLOW;
  colors[4] = YELLOW;
  colors[5] = YELLOW;
  colors[6] = YELLOW;
  redraw_color_selection(op);
  while (true) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return 7;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        play_sample(MENU_BACK_SOUND);
        return -1;
      }
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
          if(op < 6){
            colors[op] = YELLOW;
            op++;
            colors[op] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_color_selection(op);
          }
          break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
          if(op > 0){
            colors[op] = YELLOW;
            op--;
            colors[op] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            redraw_color_selection(op);
          }
          break;
        case ALLEGRO_KEY_ENTER:
          play_sample(MENU_SELECT_SOUND);
          return op;
      }
    }
  }
  return 0;
}

void redraw_map_selection(int op){
  int square_w = 500, square_h = 200;
  clear_display(BLUE, false);
  draw_text(PIXEL_28, YELLOW, sw/2, 20, ALLEGRO_ALIGN_CENTRE, "MAP SELECTION", false);
  draw_text(PIXEL_22, YELLOW, (sw/2), 100, ALLEGRO_ALIGN_CENTRE, "LAS VEGAS", false);
  al_draw_bitmap(LAS_VEGAS_ICON_BITMAP, (sw/2)-(square_w/2), (sh/2)-(square_h/2), 0);
  al_draw_rounded_rectangle((sw/2)-(square_w/2), (sh/2)-(square_h/2), (sw/2)+(square_w/2), (sh/2)+(square_h/2), 0, 0, colors[0], 5);
  al_flip_display();
}

void flip_map_selection(int op, bool go_right){
  int square_w = 500, square_h = 200;
  float positions[4];
  if(go_right) {
    positions[0] = (sw*(1-op));
    positions[1] = (sw*(2-op));
    positions[2] = (sw*(3-op));
    positions[3] = (sw*(4-op));
  }
  else {
    positions[0] = (sw*(-1-op));
    positions[1] = (sw*(-op));
    positions[2] = (sw*(1-op));
    positions[3] = (sw*(2-op));
  }
  al_flush_event_queue(queue);
  while((go_right && positions[op] > 0) || (!go_right && positions[op] < 0)){
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_TIMER){
      for (int i = 0; i < 4; i++) {
        if(go_right) positions[i] -= (sw*1.3)/60;
        else positions[i] += (sw*1.3)/60;
      }
      clear_display(BLUE, false);
      draw_text(PIXEL_28, YELLOW, sw/2, 20, ALLEGRO_ALIGN_CENTRE, "MAP SELECTION", false);
      // Lass Vegas
      draw_text(PIXEL_22, YELLOW, positions[0]+(sw/2), 100, ALLEGRO_ALIGN_CENTRE, "LAS VEGAS", false);
      al_draw_bitmap(LAS_VEGAS_ICON_BITMAP, positions[0]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), 0);
      al_draw_rounded_rectangle(positions[0]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), positions[0]+(sw/2)+(square_w/2), (sh/2)+(square_h/2), 0, 0, colors[0], 5);
      // Bordeaux
      draw_text(PIXEL_22, YELLOW, positions[1]+(sw/2), 100, ALLEGRO_ALIGN_CENTRE, "BORDEAUX", false);
      al_draw_bitmap(BORDEAUX_ICON_BITMAP, positions[1]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), 0);
      al_draw_rounded_rectangle(positions[1]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), positions[1]+(sw/2)+(square_w/2), (sh/2)+(square_h/2), 0, 0, colors[1], 5);
      // Hiroshima
      draw_text(PIXEL_22, YELLOW, positions[2]+(sw/2), 100, ALLEGRO_ALIGN_CENTRE, "Hiroshima", false);
      al_draw_bitmap(HIROSHIMA_ICON_BITMAP, positions[2]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), 0);
      al_draw_rounded_rectangle(positions[2]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), positions[2]+(sw/2)+(square_w/2), (sh/2)+(square_h/2), 0, 0, colors[2], 5);
      // Frankfurt
      draw_text(PIXEL_22, YELLOW, positions[3]+(sw/2), 100, ALLEGRO_ALIGN_CENTRE, "FRANKFURT", false);
      al_draw_bitmap(FRANKFURT_ICON_BITMAP, positions[3]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), 0);
      al_draw_rounded_rectangle(positions[3]+(sw/2)-(square_w/2), (sh/2)-(square_h/2), positions[3]+(sw/2)+(square_w/2), (sh/2)+(square_h/2), 0, 0, colors[3], 5);
      al_flip_display();
    }
  }
}

int map_selection(){
  int op = 0;
  // Selected option = WHITE
  colors[0] = WHITE;
  colors[1] = YELLOW;
  colors[2] = YELLOW;
  colors[3] = YELLOW;
  redraw_map_selection(op);
  while (true) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return 4;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        play_sample(MENU_BACK_SOUND);
        return -1;
      }
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_D:
          if(op < 3){
            colors[op] = YELLOW;
            op++;
            colors[op] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            flip_map_selection(op, true);
          }
          break;
        case ALLEGRO_KEY_LEFT:
        case ALLEGRO_KEY_A:
          if(op > 0){
            colors[op] = YELLOW;
            op--;
            colors[op] = WHITE;
            play_sample(MENU_MOVE_SOUND);
            flip_map_selection(op, false);
          }
          break;
        case ALLEGRO_KEY_ENTER:
          play_sample(MENU_SELECT_SOUND);
          return op;
      }
    }
  }
  return 0;
}
