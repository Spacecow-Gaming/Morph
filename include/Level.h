#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>

#include <irrlicht/irrlicht.h>

#include "Tile.h"

//Enumerates tile types
enum
{
    //Tile floor and wall sprites
    TILE_FLOOR,
    TILE_HEIGHT_1,
    TILE_HEIGHT_2,
    TILE_RAMP_TOP,
    TILE_RAMP_RIGHT,
    TILE_RAMP_BOTTOM,
    TILE_RAMP_LEFT
};

class Level
{
public:
    Level();
    void LoadLevel();
    void DrawLevel(irr::IrrlichtDevice*);
    virtual ~Level();

    //The array of tiles
    Tile* tiles[256];
protected:
private:
    //The dimensions of the level
    int LEVEL_WIDTH;
    int LEVEL_LENGTH;

    //Tile constants
    int TILE_WIDTH;
    int TILE_LENGTH;
    int TOTAL_TILES;
    int TILE_SPRITES;

};

#endif // LEVEL_H
