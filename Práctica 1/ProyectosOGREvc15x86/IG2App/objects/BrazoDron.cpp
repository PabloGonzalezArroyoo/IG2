#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, float size, bool txt, int id, int nh, bool adorno) : EntidadIG(m) {
	Entity* cil = mSM->createEntity("Barrel.mesh");
	if (txt) cil->setMaterialName("arms");
	cilindroNode = mNode->createChildSceneNode("cilBrazoNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->roll(Degree(90));

	rotorNode = new RotorDron(mNode->createChildSceneNode("rotorNode" + std::to_string(id)), size, txt, nh, id, adorno);

	cilindroNode->setScale(10 * size, 40 * size, 10 * size);
	mSM->getSceneNode("rotorNode" + std::to_string(id))->setPosition(130 * size, 0, 0);

	if (txt && id % 2 != 0) {
		cilindroNode->setScale(15 * size, 50 * size, 15 * size);
		mSM->getSceneNode("rotorNode" + std::to_string(id))->setPosition(220 * size, 0, 0);
	}
}

void BrazoDron::mueveHelices(int sign) {
	rotorNode->mueveHelices(sign);
}