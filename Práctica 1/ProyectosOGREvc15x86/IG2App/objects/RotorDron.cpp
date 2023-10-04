#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* m, int nh, int id) : mNode(m), numHelices(nh) {
	// Node padre
	mSM = mNode->getCreator();

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	esferaNode = mNode->createChildSceneNode("esferaNode" + std::to_string(id));
	esferaNode->attachObject(esf);
	esferaNode->setScale(1, 1, 1);

	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode("helicesRotorNode" + std::to_string(id));
	auxNode->setPosition(0, 100, 0);
	auxNode->pitch(Ogre::Degree(90));
	auxNode->setScale(0.4, 0.4, 0.4);
	helicesNode = new Aspas(auxNode, numHelices, false);
}

RotorDron::~RotorDron() {

}

void RotorDron::mueveHelices() {
	mNode->getChild("helicesRotorNode")->roll(Ogre::Degree(10));
}