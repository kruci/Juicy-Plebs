//R.K.
#include "ScreenGame.h"

ScreenGame::ScreenGame()
{
    cutscene_button = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Skip", al_map_rgb(0,0,128));

    SCIntro = new ScreenIntro(&cutscene_playing);
}

ScreenGame::~ScreenGame()
{
    if(cutscene_button != nullptr)
        delete cutscene_button;

    if(SCIntro != nullptr)
        delete SCIntro;
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
    al_clear_to_color(al_map_rgb(0,0,35));
    if(cutscene_playing == true)
    {
        SCIntro->Print();
        cutscene_button->Print();
        return;
    }

    //check if paused, and if not, compute

    //print map and entities
    //print GUI
    //check if print pause

    return;
}

bool ScreenGame::Set_mission(int mission)
{
    if(mission == 1)
    {
        SCIntro->Reset();

        SCIntro->Add_image("resources/test/zemiak.jpeg",  0.0f,  3.2f, 100, 100);
        SCIntro->Add_sound("resources/test/naobrazkumozmevidietzemiak.wav",  0.0f,  3.2f);

        SCIntro->Add_image("resources/test/badass_zemiak.jpg",  3.4f,  3.2f, 100, 100);
        SCIntro->Add_sound("resources/test/naobrazkumozmevidietzemiak_hlboke.wav",  3.4f,  3.2f);
    }

    return true;
}
