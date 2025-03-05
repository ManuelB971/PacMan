#include "ZoneJeu.h"
#include <allegro5/allegro_primitives.h>
#include <random>
#include <algorithm>
#include <fstream>
#include "iostream"
using namespace std;


void Zonejeu::loadAsciiMap(const char* asciiFilePath) {
    ifstream file(asciiFilePath);
    if (!file) {
        exit(1);
    }

    string line;
    int y = 0;
    while (getline(file, line)) {
        mapAscii.push_back(line);
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == ' ') {
                positionsMurs.emplace_back(x, y);
            }
        }
        y++;
    }
    file.close();
}
Zonejeu::Zonejeu(const char* filename) {
    mapBitmap = al_load_bitmap(filename);
    if (!mapBitmap) {
        exit(1);
    }

}

Zonejeu::~Zonejeu() {
    al_destroy_bitmap(mapBitmap);
}
vector<pair<int, int>> positionsBoules;
vector<pair<int, int>> positionsMur;
void Zonejeu::initialiserBoules() {
    const int mapHeight = mapAscii.size();
    const int mapWidth = mapAscii[0].size();

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (mapAscii[i][j] == '6') {
                positionsBoules.emplace_back(j, i);
            }
        }
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(positionsBoules.begin(), positionsBoules.end(), g);
}
void Zonejeu::initialiserMurs() {
    const int mapHeight = mapAscii.size();
    const int mapWidth = mapAscii[0].size();

    positionsMur.clear();

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (mapAscii[i][j] == ' ') {  // Assurez-vous que les murs sont bien marqués par un caractère spécifique
                positionsMur.emplace_back(j, i);  // Ajout des coordonnées des murs
            }
        }
    }
}
bool Zonejeu::checkCollisionWithWall(float x, float y) {
    const int collisionRadius = 1;
    for (const auto& mur : positionsMur) {
        float distance = sqrt(pow(mur.first - x, 2) + pow(mur.second - y, 2));
        if (distance >= collisionRadius) {

            return true;
        }
    }

    return false;
}


void Zonejeu::draw() const {
    al_draw_scaled_bitmap(
            mapBitmap,
            0, 0,
            al_get_bitmap_width(mapBitmap),
            al_get_bitmap_height(mapBitmap),
            0, 0,
            WIDTH, HEIGHT,
            0
    );



}

bool Zonejeu::checkCollisionWithCircles(float x, float y) {
    const int mapHeight = mapAscii.size();
    const int mapWidth = mapAscii[0].size();
    const int screenWidth = WIDTH;
    const int screenHeight = HEIGHT;
    const int circleRadius = 5;

    for (auto it = positionsBoules.begin(); it != positionsBoules.end(); ++it) {
        float x_pixel = it->first * (screenWidth / (float)mapWidth);
        float y_pixel = it->second * (screenHeight / (float)mapHeight);

        float distance = sqrt(pow(x_pixel - x, 2) + pow(y_pixel - y, 2));

        if (distance < circleRadius + 40) {
            mapAscii[it->second][it->first] = '@';
            positionsBoules.erase(it);
            return true;
        }
    }

    return false;
}
void Zonejeu::drawSmallWhiteCircles() {
    const int mapHeight = mapAscii.size();
    const int mapWidth = mapAscii[0].size();
    const int screenWidth = WIDTH;
    const int screenHeight = HEIGHT;
    const int circleRadius = 5;

    for (const auto& pos : positionsBoules) {
        float x_pixel = pos.first * (screenWidth / (float)mapWidth);
        float y_pixel = pos.second * (screenHeight / (float)mapHeight);
        al_draw_filled_circle(x_pixel, y_pixel, circleRadius, al_map_rgb(255, 255, 255));
    }
}
bool Zonejeu::verifierVictoire() {
    return positionsBoules.empty();
}