//R.K.
#ifndef SCREENINTRO_H
#define SCREENINTRO_H

#include "global.h"

#define CLOCKT_TO_SECONDS(clock) (double)clock/CLOCKS_PER_SEC
#define SECONDS_TO_CLOCKS(sec) (double)sec*CLOCKS_PER_SEC

class ScreenIntro
{
private:
    bool *it_is;

    struct Sound{
        bool playing = false;
        bool active = true;
        float t_start = 0;
        float t_duration = 0;
        ALLEGRO_SAMPLE *sound = nullptr;
        ALLEGRO_SAMPLE_INSTANCE *smplinst = nullptr;
        bool play_till_song_end = true;

    };

    struct Images{
        bool active = true;
        float t_start = 0;
        float t_duration = 0;
        ALLEGRO_BITMAP *bitmap = nullptr;
        float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        float vertical_change = 0, horizontal_change = 0;
    };

    bool clck_init = false;

public:
    time_t start_time;
    float max_duration;

    std::vector<Sound*> sounds;
    std::vector<Images*> images;

    ScreenIntro(bool *is_intro_running);
    virtual ~ScreenIntro();

    void Print();
    void Reset();

    /** push them in order they will be played */

    bool Add_sound(std::string soundfile, float start_play_at, float play_for);
    bool Add_image(std::string imagefile, float start_play_at, float play_for, float x1, float y1);//, float vertical_ch, float horizontal_ch);
};

#endif // SCREENINTRO_H
