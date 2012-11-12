#include "../include/CustomNode.h"

#include <irrlicht/irrlicht.h>

using namespace irr;

CustomNode::CustomNode(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
    : scene::ISceneNode(parent, smgr, id)
{
    Material.Wireframe = false;
        Material.Lighting = false;

        Vertices[0] = video::S3DVertex(0,0,10, 1,1,0,
                video::SColor(255,0,255,255), 0, 1);
        Vertices[1] = video::S3DVertex(10,0,-10, 1,0,0,
                video::SColor(255,255,0,255), 1, 1);
        Vertices[2] = video::S3DVertex(0,20,0, 0,1,1,
                video::SColor(255,255,255,0), 1, 0);
        Vertices[3] = video::S3DVertex(-10,0,-10, 0,0,1,
                video::SColor(255,0,255,0), 0, 0);
        Box.reset(Vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            Box.addInternalPoint(Vertices[i].Pos);
}

CustomNode::~CustomNode()
{
    //dtor
}
