#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* m, float size, bool txt, int nh, int id, bool adorno) : EntidadIG(m), numHelices(nh), ident(id) {
	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	if (txt) esf->setMaterialName("orange");
	esferaNode = mNode->createChildSceneNode("esferaNode" + std::to_string(id));
	esferaNode->attachObject(esf);

	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode("helicesRotorNode" + std::to_string(id));
	auxNode->pitch(Ogre::Degree(-90));
	helicesNode = new Aspas(auxNode, 3 * size, id, numHelices, txt, adorno);

	esferaNode->setScale(0.7 * size, 0.7 * size, 0.7 * size);
	auxNode->setScale(0.3 * size, 0.3 * size, 0.3 * size);
	auxNode->setPosition(0, 70 * size, 0);

	if (txt && id % 2 != 0) {
		esferaNode->setScale(0.8 * size, 0.8 * size, 0.8 * size);
		auxNode->setScale(0.4 * size, 0.4 * size, 0.4 * size);
		auxNode->setPosition(0, 85 * size, 0);
	}
}

void RotorDron::mueveHelices(int sign) {
	mNode->getChild("helicesRotorNode" + std::to_string(ident))->roll(Ogre::Degree(sign * 10));
}