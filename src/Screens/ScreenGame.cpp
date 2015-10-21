//R.K.
#include "ScreenGame.h"

ScreenGame::ScreenGame()
{
    cutscene_button = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Skip", al_map_rgb(0,0,128));
}

ScreenGame::~ScreenGame()
{
    if(cutscene_button != nullptr)
        delete cutscene_button;
}

void ScreenGame::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    if(cutscene_playing == true)
    {
        cutscene_button->Input(event, xscale, yscale);
        if(cutscene_button->is_button_clicked() == true)
        {
            cutscene_playing = false;
            cutscene_button->unclick();
        }
        return;
    }

    //mapinput
    //gui input
    //check if input to pause

    return;
}

void ScreenGame::Print()
{
    if(cutscene_playing == true)
    {
        //cutsecene->Print();
        cutscene_button->Print();
        return;
    }

    //check if paused, and if not, compute

    //print map and entities
    //print GUI
    //check if print pause

    return;
}
