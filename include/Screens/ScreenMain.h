//R.K.
#ifndef SCREENMAIN_H
#define SCREENMAIN_H

#include "global.h"
#include "include/Screens/ScreenAbout.h"
#include "include/Screens/ScreenPlay.h"
#include "include/Screens/ScreenGame.h"
#include "include/Audio/AudioHandler.h"

#include <chrono>
#include <random>

#define INTRO_SUND_FILE "resources/music/menu.ogg"

class ScreenMain
{
private:
    ALLEGRO_BITMAP *zemak_bitmap = nullptr;
    ALLEGRO_BITMAP *background = nullptr;
    Button *zemak_button = nullptr;
    int zemiak_size = 500;

    enum SMbutton_names{EXIT = 0, PLAY, ABOUT, SETTINGS};

    std::vector<Button *> buttons;

    #define NUMBER_OF_HLASKY 3
    std::mt19937 generator;//(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<AudioHandler::sound_effect *> hlasky;

    ScreenAbout *SCAbout = nullptr;
    ScreenPlay *SCPlay = nullptr;
    ScreenGame *SCGame = nullptr;
    CollisionHandler *colider = nullptr;
    RayCastCallBack *raycallback = nullptr;

    ALLEGRO_SAMPLE *intro_music = nullptr;
    ALLEGRO_SAMPLE_INSTANCE *intro_music_instance = nullptr;

    bool is_any_button_clicked();
public:
    ScreenMain();
    virtual ~ScreenMain();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENMAIN_H
