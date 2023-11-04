#pragma once

#include "BrazoDron.h"

enum DronType {
	ORIGINAL, MOTHER, CHILD
};

class Dron : public EntidadIG {
protected:
	Entity* esf;
	DronType type;
	int numHelices = 12, numBrazos = 8;
	float timer;

public:
	BrazoDron** brazos = nullptr;
	SceneNode* centroNode = nullptr;
	SceneNode* ficticioNode = nullptr;

	Dron(SceneNode* m, Vector3 pos, float size, DronType t, int nh = 12, int nb = 8, Vector3 offset = Vector3(0, 0, 0), bool adorno = false);
	virtual ~Dron();

	SceneNode* getFicticiousNode() { return ficticioNode; };

	virtual void frameRendered(const FrameEvent& evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

