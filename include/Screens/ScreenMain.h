#ifndef SCREENMAIN_H
#define SCREENMAIN_H

#include "global.h"
#include "include/Screens/ScreenAbout.h"
#include "include/Screens/ScreenPlay.h"

#define MusicON "resources/graphics/m_on.png"
#define MusicOFF "resources/graphics/m_off.png"

class ScreenMain
{
private:
    ALLEGRO_BITMAP *background = nullptr;

    enum SMbutton_names{EXIT = 0, PLAY, ABOUT, SETTINGS};

    std::vector<Button *> buttons;
    Button *Musicb = nullptr;

    ScreenAbout *SCAbout = nullptr;
    ScreenPlay * SCPlay = nullptr;

    bool is_any_button_clicked();
public:
    ScreenMain();
    virtual ~ScreenMain();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENMAIN_H
