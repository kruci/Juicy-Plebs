//R.K.
#ifndef SCREENPLAY_H
#define SCREENPLAY_H

#include "global.h"
#include "include/Saves/GameSave.h"

class ScreenPlay
{
private:
    ALLEGRO_BITMAP *background = nullptr;

    enum SPbutton_names{BACK = 0, NEWGAME, OK};

    std::vector<Button *> buttons;

    Button *but;

    ScrollableArea *scba = nullptr;
    ALLEGRO_FONT * n_font = nullptr;
    ALLEGRO_FONT * m_font = nullptr;
    InputField *inpf = nullptr;

    GameSave *gms = nullptr;

    std::vector<std::string> savefiles;
    bool couldnot_load_savefile = false;

    bool is_any_button_clicked();
    bool scan_save_files();
public:
    ScreenPlay(Button *ext_b);
    virtual ~ScreenPlay();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENPLAY_H
