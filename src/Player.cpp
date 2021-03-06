#include "../include/Player.h"
#include "../include/EventReceiver.h"

#include <irrlicht/irrlicht.h>

using namespace irr;

//Creates player camera etc
Player::Player(IrrlichtDevice* indevice)
{
    device = indevice;
    smgr = device->getSceneManager();

    //Adds camera and points it at the origin
    camera = smgr->addCameraSceneNodeFPS();
    camera->setPosition(core::vector3df(80.f,50.f,80.f));
    camera->setTarget(core::vector3df(0.f,50.f,0.f));

    //Sets speed
    speed = 5.f;

}

void Player::HandleKeys()
{
    EventReceiver* receiver;

    cameraPos = camera->getPosition();

    if(receiver->IsKeyDown( irr::KEY_KEY_W))
        cameraPos+=speed*forwardVector;

    if(receiver->IsKeyDown( irr::KEY_KEY_S))
        cameraPos-=speed*forwardVector;

    if(receiver->IsKeyDown( irr::KEY_KEY_A))
        cameraPos-=speed*rightVector;

    if(receiver->IsKeyDown( irr::KEY_KEY_D))
        cameraPos+=speed*rightVector;

    if(receiver->IsKeyDown( irr::KEY_SPACE))
        cameraPos+=speed*upVector;

    if(receiver->IsKeyDown( irr::KEY_KEY_C))
        cameraPos-=speed*upVector;
}

void Player::ComputeVectors()
{
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
}

void Player::Move()
{
    camera->setPosition(cameraPos);
}


Player::~Player()
{
    //dtor
}
