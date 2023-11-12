#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset, AnimState as, SwordState ss) : EntidadIG(m), turnTimer(), sign(1),
	turning(false), aState(as), sState(ss) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Sinbad
	sinbad = mSM->createEntity("Sinbad.mesh");
	sinbadNode = ficticioNode->createChildSceneNode();
	sinbadNode->attachObject(sinbad);
	sinbadNode->setScale(size, size, size);
	sinbadNode->translate(offset + Vector3(0, sinbadNode->getScale().y * size / 2, 0));

	sinbad->getAnimationState("RunBase")->setEnabled(true);
	sinbad->getAnimationState("RunTop")->setEnabled(true);
	sinbad->getAnimationState("RunBase")->setLoop(true);
	sinbad->getAnimationState("RunTop")->setLoop(true);
	sinbad->getAnimationState("Dance")->setEnabled(true);
	sinbad->getAnimationState("Dance")->setLoop(true);

	AnimationStateSet* aux = sinbad->getAllAnimationStates(); int i = 1;
	for (auto it = aux->getAnimationStateIterator().begin(); it != aux->getAnimationStateIterator().end(); it++) {
		std::cout << i << " - " <<  it->first << "\n";
		i++;
	}

	asignaEspadas();
}

Sinbad::~Sinbad() {
	if (espIzq != nullptr) delete espIzq;
	if (espDer != nullptr) delete espDer;
	delete sinbad;
}

void Sinbad::frameRendered(const FrameEvent& evt) {
	if (aState == WALKING) {
		sinbad->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
		sinbad->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);

		ficticioNode->pitch(Degree(0.1));

		if (!turning && turnTimer.getMillisecondsCPU() > 2000) {
			rand() % 2 == 0 ? sign = 1 : sign = -1;
			turnTimer.reset();
			turning = true;
		}

		if (turning) {
			if (turnTimer.getMillisecondsCPU() > 4000) { turning = false; turnTimer.reset(); }
			ficticioNode->yaw(Degree(0.1 * sign));
		}
	}
	else if (aState == DANCING) {
		sinbad->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_c) {
		// PREGUNTAR AL PROFE POR EL BRAZO SUELTO
		aState == WALKING ? aState = DANCING : aState = WALKING;
		if (aState == DANCING) quitaEspadas();
		else asignaEspadas();
		return true;
	}

	return false;
}

void Sinbad::arma(bool izq) {
	if (izq) {
		espIzq = mSM->createEntity("Sword.mesh");
		sinbad->attachObjectToBone("Handle.L", espIzq);
	}
	else {
		espDer = mSM->createEntity("Sword.mesh");
		sinbad->attachObjectToBone("Handle.R", espDer);
	}
}

void Sinbad::arma() {
	arma(true); arma(false);
}

void Sinbad::cambiaEspada() {
	if (sState == LEFT) {
		sinbad->detachObjectFromBone(espIzq);
		sState = RIGHT;
		asignaEspadas();
	}
	else if (sState == RIGHT) {
		sinbad->detachObjectFromBone(espDer);
		sState = LEFT;
		asignaEspadas();
	}
}

void Sinbad::quitaEspadas() {
	sinbad->detachObjectFromBone(espIzq);
	sinbad->detachObjectFromBone(espDer);
}

void Sinbad::asignaEspadas() {
	switch (sState) {
		case LEFT: arma(true); break;
		case RIGHT: arma(false); break;
		case BOTH: arma(); break;
		case NONE: quitaEspadas(); break;
	}
}