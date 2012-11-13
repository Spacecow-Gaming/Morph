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
    TILE_RED,
    TILE_WALL,
    TILE_RAMP_TOP = 4,
    TILE_RAMP_RIGHT = 6,
    TILE_RAMP_BOTTOM = 8,
    TILE_RAMP_LEFT = 10,
    AIR = 3
};

enum SHAPE
{
    CUBE,
    RAMP
};

class Level
{
public:
    Level();
    void LoadLevel(int, std::string);
    void DrawLevel(irr::IrrlichtDevice*);
    scene::SMesh* CustomMesh(video::SColor incolor, SHAPE shape);
    virtual ~Level();

    //The array of arrays of tiles - each level of the level
    Tile* tiles[10][256];
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
