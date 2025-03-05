#include <vector>
#include <utility>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <algorithm>
#include "joueur.h"
#include "ZoneJeu.h"
#include "Menu.h"
#include "Menufin.h"
#include "Fantome.h"
#include "fantome2.h"
#define WIDTH 1500
#define HEIGHT 800
using namespace std;


int main() {

    assert(al_init());
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY* fenetre = al_create_display(WIDTH, HEIGHT);
    al_set_window_position(fenetre, 0, 0);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    Menu menu(fenetre, WIDTH, HEIGHT, "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Map.png");
    if (!menu.afficher()) {
        al_destroy_display(fenetre);
        return 0;
    }

    Menufin menufin;

    bool retry = true;

    while (retry) {

        ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
        al_register_event_source(eventQueue, al_get_display_event_source(fenetre));
        al_register_event_source(eventQueue, al_get_keyboard_event_source());

        Zonejeu map("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Map.png");
        joueur player(
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\sprite1.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\sprite2.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\sprite3.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\sprite4.png",
                100, 100, 0.1f
        );

        map.loadAsciiMap("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\map.txt");
        map.initialiserBoules();
        map.initialiserMurs();

        Fantome fantome(
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome1.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome2.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome3.png",
                "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome4.png",
                843, 40, 0.2f
        );
        Fantome2 fantome2("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome1.png",
                          "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome2.png",
                          "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome3.png",
                          "C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Image\\Fantome4.png",
                          840, 935, 0.2f);
        bool running = true;
        int score = 0;
        float timer = 0.0f;
        int& vies = player.getVies();
        ALLEGRO_FONT* font1 = al_load_ttf_font("C:\\Users\\MANUEL\\CLionProjects\\PacMan\\Fonts\\ARCADE_I.TTF", 24, 0);

        vector<pair<int, int>> activeDirections;

        while (running) {
            ALLEGRO_EVENT event;

            while (al_get_next_event(eventQueue, &event)) {
                if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    running = false;
                    retry = false;
                } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
                            activeDirections.emplace_back(0, -5);
                            break;
                        case ALLEGRO_KEY_DOWN:
                            activeDirections.emplace_back(0, 5);
                            break;
                        case ALLEGRO_KEY_LEFT:
                            activeDirections.emplace_back(-5, 0);
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            activeDirections.emplace_back(5, 0);
                            break;
                    }
                } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
                    activeDirections.erase(
                            remove_if(activeDirections.begin(), activeDirections.end(),
                                           [&event](const pair<int, int>& dir) {
                                               return (event.keyboard.keycode == ALLEGRO_KEY_UP && dir == make_pair(0, -5)) ||
                                                      (event.keyboard.keycode == ALLEGRO_KEY_DOWN && dir == make_pair(0, 5)) ||
                                                      (event.keyboard.keycode == ALLEGRO_KEY_LEFT && dir == make_pair(-5, 0)) ||
                                                      (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && dir == make_pair(5, 0));
                                           }),
                            activeDirections.end());
                }
                else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        running = false;
                    }
                }
            }

            timer += 1.0f / 120.0f;

            float dx = 0, dy = 0;
            for (const auto& direction : activeDirections) {
                dx += direction.first;
                dy += direction.second;
            }

            float futurX = player.getX() + dx;
            float futurY = player.getY() + dy;



            if (dx != 0 || dy != 0 ||map.checkCollisionWithWall(futurX, futurY)) {
                player.deplacement(dx, dy);
            }
            if (player.collisionAvecFantome(&fantome,&fantome2)) {
                vies = player.perdreVie(fenetre, menufin, score, timer); ;
            }
            player.resetCollisionFlag();

            player.updateCooldown(1.0f / 120.0f);
            if (map.checkCollisionWithCircles(player.getX(), player.getY())) {
                score += 100;
            }

            if (map.verifierVictoire()) {
                running = false;
            }
            fantome.update();
            fantome2.update();
            al_clear_to_color(al_map_rgb(0, 0, 0));

            map.draw();
            al_draw_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgb(255, 255, 0), 20);

            player.draw();
            map.drawSmallWhiteCircles();
            fantome.deplacement();
            fantome2.deplacement();
            fantome.draw();
            fantome2.draw();
            al_draw_textf(font1, al_map_rgb(255, 255, 255), 20, 20, 0, "Score: %d", score);
            al_draw_textf(font1, al_map_rgb(255, 255, 255), WIDTH/2, 20, ALLEGRO_ALIGN_LEFT, "Vies: %d", vies);
            al_draw_textf(font1, al_map_rgb(255, 255, 255), WIDTH - 200, 20, ALLEGRO_ALIGN_RIGHT, "Time: %.2f", timer);

            al_flip_display();
        }

        al_destroy_font(font1);
        al_destroy_event_queue(eventQueue);

        retry = menufin.afficherEcranDeFin(fenetre, score, timer);
    }

    al_destroy_display(fenetre);
    return 0;
}

