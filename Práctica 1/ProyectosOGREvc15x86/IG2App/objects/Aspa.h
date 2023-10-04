#pragma once

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <SDL_keycode.h>

using namespace Ogre;

class Aspa {
protected:
	SceneNode* mNode = nullptr;
	SceneManager* mSM = nullptr;

public:
	SceneNode* tableroNode = nullptr;
	SceneNode* cilindroNode = nullptr;

	Aspa(SceneNode* m, int id, bool adorno = true);
	virtual ~Aspa();

	void rotate(Degree d);
};