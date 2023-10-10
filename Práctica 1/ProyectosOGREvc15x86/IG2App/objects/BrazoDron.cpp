#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, int id, int nh) : mNode(m) {
	mSM = mNode->getCreator();

	Entity* cil = mSM->createEntity("Barrel.mesh");
	cilindroNode = mNode->createChildSceneNode("cilBrazoNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(10, 40, 10);
	cilindroNode->roll(Degree(90));

	rotorNode = new RotorDron(mNode->createChildSceneNode("rotorNode" + std::to_string(id)), nh, id);
	mSM->getSceneNode("rotorNode" + std::to_string(id))->setPosition(130, 0, 0);
}

BrazoDron::~BrazoDron() {

}

void BrazoDron::mueveHelices() {
	rotorNode->mueveHelices();
}