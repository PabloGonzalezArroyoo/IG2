#include "Aspas.h"

Aspas::Aspas(SceneNode* n, int nAspas) : mNode(n), numAspas(nAspas) {
	mSM = n->getCreator();

	Entity* cil = mSM->createEntity("column.mesh");
	cilindroNode = mNode->createChildSceneNode("centerNode");
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(0.5, 0.1, 0.5);
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

Aspas::~Aspas() {
	for (int i = 0; i < numAspas; i++) delete arrayAspas[i];
	delete arrayAspas;
	arrayAspas = nullptr;
}

void Aspas::rotateAspas() {
	for (int i = 0; i < numAspas; i++) arrayAspas[i]->rotate(Degree(3));
}

void Aspas::moveCilindro() {
	cilindroNode->translate(Vector3(0, 0, -2));
}

void Aspas::setCilindroIniPos() {
	cilindroNode->setPosition(cilinderInitPos);
}