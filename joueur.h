
#ifndef PACMAN_JOUEUR_H
#define PACMAN_JOUEUR_H

#include "ZoneJeu.h"
#include "iostream"
#include <allegro5/allegro.h>
#include "Fantome.h"
#include "Menufin.h"
class joueur {
private:
    ALLEGRO_BITMAP* playerSprites[4];
    float x, y;
    float vitesse;
    int spriteIndex;
    int vies = 3;
    float cooldown;
    const float collisionCooldown = 1.0f;
public:

    joueur(const char* filename1, const char* filename2, const char* filename3, const char* filename4, float startX, float startY, float vitesse);
    ~joueur();
    void draw() const;
    void deplacement(float dx, float dy);
    int perdreVie(ALLEGRO_DISPLAY* fenetre, Menufin& menufin, int score, float timer);
    bool collisionAvecFantome(Fantome* fantome, Fantome* fantome2);
    void resetCollisionFlag();
    float getX();
    int& getVies();
    void updateCooldown(float deltaTime);
    float getY();

    bool isHitThisFrame;
};



#endif //PACMAN_JOUEUR_H
