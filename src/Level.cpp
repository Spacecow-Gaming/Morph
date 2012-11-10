#include "../include/Level.h"
#include <iostream>

Level::Level()
{
    //The dimensions of the level
    LEVEL_WIDTH = 1280;
    LEVEL_HEIGHT = 1280;

    //Tile constants
    TILE_WIDTH = 80;
    TILE_HEIGHT = 80;
    TOTAL_TILES = 256;
    TILE_SPRITES = 12;
}

void Level::LoadLevel()
{
    std::cout<<"loadlevel called";
    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream lvl( "levels/test.lvl" );


    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile will be made
        int tileType = -1;

        //Read tile from map file
        lvl >> tileType;

        //If there was a problem in reading the map
        if( lvl.fail() == true )
        {
            //Stop loading map
            lvl.close();
        }

        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            //Create a tile on the heap
            tiles[ t ] = new Tile( x, y, tileType );
        }
        //If we don't recognize the tile type
        else
        {
            //Stop loading map
            lvl.close();
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Close the file
    lvl.close();
}

void Level::DrawLevel(irr::scene::ISceneManager* smgr)
{
    irr::scene::ISceneNode* node;

    for(int i=0; i<16; i++)
    {
        for(int t=0; t<16; t++)
        {
            std::cout <<std::endl<<"drawing tile:"<<i*t;
            node = smgr->addCubeSceneNode();
            node->setPosition(irr::core::vector3df((float)i*10.f, 0.f, (float)t*10.f));
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        }

    }
}

Level::~Level()
{
    //dtor
}
