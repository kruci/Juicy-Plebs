#ifndef SCREENPLAY_H
#define SCREENPLAY_H

#include "global.h"

class ScreenPlay
{
private:
    ALLEGRO_BITMAP *background = nullptr;

    enum SPbutton_names{BACK = 0, NEWGAME, OK, BACK2};

    std::vector<Button *> buttons;

    Button *but;

    ScrollableArea *scba = nullptr;
    ALLEGRO_FONT * n_font = nullptr;
    InputField *inpf = nullptr;

    bool is_any_button_clicked();
public:
    ScreenPlay(Button *ext_b);
    virtual ~ScreenPlay();

    void Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    void Print();
};

#endif // SCREENPLAY_H
