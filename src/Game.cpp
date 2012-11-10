#include <irrlicht/irrlicht.h>

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Level.h"
#include "../include/EventReceiver.h"

Game::Game()
{
    //ctor
}

void Game::StartGame()
{
    using namespace irr;

    //Creates the device (window) containing the game
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,                    //Sets driver to OpenGL
                                          core::dimension2d<u32>(1280, 720),    //Sets window dimensions
                                          16,                                   //Sets colour depth in bits
                                          false, false, false, 0);              //Sets Vsync and some other things to false

    //Sets window caption to a double-wide char[]
    device->setWindowCaption(L"Morph");

    //Creates pointers to device's members
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    //Adds text to the GUI
    guienv->addStaticText(L"This is Morph",  //Sets text to double-wide char[]
                          core::rect<s32>(10,10,260,22),                            //Sets size of text box
                          false);                                                   //Sets the visibility of the box outline

    //Adds camera and points it at the origin
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS();

    //Hides cursor
    device->getCursorControl()->setVisible(false);

    //Creates evet receiver and attaches to device
    EventReceiver receiver(device);
    device->setEventReceiver(&receiver);

    Level level;
    level.LoadLevel();
    level.DrawLevel(smgr);

    camera->setPosition(core::vector3df(0.f,50.f,50.f));
    camera->setTarget(core::vector3df(0.f,0.f,0.f));


    //Render loop
    while(device->run())
    {
        //Sets scene default colour to a dark grey
        driver->beginScene(true, true, video::SColor(255,90,90,90));
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
