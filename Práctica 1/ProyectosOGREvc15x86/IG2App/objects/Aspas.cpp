#include "Aspas.h"

Aspas::Aspas(SceneNode* n) : mNode(n) {
	mSM = n->getCreator();

	Entity* cil = mSM->createEntity("column.mesh");
	cilindroNode = mNode->createChildSceneNode("centerNode");
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(1, 0.2, 1);
	cilindroNode->rotate(Vector3(1, 0, 0), Radian(Degree(90)));

	cilinderInitPos = cilindroNode->getPosition();

	aspasNode = mNode->createChildSceneNode("aspasNode");

	arrayAspas = new Aspa*[numAspas];
	int rot = 360 / numAspas;
	for (int i = 0; i < numAspas; i++) {
		SceneNode* auxNode = aspasNode->createChildSceneNode("aspa" + std::to_string(i));
		Aspa* aux = new Aspa(auxNode, i);
		arrayAspas[i] = aux;
		aux->rotate(Degree(rot * i));
	}
}

bool Aspas::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_j) {
		aspasNode->roll(Degree(3));
	}
	else if (evt.keysym.sym == SDLK_c) {
		cilindroNode->translate(Vector3(0,0,-2));
	}

	return true;
}

bool Aspas::keyReleased(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_c) {
		cilindroNode->setPosition(cilinderInitPos);
	}
	return true;
}