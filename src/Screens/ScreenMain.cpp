//R.K.
#include "ScreenMain.h"

ScreenMain::ScreenMain()
{
    //background = al_load_bitmap("resources/graphics/zemiak.png");
    zemak_bitmap = al_load_bitmap("resources/graphics/logo.png");
    if(zemak_bitmap == nullptr)
    {
        error_message("Could not load image : resources/graphics/logo.png");
    }
    zemak_button = new Button(100, (global::dHeight - al_get_bitmap_height(zemak_bitmap))/2,
                              100 + al_get_bitmap_width(zemak_bitmap),
                              (global::dHeight - al_get_bitmap_height(zemak_bitmap))/2 + al_get_bitmap_height(zemak_bitmap));

    std::string bnames[3] = {"Exit", "Play", "About"};

                        //x1, y1, width, height
    /*int bpoz[4][4] = {  {1300, global::dHeight -70, 120, 50},
                        {((float)global::dWidth-250.0f)/2.0f, ((float)global::dHeight-80.0f)/2.0f, 250, 80},
                        {global::dWidth - 1300 -120,global::dHeight -70,120,50},
                        {((float)global::dWidth-120.0f)/2.0f, global::dHeight-70, 120, 50}  };*/

    int b_y = (float)global::dHeight / 9.0f;

    int bpoz[3][4] = {  {1300, global::dHeight -70, 120, 50},
                        {((float)global::dWidth-220.0f), b_y*1, 200, 65},
                        {global::dWidth -200, b_y*2, 180, 58}   };

    for(int a = 0;a < 3;a++)
    {
        buttons.push_back(new Button("resources/fonts/Calibri.ttf", bpoz[a][0], bpoz[a][1], bpoz[a][0] + bpoz[a][2],bpoz[a][1] + bpoz[a][3], bnames[a], al_map_rgb(0,0,128)));
    }

    intro_music = al_load_sample(INTRO_SUND_FILE);
    if(intro_music == nullptr)
    {
        std::string dum = INTRO_SUND_FILE;
        error_message("Could not load file: " + dum);
    }
    intro_music_instance = al_create_sample_instance(intro_music);
    if(intro_music_instance == nullptr)
    {
        std::string dum = INTRO_SUND_FILE;
        error_message("Could not create sample instance: " + dum);
    }
    global::audio_player->Play_sample_instance(&intro_music_instance,ALLEGRO_PLAYMODE_LOOP);
}

ScreenMain::~ScreenMain()
{
    if(background != nullptr)
        al_destroy_bitmap(background);

    for(int a = 0;a < (int)buttons.size();a++)
    {
        delete buttons[a];
    }
    buttons.clear();

    if(SCAbout != nullptr)
        delete SCAbout;
    if(SCPlay != nullptr)
        delete SCPlay;
    if(SCGame != nullptr)
        delete SCGame;
    if(raycallback != nullptr)
        delete raycallback;
    if(colider != nullptr)
        delete colider;

    al_stop_sample_instance(intro_music_instance);
    al_detach_sample_instance(intro_music_instance);
    if(intro_music_instance != nullptr)
        al_destroy_sample_instance(intro_music_instance);
     if(intro_music != nullptr)
        al_destroy_sample(intro_music);
}

void ScreenMain::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    if(global::play == true)
    {
        if(SCGame == nullptr)
        {
            SCGame = new ScreenGame();
            colider = new CollisionHandler();
            raycallback = new RayCastCallBack();
            SCGame->colider = colider;
            colider->refscreen = SCGame;
            SCGame->raycallback = raycallback;
            raycallback->refscreen = SCGame;
            SCGame->Set_mission(global::save->Get_mission_number());
            global::audio_player->Stop_sample_instance(&intro_music_instance);
        }

        SCGame->Input(event, xscale, yscale);

        if(global::play == false)
        {
            if(SCGame != nullptr)
            {
                global::save->Save();
                delete SCGame;
                delete colider;
                delete raycallback;
                SCGame = nullptr;
                colider = nullptr;
                raycallback = nullptr;
                global::audio_player->Play_sample_instance(&intro_music_instance,ALLEGRO_PLAYMODE_LOOP);
            }
        }
        else
        {
            return;
        }
    }

    if(is_any_button_clicked() == false)
    {
        if(SCAbout != nullptr)
        {
            delete SCAbout;
            SCAbout = nullptr;
        }
        if(SCPlay != nullptr)
        {
            delete SCPlay;
            SCPlay = nullptr;
        }

        for(int a = 0;a < (int)buttons.size();a++)
        {
            buttons[a]->Input(event, xscale, yscale);
        }
        zemak_button->Input(event, xscale, yscale);
    }

    if(buttons[EXIT]->is_button_clicked() == true)
    {
        global::loop = false;
    }
    else if(buttons[PLAY]->is_button_clicked() == true)
    {
        if(SCPlay == nullptr)
        {
            SCPlay = new ScreenPlay(buttons[PLAY]);
        }
        SCPlay->Input(event, xscale, yscale);
    }
    else if(buttons[ABOUT]->is_button_clicked() == true)
    {
        if(SCAbout == nullptr)
        {
            SCAbout = new ScreenAbout(buttons[ABOUT]);
        }
        SCAbout->Input(event, xscale, yscale);
    }

    return;
}

void ScreenMain::Print()
{
    if(global::play == true)
    {
        if(SCGame == nullptr)
        {
            SCGame = new ScreenGame();
            colider = new CollisionHandler();
            raycallback = new RayCastCallBack();
            SCGame->colider = colider;
            SCGame->raycallback = raycallback;
            raycallback->refscreen = SCGame;
            colider->refscreen = SCGame;
            SCGame->Set_mission(global::save->Get_mission_number());
        }

        SCGame->Print();

        return;
    }

    if(buttons[PLAY]->is_button_clicked() == true)
    {
        if(SCPlay == nullptr)
        {
            SCPlay = new ScreenPlay(buttons[PLAY]);
        }

        SCPlay->Print();
    }
    else if(buttons[ABOUT]->is_button_clicked() == true)
    {
        if(SCAbout == nullptr)
        {
            SCAbout = new ScreenAbout(buttons[ABOUT]);
        }

        SCAbout->Print();
    }
    else
    {
        al_draw_bitmap(zemak_bitmap, zemak_button->origin_x1,zemak_button->origin_y1,0);
        if(zemak_button->is_button_clicked() == true)
        {
            zemak_button->unclick();
        }

        for(int a = 0;a < (int)buttons.size();a++)
        {
            buttons[a]->Print();
        }
    }

    return;
}

bool ScreenMain::is_any_button_clicked()
{
    for(int a = 0;a < (int)buttons.size();a++)
    {
        if(buttons[a]->is_button_clicked() == true)
        {
            return true;
        }
    }

    return false;
}
