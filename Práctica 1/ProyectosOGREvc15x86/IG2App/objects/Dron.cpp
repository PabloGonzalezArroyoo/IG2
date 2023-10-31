#include "Dron.h"

Dron::Dron(SceneNode* m, Vector3 pos, float size, bool txt, int nh, int nb, bool adorno) : EntidadIG(m), numHelices(nh),
	numBrazos(nb) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Esfera
	esf = mSM->createEntity("sphere.mesh");
	centroNode = ficticioNode->createChildSceneNode();
	centroNode->attachObject(esf);
	centroNode->setScale(1.5 * size, 1.5 * size, 1.5 * size);

	// Brazos
	brazos = new BrazoDron*[numBrazos];
	float rot = 360.0f / numBrazos;
	for (int i = 0; i < numBrazos; i++) {
		SceneNode* aux = ficticioNode->createChildSceneNode();
		brazos[i] = new BrazoDron(aux, size, txt, i, numHelices, adorno);
		aux->yaw(Ogre::Degree(rot * i));
		aux->translate(220 * size, 0, 0, SceneNode::TS_LOCAL);
	}
}

Dron::~Dron(){
	for (int i = 0; i < numBrazos; i++) delete brazos[i];
	delete[] brazos;
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (int i = 0; i < numBrazos; i++) {
			if (i % 2 == 0) brazos[i]->mueveHelices(-1);
			else brazos[i]->mueveHelices();
		}
	}

	return true;
}