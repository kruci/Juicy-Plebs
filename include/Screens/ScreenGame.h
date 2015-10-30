//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"
#include "include/Game/MapData.h"
#include "include/Saves/GameSave.h"
class CollisionHandler;
class RayCastCallBack;
#include "include/Game/CollisionHandler.h"

#define GAME_SUND_FILE "resources/music/gamesong.wav"
#define PLAYER_BITMAP_FILE "resources/graphics/Character.png"

#define KACBAR_C4 "resources/graphics/Kacbar1.png"
#define MELE_KACBAR "resources/graphics/Kacbar2.png"
#define OTHER_KACBAR "resources/graphics/ot.png"

#define AB_IMAGE_SIZE 50
#define MAX_MISSIONS 1

#define _MAP_WALLS
#define _MAP_PF_ZONES

class ScreenGame
{
private:
    bool cutscene_playing = true;
    Button *cutscene_button = nullptr;
    Button *pause_button = nullptr;
    Button *main_menu_button = nullptr;
    Button *respawn_button = nullptr;
    Button *next_lvl = nullptr;

    bool paused = false;

    float botom_panel_x1, botom_panel_y1, botom_panel_x2, botom_panel_y2;
    b2World *world = nullptr;

    signed int gui_height;
    float map_draw_x, map_draw_y;

    ALLEGRO_BITMAP *player_bmp = nullptr;
    ALLEGRO_FONT *pause_f = nullptr;
    ALLEGRO_FONT *mouse_b_f = nullptr;
    std::string mouse_but_text[3] = {"LB" , "MB", "RB"};

    ALLEGRO_SAMPLE *game_music = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *game_music_instance = nullptr;

    struct sound_effect{
        ALLEGRO_SAMPLE *sample = nullptr;
        ALLEGRO_SAMPLE_INSTANCE *instance = nullptr;
    };

    enum colision_filters{
        c_WALL =  1 ,//0x0001,
        c_PLYER_PROJECTILE =  2,//0x0002,
        c_ITEM = 4,//0x0004,
        c_ENEMY = 8,//0x0008,
        c_PLAYER = 16,//0x0010,
        c_EVENT_LOCATION = 32,//0x0020,
        c_TEST_BOX = 64//0x0040
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
        bool to_delete = false;
        universal_data data;
        bool fainding_path = false;
    };

    struct map_Item{
        b2Body *body = nullptr;
        ALLEGRO_BITMAP *bitmap = nullptr;
        int type;
        universal_data data;
        bool to_delete = false;
    };

    struct Wall{
        b2Body *body = nullptr;
        universal_data data;
    };

    enum{sl_NORMAL, sl_LB, sl_MB,  sl_RB};
    struct Ability{
        ALLEGRO_BITMAP *bitmap = nullptr;
        Button *ab_but = nullptr;
        bool in_use = false;
        bool usable = false;
        bool L_click = false, R_click = false;
        bool unlocked = false;
        float cool_down = 0;
        float remaining_cd = 0;
        float cast_time = 0;
        float remaining_time_to_cast = 0;
        int special_slot = 0;
    };


    #define NUMBER_OF_PROJECTILE_TYPES 1
    std::string projectiles_image_files[NUMBER_OF_PROJECTILE_TYPES] = {"resources/graphics/projectile_0.png"};
    std::vector<ALLEGRO_BITMAP*> projectiles_bitmaps;
    struct Projectile{
        ALLEGRO_BITMAP *bitmap = nullptr;
        b2Body *body = nullptr;
        universal_data data;
        bool to_delete = false;
        float damage = 0;
        float width_pixel = 0;
        float height_pixel = 0;
    };

    void unclick_other_ab_but(int just_clicked);

    /**so it doesnt have to create these every time*/
        float g_pro_vel_x, g_pro_vel_y, g_pro_angle;
        b2BodyDef gbody_def;
        b2PolygonShape gshape;
        b2FixtureDef gfixture;
    void add_projectile(float damage, ALLEGRO_BITMAP **bmp, float width_pixel, float height_pixel, float speed_inmeters = 3.0f);

    struct int_coords{
        int x = 0;
        int y = 0;
    };

    int_coords pixel_coors_to_pf_coords(int x, int y);

    //mess
    int dead_fade_counter = 0;
    float range = global::dHeight/2 - 10;
public:
    float p_angle = 0;
    int p_pf_poz[2] = {0};

    CollisionHandler *colider = nullptr;
    RayCastCallBack *raycallback = nullptr;
    enum enttype{C4KACK = 0, MELEKACK, DICK_BUTT, PLAYER = 99};
    enum vectors{ENTITY_VECTOR, WALLS_VECTOR, ITEMS_VECTOR, PROJECTILES_VECTOR, TEST_VECTOR};
    std::vector<entity*> entities;
    std::vector<Wall*> walls;
    std::vector<map_Item*> mItems;

    #define NUMBER_OF_SOUNDEFECTS 1
    std::string soundfiles[NUMBER_OF_SOUNDEFECTS] = { "resources/music/dead.wav" };
    enum{sound_DEAD = 0};
    std::vector<sound_effect *> sounds;

    #define NUMBER_OF_AB 5
    enum{ab_TELEPORT, ab_ATTACK_PLUVANCE, ab_BRICK, ab_AUTO_SUPACKA, ab_TEST_JUP};
    std::vector<Ability *> abilities;
    std::vector<Projectile*> projectiles;

    bool dead = false;
    bool tp_fail = false;
    bool just_tp = false;
    bool dont_move = false;
    b2Vec2 pre_tp, bonus;

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
