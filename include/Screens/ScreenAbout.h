#ifndef SCREENABOUT_H
#define SCREENABOUT_H

#include "global.h"

class ScreenAbout
{
private:
    ALLEGRO_BITMAP *background = nullptr;
    Button *but;
    Button *button_back = nullptr;
public:
    ScreenAbout(Button *ext_b);
    virtual ~ScreenAbout();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENABOUT_H
