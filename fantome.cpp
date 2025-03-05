#include "fantome.h"
#include "iostream"

Fantome::Fantome(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4, float startX, float startY, float vitesse) :
        x(startX), y(startY), vitesse(vitesse), spriteIndex(0), direction(2) {
    loadSprites(sprite1, sprite2, sprite3, sprite4);
}

Fantome::~Fantome() {
    for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(sprites[i]);
    }
}

void Fantome::loadSprites(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4) {
    sprites[0] = al_load_bitmap(sprite1);  // Vers la gauche
    sprites[1] = al_load_bitmap(sprite2);  // Vers la gauche
    sprites[2] = al_load_bitmap(sprite3);  // Vers la droite
    sprites[3] = al_load_bitmap(sprite4);  // Vers la droite

    for (int i = 0; i < 4; i++) {
        if (!sprites[i]) {
            exit(1);
        }
    }
}

void Fantome::deplacement() {

    const float scaleX = 1500.0f / 895.0f;
    const float scaleY = 800.0f / 993.0f;

    if (direction == 1) {
        if (x > 40 * scaleX) {
            x -= vitesse;
        } else {
            direction = 2;
        }
    } else if (direction == 2) {
        if (x < 840 * scaleX) {
            x += vitesse;
        } else {
            direction = 3;
        }
    } else if (direction == 3) {
        if (y < 170 * scaleY) {
            y += vitesse;
        } else {
            direction = 1;
        }
    }
}

void Fantome::draw() {

    if (direction == 1 || direction == 2) {
        al_draw_bitmap(sprites[direction - 1], x, y, 0);
    } else {
        al_draw_bitmap(sprites[direction - 1], x, y, 0);
    }
}

void Fantome::update() {
    deplacement();
    spriteIndex = (spriteIndex + 1) % 4;
}

float Fantome::getX() {
    return x;
}

float Fantome::getY() {
    return y;
}
float Fantome::getWidth() const {
    return al_get_bitmap_width(sprites[spriteIndex]);
}

float Fantome::getHeight() const {
    return al_get_bitmap_height(sprites[spriteIndex]);
}