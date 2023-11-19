#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* m, bool txt, int nh, int id, bool adorno) : EntidadIG(m), numHelices(nh), ident(id) {
	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	if (txt) esf->setMaterialName("practica1/orange");
	esferaNode = mNode->createChildSceneNode();
	esferaNode->attachObject(esf);

	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode();
	auxNode->pitch(Ogre::Degree(-90));
	helicesNode = new Aspas(auxNode, 2, numHelices, txt, adorno);

	esferaNode->setScale(0.5, 0.5, 0.5);
	auxNode->setScale(0.2, 0.2, 0.2);
	auxNode->translate(0, 50, 0);

	if (txt && id % 2 != 0) {
		esferaNode->setScale(0.6, 0.6, 0.6);
		auxNode->setScale(0.3, 0.3, 0.3);
		auxNode->translate(0, 10, 0);
	}
}

void RotorDron::mueveHelices(int sign) {
	helicesNode->getNode()->roll(Ogre::Degree(sign * 10));
}