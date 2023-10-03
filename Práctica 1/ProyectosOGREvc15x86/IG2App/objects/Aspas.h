#pragma once

#include "Aspa.h"

using namespace Ogre;

class Aspas {
protected:
	SceneNode* mNode;
	SceneManager* mSM;
	Vector3 cilinderInitPos;
	
	int numAspas = 12;

public:
	SceneNode* cilindroNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;

	Aspas(SceneNode* n, int nAspas, Vector3 offset = Vector3());
	virtual ~Aspas();

	void rotateAspas();
	void moveCilindro();
	void setCilindroIniPos();
};