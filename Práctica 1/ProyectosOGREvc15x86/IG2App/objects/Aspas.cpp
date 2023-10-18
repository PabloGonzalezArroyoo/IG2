#include "Aspas.h"

Aspas::Aspas(SceneNode* n, float size, int id, int nAspas, bool adorno) : EntidadIG(n), numAspas(nAspas) {
	Entity* cil = mSM->createEntity("Barrel.mesh");
	cilindroNode = mNode->createChildSceneNode("centerNode" + std::to_string(id));
	cilindroNode->attachObject(cil);
	cilindroNode->setScale(size * 4, size * 2, size * 4);
	cilindroNode->pitch(Degree(90));
	cilindroNode->translate(Vector3(0, 0, 10));

	cilinderInitPos = cilindroNode->getPosition();

	aspasNode = mNode->createChildSceneNode("aspasNode" + std::to_string(id));

	arrayAspas = new Aspa*[numAspas];
	int rot = 360 / numAspas;
	for (int i = 0; i < numAspas; i++) {
		SceneNode* auxNode = aspasNode->createChildSceneNode("aspa" + std::to_string(id) + "-" + std::to_string(i));
		Aspa* aux = new Aspa(auxNode, size, i, id, adorno);
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
	for (int i = 0; i < numAspas; i++) arrayAspas[i]->rotate(Degree(0.5));
}

void Aspas::moveCilindro() {
	cilindroNode->translate(Vector3(0, 0, -2));
}

void Aspas::setCilindroIniPos() {
	cilindroNode->setPosition(cilinderInitPos);
}