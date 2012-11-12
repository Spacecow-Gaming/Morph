#include "../include/Level.h"
#include <iostream>

Level::Level()
{
    std::cout << "Level constructor called";
    //The dimensions of the level
    LEVEL_WIDTH = 160;
    LEVEL_LENGTH = 160;

    //Tile constants
    TILE_WIDTH = 10;
    TILE_LENGTH = 10;
    TOTAL_TILES = 256;
    TILE_SPRITES = 12;
}

void Level::LoadLevel()
{
    std::cout<<"Loading level...";
    int x = 0, y = 0;
    std::ifstream lvl( "levels/test.lvl" );

    if(!lvl)
    {
        std::cout << "Level loading failed.";
    }

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        int tileType = -1;
        lvl >> tileType;
        if( lvl.fail() == true )
        {
            std::cout << "Level reading failed.";
            lvl.close();
        }
        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y, tileType );
        }
        //If we don't recognize the tile type
        else
        {
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
            y += TILE_LENGTH;
        }
    }
    lvl.close();
}

void Level::DrawLevel(irr::IrrlichtDevice* device)
{
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::scene::ISceneNode* tilenode;
    float tileheight;

    for(int i=0; i<256; i++)
    {


        tilenode = smgr->addCubeSceneNode(10.f);
        tilenode->setPosition(tiles[i]->position);
        tilenode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        switch (tiles[i]->type)
        {
        case TILE_FLOOR:
            tileheight = 1.f;
            tilenode->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/floor.png"));
            break;
        case TILE_HEIGHT_1:
            tileheight = 1.f;
            tilenode->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/red.png"));
            break;
        case TILE_HEIGHT_2:
            tileheight = 4.f;
            tilenode->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/wall.png"));
            break;
        case TILE_RAMP_TOP:
        case TILE_RAMP_RIGHT:
        case TILE_RAMP_BOTTOM:
        case TILE_RAMP_LEFT:
        default:
            break;
        }
        std::cout <<std::endl<<"drawing tile "<<i+1;
        std::cout << " at height "<< tileheight;
        tilenode->setScale(irr::core::vector3df(1.f,tileheight,1.f));


    }
}

Level::~Level()
{
    //dtor
}

