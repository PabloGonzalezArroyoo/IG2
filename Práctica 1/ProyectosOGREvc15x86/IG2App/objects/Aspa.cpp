#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* m) : mNode(m) {
	// Node padre
	mSM = mNode->getCreator();

	// Tablero
	Ogre::Entity* tab = mSM->createEntity("cube.mesh");
	tableroNode = mNode->createChildSceneNode("tableroNode");
	tableroNode->attachObject(tab);
	tableroNode->setScale(4, 1, 0.2);
	tableroNode->setPosition(0, 0, 0);

	// Cilindro
	Ogre::Entity* cil = mSM->createEntity("column.mesh");
	cilindroNode = mNode->createChildSceneNode("cilinderNode");
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(0.85, 0.2, 0.85);
	cilindroNode->setPosition(150, -23, 0);
}