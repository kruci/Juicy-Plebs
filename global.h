//R.K.
#ifndef GLOBAL_H
#define GLOBAL_H

//Other includes
#include <iostream>
#include <vector>
#include <cmath>

//ALLEGRO 5 includes
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_memfile.h>

//my fabulous GUI
#include "rGUIl.h"

//this project

//defines
#define DEGTORAD(deg) ((float)deg * ALLEGRO_PI)/180.0f
#define RADTODEG(rad) ((float)rad * 180.0f)/ALLEGRO_PI

#define TICK_CALC_START clock_t __tick_calc_cl = clock();
#define TICK_CALC_END std::cout << clock() - __tick_calc_cl << std::endl;

class GameSave;

namespace global
{
    extern float FPS;
    extern int dHeight;// d means display - size of drawing board
    extern int dWidth;
    extern int sHeight;// s means screen - after resise
    extern int sWidth;
    extern float xscale;
    extern float yscale;
    extern float aspectratio;
    extern int xratio; //monitor ration
    extern int yratio;
    extern ALLEGRO_TRANSFORM trans;
    extern ALLEGRO_MOUSE_STATE mouse_state;

    extern bool loop;
    extern bool audio;
    extern bool play;

    extern GameSave *save;
}

extern inline int error_message(std::string error_string);
extern inline int fatal_error_message(std::string error_string);

#endif // GLOBAL_H
