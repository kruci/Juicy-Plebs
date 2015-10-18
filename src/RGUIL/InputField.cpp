//R.K.
#include "global.h"

InputField::InputField()
{
    //ctor
}

InputField::InputField(std::string font_path, std::string init_string, int x, int y, int width, int height,
                       ALLEGRO_COLOR outline, ALLEGRO_COLOR textcolor, ALLEGRO_COLOR backgroundcolor)
                      : x1(x), y1(y), width(width), height(height), outline_color(outline), text_color(textcolor), bckground_color(backgroundcolor)
{
    x2 = x1 + width;
    y2 = y1 + height;

    int font_size = ((float)height / 5.0) * 4.0;

    font = al_load_ttf_font(font_path.c_str(), font_size, 0);


    if(font == nullptr)
    {
        al_show_native_message_box(NULL, "Error", "Failed to load font!", font_path.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    text = init_string;
    text_width =  al_get_text_width(font, text.c_str());
    text_height = al_get_font_ascent(font);

    //al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);  //alredy called in main
    bmp = al_create_bitmap(width, height);
    al_set_target_bitmap(bmp);
    al_clear_to_color(bckground_color);
    al_set_target_backbuffer(al_get_current_display());

    detectingbutton = new Button(x1, y1, x2, y2);

    al_text = al_ustr_new(text.c_str());

    as_bitmap = al_create_bitmap(width, height);

    x = x1;
    y = y1;

    origin_x1 = x1;
    origin_y1 = y1;
    origin_x2 = x2;
    origin_y2 = y2;
}

InputField::~InputField()
{
    if(font != nullptr)
        al_destroy_font(font);
    if(bmp != nullptr)
        al_destroy_bitmap(bmp);
    if(detectingbutton != nullptr)
        delete detectingbutton;
    if(al_text != nullptr)
        al_ustr_free(al_text);
    if(as_bitmap != nullptr)
        al_destroy_bitmap(as_bitmap);
}

bool InputField::Print()
{
    al_set_target_bitmap(bmp);
    al_clear_to_color(bckground_color);

    float tx = (text_width <= width ? (center == true ? (width - text_width)/2 : 0) : width - text_width);

    al_draw_text(font, text_color, tx, (height - text_height) / 2.0f, 0, text.c_str());

    if(detectingbutton->is_button_clicked() == true)
    {
        if(bling > 30)
        {
            al_draw_line(tx + text_width -2, (height - text_height) / 2.0f, tx + text_width -2, (height + text_height) / 2.0f, text_color, 2);
            if(bling > 60)
            {
                bling = 0;
            }
        }
        bling++;
    }

    al_set_target_backbuffer(al_get_current_display());
    al_draw_bitmap(bmp, x1, y1, 0);
    al_draw_rounded_rectangle(x1, y1, x2, y2, 5, 5, outline_color, 2);

    return true;
}

bool InputField::Bitmap()
{

   // al_set_target_bitmap(bmp);
    al_set_target_bitmap(as_bitmap);
    al_clear_to_color(bckground_color);

    //float tx = (text_width <= width ? 0 : width - text_width);
    float tx = (text_width <= width ? (center == true ? (width - text_width)/2 : 0) : width - text_width);

    al_draw_text(font, text_color, tx, (height - text_height) / 2.0f, 0, text.c_str());

    if(detectingbutton->is_button_clicked() == true)
    {
        if(bling > 30)
        {
            al_draw_line(tx + text_width -2, (height - text_height) / 2.0f, tx + text_width -2, (height + text_height) / 2.0f, text_color, 2);
            if(bling > 60)
            {
                bling = 0;
            }
        }
        bling++;
    }

    /*al_set_target_bitmap(as_bitmap);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_bitmap(bmp, 0, 0, 0);*/
    al_draw_rounded_rectangle(0, 0, width, height, 5, 5, outline_color, 2);
    al_set_target_backbuffer(al_get_current_display());
    return true;
}

bool InputField::Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley)
{
    int unichar = 0;

    detectingbutton->Input(ev, scalex, scaley);

    if(detectingbutton->is_button_clicked() == true && detectingbutton->is_mouse_in_it() == false &&
       ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
    {
        detectingbutton->unclick();
    }
    else if(detectingbutton->is_button_clicked() == true)
    {
        if(ev.type == ALLEGRO_EVENT_KEY_CHAR && (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE || ev.keyboard.keycode == ALLEGRO_KEY_ENTER))
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_BACKSPACE :
                    if(al_ustr_length(al_text) > 0)
                    {
                        al_ustr_remove_chr(al_text, al_ustr_length(al_text)-1);
                    }
                    break;
                case ALLEGRO_KEY_ENTER :
                    detectingbutton->unclick();
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(lenght_limit == true && (int)text.size() >= max_lenght)
            {
                return true;
            }
            unichar = ev.keyboard.unichar;

            if(unichar >= 32)
            {
                al_ustr_append_chr(al_text, unichar);
            }
        }
    }

    text = al_cstr_dup(al_text);
    text_width = al_get_text_width(font, text.c_str()) + 7;


    return true;
}

bool InputField::SetDefaultText(std::string default_text)
{
    text = default_text;
    text_width =  al_get_text_width(font, text.c_str()) + 7;

    return true;
}

bool InputField::AcceptingInput()
{
    if(detectingbutton->is_button_clicked() == true)
    {
        return true;
    }
    return false;
}

bool InputField::StopAcceptingInput()
{
    detectingbutton->unclick();
    return true;
}

std::string InputField::ActualText()
{
    return text;
}

int InputField::Get_width()
{
    return width;
}

int InputField::Get_height()
{
    return height;
}

bool InputField::change_coords(int new_x1, int new_y1, int new_x2, int new_y2)
{
    x1 = new_x1;
    y1 = new_y1;
    x2 = new_x2;
    y2 = new_y2;
    width = x2 - x1;
    height = y2 - y1;

    x = x1;
    y = y1;

    if(as_bitmap != nullptr)
    {
        al_destroy_bitmap(as_bitmap);
        as_bitmap = al_create_bitmap(width, height);
    }


    detectingbutton->change_coords(x1, y1, x2, y2);

    return true;
}

bool InputField::Setmaxlenght(int maxlenght)
{
    max_lenght = maxlenght;
    lenght_limit = true;

    return true;
}

bool InputField::Centre(bool tru_of_false){};
bool InputField::Compute(){};
