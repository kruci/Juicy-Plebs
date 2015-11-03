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
#include "include/Game/Explosion.h"

#define GAME_SUND_FILE "resources/music/gamesong.ogg"
#define PLAYER_BITMAP_FILE "resources/graphics/Character.png"

#define KACBAR_C4 "resources/graphics/Kacbar2.png"
#define MELE_KACBAR "resources/graphics/Kacbar1.png"
#define OTHER_KACBAR "resources/graphics/ot.png"
#define BOSS_KACBAR "resources/graphics/boss.png"

#define AB_IMAGE_SIZE 50
#define MAX_MISSIONS 4

//#define _MAP_WALLS
//#define _PURE_MAP_WALLS
//#define _MAP_PF_ZONES

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

    ALLEGRO_BITMAP *explosion_bmp = nullptr;
    ALLEGRO_BITMAP *player_bmp = nullptr;
    ALLEGRO_FONT *pause_f = nullptr;
    ALLEGRO_FONT *mouse_b_f = nullptr;
    std::string mouse_but_text[3] = {"LB" , "MB", "RB"};

    /**supanie*/
    ALLEGRO_BITMAP *supanie_bmp = nullptr;
    #define _SUPANIE_ARRAY_SIZE 20
    bool supanie[_SUPANIE_ARRAY_SIZE][_SUPANIE_ARRAY_SIZE] = {{false}};
    int supacka_width = 70;
    int supanie_box_size = 20;
    bool bool_supanie = false;
    int zemak_side = 400;
    int sup_s_x = (global::dWidth - zemak_side)/2, sup_s_y =  (global::dHeight - zemak_side)/2;
    b2Vec2 tp_to;
    float supacka_cd = 0;
    float dum_supacka_cd = 0;

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
        c_TEST_BOX = 64,//0x0040
        c_MAP_DETECTOR = 128,
        c_GRAPHIC_EFECT = 256,
        c_MAP_WALL_DETECTOR = 512,
        c_KYCH = 1024
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
        float hp= 0;
        float maxhp= 0;
        float shield= 0;
        float speed= 0;
        float speed_change = 1;
        float stunted_for = 0;
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


    #define NUMBER_OF_PROJECTILE_TYPES 3
    std::string projectiles_image_files[NUMBER_OF_PROJECTILE_TYPES] = {"resources/graphics/projectile_0.png",
    "resources/graphics/projectile_1.png" , "resources/graphics/projectile_2.png"};
    std::vector<ALLEGRO_BITMAP*> projectiles_bitmaps;
    struct Projectile{
        ALLEGRO_BITMAP *bitmap = nullptr;
        b2Body *body = nullptr;
        universal_data data;
        bool to_delete = false;
        int type = 99;
        float damage = 0;
        float width_pixel = 0;
        float height_pixel = 0;
        float stun_time = 0;
    };

    void unclick_other_ab_but(int just_clicked);

    /**so it doesnt have to create these every time*/
        float g_pro_vel_x, g_pro_vel_y, g_pro_angle;
        b2BodyDef gbody_def;
        b2PolygonShape gshape;
        b2FixtureDef gfixture;
    void add_projectile(float damage, ALLEGRO_BITMAP **bmp, float width_pixel, float height_pixel,
                        float speed_inmeters = 3.0f, int type = pr_PLUVANEC, float stun_time = 0.0f);

    struct int_coords{
        int x = 0;
        int y = 0;
    };


    #define NUMBER_OF_DETECTOR_TYPES 1
    std::string detector_image_files[NUMBER_OF_DETECTOR_TYPES] = {"resources/graphics/md_0.png"};
    std::vector<ALLEGRO_BITMAP*> detector_bitmaps;
    struct Detector{
        b2Body *body = nullptr;
        b2Body *antiwallbody = nullptr;
        ALLEGRO_BITMAP *bitmap = nullptr;
        universal_data data;
        int type;
        float width_pixel = 0;
        float height_pixel = 0;
        bool to_delete = false;
        float speed_change = 0; // it decrese speed by prectentage (for example 0.5 wile result in 2 times slover speed)
        float hp_change = 0;    // damage
        float time_left = 0;
        float duration = 0;
    };

        b2BodyDef dbody_def;
        b2PolygonShape dshape;
        b2FixtureDef dfixture;

    void add_detector(float damage, ALLEGRO_BITMAP **bmp, float width_pixel, float height_pixel,
                 float speed_reduction, int type, float duration);

    int_coords pixel_coors_to_pf_coords(int x, int y);

    std::mt19937 generator;
    #define RANDOM_HLSKA_POCET 21
    std::vector<sound_effect *> random_hlasky;
    int actual_hlaska = 0;

    #define SUPACIE_HLASKY_POCET 4
    std::vector<sound_effect *> supacie_hlasky;

    //mess
    //float gui_ab_x_mult = 0, ab_button_coord_x = 20, ab_button_coord_y = global::dHeight -(AB_IMAGE_SIZE+20);
    int dead_fade_counter = 0;
    float range = global::dHeight/2 - 10;
    std::vector<Explosion*> explosions;
    signed int what_clicked = -1;
