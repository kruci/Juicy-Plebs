//R.K.
#include "ScreenMain.h"


ScreenMain::ScreenMain()
{
    //background = al_load_bitmap("resources/graphics/zemiak.png");
    zemak_bitmap = al_load_bitmap("resources/graphics/zemiacik.png");
    if(zemak_bitmap == nullptr)
    {
        error_message("Could not load image : resources/graphics/zemiacik.png");
    }
    zemak_button = new Button(100, (global::dHeight - zemiak_size)/2,
                              100 + zemiak_size,
                              (global::dHeight - zemiak_size)/2 + zemiak_size);

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

    hlasky_font = al_load_ttf_font("resources/fonts/Andada-Italic.otf", 30, 0);
    if(hlasky_font == nullptr) error_message("Could not load font : resources/fonts/Andada-Italic.otf");

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
    global::audio_player->Play_sample_instance(&intro_music_instance, 0.8,ALLEGRO_PLAYMODE_LOOP);

    /*std::string dm = "resources/music/mms/";
    std::string soundfiles = "";

    for(int a = 1;a <= NUMBER_OF_HLASKY;a++)
    {
        hlasky.push_back(new AudioHandler::sound_effect);

        soundfiles = dm + std::to_string(a) + ".ogg";

        hlasky[hlasky.size()-1]->sample = al_load_sample(soundfiles.c_str());
        if(hlasky[hlasky.size()-1]->sample == nullptr)
        {
            error_message("Could not load file: " + soundfiles);
        }
        hlasky[hlasky.size()-1]->instance = al_create_sample_instance(hlasky[hlasky.size()-1]->sample);
        if(hlasky[hlasky.size()-1]->instance == nullptr)
        {
            error_message("Could not create sample instance: " + soundfiles);
        }
    }*/

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
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
    if(zemak_bitmap != nullptr)
        al_destroy_bitmap(zemak_bitmap);
    if(zemak_button != nullptr)
        delete zemak_button;

    if(hlasky_font != nullptr)
        al_destroy_font(hlasky_font);

    al_stop_sample_instance(intro_music_instance);
    al_detach_sample_instance(intro_music_instance);
    if(intro_music_instance != nullptr)
        al_destroy_sample_instance(intro_music_instance);
     if(intro_music != nullptr)
        al_destroy_sample(intro_music);

    /*for(int a = 0;a < (int)hlasky.size();a++)
    {
        global::audio_player->Stop_sample_instance(&hlasky[a]->instance);
        al_destroy_sample(hlasky[a]->sample);
        al_destroy_sample_instance(hlasky[a]->instance);
        delete hlasky[a];
    }
    hlasky.clear();*/
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

        zemak_button->Input(event, xscale, yscale) == 2;
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
        //al_draw_bitmap(zemak_bitmap, zemak_button->origin_x1,zemak_button->origin_y1,0);
        al_draw_scaled_bitmap(zemak_bitmap, 0, 0, al_get_bitmap_width(zemak_bitmap), al_get_bitmap_height(zemak_bitmap),
                              zemak_button->origin_x1, zemak_button->origin_y1, zemiak_size, zemiak_size, 0);
        al_draw_text(hlasky_font, al_map_rgba(255,255,255, 150), 300, (global::dHeight - zemiak_size)/2 + 200, 0, "*Click*");

        if(zemak_button->is_button_clicked() == true)
        {
            zemak_button->unclick();
            std::uniform_int_distribution<int> hlasky_distribution(0, number_of_written_hlasky-1);
            playing_hlaska = hlasky_distribution(generator);
        }
        if(playing_hlaska != -1)
            al_draw_text(hlasky_font, al_map_rgb(255,255,255), zemak_button->origin_x1, zemak_button->origin_y2 - 20, 0, written_hlasky[playing_hlaska].c_str());

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
