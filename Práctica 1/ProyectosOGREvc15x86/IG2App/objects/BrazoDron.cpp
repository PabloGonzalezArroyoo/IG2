#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, float size, bool txt, int id, int nh, bool adorno) : EntidadIG(m) {
	Entity* cil = mSM->createEntity("Barrel.mesh");
	if (txt) cil->setMaterialName("arms");
	cilindroNode = mNode->createChildSceneNode();
	cilindroNode->attachObject(cil);
	cilindroNode->roll(Degree(90));

	SceneNode* aux = mNode->createChildSceneNode();
	rotorNode = new RotorDron(aux, size, txt, nh, id, adorno);

	cilindroNode->setScale(10 * size, 40 * size, 10 * size);
	aux->setPosition(130 * size, 0, 0);

	if (txt && id % 2 != 0) {
		cilindroNode->setScale(15 * size, 50 * size, 15 * size);
		aux->setPosition(220 * size, 0, 0);
	}
}

void BrazoDron::mueveHelices(int sign) {
	rotorNode->mueveHelices(sign);
}