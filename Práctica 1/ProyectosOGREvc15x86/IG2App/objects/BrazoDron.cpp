#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, int id, int nh) : mNode(m) {
	mSM = mNode->getCreator();

	Entity* cil = mSM->createEntity("column.mesh");
	cilindroNode = mNode->createChildSceneNode("cilBrazoNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(1.8, 0.6, 1.8);
	cilindroNode->roll(Degree(90));
	cilindroNode->setPosition(-150, 0, 0);

	rotorNode = new RotorDron(mNode->createChildSceneNode("rotorNode" + std::to_string(id)), nh, id);
}

BrazoDron::~BrazoDron() {

}

void BrazoDron::mueveHelices() {
	rotorNode->mueveHelices();
}