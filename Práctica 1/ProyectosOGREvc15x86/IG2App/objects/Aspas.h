#pragma once

#include "Aspa.h"

using namespace Ogre;

class Aspas : public OgreBites::InputListener {
protected:
	SceneNode* mNode;
	SceneManager* mSM;
	Vector3 cilinderInitPos;
	
	int numAspas = 12;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);

public:
	SceneNode* cilindroNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;

	Aspas(SceneNode* n);
	virtual ~Aspas() {};
};