#include "../include/Tile.h"

Tile::Tile( int x, int y, int z, int tileType )
{
    position = irr::core::vector3df((float)x, (float)y, (float)z);
    type = tileType;
}

