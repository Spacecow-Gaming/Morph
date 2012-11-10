#include "../include/Tile.h"

Tile::Tile( int x, int y, int tileType )
{
    position = irr::core::vector3df((float)x, 0.f, (float)y);
    type = tileType;
}

