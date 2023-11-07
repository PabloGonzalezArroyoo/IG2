#include "Avion.h"

Avion::Avion(SceneNode* m, Vector3 pos, float size, Vector3 offset, bool txt) : EntidadIG(m), spin(false), stop(false), counter(0) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	cuerpoNode = ficticioNode->createChildSceneNode();
	cuerpoNode->attachObject(esf);
	cuerpoNode->setScale(1.5 * size, 1.5 * size, 1.5 * size);
	cuerpoNode->translate(offset + Vector3(0, cuerpoNode->getScale().y * 100, 0));
	
	// Luz
	if (!txt) {
		Light* foco = mSM->createLight("focoAvion");
		foco->setType(Light::LT_SPOTLIGHT);
		foco->setDiffuseColour(0.75, 0.75, 0.75);
		focoNode = cuerpoNode->createChildSceneNode();
		focoNode->attachObject(foco);
		focoNode->setDirection(Vector3(0, -1, 0));
	}

	// Piloto
	Entity* piloto = mSM->createEntity("ninja.mesh");
	pilotoNode = cuerpoNode->createChildSceneNode();
	pilotoNode->attachObject(piloto);
	pilotoNode->setScale(0.5, 0.5, 0.5);
	pilotoNode->translate(Vector3(0, 40, 0));
	pilotoNode->yaw(Degree(180));

	// Alas
	Entity* alaI = mSM->createEntity("cube.mesh");
	alaINode = cuerpoNode->createChildSceneNode();
	alaINode->attachObject(alaI);
	alaINode->setScale(2.5, 0.15, 1);
	alaINode->translate(Vector3(-200, 0, 0));
	Entity* alaD = mSM->createEntity("cube.mesh");
	alaDNode = cuerpoNode->createChildSceneNode();
	alaDNode->attachObject(alaD);
	alaDNode->setScale(2.5, 0.15, 1);
	alaDNode->translate(Vector3(200, 0, 0));

	// Frente
	Entity* fnt = mSM->createEntity("Barrel.mesh");
	frenteNode = cuerpoNode->createChildSceneNode();
	frenteNode->attachObject(fnt);
	frenteNode->setScale(8, 2, 8);
	frenteNode->translate(Vector3(0, 0, 100));
	frenteNode->pitch(Degree(90));

	// Helices
	helicesNode = new Aspas*[2];
	for (int i = 0; i < 2; i++) {
		SceneNode* node = cuerpoNode->createChildSceneNode();
		Aspas* aux = new Aspas(node, 0.6, 5, true);
		helicesNode[i] = aux;
		if (i == 0) node->translate(Vector3(200, 0, 53));
		else if (i == 1) node->translate(Vector3(-200, 0, 53));
	}

	if (txt) {
		esf->setMaterialName("red");
		piloto->setMaterialName("yellow");
		alaI->setMaterialName("alas");
		alaD->setMaterialName("alas");
		fnt->setMaterialName("orange");
	}
}

Avion::~Avion() {
	ficticioNode->removeAndDestroyAllChildren();
	delete helicesNode; helicesNode = nullptr;
}

void Avion::rotateHelices() {
	for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		rotateHelices();
		return true;
	}
	else if (evt.keysym.sym == SDLK_f) {
		if (!stop) spin = !spin;
		else { stop = false; spin = true; }
		return true;
	}
	else if (evt.keysym.sym == SDLK_h) {
		ficticioNode->pitch(Degree(1));
		rotateHelices();
		return true;
	}
	else if (evt.keysym.sym == SDLK_j) {
		ficticioNode->yaw(Degree(-1));
		rotateHelices();
		return true;
	}

	return false;
}

void Avion::frameRendered(const FrameEvent& evt) {
	if (spin) {
		ficticioNode->yaw(Degree(0.5));
		for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
	}
	if (stop) {
		counter += evt.timeSinceLastFrame;
		if (counter >= 5) {
			spin = false;
			counter = 0;
			stop = false;
		}
	}
};

void Avion::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (spin && msg == TECLA_R && dynamic_cast<Rio*>(entidad) != nullptr) {
		stop = true;
		counter = 0;
	}
};