#include <iostream>
#include <string>

#include "../include/Level.h"
#include "../include/CustomNode.h"

using namespace irr;

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

    //Fills all spaces with air, to avoid null pointer catastrophes
    for(int i=0; i<10; i++)
    {
        for(int t=0; t<256; t++)
        {
            tiles[i][t] = new Tile( 0, 0, 0, AIR );
        }
    }
}

void Level::LoadLevel(int iny, std::string filename)
{
    std::cout<< "Loading level...";
    int x = 0, z = 0;
    int y = iny*TILE_LENGTH;

    std::ifstream lvl(filename.c_str());

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
            tiles[iny][ t ] = new Tile( x, y, z, tileType );
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
            z += TILE_LENGTH;
        }

    }
    lvl.close();
}

scene::SMesh* Level::CustomMesh(video::SColor incolor, SHAPE shape)
{
        scene::SMesh * mesh = new scene::SMesh();
    if (shape==CUBE)
    {
        float cubeSize = 1.f;
       //f32 cubeSize = 10.f;
    video::SColor cubeColour = incolor;

    scene::SMeshBuffer * buffer = new scene::SMeshBuffer();
    u16 u[36] = { 0,2,1, 0,3,2, 1,5,4, 1,2,5, 4,6,7, 4,5,6,
                  7,3,0, 7,6,3, 9,5,2, 9,8,5, 0,11,10, 0,10,7
                };

    buffer->Indices.set_used(36);
    for (s32 i=0; i<36; ++i)
        buffer->Indices[i] = u[i];

    buffer->Vertices.set_used(12);
    buffer->Vertices[0] = video::S3DVertex(0,0,0, -10,-10,-10, cubeColour, 0, 1);
    buffer->Vertices[1] = video::S3DVertex(10,0,0, 10,-10,-10, cubeColour, 1, 1);
    buffer->Vertices[2] = video::S3DVertex(10,10,0, 10, 10,-10, cubeColour, 1, 0);
    buffer->Vertices[3] = video::S3DVertex(0,10,0, -10, 10,-10, cubeColour, 0, 0);
    buffer->Vertices[4] = video::S3DVertex(10,0,10, 10,-10, 10, cubeColour, 0, 1);
    buffer->Vertices[5] = video::S3DVertex(10,10,10, 10, 10, 10, cubeColour, 0, 0);
    buffer->Vertices[6] = video::S3DVertex(0,10,10, -10, 10, 10, cubeColour, 1, 0);
    buffer->Vertices[7] = video::S3DVertex(0,0,10, -10,-10, 10, cubeColour, 1, 1);
    buffer->Vertices[8] = video::S3DVertex(0,10,10, -10, 10, 10, cubeColour, 0, 1);
    buffer->Vertices[9] = video::S3DVertex(0,10,0, -10, 10,-10, cubeColour, 1, 1);
    buffer->Vertices[10] = video::S3DVertex(10,0,10, 10,-10, 10, cubeColour, 1, 0);
    buffer->Vertices[11] = video::S3DVertex(10,0,0, 10,-10,-10, cubeColour, 0, 0);

    buffer->BoundingBox.reset(0,0,0);

    for (int i=0; i<12; ++i)
    {
        buffer->Vertices[i].Pos -= core::vector3df(0.5f, 0.5f, 0.5f);
        buffer->Vertices[i].Pos *= cubeSize;
        buffer->BoundingBox.addInternalPoint(buffer->Vertices[i].Pos);
    }
    mesh->addMeshBuffer(buffer);

    return mesh;
    }



}

void Level::DrawLevel(irr::IrrlichtDevice* device)
{
    std::cout << "\nDrawing level";
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::scene::ISceneNode* tilenode;

    float tilescale = 1.f;

    for (int y=0; y<10; y++)
    {

        for(int t=0; t<256; t++)
        {

            //tilenode = smgr->addCubeSceneNode(10.f);




            video::SColor tilecolor(0,0,0,0);


            switch (tiles[y][t]->type)
            {
            case TILE_FLOOR:
                tilecolor = video::SColor(255,90,90,90);
                tilescale = 1.f;
                break;
            case TILE_RED:
                tilecolor = video::SColor(255,255,0,0);
                tilescale = 1.f;
                break;
            case TILE_WALL:
                tilecolor = video::SColor(255,200,200,200);
                tilescale = 1.f;
                break;
            case TILE_RAMP_TOP:
            case TILE_RAMP_RIGHT:
            case TILE_RAMP_BOTTOM:
            case TILE_RAMP_LEFT:
            case AIR:
                tilenode->setVisible(false);
                tilescale = 1.f;
                break;
            default:
                break;
            }

            tilenode = smgr->addMeshSceneNode(CustomMesh(tilecolor, CUBE));
            //tilenode = smgr->addCubeSceneNode(10.f);

            tilenode->setPosition(tiles[y][t]->position);
            tilenode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            tilenode->getMaterial(0).Shininess = 0.0f;

            std::cout <<"\ndrawing tile"<<t+1;

        }
    }

}

Level::~Level()
{
    //dtor
}

