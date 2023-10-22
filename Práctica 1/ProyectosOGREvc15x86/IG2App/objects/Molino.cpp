#include "Molino.h"

// NOTA:
// Opción 1 -> nodo ficticio posicionado en el centro del molino que será padre de las aspas, rotar este
// Opción 2 -> trasladar al origen, rotar, trasladar de vuelta

Molino::Molino(SceneNode* m) : EntidadIG(m), spin(false), state(NORMAL), counter(0) {
	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	techoNode = mNode->createChildSceneNode("techoNode");
	techoNode->attachObject(esf);
	techoNode->setScale(1, 1, 1);

	// Cuerpo
	Entity* cuerp = mSM->createEntity("Barrel.mesh");
	cuerpoNode = mNode->createChildSceneNode("cuerpoNode");
	cuerpoNode->attachObject(cuerp);
	cuerpoNode->setScale(40, 50, 40);
	cuerpoNode->setPosition(0, -150, 0);

	// Aspas
	nodoFicticio = mNode->createChildSceneNode("nodoFicticio");
	SceneNode* auxNode = nodoFicticio->createChildSceneNode("aspasMolinoNode");
	auxNode->setPosition(0, 0, 110);
	aspasNode = new Aspas(auxNode, 2, 6);

	// Plano
	SceneNode* aux = mNode->createChildSceneNode("planoMolinoNode");
	suelo = new Plano(aux, "molino", 300, 300, "grassTexture");
	aux->translate(Vector3(0, -310, 0));
}

Molino::~Molino() {
	delete aspasNode; aspasNode = nullptr;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_h) {
		// Opcion 1 -> rotar con yaw
		mNode->getChild("nodoFicticio")->yaw(Ogre::Degree(3));

		// Opcion 2 -> trasladar, rotar, trasladar
		/*Node* aux = mNode->getChild("aspasMolinoNode");
		aux->translate(0, 0, -110);
		aux->yaw(Ogre::Degree(3));
		aux->translate(0, 0, 110);*/
	}
	else if (evt.keysym.sym == SDLK_j) aspasNode->rotateAspas();
	else if (evt.keysym.sym == SDLK_c) aspasNode->moveCilindro();
	else if (evt.keysym.sym == SDLK_f && state == NORMAL) spin ? spin = false : spin = true;

	return true;
}

bool Molino::keyReleased(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_c) aspasNode->setCilindroIniPos();

	return true;
}

void Molino::frameRendered(const FrameEvent& evt) {
	if (spin) aspasNode->rotateAspas();
	if (state == INTERVAL) {
		counter += evt.timeSinceLastFrame;
		if (!spin) spin = counter >= 1.0f;
		else {
			spin = counter <= 4.0f;
			if (!spin) counter = 0;
		}
	}
}

void Molino::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (spin && msg == TECLA_T && dynamic_cast<Rio*>(entidad) != nullptr) {
		state = INTERVAL;
		spin = false;
		sendEvent(STOP, this);
	}
};