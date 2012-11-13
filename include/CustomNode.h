#ifndef CUSTOMNODE_H
#define CUSTOMNODE_H

#include <irrlicht/irrlicht.h>

using namespace irr;


class CustomNode : public scene::ISceneNode
{

    core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[12];
    video::SMaterial Material;

public:

    CustomNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
        : scene::ISceneNode(parent, mgr, id)
    {
        Material.Wireframe = false;
        Material.Lighting = false;

        Vertices[0] = video::S3DVertex(0, 0, 0, -10, -10, -10, video::SColor(255,90,90,90), 0, 1);
        Vertices[1] = video::S3DVertex(10, 0, 0, 10, -10, -10, video::SColor(255,90,90,90), 1, 1);
        Vertices[2] = video::S3DVertex(10, 10, 0, 10, 10, -10, video::SColor(255,90,90,90), 1, 0);
        Vertices[3] = video::S3DVertex(0, 10, 0, -10, 10, -10, video::SColor(255,90,90,90), 0, 0);
        Vertices[4] = video::S3DVertex(10, 0, 10, 10, -10, 10, video::SColor(255,90,90,90), 0, 1);
        Vertices[5] = video::S3DVertex(10, 10, 10, 10, 10, 10, video::SColor(255,90,90,90), 0, 0);
        Vertices[6] = video::S3DVertex(0, 10, 10, -10, 10, 10, video::SColor(255,90,90,90), 1, 0);
        Vertices[7] = video::S3DVertex(0, 0, 10, -10, -10, 10, video::SColor(255,90,90,90), 1, 1);
        Vertices[8] = video::S3DVertex(0, 10, 10, -10, 10, 10, video::SColor(255,90,90,90), 0, 1);
        Vertices[9] = video::S3DVertex(0, 10, 0, -10, 10, -10, video::SColor(255,90,90,90), 1, 1);
        Vertices[10] = video::S3DVertex(10, 0, 10, 10, -10, 10, video::SColor(255,90,90,90), 1, 0);
        Vertices[11] = video::S3DVertex(10, 0, 0, 10, -10, -10, video::SColor(255,90,90,90), 0, 0);

        Box.reset(Vertices[0].Pos);
        for (s32 i=1; i<12; ++i)
            Box.addInternalPoint(Vertices[i].Pos);
    }


    virtual void OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();
    }

    virtual void render()
    {
        u16 indices[] = { 0, 2, 10,/**/0, 3, 2,/**/10, 5, 4,/**/10, 2, 5,/**/4, 6, 7,/**/4, 5, 6,
        /**/7, 3, 0,/**/7, 6, 3,/**/9, 5, 2,/**/9, 8, 5,/**/0, 10, 10,/**/0, 10, 7 };

        video::IVideoDriver* driver = SceneManager->getVideoDriver();

        driver->setMaterial(Material);
        driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->drawVertexPrimitiveList(&Vertices[0], 12, &indices[0], 12, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
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
