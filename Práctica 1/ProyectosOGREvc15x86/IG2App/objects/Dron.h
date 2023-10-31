#pragma once

#include "BrazoDron.h"

class Dron : public EntidadIG {
protected:
	Entity* esf;
	int numHelices = 12, numBrazos = 8;

public:
	BrazoDron** brazos = nullptr;
	SceneNode* centroNode = nullptr;
	SceneNode* ficticioNode = nullptr;

	Dron(SceneNode* m, Vector3 pos, float size, bool txt, int nh = 12, int nb = 8, bool adorno = false);
	virtual ~Dron();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

