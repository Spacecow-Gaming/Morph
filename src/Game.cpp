#include <irrlicht/irrlicht.h>

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Level.h"

Game::Game()
{
    //ctor
}

//Starts game
bool Game::StartGame()
{
    using namespace irr;

    //Creates the device (window) containing the game
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,                    //Sets driver to OpenGL
                                          core::dimension2d<u32>(1280, 720),    //Sets window dimensions
                                          16,                                   //Sets colour depth in bits
                                          false, false, false, 0);              //Sets Vsync and some other things to false

    //Sets window caption to a double-wide char[]
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

    //Creates pointers to device's members
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    //Adds text to the GUI
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",  //Sets text to double-wide char[]
                          core::rect<s32>(10,10,260,22),                            //Sets size of text box
                          false);                                                   //Sets the visibility of the box outline

    scene::IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );


    if (node)
    {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );
    }
    smgr->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));
    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(255,255,255,255));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

}

Game::~Game()
{
    //dtor
}
