#include "Dron.h"

Dron::Dron(SceneNode* m, Vector3 pos, float size, DronType t, int nh, int nb, Vector3 offset, bool adorno) : EntidadIG(m), numHelices(nh),
	numBrazos(nb), type(t), stop(false) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Esfera
	esf = mSM->createEntity("sphere.mesh");
	centroNode = ficticioNode->createChildSceneNode();
	centroNode->attachObject(esf);
	centroNode->setScale(2 * size, 2 * size, 2 * size);

	// Brazos
	brazos = new BrazoDron*[numBrazos];
	float rot = 360.0f / numBrazos;
	for (int i = 0; i < numBrazos; i++) {
		SceneNode* aux = centroNode->createChildSceneNode();
		brazos[i] = new BrazoDron(aux, t != ORIGINAL, i, numHelices, adorno);
		aux->yaw(Ogre::Degree(rot * i));
		if (t != ORIGINAL && i % 2 != 0) aux->translate(176, 0, 0, SceneNode::TS_LOCAL);
		else aux->translate(104, 0, 0, SceneNode::TS_LOCAL);

	}

	if (t != ORIGINAL) {
		//ficticioNode->yaw(Degree(-120));
		centroNode->translate(offset + Vector3(0, centroNode->getScale().y * 100, 0));
		if (t == MOTHER) esf->setMaterialName("red");
		else if (t == CHILD) esf->setMaterialName("smile");
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

void Dron::frameRendered(const FrameEvent& evt) {
	if (type != ORIGINAL) {
		if (!stop) ficticioNode->pitch(Degree(1));
		else ficticioNode->yaw(Degree(3));
		timer += evt.timeSinceLastFrame;
		if (!stop && timer > 2) stop = true;
		else if (stop && timer > 4) {
			stop = false;
			timer = 0;
		}
	}
}