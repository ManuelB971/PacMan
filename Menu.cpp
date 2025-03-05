#include "Menu.h"

using namespace std;

Menu::Menu(ALLEGRO_DISPLAY* fenetre, int width, int height, const char* mapFilename)
        : Zonejeu(mapFilename), fenetre(fenetre), width(width), height(height) {
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Fonts\\ARCADE_I.TTF", 24, 0);
    Gfont = al_load_ttf_font("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Fonts\\ARCADE_I.TTF", 120, 0);
}

bool Menu::afficher()  {
    bool inMenu = true;
    bool startGame = false;

    int rectX = width / 2 - 100;
    int rectY = height / 2 - 50;
    int rectWidth = 200;
    int rectHeight = 100;

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(fenetre));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    while (inMenu) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        this->draw();

        al_draw_filled_rectangle(rectX, rectY, rectX + rectWidth, rectY + rectHeight, al_map_rgb(255, 255, 0));
        al_draw_text(font, al_map_rgb(0, 0, 0), width / 2, height / 2 - 25, ALLEGRO_ALIGN_CENTRE, "JOUER");
        al_draw_text(Gfont, al_map_rgb(255, 255, 0), width / 2, height / 4, ALLEGRO_ALIGN_CENTRE, "PACMAN");
        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            inMenu = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;

            if (estDansRectangle(mouseX, mouseY, rectX, rectY, rectWidth, rectHeight)) {
                startGame = true;
                inMenu = false;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                inMenu = false;
            }
        }
    }

    al_destroy_event_queue(eventQueue);
    return startGame;
}

bool Menu::estDansRectangle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
    return (x >= rectX && x <= rectX + rectWidth && y >= rectY && y <= rectY + rectHeight);
}
