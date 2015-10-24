//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"
#include "include/Game/MapData.h"

class ScreenGame
{
private:
    bool cutscene_playing = true;
    Button *cutscene_button = nullptr;
    Button *pause_button = nullptr;
    Button *main_menu_button = nullptr;

    bool paused = false;

    float botom_panel_x1, botom_panel_y1, botom_panel_x2, botom_panel_y2;
    b2World *world = nullptr;

    signed int gui_height;
    float map_draw_x, map_draw_y;

    ALLEGRO_BITMAP *player_bmp = nullptr;
public:
    ScreenIntro * SCIntro = nullptr;
    BigBitmap *map_bitmap = nullptr;
    MapData *mapdat = nullptr;

    ScreenGame();
    virtual ~ScreenGame();

    bool Set_mission(int mission);

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENGAME_H
