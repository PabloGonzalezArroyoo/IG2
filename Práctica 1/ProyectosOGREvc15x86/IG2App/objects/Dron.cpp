#include "Dron.h"

Dron::Dron(SceneNode* m, float size, DronType t, int nh, int nb, bool adorno) : EntidadIG(m), numHelices(nh), numBrazos(nb),
	type(t) {
	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	if (type == MOTHER) esf->setMaterialName("red");
	else if (type == CHILD) esf->setMaterialName("smile");
	centroNode = mNode->createChildSceneNode("centroNode");
	centroNode->attachObject(esf);
	centroNode->setScale(1.5 * size, 1.5 * size, 1.5 * size);

	// Brazos
	brazos = new BrazoDron*[numBrazos];
	float rot = 360.0f / numBrazos;
	for (int i = 0; i < numBrazos; i++) {
		SceneNode* aux = mNode->createChildSceneNode("brazoNode" + std::to_string(i));
		brazos[i] = new BrazoDron(aux, size, type != ORIGINAL, i, numHelices, adorno);
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