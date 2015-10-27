//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"
#include "include/Game/MapData.h"

#define GAME_SUND_FILE "resources/music/gamesong.wav"
#define PLAYER_BITMAP_FILE "resources/graphics/Character.png"

#define KACBAR_C4 "resources/graphics/Kacbar1.png"
#define MELE_KACBAR "resources/graphics/Kacbar2.png"
#define OTHER_KACBAR "resources/graphics/ot.png"

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

    //enum enttype{PLAYER = 0, C4KACK, MELEKACK, BOSS};
    enum vectors{ENTITY_VECTOR, WALLS_VECTOR, ITEMS_VECTOR};

    enum colision_filters{
        c_WALL = 0x0001,
        c_PLYER_PROJECTILE = 0x0002,
        c_ITEM = 0x0004,
        c_ENEMY = 0x0008,
        c_PLAYER = 0x0010
    };

    struct universal_data{
        int vectro_poz;
        int which_vector;
    };

    //1. entity is player
    struct entity{
        b2Body *body = nullptr;
        ALLEGRO_BITMAP *bitmap = nullptr;
        int type;
        float hp;
        float shield;
        float speed;
        universal_data data;
    };

    struct map_Item{
        b2Body *body = nullptr;
        ALLEGRO_BITMAP *bitmap = nullptr;
        int type;
        universal_data data;
    };

    struct Wall{
        b2Body *body = nullptr;
        universal_data data;
    };

    std::vector<entity*> entities;
    std::vector<Wall*> walls;
    std::vector<map_Item*> mItems;

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
