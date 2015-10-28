//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"
#include "include/Game/MapData.h"
#include "include/Saves/GameSave.h"
class CollisionHandler;
#include "include/Game/CollisionHandler.h"

#define GAME_SUND_FILE "resources/music/gamesong.wav"
#define PLAYER_BITMAP_FILE "resources/graphics/Character.png"

#define KACBAR_C4 "resources/graphics/Kacbar1.png"
#define MELE_KACBAR "resources/graphics/Kacbar2.png"
#define OTHER_KACBAR "resources/graphics/ot.png"

#define _MAP_WALLS

class ScreenGame
{
private:
    bool cutscene_playing = true;
    Button *cutscene_button = nullptr;
    Button *pause_button = nullptr;
    Button *main_menu_button = nullptr;
    Button *respawn_button = nullptr;

    bool paused = false;

    float botom_panel_x1, botom_panel_y1, botom_panel_x2, botom_panel_y2;
    b2World *world = nullptr;

    signed int gui_height;
    float map_draw_x, map_draw_y;

    ALLEGRO_BITMAP *player_bmp = nullptr;
    ALLEGRO_FONT *pause_f = nullptr;

    ALLEGRO_SAMPLE *game_music = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *game_music_instance = nullptr;

    struct sound_effect{
        ALLEGRO_SAMPLE *sample = nullptr;
        ALLEGRO_SAMPLE_INSTANCE *instance = nullptr;
    };

    enum colision_filters{
        c_WALL = 0x0001,
        c_PLYER_PROJECTILE = 0x0002,
        c_ITEM = 0x0004,
        c_ENEMY = 0x0008,
        c_PLAYER = 0x0010,
        c_EVENT_LOCATION = 0x0020
    };

    struct universal_data{
        int vectro_poz;
        int which_vector;
    };

     #ifdef _MAP_WALLS
    b2Body *walltester = nullptr;
    universal_data walltesterdat;
    #endif

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

    //mess
    int dead_fade_counter = 0;
public:
    float p_angle = 0;

    CollisionHandler *colider = nullptr;
    enum enttype{C4KACK = 0, MELEKACK, DICK_BUTT, PLAYER = 99};
    enum vectors{ENTITY_VECTOR, WALLS_VECTOR, ITEMS_VECTOR};
    std::vector<entity*> entities;
    std::vector<Wall*> walls;
    std::vector<map_Item*> mItems;

    #define NUMBER_OF_SOUNDEFECTS 1
    std::string soundfiles[NUMBER_OF_SOUNDEFECTS] = { "resources/music/dead.wav" };
    enum{sound_DEAD = 0};
    std::vector<sound_effect *> sounds;

    bool dead = false;
    bool tp_to_wall = false;

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
