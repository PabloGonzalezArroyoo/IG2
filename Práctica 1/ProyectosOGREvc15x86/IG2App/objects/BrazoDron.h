#pragma once

#include "RotorDron.h"

class BrazoDron {
protected:
	SceneNode* mNode = nullptr;
	SceneManager* mSM = nullptr;

public:
	RotorDron* rotorNode = nullptr;
	SceneNode* cilindroNode = nullptr;

	BrazoDron(SceneNode* m, int id, int nh);
	virtual ~BrazoDron();

	void mueveHelices();
};