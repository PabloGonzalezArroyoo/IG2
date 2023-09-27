#pragma once

#include <OgreSceneNode.h>
//#include <OgreTrays.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <SDL_keycode.h>


class Aspa : public OgreBites::InputListener {
protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* tableroNode = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;

public:
	Aspa(Ogre::SceneNode* m);
	virtual ~Aspa() {};
};