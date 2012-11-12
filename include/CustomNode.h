#ifndef CUSTOMNODE_H
#define CUSTOMNODE_H

#include <irrlicht/irrlicht.h>

using namespace irr;


class CustomNode : public scene::ISceneNode
{

    core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[4];
    video::SMaterial Material;

public:

    CustomNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
        : scene::ISceneNode(parent, mgr, id)
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

    virtual const core::aabbox3d<f32>& getBoundingBox() const
    {
        return Box;
    }

    virtual u32 getMaterialCount() const
    {
        return 1;
    }

    virtual video::SMaterial& getMaterial(u32 i)
    {
        return Material;
    }
};


#endif // CUSTOMNODE_H
