#ifndef COLORS_H
#define COLORS_H

#include <allegro5/allegro5.h>

namespace top_gear{

    namespace colors {

        extern ALLEGRO_COLOR BLACK;
        extern ALLEGRO_COLOR WHITE;
        extern ALLEGRO_COLOR GREY;
        extern ALLEGRO_COLOR BLUE;
        extern ALLEGRO_COLOR LIGHT_BLUE;
        extern ALLEGRO_COLOR RED;
        extern ALLEGRO_COLOR ORANGE;
        extern ALLEGRO_COLOR YELLOW_ORANGE;
        extern ALLEGRO_COLOR YELLOW;
        extern ALLEGRO_COLOR GREEN;
        extern ALLEGRO_COLOR LAS_VEGAS_SOIL;
        extern ALLEGRO_COLOR FRANKFURT_SOIL;
        extern ALLEGRO_COLOR HIROSHIMA_SOIL;


        void init_colors();
        ALLEGRO_COLOR rgb(int r, int g, int b);

    }

}

#endif