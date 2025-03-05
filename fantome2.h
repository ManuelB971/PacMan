#ifndef PACMAN_FANTOME2_H
#define PACMAN_FANTOME2_H

#include "fantome.h"

class Fantome2 : public Fantome {
public:
    Fantome2(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4, float startX, float startY, float vitesse);
    void deplacement() override;
    void loadSprites(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4)override;
    void draw()override;
    void update() override;
};


#endif //PACMAN_FANTOME2_H
