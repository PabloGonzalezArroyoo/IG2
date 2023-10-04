#pragma once

#include "Aspas.h"

class RotorDron {
protected:
	SceneNode* mNode = nullptr;
	SceneManager* mSM = nullptr;
	int numHelices;

public:
	Aspas* helicesNode = nullptr;
	SceneNode* esferaNode = nullptr;

	RotorDron(SceneNode* m, int nh, int id);
	virtual ~RotorDron();

	void mueveHelices();
};