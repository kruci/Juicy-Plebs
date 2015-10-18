#include "ScreenPlay.h"

ScreenPlay::ScreenPlay(Button *ext_b) : but(ext_b)
{
    std::string bnames[4] = {"Back", "New game"};

    int bpoz[4][4] = {  {1300, global::dHeight -70, 120, 50},
                        { (global::dWidth-120)/2, global::dHeight -70, 120, 50},    };

    for(int a = 0;a < 2;a++)
    {
        buttons.push_back(new Button("resources/fonts/Calibri.ttf", bpoz[a][0], bpoz[a][1], bpoz[a][0] + bpoz[a][2],bpoz[a][1] + bpoz[a][3], bnames[a], al_map_rgb(0,0,128)));
    }

    scba = new ScrollableArea(((float)global::dWidth - 500.0f)/2.0f ,100, 500 ,global::dHeight-200);
    scba->background_col = al_map_rgba(0,0,0,128);
}

ScreenPlay::~ScreenPlay()
{
     if(background != nullptr)
        al_destroy_bitmap(background);

    for(int a = 0;a < buttons.size();a++)
    {
        delete buttons[a];
    }
    buttons.clear();

    if(scba != nullptr)
        delete scba;

    if(inpf != nullptr)
        delete inpf;
}

void ScreenPlay::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    if(is_any_button_clicked() == false)
    {
        scba->Input(event, xscale, yscale);

        for(int a = 0;a < buttons.size();a++)
        {
            buttons[a]->Input(event, xscale, yscale);
        }
    }

    if(buttons[BACK]->is_button_clicked() == true)
    {
        but->unclick();
    }
    else if(buttons[NEWGAME]->is_button_clicked() == true)
    {
    }


    return;
}

void ScreenPlay::Print()
{
    al_clear_to_color(al_map_rgb(0,125,0));
    scba->Print();

    for(int a = 0;a < buttons.size();a++)
    {
            buttons[a]->Print();
    }
}

bool ScreenPlay::is_any_button_clicked()
{
    for(int a = 0;a < buttons.size();a++)
    {
        if(buttons[a]->is_button_clicked() == true)
        {
            return true;
        }
    }

    return false;
}
