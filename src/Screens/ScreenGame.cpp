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
    respawn_button = new Button("resources/fonts/Calibri.ttf", (global::dWidth - 120)/2, global::dHeight -70,
                                (global::dWidth - 120)/2 + 120, global::dHeight -70 + 50, "Reload", al_map_rgb(0,0,128));

    next_lvl = new Button("resources/fonts/Calibri.ttf", (global::dWidth - 150)/2, 20,
                                (global::dWidth - 120)/2 + 150, 20 + 62, "Next level", al_map_rgb(0,0,128));

    pause_f = al_load_ttf_font("resources/fonts/Calibri.ttf", 50, 0);
    if(pause_f == nullptr)
    {
        error_message("Could not load font: resources/fonts/Calibri.ttf");
    }

    explosion_bmp = al_load_bitmap("resources/graphics/exp.png");
    if(explosion_bmp == nullptr)
    {
        error_message("Could not load image: resources/graphics/exp.png");
    }

    mouse_b_f = al_load_ttf_font("resources/fonts/Calibri.ttf", 15, 0);
    if(mouse_b_f == nullptr)
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

    for(int a = 0;a < NUMBER_OF_SOUNDEFECTS;a++)
    {
        sounds.push_back(new sound_effect);
        sounds[a]->sample = al_load_sample(soundfiles[a].c_str());
        if(sounds[a]->sample == nullptr)
        {
            error_message("Could not load file: " + soundfiles[a]);
        }
        sounds[a]->instance = al_create_sample_instance(sounds[a]->sample);
        if(game_music_instance == nullptr)
        {
            error_message("Could not create sample instance: " + soundfiles[a]);
        }
    }

    //std::string ab_images[NUMBER_OF_AB] = {};
    float ab_button_coord_x = 20, ab_button_coord_y = global::dHeight -(AB_IMAGE_SIZE+20);
    bool ab_active[NUMBER_OF_AB] = {true, true, true, false, false};
    float ab_cd[NUMBER_OF_AB] = {1.5, 0.2, 3, 0.8, -1};
    float ab_ct[NUMBER_OF_AB] = {0.1,   0, 0,   0,  0};

    std::string ddum = "resources/graphics/item_";
    std::string ddum2;
    float dum_x1 = 1150, dum_x2 = 1030;

    for(int a = 0;a < NUMBER_OF_AB;a++)
    {
        abilities.push_back(new Ability);
        abilities[a]->usable = ab_active[a];
        abilities[a]->unlocked = global::save->Get_item(a);

        abilities[a]->cool_down = global::save->Get_ab_cd(a) ;
        if(abilities[a]->cool_down == -1)
            abilities[a]->cool_down = ab_cd[a];

        abilities[a]->cast_time = global::save->Get_ab_cast_t(a) ;
        if(abilities[a]->cast_time == -1)
            abilities[a]->cast_time = ab_ct[a];

        if(ab_active[a] == true)
        {
            ddum2 = ddum + std::to_string(a) + ".png";
            abilities[a]->bitmap = al_load_bitmap(ddum2.c_str());
            if(abilities[a]->bitmap == nullptr)
            {
                error_message("Could not load iamge: " + ddum2);
            }

            if(a > 1)
            {
                abilities[a]->ab_but = new Button(ab_button_coord_x, ab_button_coord_y, ab_button_coord_x + AB_IMAGE_SIZE, ab_button_coord_y + AB_IMAGE_SIZE);
            }
            else if(a == 0)
            {
                abilities[a]->ab_but = new Button(dum_x1, ab_button_coord_y, dum_x1 + AB_IMAGE_SIZE, ab_button_coord_y + AB_IMAGE_SIZE);
                abilities[a]->unlocked = 1;
            }
            else if(a == 1)
            {
                abilities[a]->ab_but = new Button(dum_x2, ab_button_coord_y, dum_x2 + AB_IMAGE_SIZE, ab_button_coord_y + AB_IMAGE_SIZE);
                abilities[a]->unlocked = 1;
            }
        }
    }

    for(int a = 0;a < NUMBER_OF_PROJECTILE_TYPES;a++)
    {
        projectiles_bitmaps.push_back(al_load_bitmap(projectiles_image_files[a].c_str()));
        if(projectiles_bitmaps[a] == nullptr)
        {
            error_message("Could not load iamge: " + projectiles_image_files[a]);
        }
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

    if(explosion_bmp != nullptr)
        al_destroy_bitmap(explosion_bmp);

    if(pause_f != nullptr)
        al_destroy_font(pause_f);

    if(mouse_b_f!= nullptr)
        al_destroy_font(mouse_b_f);

    if(next_lvl != nullptr)
        delete next_lvl;

    for(int a = 0;a < (int)entities.size();a++)
    {
        world->DestroyBody(entities[a]->body);
        al_destroy_bitmap(entities[a]->bitmap);
        delete entities[a];
    }
    entities.clear();

    for(int a = 0;a < (int)abilities.size();a++)
    {
        if(abilities[a]->bitmap != nullptr)
            al_destroy_bitmap(abilities[a]->bitmap);

        if(abilities[a]->ab_but != nullptr)
            delete abilities[a]->ab_but;

        delete abilities[a];
    }
    abilities.clear();

    for(int a = 0;a < (int)sounds.size();a++)
    {
        global::audio_player->Stop_sample_instance(&sounds[a]->instance);
        al_destroy_sample(sounds[a]->sample);
        al_destroy_sample_instance(sounds[a]->instance);
        delete sounds[a];
    }
    sounds.clear();

    for(int a = 0;a < (int)walls.size();a++)
    {
        world->DestroyBody(walls[a]->body);
        delete walls[a];
    }
    walls.clear();

    for(int a = 0;a < explosions.size();a++)
    {
        delete explosions[a];
    }
    explosions.clear();

    for(int a = 0;a < (int)mItems.size();a++)
    {
        world->DestroyBody(mItems[a]->body);
        al_destroy_bitmap(mItems[a]->bitmap);
        delete mItems[a];
    }
    mItems.clear();

    for(int a = 0;a < (int)projectiles_bitmaps.size();a++)
    {
        if(projectiles_bitmaps[a] != nullptr)
            al_destroy_bitmap(projectiles_bitmaps[a]);
    }
    projectiles_bitmaps.clear();

    #ifdef _MAP_WALLS
    if(walltester != nullptr)
    {
        world->DestroyBody(walltester);
        walltester = nullptr;
    }
    #endif // _MAP_WALLS

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
            global::audio_player->Play_sample_instance(&game_music_instance, 0.8f,ALLEGRO_PLAYMODE_LOOP);
        }
        return;
    }
    else if(dead == true)
    {
        if(main_menu_button->Input(event, xscale, yscale) == 2)
        {
            global::play = false;
            return;
        }
        else if(respawn_button->Input(event, xscale, yscale) == 2)
        {
            Set_mission(global::save->Get_mission_number());
            cutscene_playing = false;
            global::audio_player->Play_sample_instance(&game_music_instance, 0.8f,ALLEGRO_PLAYMODE_LOOP);
            respawn_button->unclick();
            return;
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
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && global::audio_b->is_button_clicking() == false
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

    #ifdef _MAP_WALLS
    float m_vec_x = (global::mouse_state.x/xscale - (METERS_TO_PIXELS(walltester->GetPosition().x) -map_draw_x));
    float m_vec_y = (global::mouse_state.y/yscale - (-METERS_TO_PIXELS(walltester->GetPosition().y) -map_draw_y));

    walltester->SetLinearVelocity(b2Vec2(PIXELS_TO_METERS(m_vec_x) , -PIXELS_TO_METERS(m_vec_y) ));
    #endif // _MAP_WALLS

    if(entities.size() == 1)
    {
        if(next_lvl->Input(event, xscale, yscale) == 2)
        {
            global::save->Set_mission_number(global::save->Get_mission_number()+1);
            if(global::save->Get_mission_number() > MAX_MISSIONS)
                global::save->Set_mission_number(MAX_MISSIONS);

            Set_mission(global::save->Get_mission_number());
        }
    }

    for(int a = 0;a < abilities.size();a++)
    {
        if(abilities[a]->usable == true && abilities[a]->unlocked == true)
        {
            abilities[a]->ab_but->Input(event, xscale, yscale);
            if(abilities[a]->ab_but->jst_clicked == true)
            {
                unclick_other_ab_but(a);
            }
        }
    }

    if(global::mouse_state.y/yscale < global::dHeight - gui_height)
    {
        if(abilities[ab_TELEPORT]->remaining_cd <= 0 && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && (event.mouse.button == 2 ||
           (abilities[ab_TELEPORT]->ab_but->is_button_clicked() == true && event.mouse.button == 1)))
        {

            abilities[ab_TELEPORT]->remaining_cd = abilities[ab_TELEPORT]->cool_down;
            abilities[ab_TELEPORT]->ab_but->unclick();
            entities[0]->body->SetTransform(b2Vec2( PIXELS_TO_METERS( ( (float)global::mouse_state.x/xscale +  (float)map_draw_x) ) ,
                                                -PIXELS_TO_METERS( (  (float)global::mouse_state.y/yscale +  (float)map_draw_y) )), 0);
        }
        else if(abilities[ab_ATTACK_PLUVANCE]->remaining_cd <= 0 && global::mouse_state.buttons == 1 && abilities[ab_ATTACK_PLUVANCE]->unlocked == true &&
                abilities[ab_TELEPORT]->ab_but->is_button_clicked() == false)
        {
            abilities[ab_ATTACK_PLUVANCE]->remaining_cd = abilities[ab_ATTACK_PLUVANCE]->cool_down;
            abilities[ab_ATTACK_PLUVANCE]->ab_but->unclick();

            add_projectile(0.6f, &projectiles_bitmaps[0], 6, 6, 3);
        }
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
            global::audio_player->Play_sample_instance(&game_music_instance, 0.8f,ALLEGRO_PLAYMODE_LOOP);

        return;
    }
    else if(paused == false && dead == false)
    {
        world->Step(1.0f/global::FPS, 8, 5); // collisison

        /*just_tp = false;
        if(tp_fail == true)
        {
            tp_fail = false;
            entities[0]->body->SetTransform(pre_tp, 0);
        }*/

        for(int a = 0;a < abilities.size();a++)
        {
            if(abilities[a]->remaining_cd > 0)
            {
                abilities[a]->remaining_cd -= 1.0/global::FPS;

                if(abilities[a]->remaining_cd < 0)
                    abilities[a]->remaining_cd = 0;
            }
        }

        //cammera
        map_draw_x = METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - global::dWidth/2;
        map_draw_y = -METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - global::dHeight/2;

        //cammera cornsrs fix
        if(map_draw_x < 0)
        {
            map_draw_x = 0;
        }
        else if(map_draw_x > map_bitmap->width - global::dWidth)
        {
            map_draw_x = map_bitmap->width - global::dWidth;
        }

        if(map_draw_y < 0)
        {
            map_draw_y = 0;
        }
        else if(map_draw_y > map_bitmap->height - (global::dHeight - gui_height))
        {
            map_draw_y = map_bitmap->height - global::dHeight;
        }

        //player rot
        p_angle = atan2( (global::mouse_state.y) / (global::yscale) - (-METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - map_draw_y),
                            (global::mouse_state.x) / (global::xscale) - (METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - map_draw_x) );
        entities[0]->body->SetTransform(entities[0]->body->GetPosition(),p_angle);

    }

    //map
    map_bitmap->Draw_bitmap_region(map_draw_x, map_draw_y, global::dWidth, global::dHeight - gui_height, 0, 0, 0);


    #ifdef _MAP_PF_ZONES
    int c1 = map_draw_x / 50;
    int c2 = map_draw_y /50;
    int c_of1 = map_draw_x - c1*50;
    int c_of2 = map_draw_y - c2*50;

    for(int a = 0;a < 30;a++)
    {
        for(int b = 0;b < 30;b++)
        {
            al_draw_filled_rectangle((a)*50 - c_of1,(b)*50 - c_of2,(a)*50 +50 - c_of1, (b)*50 +50 - c_of2,
                                     al_map_rgba( (mapdat->pat_finding_grid[a+c1][b+c2]*250),(1-mapdat->pat_finding_grid[a+c1][b+c2]*250),0,180));
        }
    }
    #endif // _MAP_PF_ZONES

    //items
    for(int a = 0;a < (int)mItems.size();)
    {
        if(mItems[a]->to_delete == true)
        {
            world->DestroyBody(mItems[a]->body);
            al_destroy_bitmap(mItems[a]->bitmap);
            delete mItems[a];
            mItems.erase(mItems.begin()+a);
            continue;
        }

        if(METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) +40 >= map_draw_x &&
           METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) - 40 <= map_draw_x + global::dWidth &&
           METERS_TO_PIXELS(-mItems[a]->body->GetPosition().y) +40 >= map_draw_y &&
           METERS_TO_PIXELS(-mItems[a]->body->GetPosition().y) - 40 <= map_draw_y + global::dHeight)
        {
            al_draw_bitmap(mItems[a]->bitmap, METERS_TO_PIXELS(mItems[a]->body->GetPosition().x) - map_draw_x - al_get_bitmap_width(mItems[a]->bitmap)/2,
                                   -METERS_TO_PIXELS(mItems[a]->body->GetPosition().y) - map_draw_y - al_get_bitmap_height(mItems[a]->bitmap)/2, 0);

        }
        mItems[a]->data.vectro_poz = a;
        a++;
    }
    //merge these 2 fors ?
    //npc
    b2RayCastInput input;
    b2RayCastOutput output;
    float k_angle;
    float bar;
    for(int a = 1;a < (int)entities.size();)
    {
        if(entities[a]->hp <= 0 || entities[a]->to_delete == true)
        {
            if(entities[a]->type == C4KACK)
            {
                explosions.push_back(new Explosion(METERS_TO_PIXELS(entities[a]->body->GetPosition().x) - map_draw_x, -METERS_TO_PIXELS(entities[a]->body->GetPosition().y)-map_draw_y ));
            }

            world->DestroyBody(entities[a]->body);
            al_destroy_bitmap(entities[a]->bitmap);
            delete entities[a];
            entities.erase(entities.begin()+a);
            continue;
        }

        if(METERS_TO_PIXELS(entities[a]->body->GetPosition().x) +40 >= map_draw_x &&
           METERS_TO_PIXELS(entities[a]->body->GetPosition().x) - 40 <= map_draw_x + global::dWidth &&
           METERS_TO_PIXELS(-entities[a]->body->GetPosition().y) +40 >= map_draw_y &&
           METERS_TO_PIXELS(-entities[a]->body->GetPosition().y) - 40 <= map_draw_y + global::dHeight)
        {
            input.p1 = entities[a]->body->GetPosition();
            input.p2 = entities[0]->body->GetPosition();
            input.maxFraction = 1;

            dont_move = false;
            world->RayCast(raycallback, entities[a]->body->GetPosition(), entities[0]->body->GetPosition());

            if( dont_move == false/*entities[0]->body->GetFixtureList()->RayCast(&output, input, 0) == true*/)
            {
                entities[0]->fainding_path = true;
                k_angle = atan2(-entities[0]->body->GetPosition().y + entities[a]->body->GetPosition().y ,
                                entities[0]->body->GetPosition().x - entities[a]->body->GetPosition().x );
                entities[a]->body->SetTransform(entities[a]->body->GetPosition(), k_angle);
                entities[a]->body->SetLinearVelocity(b2Vec2(entities[a]->speed * cos(k_angle), -entities[a]->speed* sin(k_angle)));
            }
            al_draw_rotated_bitmap(entities[a]->bitmap,
            40, 40, METERS_TO_PIXELS(entities[a]->body->GetPosition().x) - map_draw_x,
                                   -METERS_TO_PIXELS(entities[a]->body->GetPosition().y) - map_draw_y, k_angle, 0);

            //hp bar background
            al_draw_filled_rectangle(METERS_TO_PIXELS(entities[a]->body->GetPosition().x)- 25 - map_draw_x,
                                     -METERS_TO_PIXELS(entities[a]->body->GetPosition().y)- 35 - map_draw_y,
                                     METERS_TO_PIXELS(entities[a]->body->GetPosition().x)+ 25 - map_draw_x,
                                     -METERS_TO_PIXELS(entities[a]->body->GetPosition().y)- 30 - map_draw_y, al_map_rgba(255,0,0,120));
            //hp bar hp
            bar = (entities[a]->hp/entities[a]->maxhp)*50;
            al_draw_filled_rectangle(METERS_TO_PIXELS(entities[a]->body->GetPosition().x)- 25 - map_draw_x,
                                     -METERS_TO_PIXELS(entities[a]->body->GetPosition().y)- 35 - map_draw_y,
                                     METERS_TO_PIXELS(entities[a]->body->GetPosition().x)- 25 + bar - map_draw_x,
                                     -METERS_TO_PIXELS(entities[a]->body->GetPosition().y)- 30 - map_draw_y, al_map_rgba(0,200,0,180));
        }
        else
        {
            entities[a]->body->SetLinearVelocity(b2Vec2(0, 0));
        }
        entities[a]->data.vectro_poz = a;
        a++;
    }

    //explosions
    for(int a = 0;a < explosions.size();)
    {
        if(explosions[a]->Print() == false)
        {
            delete explosions[a];
            explosions.erase(explosions.begin()+a);
            continue;
        }
        a++;
    }

    //projectiles
    int reduced = 0;
    for(int a = 0;a < (int)projectiles.size();)
    {
        /*if(projectiles[a]->to_delete == true)
        {
            gt_detele:
            world->DestroyBody(projectiles[a]->body);
            delete projectiles[a];
            projectiles.erase(projectiles.begin()+a);
            continue;
        }*/

        if(METERS_TO_PIXELS(projectiles[a]->body->GetPosition().x) + projectiles[a]->width_pixel
           >= METERS_TO_PIXELS(entities[0]->body->GetPosition().x) -range &&
           METERS_TO_PIXELS(projectiles[a]->body->GetPosition().x) - projectiles[a]->width_pixel
           <= METERS_TO_PIXELS(entities[0]->body->GetPosition().x) + range &&
           METERS_TO_PIXELS(-projectiles[a]->body->GetPosition().y) + projectiles[a]->height_pixel
           >= METERS_TO_PIXELS(-entities[0]->body->GetPosition().y) -range &&
           METERS_TO_PIXELS(-projectiles[a]->body->GetPosition().y) - projectiles[a]->height_pixel
           <= METERS_TO_PIXELS(-entities[0]->body->GetPosition().y) + range&&
           projectiles[a]->to_delete == false )
        {

            al_draw_rotated_bitmap(projectiles[a]->bitmap, projectiles[a]->width_pixel, projectiles[a]->height_pixel,
                                   METERS_TO_PIXELS(projectiles[a]->body->GetPosition().x) - map_draw_x,
                                   -METERS_TO_PIXELS(projectiles[a]->body->GetPosition().y) - map_draw_y, projectiles[a]->body->GetAngle(), 0);
        }
        else
        {
            gt_detele:
            world->DestroyBody(projectiles[a]->body);
            delete projectiles[a];
            projectiles.erase(projectiles.begin()+a);
            continue;
        }
        projectiles[a]->data.vectro_poz = a;
        a++;
    }

    //player
    al_draw_rotated_bitmap(entities[0]->bitmap, 50.0f, 50.0f, METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - map_draw_x,
                           -METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - map_draw_y, entities[0]->body->GetAngle(), 0);
    //-----

    #ifdef _PURE_MAP_WALLS
    for(int a = 0;a < (int)mapdat->objects.size();a++)
    {
        if(mapdat->objects[a]->type == MapData::WALL)
        {
            al_draw_rectangle(mapdat->objects[a]->x1 - map_draw_x, mapdat->objects[a]->y1 - map_draw_y,
                              mapdat->objects[a]->x2- map_draw_x, mapdat->objects[a]->y2- map_draw_y,al_map_rgb(0,0,0),2);
        }
    }
    #endif // _PURE_MAP_WALLS

    #ifdef _MAP_WALLS
    al_draw_filled_rectangle(METERS_TO_PIXELS(walltester->GetPosition().x) - map_draw_x -20,
                            -METERS_TO_PIXELS(walltester->GetPosition().y) - map_draw_y -20,
                             METERS_TO_PIXELS(walltester->GetPosition().x) - map_draw_x +20,
                            -METERS_TO_PIXELS(walltester->GetPosition().y) - map_draw_y +20,
                             al_map_rgb(0,0,0));
    #endif // _MAP_WALLS


    //print GUI
    al_draw_filled_rectangle(0, global::dHeight - gui_height, global::dWidth, global::dHeight, al_map_rgb(88,88,88));
    al_draw_filled_rectangle(0, global::dHeight - gui_height, global::dWidth, global::dHeight - gui_height +3, al_map_rgb(230,228,216));
    pause_button->Print();

    for(int a = 0;a < abilities.size();a++)
    {
        if(abilities[a]->usable == true && abilities[a]->unlocked == true)
        {
            al_draw_bitmap(abilities[a]->bitmap ,abilities[a]->ab_but->origin_x1, abilities[a]->ab_but->origin_y1, 0);
            al_draw_filled_rectangle(abilities[a]->ab_but->origin_x1,
                                     abilities[a]->ab_but->origin_y1 + AB_IMAGE_SIZE - ( (abilities[a]->remaining_cd/abilities[a]->cool_down) * AB_IMAGE_SIZE),
                                     abilities[a]->ab_but->origin_x2,
                                     abilities[a]->ab_but->origin_y2,
                                     al_map_rgba(0,0,0,128));
            if(abilities[a]->ab_but->is_button_clicked() == true)
            {
                al_draw_rectangle(abilities[a]->ab_but->origin_x1, abilities[a]->ab_but->origin_y1, abilities[a]->ab_but->origin_x2,
                                  abilities[a]->ab_but->origin_y2 ,al_map_rgb(255,255,255),2);
            }
        }

        if(a < 3)
        {
            al_draw_text(mouse_b_f, al_map_rgb(255,255,255), 1030 + a*(60) + (50-al_get_text_width( mouse_b_f, mouse_but_text[a].c_str()))/2,
                         global::dHeight -(AB_IMAGE_SIZE+37), 0, mouse_but_text[a].c_str());
        }
    }

    if(entities.size() == 1)
    {
        next_lvl->Print();
    }

    if(paused == true)
    {
        al_draw_filled_rectangle(0,0, global::dWidth, global::dHeight, al_map_rgba(0,0,0,185));
        al_draw_text(pause_f, al_map_rgb(200,200,200), (global::dWidth - al_get_text_width( pause_f, "Click to unpause"))/2,
                     (global::dHeight - al_get_font_ascent(pause_f))/2, 0, "Click to unpause");
        main_menu_button->Print();

    }
    else if(dead == true)
    {
        if(dead_fade_counter < 40)
            dead_fade_counter++;

        al_draw_filled_rectangle(0,0, global::dWidth, global::dHeight, al_map_rgba(0,0,0,150 + dead_fade_counter*2));
        al_draw_text(pause_f, al_map_rgb(200,200,200), (global::dWidth - al_get_text_width( pause_f, "Si mŕrtvy (nooob)"))/2,
                     (global::dHeight - al_get_font_ascent(pause_f))/2, 0, "Si mŕrtvy (nooob)");
        main_menu_button->Print();
        respawn_button->Print();
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
    dead_fade_counter = 0;
    dead = false;
    paused = false;
    cutscene_playing = true;

    if(mission > MAX_MISSIONS)
    {
        mission = MAX_MISSIONS;
    }

    for(int a = 0;a < (int)sounds.size();a++)
    {
        global::audio_player->Stop_sample_instance(&sounds[a]->instance);
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
        al_destroy_bitmap(entities[a]->bitmap);
        delete entities[a];
    }
    entities.clear();

    for(int a = 0;a < (int)walls.size();a++)
    {
        world->DestroyBody(walls[a]->body);
        delete walls[a];
    }
    walls.clear();

    for(int a = 0;a < (int)mItems.size();a++)
    {
        world->DestroyBody(mItems[a]->body);
        al_destroy_bitmap(mItems[a]->bitmap);
        delete mItems[a];
    }
    mItems.clear();

    for(int a = 0;a < (int)projectiles.size();a++)
    {
        world->DestroyBody(projectiles[a]->body);
        delete projectiles[a];
    }
    projectiles.clear();

    for(int a = 0;a < explosions.size();a++)
    {
        delete explosions[a];
    }
    explosions.clear();

    for(int a = 0;a < (int)abilities.size();a++)
    {
        abilities[a]->remaining_cd = 0;
        abilities[a]->remaining_time_to_cast = 0;
    }

    #ifdef _MAP_WALLS
    if(walltester != nullptr)
    {
        world->DestroyBody(walltester);
        walltester = nullptr;
    }
    #endif // _MAP_WALLS

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
    mapdat = new MapData("resources/maps/map" + std::to_string(mission) + ".map", map_bitmap->width, map_bitmap->height);
    map_draw_x = mapdat->player_spawm_x - global::dWidth/2;
    map_draw_y = mapdat->player_spawm_y - (global::dHeight - gui_height)/2;
    world = new b2World(b2Vec2(0,0));


    world->SetContactListener(colider);

    #ifdef _MAP_WALLS
    b2BodyDef wdef;
    wdef.type = b2_dynamicBody;
    wdef.position.Set(PIXELS_TO_METERS(mapdat->player_spawm_x), PIXELS_TO_METERS(-mapdat->player_spawm_y));
    //wdef.position.Set(0,0);
    wdef.angle = 0;
    wdef.allowSleep = false;
    wdef.awake = true;
    walltester = world->CreateBody(&wdef);
    //walltester->SetTransform()

    b2PolygonShape wshape;
    wshape.SetAsBox(0.2f, 0.2f);
    b2FixtureDef wfixt;
    wfixt.shape = &wshape;
    wfixt.filter.categoryBits = c_TEST_BOX; //what this is
    wfixt.filter.maskBits = c_WALL;
    walltester->CreateFixture(&wfixt);
    walltesterdat.vectro_poz = 0;
    walltesterdat.which_vector = TEST_VECTOR;
    walltester->SetUserData( &walltesterdat );
    #endif // _MAP_WALLS

    std::string dum;
    /**Player*/
    entities.push_back(new entity);
    b2BodyDef Player_body_def;
    Player_body_def.type = b2_dynamicBody;
    Player_body_def.position.Set(PIXELS_TO_METERS(mapdat->player_spawm_x), PIXELS_TO_METERS(-mapdat->player_spawm_y)); //set the starting position
    Player_body_def.angle = 0; //set the starting angle
    Player_body_def.allowSleep = false;
    Player_body_def.awake = true;
    entities[entities.size()-1]->body = world->CreateBody(&Player_body_def);

    b2Vec2 vertices[6];
    vertices[0].Set(-PIXELS_TO_METERS(49),  -PIXELS_TO_METERS(22)); //left bottom
    vertices[1].Set( PIXELS_TO_METERS(13),  -PIXELS_TO_METERS(47));
    vertices[2].Set( PIXELS_TO_METERS(47),  -PIXELS_TO_METERS(40));
    vertices[3].Set( PIXELS_TO_METERS(47),   PIXELS_TO_METERS(34));
    vertices[4].Set( PIXELS_TO_METERS(40),   PIXELS_TO_METERS(48));
    vertices[5].Set(-PIXELS_TO_METERS(49),   PIXELS_TO_METERS(23));

    b2PolygonShape Player_shape;
    Player_shape.Set(vertices, 6);
    //Player_shape.SetAsBox(0.4, 0.5);

    b2FixtureDef Player_fixture_def;
    Player_fixture_def.shape = &Player_shape;
    Player_fixture_def.filter.categoryBits = c_PLAYER; //what this is
    Player_fixture_def.filter.maskBits = c_WALL | c_ITEM | c_ENEMY | c_EVENT_LOCATION;//what i collide with
    entities[entities.size()-1]->body->CreateFixture(&Player_fixture_def);
    entities[entities.size()-1]->type = 99;
    entities[entities.size()-1]->data.vectro_poz = entities.size()-1;
    entities[entities.size()-1]->data.which_vector = ENTITY_VECTOR;
    entities[entities.size()-1]->body->SetUserData( &entities[entities.size()-1]->data );

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
            body_def.allowSleep = false;
            body_def.awake = true;
            //walls_and_items[walls_and_items.size()-1]= world->CreateBody(&body_def);
            walls.push_back(new Wall);
            walls[walls.size()-1]->body = world->CreateBody(&body_def);
            shape.SetAsBox(PIXELS_TO_METERS((width/2.0f)), PIXELS_TO_METERS((height/2.0f)));
            fixture.shape = &shape;
            fixture.isSensor = false;
            fixture.filter.categoryBits = c_WALL;
            fixture.filter.maskBits = c_PLAYER | c_PLYER_PROJECTILE | c_ENEMY | c_TEST_BOX;
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
            body_def.allowSleep = false;
            body_def.awake = true;
            //body_def.bullet = true;
            entities[entities.size()-1]->body = world->CreateBody(&body_def);

            shape.SetAsBox(PIXELS_TO_METERS(20), PIXELS_TO_METERS(20));
            fixture.shape = &shape;
            fixture.isSensor = false;
            fixture.filter.categoryBits = c_ENEMY;
            fixture.filter.maskBits = c_WALL | c_PLYER_PROJECTILE | c_PLAYER | c_TEST_BOX;

            entities[entities.size()-1]->body->CreateFixture(&fixture);
            entities[entities.size()-1]->type = mapdat->objects[a]->enemy;
            entities[entities.size()-1]->data.vectro_poz = entities.size()-1;
            entities[entities.size()-1]->data.which_vector = ENTITY_VECTOR;
            entities[entities.size()-1]->body->SetUserData( &entities[entities.size()-1]->data );

            entities[entities.size()-1]->maxhp = entities[entities.size()-1]->hp = mapdat->objects[a]->hp;
            entities[entities.size()-1]->speed = mapdat->objects[a]->speed;

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
            body_def.allowSleep = false;
            body_def.awake = true;
            mItems.push_back(new map_Item);
            mItems[mItems.size()-1]->body = world->CreateBody(&body_def);
            shape.SetAsBox(PIXELS_TO_METERS(30), PIXELS_TO_METERS(30));
            fixture.filter.categoryBits = c_ITEM;
            fixture.filter.maskBits = c_PLAYER ;
            fixture.isSensor = true;
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

void ScreenGame::unclick_other_ab_but(int just_clicked)
{
    for(int a = 0;a < (int)abilities.size();a++)
    {
        if(abilities[a]->usable == true && a != just_clicked)
           abilities[a]->ab_but->unclick();
    }
    return;
}

void ScreenGame::add_projectile(float damage, ALLEGRO_BITMAP **bmp, float width_pixel, float height_pixel, float speed_inmeters)
{
    /*g_pro_vel_x = (global::mouse_state.x/global::xscale - (METERS_TO_PIXELS(entities[0]->body->GetPosition().x) -map_draw_x));
    g_pro_vel_y = (global::mouse_state.y/global::yscale - (-METERS_TO_PIXELS(entities[0]->body->GetPosition().y) -map_draw_y));*/

    g_pro_angle = atan2( (global::mouse_state.y) / (global::yscale) - (-METERS_TO_PIXELS(entities[0]->body->GetPosition().y) - map_draw_y),
                    (global::mouse_state.x) / (global::xscale) - (METERS_TO_PIXELS(entities[0]->body->GetPosition().x) - map_draw_x) );


    projectiles.push_back(new Projectile);
    projectiles[projectiles.size()-1]->bitmap = *bmp;

    gbody_def.type = b2_dynamicBody;
    gbody_def.position.Set(entities[0]->body->GetPosition().x, entities[0]->body->GetPosition().y);
    gbody_def.allowSleep = false;
    gbody_def.awake = true;
    gbody_def.bullet = true;
    gbody_def.angle = g_pro_angle;
    //gbody_def.linearVelocity = b2Vec2( PIXELS_TO_METERS(g_pro_vel_x), (-PIXELS_TO_METERS(g_pro_vel_y)) );
    gbody_def.linearVelocity = b2Vec2(speed_inmeters*cos(g_pro_angle) ,-(speed_inmeters*sin(g_pro_angle)) );
    projectiles[projectiles.size()-1]->body = world->CreateBody(&gbody_def);
    projectiles[projectiles.size()-1]->damage = damage;
    projectiles[projectiles.size()-1]->width_pixel = width_pixel;
    projectiles[projectiles.size()-1]->height_pixel = height_pixel;

    gshape.SetAsBox(PIXELS_TO_METERS(width_pixel),PIXELS_TO_METERS(height_pixel));

    gfixture.shape = &gshape;

    gfixture.filter.categoryBits = c_PLYER_PROJECTILE;
    gfixture.filter.maskBits = c_WALL | c_ENEMY;
    projectiles[projectiles.size()-1]->body->CreateFixture(&gfixture);
    projectiles[projectiles.size()-1]->data.vectro_poz = projectiles.size()-1;
    projectiles[projectiles.size()-1]->data.which_vector = PROJECTILES_VECTOR;
    projectiles[projectiles.size()-1]->body->SetUserData( &projectiles[projectiles.size()-1]->data );

    return;
}

ScreenGame::int_coords ScreenGame::pixel_coors_to_pf_coords(int x, int y)
{
    int_coords c;

    int a = x / 50;
    int b = y / 50;

    c.x = a;
    c.y = b;

    return c;
}
