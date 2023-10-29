#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, int id, int nh, bool adorno) : EntidadIG(m) {
	Entity* cil = mSM->createEntity("Barrel.mesh");
	cil->setMaterialName("arms");
	cilindroNode = mNode->createChildSceneNode("cilBrazoNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->roll(Degree(90));

	rotorNode = new RotorDron(mNode->createChildSceneNode("rotorNode" + std::to_string(id)), nh, id, adorno);

	if (id % 2 != 0) {
		cilindroNode->setScale(15, 50, 15);
		mSM->getSceneNode("rotorNode" + std::to_string(id))->setPosition(220, 0, 0);
	}
	else {
		cilindroNode->setScale(10, 40, 10);
		mSM->getSceneNode("rotorNode" + std::to_string(id))->setPosition(130, 0, 0);
	}
}

void BrazoDron::mueveHelices(int sign) {
	rotorNode->mueveHelices(sign);
}