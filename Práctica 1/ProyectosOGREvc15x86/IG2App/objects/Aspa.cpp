#include "Aspa.h"

Aspa::Aspa(SceneNode* m, int i, int id, bool adorno) : mNode(m) {
	// Node padre
	mSM = mNode->getCreator();

	// Tablero
	Entity* tab = mSM->createEntity("cube.mesh");
	tableroNode = mNode->createChildSceneNode("tableroNode" + std::to_string(id) + "-" + std::to_string(i));
	tableroNode->attachObject(tab);
	tableroNode->setScale(5, 0.5, 0.1);
	tableroNode->setPosition(0, 0, 0);

	// Cilindro
	if (adorno) {
		Entity* cil = mSM->createEntity("Barrel.mesh");
		cilindroNode = mNode->createChildSceneNode("cilinderNode" + std::to_string(id));
		cilindroNode->attachObject(cil);
		cilindroNode->setScale(3, 6, 3);
		cilindroNode->setPosition(200, 0, 12.5f);
	}
}

Aspa::~Aspa() {
	mSM = nullptr;
	mNode = nullptr;
}

void Aspa::rotate(Degree d) {
	mNode->roll(d);
	if (cilindroNode != nullptr) cilindroNode->roll(-d);
}
