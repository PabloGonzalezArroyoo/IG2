#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* m, int nh, int id, bool adorno) : EntidadIG(m), numHelices(nh), ident(id) {
	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	esf->setMaterialName("orange");
	esferaNode = mNode->createChildSceneNode("esferaNode" + std::to_string(id));
	esferaNode->attachObject(esf);


	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode("helicesRotorNode" + std::to_string(id));
	auxNode->pitch(Ogre::Degree(-90));
	helicesNode = new Aspas(auxNode, 3, id, numHelices, adorno);

	if (id % 2 != 0) {
		esferaNode->setScale(0.8, 0.8, 0.8);
		auxNode->setScale(0.4, 0.4, 0.4);
		auxNode->setPosition(0, 85, 0);
	}
	else {
		esferaNode->setScale(0.7, 0.7, 0.7);
		auxNode->setScale(0.3, 0.3, 0.3);
		auxNode->setPosition(0, 70, 0);
	}
}

void RotorDron::mueveHelices(int sign) {
	mNode->getChild("helicesRotorNode" + std::to_string(ident))->roll(Ogre::Degree(sign * 10));
}