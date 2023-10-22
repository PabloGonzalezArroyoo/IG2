#pragma once

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>
#include <vector>
#include <iostream>

using namespace Ogre;

enum MessageType {
	TECLA_R, TECLA_T, STOP
};

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

	void sendEvent(MessageType msg, EntidadIG* entidad);
	virtual void receiveEvent(MessageType msg, EntidadIG* entidad) {};
};

