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
    std::cout << "Game started\n";


    //Creates the device (window) containing the game
    device = createDevice(video::EDT_OPENGL,                    //Sets driver to OpenGL
                                          core::dimension2d<u32>(1280, 720),    //Sets window dimensions
                                          16,                                   //Sets colour depth in bits
                                          false, false, true, NULL);              //Sets Vsync and some other things to false



    std::cout << "Device created\n";
    //Creates pointers to device's members
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    //Set font
    guienv->getSkin()->setFont(guienv->getFont("media/fontlucida.png"));

    //Adds text to the GUI
    guienv->addStaticText(L"Use WASD to move.\nPress SPACE to ascend\nPress C to descend.",  //Sets text to double-wide char[]
                          core::rect<s32>(10,10,260,70),                            //Sets size of text box
                          true, true, 0, -1, true);                                  //Sets the visibility of the box outline and some others

    //Hides cursor
    device->getCursorControl()->setVisible(false);

    //Attaches event reciver to device
    device->setEventReceiver(&receiver);

    Level level;

    //Loads the slices of the level from different files
    level.LoadLevel(0, "levels/test.lvl.0");
    level.LoadLevel(1, "levels/test.lvl.1");
    level.LoadLevel(2, "levels/test.lvl.2");
    level.LoadLevel(3, "levels/test.lvl.3");
    level.LoadLevel(4, "levels/test.lvl.4");

    level.DrawLevel(device);

    //Creates player with context
    Player player(device);

    //Creates light, sets properties
    scene::ILightSceneNode* lightnode = smgr->addLightSceneNode(0, core::vector3df(160.f,80.f,160.f), video::SColorf(0.3,0.3,0.3,0.1));
    lightnode->setRadius(3200.f);
    lightnode->enableCastShadow(true);
    int lastFPS = -1;

    //Render loop
    while(device->run())
    {
        //Sets scene default colour to blue
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
