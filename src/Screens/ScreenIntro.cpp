#include "ScreenIntro.h"

ScreenIntro::ScreenIntro(bool *is_intro_running) : it_is(is_intro_running)
{
    //ctor
}

ScreenIntro::~ScreenIntro()
{
    //dtor
}

void ScreenIntro::Print()
{
    al_clear_to_color(al_map_rgb(0,0,85));

    return;
}
