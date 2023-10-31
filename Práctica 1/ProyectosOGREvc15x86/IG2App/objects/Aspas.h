#pragma once

#include "Aspa.h"

using namespace Ogre;

class Aspas : public EntidadIG {
protected:
	Vector3 cilinderInitPos;
	
	int numAspas;

public:
	SceneNode* cilindroNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;

	Aspas(SceneNode* n, float size, int id, int nAspas = 12, bool txt = true, bool adornos = true);
	virtual ~Aspas();

	void rotateAspas();
	void moveCilindro();
	void setCilindroIniPos();
};