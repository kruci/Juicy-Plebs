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

    game_music = al_load_sample(GAME_SUND_FILE);
    if(game_music == nullptr)
    {
        std::string dum = GAME_SUND_FILE;
        error_message("Could not load file: " + dum);
    }
    game_music_instance = al_create_sample_instance(game_music);
    if(game_music_instance == nullptr)
    {
        std::string dum = GAME_SUND_FILE;
        error_message("Could not create sample instance: " + dum);
    }
}

ScreenGame::~ScreenGame()
{
    al_stop_sample_instance(game_music_instance);
    al_detach_sample_instance(game_music_instance);
    if(game_music_instance != nullptr)
        al_destroy_sample_instance(game_music_instance);
     if(game_music != nullptr)
        al_destroy_sample(game_music);

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
        al_destroy_bitmap(entities[a]->bitmap);
    }
    entities.clear();

    for(int a = 0;a < walls.size();a++)
    {
        world->DestroyBody(walls[a]->body);
    }
    walls.clear();

    for(int a = 0;a < mItems.size();a++)
    {
        world->DestroyBody(mItems[a]->body);
        al_destroy_bitmap(mItems[a]->bitmap);
    }
    mItems.clear();

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
            global::audio_player->Play_sample_instance(&game_music_instance, ALLEGRO_PLAYMODE_LOOP);
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
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && global::audio_b->is_button_clicking() == false
            && global::audio_b->jst_clicked == false)
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
        if(cutscene_playing == false)
            global::audio_player->Play_sample_instance(&game_music_instance, ALLEGRO_PLAYMODE_LOOP);

        return;
    }
    else if(paused == false)
    {
        world->Step(1.0f/global::FPS, 5, 2); // collisison
        //cammera
        map_draw_x = METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - global::dWidth/2;
        map_draw_y = -METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - global::dHeight/2;
        //player rot
        float p_angle = atan2( (global::mouse_state.y) / (global::yscale) - (-METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - map_draw_y),
                            (global::mouse_state.x) / (global::xscale) - (METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - map_draw_x) );
        entities[0]->body->SetTransform(entities[0]->body->GetPosition(),p_angle);

        //cammera cornsrs fix
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

    //map
    map_bitmap->Draw_bitmap_region(map_draw_x, map_draw_y, global::dWidth, global::dHeight - gui_height, 0, 0, 0);

    //items
    for(int a = 0;a < (int)mItems.size();a++)
    {
        if(METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) +40 >= map_draw_x &&
           METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) - 40 <= map_draw_x + global::dWidth &&
           METERS_TO_PIXELS(-mItems[a]->body->GetPosition().y) +40 >= map_draw_y &&
           METERS_TO_PIXELS(-mItems[a]->body->GetPosition().y) - 40 <= map_draw_y + global::dHeight)
        {
            al_draw_bitmap(mItems[a]->bitmap, METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) - map_draw_x - al_get_bitmap_width(mItems[a]->bitmap)/2,
                                   -METERS_TO_PIXELS(mItems[a]->body->GetPosition().y) - map_draw_y - al_get_bitmap_height(mItems[a]->bitmap)/2, 0);
        }
    }
    //merge these 2 fors ?
    //npc
    for(int a = 1;a < (int)entities.size();a++)
    {
        if(METERS_TO_PIXELS(entities[a]->body->GetPosition().x) +40 >= map_draw_x &&
           METERS_TO_PIXELS(entities[a]->body->GetPosition().x) - 40 <= map_draw_x + global::dWidth &&
           METERS_TO_PIXELS(-entities[a]->body->GetPosition().y) +40 >= map_draw_y &&
           METERS_TO_PIXELS(-entities[a]->body->GetPosition().y) - 40 <= map_draw_y + global::dHeight)
        {

            al_draw_rotated_bitmap(entities[a]->bitmap,
            40, 40, METERS_TO_PIXELS(entities[a]->body->GetPosition().x) - map_draw_x,
                                   -METERS_TO_PIXELS(entities[a]->body->GetPosition().y) - map_draw_y, 0, 0);
        }
    }
    //player
    al_draw_rotated_bitmap(entities[0]->bitmap, 50.0f, 50.0f, METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - map_draw_x,
                           -METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - map_draw_y, entities[0]->body->GetAngle(), 0);
    //-----

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

    global::audio_player->Stop_sample_instance(&game_music_instance);

    /*for(int a = 0;a < global::audio_player->global_sounds.size();a++)
    {
        al_set_sample_instance_gain(global::audio_player->global_sounds[a],0);
    }*/

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
        al_destroy_bitmap(entities[a]->bitmap);
    }
    entities.clear();

    for(int a = 0;a < walls.size();a++)
    {
        world->DestroyBody(walls[a]->body);
    }
    walls.clear();

    for(int a = 0;a < mItems.size();a++)
    {
        world->DestroyBody(mItems[a]->body);
        al_destroy_bitmap(mItems[a]->bitmap);
    }
    mItems.clear();

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

    std::string dum;
    /**Player*/
    entities.push_back(new entity);
    b2BodyDef Player_body_def;
    Player_body_def.type = b2_dynamicBody;
    Player_body_def.position.Set(PIXELS_TO_METERS(mapdat->player_spawm_x), PIXELS_TO_METERS(-mapdat->player_spawm_y)); //set the starting position
    Player_body_def.angle = 0; //set the starting angle
    entities[entities.size()-1]->body = world->CreateBody(&Player_body_def);

    b2Vec2 vertices[6];
    vertices[0].Set(-PIXELS_TO_METERS(49),  -PIXELS_TO_METERS(22)); //left bottom
    vertices[1].Set( PIXELS_TO_METERS(13),  -PIXELS_TO_METERS(47));
    vertices[2].Set( PIXELS_TO_METERS(47),  -PIXELS_TO_METERS(40));
    vertices[3].Set( PIXELS_TO_METERS(47),   PIXELS_TO_METERS(64));
    vertices[4].Set( PIXELS_TO_METERS(40),   PIXELS_TO_METERS(48));
    vertices[5].Set(-PIXELS_TO_METERS(49),   PIXELS_TO_METERS(23));

    b2PolygonShape Player_shape;
    Player_shape.Set(vertices, 6);

    b2FixtureDef Player_fixture_def;
    Player_fixture_def.shape = &Player_shape;
    Player_fixture_def.filter.categoryBits = c_PLAYER; //what this is
    Player_fixture_def.filter.maskBits = c_WALL | c_ENEMY | c_ITEM;//what i collide with
    entities[entities.size()-1]->body->CreateFixture(&Player_fixture_def);

    entities[entities.size()-1]->bitmap = al_load_bitmap(PLAYER_BITMAP_FILE);
    if(entities[entities.size()-1]->bitmap == nullptr)
    {
        dum = PLAYER_BITMAP_FILE;
        error_message("Could not load image: " + dum);
    }

    //load other
    b2BodyDef body_def;
    b2PolygonShape shape; //Player_shape.SetAsBox(0.5f, 0.5f);
    b2FixtureDef fixture;
    float mid_x = 0, mid_y = 0, width = 0, height = 0;
    for(int a = 0;a < (int)mapdat->objects.size();a++)
    {
        if(mapdat->objects[a]->type == MapData::WALL)
        {
            width = (mapdat->objects[a]->x1 > mapdat->objects[a]->x2 ? mapdat->objects[a]->x1 - mapdat->objects[a]->x2:
                     mapdat->objects[a]->x2 - mapdat->objects[a]->x1);
            height = (mapdat->objects[a]->y1 > mapdat->objects[a]->y2 ? mapdat->objects[a]->y1 - mapdat->objects[a]->y2:
                     mapdat->objects[a]->y2 - mapdat->objects[a]->y1);

            mid_x = (mapdat->objects[a]->x1 > mapdat->objects[a]->x2 ? mapdat->objects[a]->x2 + width/2 : mapdat->objects[a]->x1 + width/2);
            mid_y = (mapdat->objects[a]->y1 > mapdat->objects[a]->y2 ? mapdat->objects[a]->y2 + height/2 : mapdat->objects[a]->y1 + height/2);
            //walls_and_items.push_back(new B2body);
            body_def.type = b2_staticBody;
            body_def.position.Set(PIXELS_TO_METERS(mid_x), -PIXELS_TO_METERS(mid_y));
            //walls_and_items[walls_and_items.size()-1]= world->CreateBody(&body_def);
            walls.push_back(new Wall);
            walls[walls.size()-1]->body = world->CreateBody(&body_def);
            shape.SetAsBox(PIXELS_TO_METERS(width/2), PIXELS_TO_METERS(height/2));
            fixture.shape = &shape;
            fixture.filter.categoryBits = c_WALL;
            fixture.filter.maskBits = c_PLAYER | c_PLYER_PROJECTILE | c_ENEMY | c_ITEM;
            walls[walls.size()-1]->body->CreateFixture(&fixture);
            walls[walls.size()-1]->data.vectro_poz = walls.size()-1;
            walls[walls.size()-1]->data.which_vector = WALLS_VECTOR;
            walls[walls.size()-1]->body->SetUserData( &walls[walls.size()-1]->data );
        }
        else if(mapdat->objects[a]->type == MapData::ENEMY_SPAWN)
        {
            entities.push_back(new entity);
            body_def.type = b2_dynamicBody;
            body_def.position.Set(PIXELS_TO_METERS(mapdat->objects[a]->x1), -PIXELS_TO_METERS(mapdat->objects[a]->y1));
            entities[entities.size()-1]->body = world->CreateBody(&body_def);
            shape.SetAsBox(PIXELS_TO_METERS(30), PIXELS_TO_METERS(30));
            fixture.filter.categoryBits = c_ENEMY;
            fixture.filter.maskBits = c_PLAYER | c_PLYER_PROJECTILE | c_WALL;
            fixture.shape = &shape;
            entities[entities.size()-1]->body->CreateFixture(&fixture);
            entities[entities.size()-1]->data.vectro_poz = entities.size()-1;
            entities[entities.size()-1]->data.which_vector = ITEMS_VECTOR;
            entities[entities.size()-1]->body->SetUserData( &entities[entities.size()-1]->data );

            std::string kackar_bitmap;
            if(mapdat->objects[a]->enemy == 0)
            {
                kackar_bitmap = KACBAR_C4;
            }
            else if(mapdat->objects[a]->enemy == 1)
            {
                kackar_bitmap = MELE_KACBAR;
            }
            else
            {
                kackar_bitmap = OTHER_KACBAR;
            }

            entities[entities.size()-1]->bitmap = al_load_bitmap(kackar_bitmap.c_str());
            if(entities[entities.size()-1]->bitmap == nullptr)
            {
                error_message("Could not load image: " + kackar_bitmap);
            }
        }
        else if(mapdat->objects[a]->type == MapData::ITEM_SPAWN)
        {
            //walls_and_items.pushback(new B2body);
            body_def.type = b2_staticBody;
            body_def.position.Set(PIXELS_TO_METERS(mapdat->objects[a]->x1), -PIXELS_TO_METERS(mapdat->objects[a]->y1));
            mItems.push_back(new map_Item);
            mItems[mItems.size()-1]->body = world->CreateBody(&body_def);
            shape.SetAsBox(PIXELS_TO_METERS(30), PIXELS_TO_METERS(30));
            fixture.filter.categoryBits = c_ENEMY;
            fixture.filter.maskBits = c_PLAYER | c_PLYER_PROJECTILE | c_WALL;
            fixture.shape = &shape;
            mItems[mItems.size()-1]->body->CreateFixture(&fixture);
            mItems[mItems.size()-1]->type = mapdat->objects[a]->item;
            mItems[mItems.size()-1]->data.vectro_poz = mItems.size()-1;
            mItems[mItems.size()-1]->data.which_vector = ITEMS_VECTOR;
            mItems[mItems.size()-1]->body->SetUserData( &mItems[mItems.size()-1]->data );

            dum = "resources/graphics/item_" + std::to_string(mapdat->objects[a]->item) + ".png";
            mItems[mItems.size()-1]->bitmap = al_load_bitmap(dum.c_str());
            if(mItems[mItems.size()-1]->bitmap == nullptr)
            {
                error_message("Could not load image: " + dum);
            }
        }
    }

    return true;
}
