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

	Vector3 bolaPos = cuerpoNode->getPosition();
	
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
	pilotoNode = ficticioNode->createChildSceneNode();
	pilotoNode->attachObject(piloto);
	pilotoNode->setScale(0.8 * size, 0.8 * size, 0.8 * size);
	pilotoNode->translate(bolaPos + Vector3(0, 55, 0) * size);
	pilotoNode->yaw(Degree(180));

	// Alas
	Entity* alaI = mSM->createEntity("cube.mesh");
	alaINode = ficticioNode->createChildSceneNode();
	alaINode->attachObject(alaI);
	alaINode->setScale(4 * size, 0.2 * size, 1.5 * size);
	alaINode->translate(bolaPos + Vector3(-250, 0, 0) * size);
	Entity* alaD = mSM->createEntity("cube.mesh");
	alaDNode = ficticioNode->createChildSceneNode();
	alaDNode->attachObject(alaD);
	alaDNode->setScale(4 * size, 0.2 * size, 1.5 * size);
	alaDNode->translate(bolaPos + Vector3(250, 0, 0) * size);

	// Frente
	Entity* fnt = mSM->createEntity("Barrel.mesh");
	frenteNode = ficticioNode->createChildSceneNode();
	frenteNode->attachObject(fnt);
	frenteNode->setScale(15 * size, 4 * size, 15 * size);
	frenteNode->translate(bolaPos + Vector3(0, 0, 150) * size);
	frenteNode->pitch(Degree(90));

	// Helices
	helicesNode = new Aspas*[2];
	for (int i = 0; i < 2; i++) {
		SceneNode* node = ficticioNode->createChildSceneNode();
		Aspas* aux = new Aspas(node, 1 * size, 5, true);
		helicesNode[i] = aux;
		if (i == 0) node->translate(bolaPos + Vector3(250, 0, 80) * size);
		else if (i == 1) node->translate(bolaPos + Vector3(-250, 0, 80) * size);
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
	delete helicesNode; helicesNode = nullptr;
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
		return true;
	}
	else if (evt.keysym.sym == SDLK_f) {
		if (!stop) spin ? spin = false : spin = true;
		else { stop = false; spin = true; }
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