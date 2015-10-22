//R.K.
#ifndef SCREENINTRO_H
#define SCREENINTRO_H

#include "global.h"

#define CLOCKT_TO_SECONDS(clock) (float)clock/CLOCKS_PER_SEC
#define SECONDS_TO_CLOCKS(sec) (float)sec*CLOCKS_PER_SEC

class ScreenIntro
{
private:
    bool *it_is;

    struct Sound{
        bool playing = false;
        bool active = false;
        clock_t ct_start;
        clock_t ct_duration;
        ALLEGRO_SAMPLE *sound = nullptr;
        ALLEGRO_SAMPLE_INSTANCE *smplinst = nullptr;
        float t_start = 0;
        float duration = 0;
        float t2 = 0;
        bool play_till_song_end = true;

    };

    struct Images{
        bool active = true;
        clock_t ct_start;
        clock_t ct_duration;
        ALLEGRO_BITMAP *bitmap = nullptr;
        float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        float t_start = 0;
        float duration = 0;
        float vertical_change = 0, horizontal_change = 0;
    };

    bool clck_init = false;

public:
    clock_t start_time;

    std::vector<Sound*> sounds;
    std::vector<Images*> images;

    ScreenIntro(bool *is_intro_running);
    virtual ~ScreenIntro();

    void Print();

    /** push them in order they will be played */

    bool Add_sound(std::string soundfile, clock_t start_play_at, clock_t play_for);
    bool Add_image(std::string imagefile, clock_t start_play_at, clock_t play_for, float x1, float y1);//, float vertical_ch, float horizontal_ch);
};

#endif // SCREENINTRO_H
