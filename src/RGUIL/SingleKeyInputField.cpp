#include "global.h"

SingleKeyInputField::SingleKeyInputField(std::string font_path, int al_key_code, int x, int y, int width, int height,
                                        ALLEGRO_COLOR outline, ALLEGRO_COLOR textcolor, ALLEGRO_COLOR backgroundcolor)
                                        : InputField(font_path, "", x, y, width, height, outline, textcolor, backgroundcolor)
{
    al_key = al_key_code;

    if(al_key == 999)
    {
        text = "";
        text_width = 7;
    }
    else
    {
        text = al_keycode_to_name(al_key);
        text_width = al_get_text_width(font, text.c_str()) + 7;
    }
}

SingleKeyInputField::~SingleKeyInputField()
{
}

bool SingleKeyInputField::Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley)
{
    detectingbutton->Input(ev, scalex, scaley);

    if(detectingbutton->is_button_clicked() == true && detectingbutton->is_mouse_in_it() == false &&
       ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
    {
        detectingbutton->unclick();
    }
    else if(detectingbutton->is_button_clicked() == true)
    {
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                detectingbutton->unclick();
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
            {
                al_key = 999;
            }
            else
            {
                al_key = ev.keyboard.keycode;
            }
        }
    }

    if(al_key == 999)
    {
        text = "";
        text_width = 7;
        return true;
    }

    text = al_keycode_to_name(al_key);
    text_width = al_get_text_width(font, text.c_str()) + 7;

    return true;
}

bool SingleKeyInputField::Compute()
{
    if(al_key == 999)
    {
        text = "";
        text_width = 7;
        return true;
    }

    text = al_keycode_to_name(al_key);
    text_width = al_get_text_width(font, text.c_str()) + 7;

    return true;
}

bool SingleKeyInputField::Centre(bool tru_of_false)
{
    return (center = tru_of_false);
}
