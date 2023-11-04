#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* m, bool txt, int id, int nh, bool adorno) : EntidadIG(m) {
	Entity* cil = mSM->createEntity("Barrel.mesh");
	if (txt) cil->setMaterialName("arms");
	cilindroNode = mNode->createChildSceneNode();
	cilindroNode->attachObject(cil);
	cilindroNode->roll(Degree(90));

	SceneNode* aux = mNode->createChildSceneNode();
	rotorNode = new RotorDron(aux, txt, nh, id, adorno);

	cilindroNode->setScale(6, 24, 6);
	aux->translate(110, 0, 0);

	if (txt && id % 2 != 0) {
		cilindroNode->setScale(9, 30, 9);
		aux->translate(30, 0, 0);
	}
}

void BrazoDron::mueveHelices(int sign) {
	rotorNode->mueveHelices(sign);
}