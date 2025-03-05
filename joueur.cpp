#include "ZoneJeu.h"
#include "joueur.h"
#include "Menufin.h"
#include <allegro5/allegro.h>

using namespace std;

joueur::joueur(const char* filename1, const char* filename2, const char* filename3, const char* filename4, float startX, float startY, float vitesse) :
        x(startX), y(startY), vitesse(vitesse), spriteIndex(0),vies(3), cooldown(0.0f),isHitThisFrame(false) {
    playerSprites[0] = al_load_bitmap(filename1);
    playerSprites[1] = al_load_bitmap(filename2);
    playerSprites[2] = al_load_bitmap(filename3);
    playerSprites[3] = al_load_bitmap(filename4);

    for (int i = 0; i < 3; i++) {
        if (!playerSprites[i]) {
            exit(1);
        }
    }
}

int joueur::perdreVie(ALLEGRO_DISPLAY* fenetre, Menufin& menufin, int score, float timer) {
    --vies;
    if (vies == 0) {
        menufin.afficherEcranDeFin(fenetre, score, timer);
        exit(0);
    }
    return vies;
}
void joueur::resetCollisionFlag() {
    isHitThisFrame = false;
}
void joueur::updateCooldown(float deltaTime) {
    if (cooldown > 0.0f) {
        cooldown -= deltaTime;
    } else {
        isHitThisFrame = false;
    }
}
bool joueur::collisionAvecFantome(Fantome* fantome, Fantome* fantome2) {
    if (cooldown > 0.0f) {
        return false;
    }

    if (x < fantome->getX() + fantome->getWidth() &&
        x + 50 > fantome->getX() &&
        y < fantome->getY() + fantome->getHeight() &&
        y + 50 > fantome->getY()) {
        cooldown = collisionCooldown;
        isHitThisFrame = true;
        return true;
    }

    if (x < fantome2->getX() + fantome2->getWidth() &&
        x + 50 > fantome2->getX() &&
        y < fantome2->getY() + fantome2->getHeight() &&
        y + 50 > fantome2->getY()) {
        cooldown = collisionCooldown;
        isHitThisFrame = true;  
        return true;
    }
    return false;
}

void joueur::deplacement(float dx, float dy) {
    x= x + dx * vitesse ;
    y =y + dy * vitesse;
    if (x < 0) x = 0;
    if (x > WIDTH) x = WIDTH -100;
    if (y < 0) y = 0;
    if (y > HEIGHT) y = HEIGHT -100;

    spriteIndex = (spriteIndex + 1) % 3;
}



joueur::~joueur() {
    for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(playerSprites[i]);
    }
}

void joueur::draw() const {
    al_draw_bitmap(playerSprites[spriteIndex], x, y, 0);
}

float joueur::getX() {
    return x;
}

float joueur::getY() {
    return y;
}

int& joueur::getVies() {
    return vies;
}
