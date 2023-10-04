#pragma once

#include "Aspa.h"

using namespace Ogre;

class Aspas {
protected:
	SceneNode* mNode;
	SceneManager* mSM;
	Vector3 cilinderInitPos;
	
	int numAspas;

public:
	SceneNode* cilindroNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;

	Aspas(SceneNode* n, int nAspas = 12, bool adornos = true);
	virtual ~Aspas();

	void rotateAspas();
	void moveCilindro();
	void setCilindroIniPos();
};