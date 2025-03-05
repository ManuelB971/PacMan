#include "Menufin.h"
#include "Menu.h"
#define WIDTH 1500
#define HEIGHT 800

bool Menufin::afficherEcranDeFin(ALLEGRO_DISPLAY* fenetre, int score, float temps) {
    ALLEGRO_FONT* font2 = al_load_ttf_font("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Fonts\\ARCADE_I.TTF", 48, 0);
    if (!font2) {

        return false;
    }

    ALLEGRO_COLOR boutonCouleur = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR texteCouleur = al_map_rgb(255, 255, 255);

    int boutonX = WIDTH / 2 - 150;
    int boutonY = HEIGHT / 2 + 50;
    int boutonLargeur = 300;
    int boutonHauteur = 100;

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(fenetre));

    bool retry = false;
    bool waiting = true;

    while (waiting) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_textf(font2, texteCouleur, WIDTH / 2, HEIGHT / 4, ALLEGRO_ALIGN_CENTER, "FIN DE PARTIE");
        al_draw_textf(font2, texteCouleur, WIDTH / 2, HEIGHT / 4 + 100, ALLEGRO_ALIGN_CENTER, "Score: %d", score);
        al_draw_textf(font2, texteCouleur, WIDTH / 2, HEIGHT / 4 + 200, ALLEGRO_ALIGN_CENTER, "Time: %.2f ", temps);

        al_draw_filled_rectangle(boutonX, boutonY, boutonX + boutonLargeur, boutonY + boutonHauteur, boutonCouleur);
        al_draw_text(font2, al_map_rgb(0, 0, 0), WIDTH / 2, boutonY + 25, ALLEGRO_ALIGN_CENTER, "Retry");

        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            waiting = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouseX = event.mouse.x;
            int mouseY = event.mouse.y;

            if (mouseX >= boutonX && mouseX <= boutonX + boutonLargeur &&
                mouseY >= boutonY && mouseY <= boutonY + boutonHauteur) {
                retry = true;
                waiting = false;
            }

        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                waiting = false;
            }
        }
    }

    al_destroy_font(font2);
    al_destroy_event_queue(eventQueue);

    return retry;
}
