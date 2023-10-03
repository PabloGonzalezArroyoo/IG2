#pragma once

#include "Aspas.h"

class Molino : public OgreBites::InputListener {
protected:
	SceneNode* mNode = nullptr;
	SceneManager* mSM = nullptr;

public:
	SceneNode* techoNode = nullptr;
	SceneNode* cuerpoNode = nullptr;
	Aspas* aspasNode = nullptr;
	SceneNode* nodoFicticio = nullptr;

	Molino(SceneNode* m);
	virtual ~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
};