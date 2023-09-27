#include "Aspa.h"

Aspa::Aspa(SceneNode* m, int id) : mNode(m) {
	// Node padre
	mSM = mNode->getCreator();

	// Tablero
	Entity* tab = mSM->createEntity("cube.mesh");
	tableroNode = mNode->createChildSceneNode("tableroNode" + std::to_string(id));
	tableroNode->attachObject(tab);
	tableroNode->setScale(10, 1, 0.2);
	tableroNode->setPosition(0, 0, 0);

	// Cilindro
	Entity* cil = mSM->createEntity("column.mesh");
	cilindroNode = mNode->createChildSceneNode("cilinderNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(0.85, 0.2, 0.85);
	cilindroNode->setPosition(400, -23, 20);
}

Aspa::~Aspa() {
	mSM = nullptr;
	delete mNode; mNode = nullptr;
	delete cilindroNode; cilindroNode = nullptr;
	delete tableroNode; tableroNode = nullptr;
}

void Aspa::rotate(Degree d) {
	mNode->roll(d);
	//cilindroNode->roll(-d);
}
