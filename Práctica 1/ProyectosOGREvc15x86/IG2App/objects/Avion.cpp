#include "Avion.h"

Avion::Avion(SceneNode* m, Vector3 pos, float size) : EntidadIG(m), spin(false), stop(false), counter(0) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode("ficticioAvionNode");
	ficticioNode->setPosition(Vector3(pos.x, 0, 0));
	offset = -1000;

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	cuerpoNode = ficticioNode->createChildSceneNode("centroAvionNode");
	cuerpoNode->attachObject(esf);
	cuerpoNode->setScale(1.5 * size, 1.5 * size, 1.5 * size);
	cuerpoNode->translate(Vector3(offset, 0, 0) * size);

	// Piloto
	Entity* piloto = mSM->createEntity("ninja.mesh");
	pilotoNode = ficticioNode->createChildSceneNode("pilotoAvionNode");
	pilotoNode->attachObject(piloto);
	pilotoNode->setScale(0.8 * size, 0.8 * size, 0.8 * size);
	pilotoNode->translate(Vector3(offset, 55, 0) * size);
	pilotoNode->yaw(Degree(180));

	// Alas
	Entity* alaI = mSM->createEntity("cube.mesh");
	alaINode = ficticioNode->createChildSceneNode("alaIAvionNode");
	alaINode->attachObject(alaI);
	alaINode->setScale(4 * size, 0.2 * size, 1.5 * size);
	alaINode->translate(Vector3(-250 + offset, 0, 0) * size);
	Entity* alaD = mSM->createEntity("cube.mesh");
	alaDNode = ficticioNode->createChildSceneNode("alaDAvionNode");
	alaDNode->attachObject(alaD);
	alaDNode->setScale(4 * size, 0.2 * size, 1.5 * size);
	alaDNode->translate(Vector3(250 + offset, 0, 0) * size);

	// Frente
	Entity* fnt = mSM->createEntity("Barrel.mesh");
	frenteNode = ficticioNode->createChildSceneNode("fntAvionNode");
	frenteNode->attachObject(fnt);
	frenteNode->setScale(15 * size, 4 * size, 15 * size);
	frenteNode->translate(Vector3(offset, 0, 150) * size);
	frenteNode->pitch(Degree(90));

	// Helices
	helicesNode = new Aspas*[2];
	for (int i = 0; i < 2; i++) {
		SceneNode* node = ficticioNode->createChildSceneNode("heliceAvionNode" + std::to_string(i));
		Aspas* aux = new Aspas(node, 1 * size, i, 5);
		helicesNode[i] = aux;
		if (i == 0) node->translate(Vector3(250 + offset, 0, 80) * size);
		else if (i == 1) node->translate(Vector3(-250 + offset, 0, 80) * size);
	}
}

Avion::~Avion() {
	// TO DO: borrar aspas
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
		return true;
	}
	else if (evt.keysym.sym == SDLK_f) {
		if (!stop) spin ? spin = false : spin = true;
		else stop = false;
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
		}
	}
};

void Avion::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (spin && msg == TECLA_R && dynamic_cast<Molino*>(entidad) != nullptr) stop = true;
};