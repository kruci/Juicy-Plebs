//R.K.
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "global.h"
#include "include/Screens/ScreenIntro.h"

class ScreenGame
{
private:
    bool cutscene_playing = true;
    Button *cutscene_button = nullptr;

    bool paused = false;
public:
    ScreenIntro * SCIntro = nullptr;

    ScreenGame();
    virtual ~ScreenGame();

    bool Set_mission(int mission);

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENGAME_H
