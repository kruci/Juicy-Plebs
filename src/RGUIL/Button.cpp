#include "global.h"

Button::Button()
{
    //ctor
}

Button::Button(std::string font_to_load, int x1, int y1, int x2, int y2, std::string text, ALLEGRO_COLOR color, std::string image)
              :x1(x1), x2(x2), y1(y1), y2(y2), text(text), color(color)
{
    width  = x2 - x1;
    height = y2 - y1;

    if(image != "0")
    {
        b_has_image = true;
        bmp = al_load_bitmap(image.c_str());
        if(bmp == nullptr)
        {
            std::string ec = image + "  Not found!";
            al_show_native_message_box(al_get_current_display(), "Error", ec.c_str(), font_to_load.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
        }
        image_width = al_get_bitmap_width(bmp);
        image_height = al_get_bitmap_height(bmp);

        image_scale_x = (float)width / (float)image_width;
        image_scale_y = (float)height / (float)image_height;
    }

    //compute text position
    const char *t = text.c_str();
    int font_size = ((float)height / 5.0f) * 3.8f;

    font = al_load_ttf_font(font_to_load.c_str(), font_size, 0);


    if(font == nullptr)
    {
        al_show_native_message_box(NULL, "Error", "Failed to load font!", font_to_load.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    int fontwidth = al_get_text_width(font, t);

    if(fontwidth >= width)
    {
        font_size = (float)font_size * ((float)width/(float)fontwidth);

        al_destroy_font(font);
        font = al_load_ttf_font(font_to_load.c_str(),font_size,0);
    }

    centerx = (float)x1 + (float)width  / 2.0f;
    centery = (float)y1 + (float)height / 2.0f;

    textx = (float)x1 + (float)(width - al_get_text_width(font, t)) / 2.0f;
    texty = (float)y1 + (float)(height -al_get_font_ascent(font))   / 2.0f;
    texty_ =  (float)(height -al_get_font_ascent(font))   / 2.0f;

    x = x1;
    y = y1;

    origin_x1 = x1;
    origin_y1 = y1;
    origin_x2 = x2;
    origin_y2 = y2;

    as_bitmap = al_create_bitmap(width, height);
}

Button::Button(int x_1, int y_1, int x_2, int y_2)
{
    x1 = x_1;
    y1 = y_1;
    x2 = x_2;
    y2 = y_2;

    width  = x2 - x1;
    height = y2 - y1;

    origin_x1 = x1;
    origin_y1 = y1;
    origin_x2 = x2;
    origin_y2 = y2;
}

Button::~Button()
{
    if(font != nullptr)
        al_destroy_font(font);
    if(bmp != nullptr)
        al_destroy_bitmap(bmp);
    if(as_bitmap != nullptr)
        al_destroy_bitmap(as_bitmap);

    //std::cout << "Delet button " << text << std::endl;
}


bool Button::Print()
{
    if(clicking == true)
    {
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0.0f, 0.0f, image_width, image_height, x1, y1, width, height, 0);
        }
        al_draw_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, al_map_rgb(0,0,0), 2.0f);
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, al_map_rgba(0,0,0,150));
        al_draw_text(font,al_map_rgb(255,255,255), textx, texty, 0, text.c_str());
    }
    else if(mouse_on_it == true)
    {
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0, 0, image_width, image_height, x1, y1, width, height, 0);
        }
        al_draw_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, al_map_rgb(0,0,0), 2.0f);
        al_draw_text(font,al_map_rgb(255,255,255), textx, texty, 0, text.c_str());
    }
    else
    {
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0, 0, image_width, image_height, x1, y1, width, height, 0);
        }
        al_draw_rounded_rectangle(x1, y1, x2, y2, 5.0f, 5.0f, al_map_rgba(0,0,0,150), 1.0f);
        al_draw_text(font,al_map_rgb(255,255,255), textx, texty , 0, text.c_str());
    }
    return true;
}

