#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* m, int nh, int id) : mNode(m), numHelices(nh), ident(id) {
	// Node padre
	mSM = mNode->getCreator();

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	esferaNode = mNode->createChildSceneNode("esferaNode" + std::to_string(id));
	esferaNode->attachObject(esf);
	esferaNode->setScale(0.7, 0.7, 0.7);

	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode("helicesRotorNode" + std::to_string(id));
	auxNode->setPosition(0, 70, 0);
	auxNode->pitch(Ogre::Degree(90));
	auxNode->setScale(0.3, 0.3, 0.3);
	helicesNode = new Aspas(auxNode, id, numHelices, false);
}

RotorDron::~RotorDron() {

}

void RotorDron::mueveHelices() {
	mNode->getChild("helicesRotorNode" + std::to_string(ident))->roll(Ogre::Degree(10));
}