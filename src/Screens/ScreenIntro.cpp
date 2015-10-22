//R.K.
#include "ScreenIntro.h"

ScreenIntro::ScreenIntro(bool *is_intro_running) : it_is(is_intro_running)
{
    //ctor
}

ScreenIntro::~ScreenIntro()
{
    for(int a = 0;a < (int)sounds.size();a++)
    {
        global::audio_player->Stop_sample_instance(&sounds[a]->smplinst);
        al_destroy_sample_instance(sounds[a]->smplinst);
        al_destroy_sample(sounds[a]->sound);
    }
    sounds.clear();

    for(int a = 0;a < (int)images.size();a++)
    {
        al_destroy_bitmap(images[a]->bitmap);
    }
    images.clear();
}

void ScreenIntro::Print()
{
    if(clck_init == false)
    {
        start_time = clock();
        clck_init = true;
    }

    al_clear_to_color(al_map_rgb(0,0,85));

    for(int a = 0;a < (int)sounds.size();a++)
    {
        if(sounds[a]->active == true)
        {
            if(sounds[a]->playing == false && (clock() - start_time) >= sounds[a]->ct_start)
            {
                sounds[a]->playing = true;
                global::audio_player->Play_sample_instance(&sounds[a]->smplinst,ALLEGRO_PLAYMODE_ONCE);
            }
            else if(sounds[a]->playing == true && (clock() - start_time) > sounds[a]->ct_start + sounds[a]->ct_duration)
            {
                sounds[a]->playing = false;
                global::audio_player->Stop_sample_instance(&sounds[a]->smplinst);
                sounds[a]->active = false;
            }
        }
    }

    for(int a = 0;a < (int)images.size();a++)
    {
        if(images[a]->active == true)
        {
            if((clock() - start_time) >= images[a]->ct_start)
            {
                al_draw_bitmap(images[a]->bitmap, images[a]->x1, images[a]->y1, 0);
            }
            else if( (clock() - start_time) > images[a]->ct_start + images[a]->ct_duration)
            {
                images[a]->active = false;
            }
        }
    }

    return;
}

bool ScreenIntro::Add_sound(std::string soundfile, clock_t start_play_at, clock_t play_for)
{
    sounds.push_back(new Sound);

    sounds[sounds.size()-1]->sound = al_load_sample(soundfile.c_str());
    if(sounds[sounds.size()-1]->sound == nullptr)
    {
        error_message("Could not load sound: " + soundfile);
    }
    sounds[sounds.size()-1]->smplinst = al_create_sample_instance(sounds[sounds.size()-1]->sound);
    if(sounds[sounds.size()-1]->smplinst == nullptr)
    {
        error_message("Could not create sample instance: " + soundfile);
    }
    sounds[sounds.size()-1]->ct_start = start_play_at;
    sounds[sounds.size()-1]->ct_duration = play_for;

    return true;
}

bool ScreenIntro::Add_image(std::string imagefile, clock_t start_play_at, clock_t play_for, float x1, float y1)
{
    images.push_back(new Images);
    images[images.size()-1]->bitmap = al_load_bitmap(imagefile.c_str());

    images[images.size()-1]->ct_start = start_play_at;
    images[images.size()-1]->ct_duration = play_for;
    images[images.size()-1]->x1 = x1;
    images[images.size()-1]->y1 = y1;

    return true;
}
