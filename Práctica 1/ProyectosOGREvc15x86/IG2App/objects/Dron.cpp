#include "Dron.h"

Dron::Dron(SceneNode* m, int nh, int nb) : mNode(m), numHelices(nh), numBrazos(nb) {
	// Node padre
	mSM = mNode->getCreator();

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	centroNode = mNode->createChildSceneNode("centroNode");
	centroNode->attachObject(esf);
	centroNode->setScale(1.5, 1.5, 1.5);

	// Brazos
	brazos = new BrazoDron*[numBrazos];
	float rot = 360.0f / numBrazos;
	for (int i = 0; i < numBrazos; i++) {
		SceneNode* aux = mNode->createChildSceneNode("brazoNode" + std::to_string(i));
		brazos[i] = new BrazoDron(aux, i, numHelices);
		aux->yaw(Ogre::Degree(rot * i));
		aux->translate(200, 0, 0);
	}
}

Dron::~Dron(){

}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (int i = 0; i < numBrazos; i++) {
			brazos[i]->mueveHelices();
		}
	}

	return true;
}