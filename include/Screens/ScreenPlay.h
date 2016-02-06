//R.K.
#ifndef SCREENPLAY_H
#define SCREENPLAY_H

#include "global.h"
#include "include/Saves/GameSave.h"
#include <sstream>
#include <iomanip>

class ScreenPlay
{
private:
    ALLEGRO_BITMAP *background = nullptr;
    ALLEGRO_BITMAP *zemak_bitmpa = nullptr;

    enum SPbutton_names{BACK = 0, NEWGAME, OK};

    std::vector<Button *> buttons;

    Button *but;

    ScrollableArea *scba = nullptr;
    ALLEGRO_FONT * n_font = nullptr;
    ALLEGRO_FONT * m_font = nullptr;
    ALLEGRO_FONT *s_font = nullptr;
    InputField *inpf = nullptr;

    GameSave *gms = nullptr;

    std::vector<std::string> savefiles;
    bool couldnot_load_savefile = false;

    bool is_any_button_clicked();
    bool scan_save_files();

    //graphic calcl trash
    #define ZEMIAK_SIZE 100
    float *zemaky = nullptr;
    int number_of_zemaky = 0;

public:
    ScreenPlay(Button *ext_b);
    virtual ~ScreenPlay();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENPLAY_H
