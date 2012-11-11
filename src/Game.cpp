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
                                          false, false, true, 0);              //Sets Vsync and some other things to false


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

    //Creates event receiver and attaches to device
    EventReceiver receiver;
    device->setEventReceiver(&receiver);

    Level level;
    level.LoadLevel();
    level.DrawLevel(device);

    camera->setPosition(core::vector3df(0.f,50.f,0.f));
    camera->setTarget(core::vector3df(0.f,0.f,0.f));

    int lastFPS = -1;


    //Creates light, sets properties
    scene::ILightSceneNode* lightnode = smgr->addLightSceneNode();
    lightnode->setPosition(core::vector3df(80.f,80.f,80.f));
    lightnode->setRadius(3200.f);
    lightnode->enableCastShadow(false);


    //Render loop
    while(device->run())
    {
        //Sets scene default colour to a dark grey
        driver->beginScene(true, true, video::SColor(255,32,64,128));
        smgr->drawAll();
        guienv->drawAll();

        //Sets direction vectors, will move to Player class later
        core::vector3df forwardVector, rightVector, upVector, cameraPos;

        cameraPos = camera->getPosition();

        //Compute new forward vector
        forwardVector = camera->getTarget() - camera->getPosition();

        //Set the Y to 0 so the vectors are calculated on the XZ plane
        forwardVector.Y = 0.0f;
        forwardVector.normalize();

        //Compute new right vector
        rightVector = camera->getUpVector().crossProduct ( forwardVector );
        rightVector.normalize();

        //Compute new up vector
        upVector = forwardVector.crossProduct( rightVector );
        upVector.normalize();

        if(receiver.IsKeyDown(irr::KEY_ESCAPE))
        {
           std::cout << std::endl << "exiting due to user input";
                device->drop();
        }


            if(receiver.IsKeyDown( irr::KEY_KEY_W))
                cameraPos+=5.f*forwardVector;

            if(receiver.IsKeyDown( irr::KEY_KEY_S))
                cameraPos-=5.f*forwardVector;

            if(receiver.IsKeyDown( irr::KEY_KEY_A))
                cameraPos-=5.f*rightVector;

            if(receiver.IsKeyDown( irr::KEY_KEY_D))
                cameraPos+=5.f*rightVector;

            if(receiver.IsKeyDown( irr::KEY_SPACE))
                cameraPos+=5.f*upVector;

            if(receiver.IsKeyDown( irr::KEY_KEY_C))
                cameraPos-=5.f*upVector;


        camera->setPosition(cameraPos);

        //Initialise FPS
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
