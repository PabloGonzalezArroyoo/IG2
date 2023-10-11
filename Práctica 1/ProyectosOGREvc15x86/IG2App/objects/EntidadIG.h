#pragma once

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <SDL_keycode.h>
#include <vector>

using namespace Ogre;

class EntidadIG : public OgreBites::InputListener {
protected:
	SceneNode* mNode = nullptr;
	SceneManager* mSM = nullptr;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		return false;
	}

	virtual void frameRendered(const FrameEvent& evt) {};

public:
	// Constructora
	EntidadIG(SceneNode* node);

	static std::vector<EntidadIG*> appListeners;

	static void addListener(EntidadIG* entidad) {
		appListeners.push_back(entidad);
	}

	void sendEvent(EntidadIG* entidad);
	virtual void receiveEvent(EntidadIG* entidad) {};
};

