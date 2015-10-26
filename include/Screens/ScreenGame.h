//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"
#include "include/Game/MapData.h"

#define GAME_SUND_FILE "resources/music/gamesong.wav"

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
    ALLEGRO_FONT *pause_f = nullptr;

    ALLEGRO_SAMPLE *game_music = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *game_music_instance = nullptr;

    struct entity{
        b2Body *body = nullptr;
        int type;
        float hp;
        float shield;
        float speed;
    };

    std::vector<entity*> entities;

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
