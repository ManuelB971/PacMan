#ifndef PACMAN_MENU_H
#define PACMAN_MENU_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_primitives.h"

#include "ZoneJeu.h"
class Menu : public Zonejeu{
private:
    ALLEGRO_DISPLAY* fenetre;
    int width, height;
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* Gfont;
    bool estDansRectangle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight);
public:
    Menu(ALLEGRO_DISPLAY* display, int w, int h, const char* mapFilename);
    ~Menu() override{if (font) {al_destroy_font(font);}};
    bool afficher();

};


#endif //PACMAN_MENU_H
