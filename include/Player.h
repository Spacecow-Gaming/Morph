#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht/irrlicht.h>

using namespace irr;

class Player
{
public:
    Player(IrrlichtDevice*);
    void HandleKeys();
    void ComputeVectors();
    void Move();
    ~Player();

    core::vector3df cameraPos;
protected:
private:
    IrrlichtDevice* device;
    scene::ISceneManager* smgr;
    scene::ICameraSceneNode* camera;

    //Direction vectors
    core::vector3df forwardVector, rightVector, upVector;

    //Speed variable
    float speed;
};

#endif // PLAYER_H
