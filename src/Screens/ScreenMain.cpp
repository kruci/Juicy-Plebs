//R.K.
#include "ScreenMain.h"

ScreenMain::ScreenMain()
{
    //background = al_load_bitmap("resources/graphics/zemiak.png");

    std::string bnames[3] = {"Exit", "Play", "About"};

                        //x1, y1, width, height
    /*int bpoz[4][4] = {  {1300, global::dHeight -70, 120, 50},
                        {((float)global::dWidth-250.0f)/2.0f, ((float)global::dHeight-80.0f)/2.0f, 250, 80},
                        {global::dWidth - 1300 -120,global::dHeight -70,120,50},
                        {((float)global::dWidth-120.0f)/2.0f, global::dHeight-70, 120, 50}  };*/

    int b_y = (float)global::dHeight / 9.0f;

    int bpoz[3][4] = {  {1300, global::dHeight -70, 120, 50},
                        {((float)global::dWidth-220.0f), b_y*1, 200, 65},
                        {global::dWidth -200, b_y*2, 180, 58}   };

    for(int a = 0;a < 3;a++)
    {
        buttons.push_back(new Button("resources/fonts/Calibri.ttf", bpoz[a][0], bpoz[a][1], bpoz[a][0] + bpoz[a][2],bpoz[a][1] + bpoz[a][3], bnames[a], al_map_rgb(0,0,128)));
    }

    Musicb = new Button("resources/fonts/Calibri.ttf", global::dWidth -60, 20, global::dWidth -60 + 40,20 +40, "", al_map_rgba(0,0,0,0), ( global::audio == true ? MusicON : MusicOFF));
}

ScreenMain::~ScreenMain()
{
    if(background != nullptr)
        al_destroy_bitmap(background);

    for(int a = 0;a < buttons.size();a++)
    {
        delete buttons[a];
    }
    buttons.clear();

    if(SCAbout != nullptr)
        delete SCAbout;
    if(SCPlay != nullptr)
        delete SCPlay;

    delete Musicb;
}

void ScreenMain::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    if(global::play == true)
    {
        if(SCGame == nullptr)
        {
            SCGame = new ScreenGame();
        }

        SCGame->Input(event, xscale, yscale);

        return;
    }
    else
    {
        if(SCGame != nullptr)
        {
            delete SCGame;
        }
    }

    if(is_any_button_clicked() == false)
    {
        if(SCAbout != nullptr)
        {
            delete SCAbout;
            SCAbout = nullptr;
        }
        if(SCPlay != nullptr)
        {
            delete SCPlay;
            SCPlay = nullptr;
        }

        Musicb->Input(event, xscale, yscale);
        if(Musicb->is_button_clicked() == true)
        {
            Musicb->unclick();
            global::audio = (global::audio == true ? global::audio = false : global::audio = true);

            if(global::audio == true)
            {
                al_destroy_bitmap(Musicb->bmp);
                Musicb->bmp = al_load_bitmap(MusicON);
            }
            else
            {
                al_destroy_bitmap(Musicb->bmp);
                Musicb->bmp = al_load_bitmap(MusicOFF);
            }
        }

        for(int a = 0;a < buttons.size();a++)
        {
            buttons[a]->Input(event, xscale, yscale);
        }
    }

    if(buttons[EXIT]->is_button_clicked() == true)
    {
        global::loop = false;
    }
    else if(buttons[PLAY]->is_button_clicked() == true)
    {
        if(SCPlay == nullptr)
        {
            SCPlay = new ScreenPlay(buttons[PLAY]);
        }
        SCPlay->Input(event, xscale, yscale);
    }
    else if(buttons[ABOUT]->is_button_clicked() == true)
    {
        if(SCAbout == nullptr)
        {
            SCAbout = new ScreenAbout(buttons[ABOUT]);
        }
        SCAbout->Input(event, xscale, yscale);
    }

    return;
}

void ScreenMain::Print()
{
    if(global::play == true)
    {
        if(SCGame == nullptr)
        {
            SCGame = new ScreenGame();
        }

        SCGame->Print();

        return;
    }

    if(buttons[PLAY]->is_button_clicked() == true)
    {
        if(SCPlay == nullptr)
        {
            SCPlay = new ScreenPlay(buttons[PLAY]);
        }

        SCPlay->Print();
    }
    else if(buttons[ABOUT]->is_button_clicked() == true)
    {
        if(SCAbout == nullptr)
        {
            SCAbout = new ScreenAbout(buttons[ABOUT]);
        }

        SCAbout->Print();
    }
    else
    {
        //al_draw_bitmap(background,0,0,0);
        Musicb->Print();

        for(int a = 0;a < buttons.size();a++)
        {
            buttons[a]->Print();
        }
    }

    return;
}

bool ScreenMain::is_any_button_clicked()
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
