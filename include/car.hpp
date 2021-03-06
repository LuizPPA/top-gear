#ifndef CAR_H 
#define CAR_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "object.hpp"

// Environmental values
#define GRASS_SLOW_EFFECT 0.13333333333
#define NO_ACCELERATE_EFFECT 0.05433333333
#define BREAK_EFFECT 0.73
#define WRONG_GEAR_EFFECT 0.00166666666
#define DISTANCE_VARIATION 0.147778
#define STARTING_DISTANCE 130
#define COLLISION_DISTANCE 50
#define COLLISION_CRITICAL_DISTACE 30

#define STANDARD_CAR_WIDTH 166.0
#define STANDARD_CAR_HEIGHT 120.0

namespace top_gear {

  enum CarsTypes {
    DOMINUS = 1,
    OCTANE = 2,
    ROADHOG = 3,
    MAVERICK = 4
  };

  class Car {
    private:
      int lvl;
      char *name;
      int points;
      float width;
      float apparent_width;
      float height;
      float apparent_height;
      float speed;
      float x; // The Car center x coordinate (on the road, where 0 is the center)
      float screen_x; // The Car center x coordinate (on the screen, where 0 is the left border of the window)
      float y; // The Car bottom y coordinate (on the road, a virtual environment)
      float screen_y; // The Car center y coordinate (on the screen, where 0 is the top of the window)
      float nitrox;
      int gear;
      int max_gear;
      bool will_colide;
      bool going_right;
      ALLEGRO_BITMAP* texture;
      
      bool is_aligned_to(Object* object);
      bool is_aligned_to(Car* car);
      float ai_gear_up_point();
      static int partition(Car** cars, int first, int last);
      static Car** quick_sort_helper(Car** cars, int first, int last);

    public:
      Car(ALLEGRO_BITMAP* texture);
      Car(int lvl, ALLEGRO_BITMAP *texture);

      int get_lvl() { return this->lvl; }
      char* get_name() { return this->name; }
      int get_points() { return this->points; }
      float get_width() { return this->width; }
      float get_apparent_width() { return this->apparent_width; }
      float set_apparent_width(float apparent_width) { this->apparent_width = apparent_width; }
      float get_height() { return this->height; }
      float get_apparent_height() { return this->apparent_height; }
      float set_apparent_height(float apparent_height) { this->apparent_height = apparent_height; }
      float get_speed() { return this->speed; }
      float set_speed(float speed) { this->speed = speed; }
      float get_x() { return this->x; }
      float set_x(float x) { this->x = x; }
      float get_screen_x() { return this->screen_x; }
      float set_screen_x(float screen_x) { this->screen_x = screen_x; }
      float get_y() { return this->y; }
      float set_y(float y) { this->y = y; }
      float get_screen_y() { return this->screen_y; }
      float set_screen_y(float screen_y) { this->screen_y = screen_y; }
      float get_nitrox() { return this->nitrox; }
      float set_nitrox(float nitrox) { this->nitrox = nitrox; }
      float speed_increase();
      int get_gear() { return this->gear; }
      int get_max_gear() { return this->max_gear; }
      bool get_will_colide() { return this->will_colide; }
      bool get_going_right() { return this->going_right; }
      ALLEGRO_BITMAP* get_texture() { return this->texture; }

      void gear_up();
      void gear_down();
      void set_gear(int gear);
      void control_ia(Car** cars, Object** objects, int car_count, int object_count, bool play_sounds);
      int get_gear_progress();
      bool car_collided(Car** cars, Object** objects, int car_count, int object_count);
      static void restart_positions(Car** Cars, int count);
      static float max_speed(int gear);
      static Car** quick_sort_cars(Car** cars, int size);
  };

}

#endif