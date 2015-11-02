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

    //#define NUMBER_OF_HLASKY 3
    std::mt19937 generator;//(std::chrono::system_clock::now().time_since_epoch().count());
    //std::vector<AudioHandler::sound_effect *> hlasky;

    int number_of_written_hlasky = 19;
    signed int playing_hlaska = -1;
    ALLEGRO_FONT * hlasky_font = nullptr;
    std::string written_hlasky[19] = { "Je to malá hra pre ľudstvo no obrovská pre zemiak.",
        "Čo to je? Vyrážka? Zomriem... aha... klíčok.",
        "Hádaj na aké číslo myslím! Áno je to 47...",
        "Túto hru ukáž svojej mame!",
        "Majú zrnká ryže vädomie? Majú vedomie samostatné alebo kolektívne?",
        "Nevieš aké víza potrebuje zemiak na pobyt v USA?",
        "Je divné, že mám teraz chuť na hranolky?",
        "Zober zemiak, nie drogu!",
        "Vedel si, že? Nakoľko zemiak nemá alkohol dehydrogenázu, nemôže sa opiť!",
        "Mal som jedného kamoša, skončil v šaláte! Hehe, robím si srandu, skočil z mosta.",
        "Máš niečo na obrazovke presneeee tu ------------------->",
        "Nevieš koľko je hodín? Nenosím hodinky.",
        "Trimetylthiobutanal? No fuj!",
        "I am legal senpai!",
        "Vieš o tom, že nemám ani rok? Ľudia majú tak pomalý mentálny vývin!",
        "Nechcem sa rozprávať o viere ale... veríš v pohoria? Ja som totiž kopconeveriaci!",
        "Premýšľal si niekedy nad tým ako vyzerá trojdimenzionálna priestor?",
        "Múmia sa vracia! {retrun \"múmia\"}",
        "Keď môžem na psa zavaliť prd, môžem naň ho zvaliť i zle nakódenú hru?" };

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
