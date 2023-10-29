#include "Aspa.h"

Aspa::Aspa(SceneNode* m, float size, int i, int id, bool adorno) : EntidadIG(m) {
	// Tablero
	Entity* tab = mSM->createEntity("cube.mesh");
	tab->setMaterialName("brown");
	tableroNode = mNode->createChildSceneNode("tableroNode" + std::to_string(id) + "-" + std::to_string(i));
	tableroNode->attachObject(tab);
	tableroNode->setScale(size, size * 0.25, 0.1 * size);
	tableroNode->translate(Vector3(size * 50, 0, 0));

	// Cilindro
	if (adorno) {
		Entity* cil = mSM->createEntity("Barrel.mesh");
		cil->setMaterialName("red");
		cilindroNode = mNode->createChildSceneNode("cilinderNode" + std::to_string(id) + "-" + std::to_string(i));
		cilindroNode->attachObject(cil);
		cilindroNode->setScale(size, size * 2.5, size);
		cilindroNode->setPosition(size * 80, 0, size * 8);
	}
}

void Aspa::rotate(Degree d) {
	mNode->roll(d);
	if (cilindroNode != nullptr) cilindroNode->roll(-d);
}
