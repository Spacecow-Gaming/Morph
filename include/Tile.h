#ifndef TILE_H
#define TILE_H

#include <irrlicht/irrlicht.h>

class Tile
{
public:
    //Initializes the variables
    Tile( int x, int y, int tileType );

    //The tile type
    int type;

    //Position
    irr::core::vector3df position;
protected:
private:
};

#endif // TILE_H