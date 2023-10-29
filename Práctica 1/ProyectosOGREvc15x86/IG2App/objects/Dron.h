#pragma once

#include "BrazoDron.h"

class Dron : public EntidadIG {
protected:
	int numHelices = 12, numBrazos = 8;

public:
	BrazoDron** brazos = nullptr;
	SceneNode* centroNode = nullptr;

	Dron(SceneNode* m, int nh = 12, int nb = 8, bool adorno = false);
	virtual ~Dron();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

