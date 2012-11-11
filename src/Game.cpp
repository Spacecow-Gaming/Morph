#include <irrlicht/irrlicht.h>
#include <iostream>

#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Level.h"
#include "../include/EventReceiver.h"

using namespace irr;

Game::Game()
{
    //ctor
}

void Game::InitGame()
{
    std::cout << "Game started";

    //Creates the device (window) containing the game
    device = createDevice(video::EDT_OPENGL,                    //Sets driver to OpenGL
                                          core::dimension2d<u32>(1280, 720),    //Sets window dimensions
                                          16,                                   //Sets colour depth in bits
                                          false, false, true, 0);              //Sets Vsync and some other things to false

    std::cout << "Device created";
    //Creates pointers to device's members
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    //Adds text to the GUI
    guienv->addStaticText(L"This is Morph",  //Sets text to double-wide char[]
                          core::rect<s32>(10,10,260,22),                            //Sets size of text box
                          false);                                                   //Sets the visibility of the box outline

    //Hides cursor
    device->getCursorControl()->setVisible(false);

    //Attaches event reciver to device
    device->setEventReceiver(&receiver);

    Level level;
    level.LoadLevel();
    level.DrawLevel(device);

    //Creates player with context
    Player player(device);

    //Creates light, sets properties
    scene::ILightSceneNode* lightnode = smgr->addLightSceneNode();
    lightnode->setPosition(core::vector3df(160.f,80.f,160.f));
    lightnode->setRadius(3200.f);
    lightnode->enableCastShadow(true);

    int lastFPS = -1;

    //Render loop
    while(device->run())
    {
        //Sets scene default colour to a dark grey
        driver->beginScene(true, true, video::SColor(255,32,64,128));
        smgr->drawAll();
        guienv->drawAll();

        if(receiver.IsKeyDown(irr::KEY_ESCAPE))
        {
            std::cout << std::endl << "Exiting due to user input";
            device->drop();
        }

        player.HandleKeys();
        player.ComputeVectors();
        player.Move();

        int fps = driver->getFPS();

        //Change window caption to FPS
        if (lastFPS != fps)
        {
            core::stringw str = L"Morph [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
        driver->endScene();
    }
    device->drop();
}

Game::~Game()
{
    //dtor
}