public:
    int actual_mission = 0;

    //mess
    float gui_ab_x_mult = 0, ab_button_coord_x = 20, ab_button_coord_y = global::dHeight -(AB_IMAGE_SIZE+20);
    int selected_ab_for_midle_b = 0;
    int middle_b_poz = 0;
    int scrollable_ab = 0;
    std::vector<int> scrollable_ab_index;
    //----

    float p_angle = 0;
    int p_pf_poz[2] = {0};

    CollisionHandler *colider = nullptr;
    RayCastCallBack *raycallback = nullptr;
    enum enttype{C4KACK = 0, MELEKACK, DICK_BUTT, PLAYER = 99, BOSS = 4};
    enum vectors{ENTITY_VECTOR, WALLS_VECTOR, ITEMS_VECTOR, PROJECTILES_VECTOR, TEST_VECTOR, DETECTOR_VECTOR};
    std::vector<entity*> entities;
    std::vector<Wall*> walls;
    std::vector<map_Item*> mItems;

    #define NUMBER_OF_SOUNDEFECTS 10
    std::string soundfiles[NUMBER_OF_SOUNDEFECTS] = { "resources/music/dead.ogg", "resources/music/boom.ogg",
                "resources/music/alhukackar.ogg", "resources/music/pluvnutie.ogg", "resources/music/teleport.ogg",
                "resources/music/kych.ogg", "resources/music/tehla_thorw.ogg", "resources/music/tehla_to_head.ogg",
                "resources/music/nails.ogg", "resources/music/click.ogg"};
    enum{sound_DEAD = 0, sound_BOOM, sound_ALHUKACKAR, sound_FLUS, sound_TELEPORT, sound_KYCH, sound_BRICKTHROW,
         sound_BRICKTOHEAD, sound_NAILS, sound_CLICK};
    std::vector<sound_effect *> sounds;

    #define NUMBER_OF_AB 9
    enum{ab_TELEPORT, ab_ATTACK_PLUVANCE, ab_BRICK, ab_AUTO_SUPACKA, ab_TEST_JUP, ab_KLINCE, ab_KORENIE, ab_LIGHT_SHOES, ab_DIE_MOTHAFUCKA_DIE};

    std::vector<Ability *> abilities;
    Button *middle_b_ab = nullptr;

    enum{pr_PLUVANEC, pr_BRICK, pr_KYCH};
    std::vector<Projectile*> projectiles;
    enum{d_KLINCE};
    std::vector<Detector*> detectors;

    bool dead = false;
    bool tp_fail = false;
    bool just_tp = false;
    bool dont_move = false;
    b2Vec2 pre_tp, bonus;
    bool die_you_all_mothafuckers = false;
    float die_you_all_mothafuckers_damage = 20;

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
