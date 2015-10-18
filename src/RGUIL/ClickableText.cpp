//R.K.
#include "global.h"

ClickableText::ClickableText(std::string normal_font, std::string bold_font, int x, int y, int font_height, ALLEGRO_COLOR text_color, std::string text_string)
                            : ct_normal_font(normal_font), ct_bold_font(bold_font), ct_original_x(x), ct_original_y(y), ct_text_color(text_color), ct_text(text_string),
                            Button(normal_font, x , y, x, y, "", al_map_rgba(0,0,0,0))
{
    ct_nfont = al_load_ttf_font(normal_font.c_str(), font_height, 0);
    if(ct_nfont == nullptr)
    {
        al_show_native_message_box(NULL, "Error", "Failed to load font!", normal_font.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }
    ct_bfont = al_load_ttf_font(bold_font.c_str(), font_height, 0);
    if(ct_bfont == nullptr)
    {
        al_show_native_message_box(NULL, "Error", "Failed to load font!", bold_font.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ct_bascent = al_get_font_line_height(ct_bfont);
    ct_bwidth = al_get_text_width(ct_bfont, ct_text.c_str());
    ct_width = ct_bwidth;
    ct_height = ct_bascent;

    ct_x1 = ct_original_x;
    ct_y1 = ct_original_y;
    ct_x2 = ct_original_x + ct_bwidth;
    ct_y2 = ct_original_y + ct_bascent;

    change_coords(ct_x1, ct_y1, ct_x2, ct_y2);
}

ClickableText::~ClickableText()
{
    if(ct_nfont != nullptr)
        al_destroy_font(ct_nfont);
    if(ct_bfont != nullptr)
        al_destroy_font(ct_bfont);
}

bool ClickableText::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    return Button::Input(event, xscale, yscale);
}

bool ClickableText::Print()
{
    if(clicking == true)
    {
        al_draw_text(ct_nfont, ct_text_color, ct_x1, ct_y1, 0, ct_text.c_str());
        al_draw_text(ct_nfont, al_map_rgba(0,0,0,100), ct_x1, ct_y1, 0, ct_text.c_str());
    }
    else if(mouse_on_it == true)
    {
        al_draw_text(ct_nfont, ct_text_color, ct_x1, ct_y1, 0, ct_text.c_str());
        al_draw_text(ct_nfont, al_map_rgba(0,0,0,50), ct_x1, ct_y1, 0, ct_text.c_str());
    }
    else
    {
        al_draw_text(ct_nfont, ct_text_color, ct_x1, ct_y1, 0, ct_text.c_str());
    }

    if(clicked == true && outline_if_clicked == true)
    {
        al_draw_text(ct_bfont, ct_outline_color, ct_x1, ct_y1, 0, ct_text.c_str());
        al_draw_text(ct_nfont, ct_text_color, ct_x1, ct_y1, 0, ct_text.c_str());
    }

    return true;
}

void ClickableText::Click()
{
    clicked = true;
}
