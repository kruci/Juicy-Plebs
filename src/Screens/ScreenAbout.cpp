//R.K.
#include "ScreenAbout.h"

ScreenAbout::ScreenAbout(Button *ext_b) : but(ext_b)
{
    background = al_load_bitmap("resources/graphics/about.png");
    if(background == nullptr) error_message("Could not load image : resources/graphics/about.png");
    button_back = new Button("resources/fonts/Calibri.ttf", 1300, global::dHeight -70, 1300 + 120, global::dHeight -70 + 50, "Back", al_map_rgb(0,0,128));
}

ScreenAbout::~ScreenAbout()
{
    if(background != nullptr)
        al_destroy_bitmap(background);
    if(button_back != nullptr)
        delete button_back;
}

void ScreenAbout::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    button_back->Input(event, xscale, yscale);

    if(button_back->is_button_clicked() == true)
    {
        but->unclick();
    }
}

void ScreenAbout::Print()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(background, (global::dWidth - al_get_bitmap_width(background))/2,
                   (global::dHeight - al_get_bitmap_height(background))/2, 0);
    button_back->Print();
}
