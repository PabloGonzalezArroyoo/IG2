#pragma once

#include "BrazoDron.h"

class Dron : public EntidadIG {
protected:
	DronType type;
	int numHelices = 12, numBrazos = 8;

public:
	BrazoDron** brazos = nullptr;
	SceneNode* centroNode = nullptr;

	Dron(SceneNode* m, float size, DronType t, int nh = 12, int nb = 8, bool adorno = false);
	virtual ~Dron();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

