#pragma once

#include "EntidadIG.h"

using namespace Ogre;

class Aspa : public EntidadIG {
public:
	SceneNode* tableroNode = nullptr;
	SceneNode* cilindroNode = nullptr;

	Aspa(SceneNode* m, float size, bool txt = true, bool adorno = true);
	virtual ~Aspa() {};

	void rotate(Degree d);
};