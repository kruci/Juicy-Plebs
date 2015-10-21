#ifndef SCREENINTRO_H
#define SCREENINTRO_H

#include "global.h"

#define SECONDS_TO_GAME_TICKS(s) global::FPS*s
#define GAME_TICKS_TO_SECONDS s/global::FPS

class ScreenIntro
{
private:
    bool *it_is;

    struct Sound{
        ALLEGRO_SAMPLE *sound = nullptr;
        int t_start = 0;
        int duration = 0;
        bool play_till_end = true;
    };

    struct Images{
        ALLEGRO_BITMAP *bitmap = nullptr;
        float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        float vertical_change = 0, horizontal_change = 0;
    };

public:
    std::vector<Sound*> sounds;
    std::vector<Images*> images;

    ScreenIntro(bool *is_intro_running);
    virtual ~ScreenIntro();

    void Print();

    int Seconds_to_();
};

#endif // SCREENINTRO_H
