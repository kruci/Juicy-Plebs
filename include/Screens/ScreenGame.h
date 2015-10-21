//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"

class ScreenGame
{
private:
    bool cutscene_playing = true;
    Button *cutscene_button = nullptr;

    bool paused = false;
public:
    ScreenGame();
    virtual ~ScreenGame();

    bool Set_mission(int mission);

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENGAME_H
