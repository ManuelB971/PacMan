#ifndef PACMAN_ZONEJEU_H
#define PACMAN_ZONEJEU_H


#include <vector>
#include <allegro5/allegro.h>
#include <string>
#define WIDTH 1500
#define HEIGHT 800
class Zonejeu {
private:
    ALLEGRO_BITMAP* mapBitmap;
    std::vector<std::vector<bool>> grid; // 0 = vide, 1 = mur
    std::vector<std::string> mapAscii;
    std::vector<std::pair<int, int>> positionsMurs;

public:
    Zonejeu(const char* filename);
    virtual ~Zonejeu();
    void draw() const;
    void drawSmallWhiteCircles();
    void loadAsciiMap(const char* asciiFilePath);
    bool checkCollisionWithCircles(float x, float y);
    bool verifierVictoire();
    void initialiserBoules();
    void initialiserMurs();
    bool checkCollisionWithWall(float x, float y);
};

#endif //PACMAN_ZONEJEU_H
