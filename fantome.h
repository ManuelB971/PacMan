
#ifndef PACMAN_FANTOME_H
#define PACMAN_FANTOME_H



#include "allegro5/allegro.h"
#include <string>


class Fantome {
private:


    virtual void loadSprites(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4);

protected:
    ALLEGRO_BITMAP* sprites[4];
    int direction;
    float x;
    float vitesse;
    float y;
    int spriteIndex;
public:
    Fantome(const char* sprite1, const char* sprite2, const char* sprite3, const char* sprite4, float startX, float startY, float vitesse);
    ~Fantome();

    virtual void deplacement();
    virtual void draw() ;
    virtual void update();
    float getX();
    float getY();
    float getWidth() const;
    float getHeight() const;

};



#endif //PACMAN_FANTOME_H
