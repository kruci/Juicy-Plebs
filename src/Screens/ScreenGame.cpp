//R.K.
#include "ScreenGame.h"

ScreenGame::ScreenGame()
{
    cutscene_button = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Skip", al_map_rgb(0,0,128));

    SCIntro = new ScreenIntro(&cutscene_playing);

    gui_height = 100 + (global::dHeight - 810);
    if(gui_height <= 0)
    {
        gui_height = 100;
    }

    player_bmp = al_load_bitmap("resources/graphics/Character.png");
    if(player_bmp == nullptr)
        error_message("Could not load image: resources/graphics/Character.png");

    pause_button = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Pause", al_map_rgb(0,0,128));
    main_menu_button = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Main menu", al_map_rgb(0,0,128));

    pause_f = al_load_ttf_font("resources/fonts/Calibri.ttf", 50, 0);
    if(pause_f == nullptr)
    {
        error_message("Could not load font: resources/fonts/Calibri.ttf");
    }
}

ScreenGame::~ScreenGame()
{
    if(cutscene_button != nullptr)
        delete cutscene_button;

    if(SCIntro != nullptr)
        delete SCIntro;

    if(map_bitmap != nullptr)
        delete map_bitmap;

    if(mapdat != nullptr)
        delete mapdat;

    if(pause_button != nullptr)
        delete pause_button;

    if(main_menu_button != nullptr)
        delete main_menu_button;

    if(player_bmp != nullptr)
        al_destroy_bitmap(player_bmp);

    if(pause_f != nullptr)
        al_destroy_font(pause_f);

    for(int a = 0;a < (int)entities.size();a++)
    {
        world->DestroyBody(entities[a]->body);
    }
    entities.clear();

    if(world != nullptr)
        delete world;
}

void ScreenGame::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    if(cutscene_playing == true)
    {
        cutscene_button->Input(event, xscale, yscale);
        if(cutscene_button->is_button_clicked() == true)
        {
            cutscene_playing = false;
            cutscene_button->unclick();
            SCIntro->Stop();
        }
        return;
    }
    else if(paused == true)
    {
        if(main_menu_button->Input(event, xscale, yscale) == 2)
        {
            global::play = false;
            return;
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            paused = false;
            pause_button->unclick();
        }
    }
    else if(pause_button->Input(event, xscale, yscale) == 2)
    {
        paused = true;
        return;
    }

    //mapinput
    //gui input
    //check if input to pause

    return;
}

void ScreenGame::Print()
{
    if(global::play == false)
    {
        return;
    }

    al_clear_to_color(al_map_rgb(0,0,35));
    if(cutscene_playing == true)
    {
        SCIntro->Print();
        cutscene_button->Print();
        return;
    }
    else if(paused == false)
    {
        world->Step(1.0f/global::FPS, 5, 2); // collisison



        if(map_draw_x < global::dWidth/2)
        {
            map_draw_x = 0;
        }
        else if(map_draw_x > map_bitmap->width - global::dWidth/2)
        {
            map_draw_x = map_bitmap->width - global::dWidth;
        }

        if(map_draw_y < (global::dWidth - gui_height)/2)
        {
            map_draw_y = 0;
        }
        else if(map_draw_y > map_bitmap->height - (global::dWidth - gui_height)/2)
        {
            map_draw_y = map_bitmap->height - global::dHeight;
        }
    }

    map_bitmap->Draw_bitmap_region(map_draw_x, map_draw_y, global::dWidth, global::dHeight - gui_height, 0, 0, 0);
    //print map and entities
    //print GUI
    al_draw_filled_rectangle(0, global::dHeight - gui_height, global::dWidth, global::dHeight, al_map_rgb(88,88,88));
    pause_button->Print();

    if(paused == true)
    {
        al_draw_filled_rectangle(0,0, global::dWidth, global::dHeight, al_map_rgba(0,0,0,185));
        al_draw_text(pause_f, al_map_rgb(200,200,200), (global::dWidth - al_get_text_width( pause_f, "Click to unpause"))/2,
                     (global::dHeight - al_get_font_ascent(pause_f))/2, 0, "Click to unpause");
        main_menu_button->Print();

    }

    return;
}

bool ScreenGame::Set_mission(int mission)
{
    ALLEGRO_FONT *loading_f = nullptr;
    loading_f = al_load_ttf_font("resources/fonts/Calibri.ttf", 40, 0);
    if(loading_f != nullptr)
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(loading_f, al_map_rgb(255,255,255), (global::dWidth - al_get_text_width( loading_f, "Loading ..."))/2,
                     (global::dHeight - al_get_font_ascent(loading_f))/2, 0, "Loading ...");
        al_flip_display();
        al_destroy_font(loading_f);
    }

    for(int a = 0;a < global::audio_player->global_sounds.size();a++)
    {
        al_set_sample_instance_gain(global::audio_player->global_sounds[a],0);
    }

    if(mission == 1)
    {
        SCIntro->Reset();

        SCIntro->Add_image("resources/cutscenes/test/zemiak.jpeg",  0.0f,  3.2f, 100, 100);
        SCIntro->Add_sound("resources/cutscenes/test/naobrazkumozmevidietzemiak.wav",  0.0f,  3.2f);

        SCIntro->Add_image("resources/cutscenes/test/badass_zemiak.jpg",  3.4f,  3.2f, 100, 100);
        SCIntro->Add_sound("resources/cutscenes/test/naobrazkumozmevidietzemiak_hlboke.wav",  3.4f,  3.2f);
    }
    //add more mission intro code or do universal cfg loader

    if(map_bitmap != nullptr)
    {
        delete map_bitmap;
        map_bitmap = nullptr;
    }

    for(int a = 0;a < (int)entities.size();a++)
    {
        world->DestroyBody(entities[a]->body);
    }
    entities.clear();

    if(world != nullptr)
    {
        delete world;
        world = nullptr;
    }

    if(mapdat != nullptr)
    {
        delete mapdat;
        mapdat = nullptr;
    }

    map_bitmap = new BigBitmap("resources/maps/map" + std::to_string(mission) + ".jpg", 512, 512);
    mapdat = new MapData("resources/maps/map" + std::to_string(mission) + ".map");
    map_draw_x = mapdat->player_spawm_x - global::dWidth/2;
    map_draw_y = mapdat->player_spawm_y - (global::dHeight - gui_height)/2;
    world = new b2World(b2Vec2(0,0));

    //player


    return true;
}