bool Button::Bitmap()
{
    al_set_target_bitmap(as_bitmap);
    al_clear_to_color(al_map_rgba(0,0,0,0));

    if(clicking == true)
    {
        al_draw_filled_rounded_rectangle(0, 0, width, height, 5, 5, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0, 0, image_width, image_height, 0, 0, width, height, 0);
        }
        al_draw_rounded_rectangle(0, 0, width, height, 5, 5, al_map_rgb(0,0,0), 2);
        al_draw_filled_rounded_rectangle(0, 0, width, height, 5, 5, al_map_rgba(0,0,0,150));
        al_draw_text(font,al_map_rgb(255,255,255), textx - x1, texty_, 0, text.c_str());
    }
    else if(mouse_on_it == true)
    {
        al_draw_filled_rounded_rectangle(0, 0, width, height, 5, 5, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0, 0, image_width, image_height, 0, 0, width, height, 0);
        }
        al_draw_rounded_rectangle(0, 0, width, height, 5, 5, al_map_rgb(0,0,0), 2);
        al_draw_text(font,al_map_rgb(255,255,255), textx - x1, texty_, 0, text.c_str());
    }
    else
    {
        al_draw_filled_rounded_rectangle(0, 0, width, height, 5, 5, color);
        if(b_has_image == true)
        {
            al_draw_scaled_bitmap(bmp, 0, 0, image_width, image_height, 0, 0, width, height, 0);
        }
        al_draw_rounded_rectangle(0, 0, width, height, 5, 5, al_map_rgba(0,0,0,150), 1);
        al_draw_text(font,al_map_rgb(255,255,255), textx - x1, texty_, 0, text.c_str());
    }

    al_set_target_backbuffer(al_get_current_display());

    return true;
}

int  Button::Input(ALLEGRO_EVENT &event, float &scalex, float &scaley)
{
    if(active == false)
    {
        return 9;
    }
    /**return 0  if mouse is on button but mouse button isnt down
       return 1  if mouse is on button and mouse button is down
       return 2  if mouse clicked this button
       return 3  if mouse isnt on button and mouse isnt clicking
       return 9  if button is not active**/
    if(rguil::mouse_state->x >= x1*scalex && rguil::mouse_state->x <= x2*scalex &&
       rguil::mouse_state->y >= y1*scaley && rguil::mouse_state->y <= y2*scaley)
    {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && clicking == true)
        {
            if(clicked == true)
            {
                clicked_again = true;
            }
            clicking = false;
            clicked = true;
            return 2;
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || clicking == true)
        {
            clicking = true;
            return 1;
        }
        else
        {
            mouse_on_it = true;
            clicking = false;
            return 0;
        }
        //Another variant
        /*if(al_mouse_button_down(&gv::mouse_state, 1) == true)
        {
            clicking = true;
            return 1;
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && clicking == true)
        {
            clicking = false;
            clicked = true;
            return 2;
        }
        else
        {
            mouse_on_it = true;
            clicking = false;
            return 0;
        }*/
    }
    else
    {
        mouse_on_it = false;
        clicking = false;
        return 3;
    }

    return -1;
}


bool Button::is_button_clicked()
{
    if(clicked == true)
    {
       return true;
    }
    return false;
}

bool Button::is_button_clicking()
{
    if(clicking == true)
    {
       return true;
    }
    return false;
}

bool Button::is_button_clicked_again()
{
    if(clicked_again == true)
    {
       return true;
    }
    return false;
}

bool Button::is_mouse_in_it()
{
    if(mouse_on_it == true)
    {
       return true;
    }
    return false;
}

bool Button::unclick()
{
    clicked = false;
    clicked_again = false;
    return true;
}

bool Button::has_image()
{
    if(b_has_image == true)
    {
        return true;
    }
    return false;
}

int Button::Get_width()
{
    return width;
}

int Button::Get_height()
{
    return height;
}

bool Button::change_coords(int new_x1, int new_y1, int new_x2, int new_y2)
{
    x1 = new_x1;
    y1 = new_y1;
    x2 = new_x2;
    y2 = new_y2;

    x = x1;
    y = y1;

    if(as_bitmap != nullptr)
    {
        al_destroy_bitmap(as_bitmap);
        as_bitmap = al_create_bitmap(width, height);
    }

    return true;
}

bool Button::Active(bool true_or_false)
{
    return active = true_or_false;
}
