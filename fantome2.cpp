#include "fantome2.h"

Fantome2::Fantome2(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4, float startX, float startY, float vitesse)
        : Fantome(sprite1, sprite2, sprite3, sprite4, startX, startY, vitesse) {
}



void Fantome2::deplacement() {
    const float scaleX = 1500.0f / 895.0f;
    const float scaleY = 800.0f / 993.0f;

    if (direction == 1) {
        if (x > 53 * scaleX) {
            x -= vitesse;
        } else {
            direction = 2;
        }
    }
    else if (direction == 2) {
        if (y > 927 * scaleY) {
            y -= vitesse;
        } else {
            direction = 3;
        }
    }
    else if (direction == 3) {
        if (x < 840 * scaleX) {
            x += vitesse;
        } else {
            direction = 4;
        }
    }
    else if (direction == 4) {
        if (y < 935 * scaleY) {
            y += vitesse;
        } else {
            direction = 1;
        }
    }
}
void Fantome2::loadSprites(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4) {
    sprites[0] = al_load_bitmap(sprite1);
    sprites[1] = al_load_bitmap(sprite2);
    sprites[2] = al_load_bitmap(sprite3);
    sprites[3] = al_load_bitmap(sprite4);

    for (int i = 0; i < 4; i++) {
        if (!sprites[i]) {
            exit(1);
        }
    }
}

void Fantome2::draw() {

    if (direction == 1 || direction == 2) {
        al_draw_bitmap(sprites[direction - 1], x, y, 0);
    } else {
        al_draw_bitmap(sprites[direction - 1], x, y, 0);
    }
}


void Fantome2::update() {
    deplacement();
    spriteIndex = (spriteIndex + 1) % 4;
}