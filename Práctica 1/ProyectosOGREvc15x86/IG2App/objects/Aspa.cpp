#include "Aspa.h"

Aspa::Aspa(SceneNode* m, float size, bool txt, bool adorno) : EntidadIG(m) {
	// Tablero
	Entity* tab = mSM->createEntity("cube.mesh");
	if(txt) tab->setMaterialName("brown");
	tableroNode = mNode->createChildSceneNode();
	tableroNode->attachObject(tab);
	tableroNode->setScale(size, size * 0.25, 0.1 * size);
	tableroNode->translate(Vector3(size * 50, 0, 0));

	// Cilindro
	if (adorno) {
		Entity* cil = mSM->createEntity("Barrel.mesh");
		if (txt) cil->setMaterialName("red");
		cilindroNode = mNode->createChildSceneNode();
		cilindroNode->attachObject(cil);
		cilindroNode->setScale(size, size * 2.5, size);
		cilindroNode->setPosition(size * 80, 0, size * 8);
	}
}

void Aspa::rotate(Degree d) {
	mNode->roll(d);
	if (cilindroNode != nullptr) cilindroNode->roll(-d);
}
