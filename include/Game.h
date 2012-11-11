#ifndef GAME_H
#define GAME_H

#include <irrlicht/irrlicht.h>
#include "EventReceiver.h"


class Game
{
public:
    Game();
    void InitGame();
    virtual ~Game();
protected:
private:
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIEnvironment* guienv;
    EventReceiver receiver;
};
#endif // GAME_H
