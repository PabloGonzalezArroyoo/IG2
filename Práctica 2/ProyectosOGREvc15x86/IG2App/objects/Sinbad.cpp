#include "Sinbad.h"
#include "Avion.h"

Sinbad::Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset, AnimState as, SwordState ss) : EntidadIG(m),
	turnTimer(), msgTimer(), sign(1), turning(false), msgSent(false), aState(as), swState(ss) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Sinbad
	sinbad = mSM->createEntity("Sinbad.mesh");
	sinbadNode = ficticioNode->createChildSceneNode();
	sinbadNode->attachObject(sinbad);
	sinbadNode->setScale(size, size, size);
	center = ficticioNode->getPosition();
	center. y = sinbadNode->getPosition().y;

	sinbad->getAnimationState("RunBase")->setEnabled(true);
	sinbad->getAnimationState("RunTop")->setEnabled(true);
	sinbad->getAnimationState("RunBase")->setLoop(true);
	sinbad->getAnimationState("RunTop")->setLoop(true);
	sinbad->getAnimationState("Dance")->setEnabled(true);
	sinbad->getAnimationState("Dance")->setLoop(true);
	sinbad->getAnimationState("IdleTop")->setLoop(true);
	sinbad->getAnimationState("IdleTop")->setEnabled(true);
	sinbad->getAnimationState("IdleBase")->setLoop(true);
	sinbad->getAnimationState("IdleBase")->setEnabled(true);

	asignaEspadas();

	// Plano
	SceneNode* platformNode = ficticioNode->createChildSceneNode();
	platformNode->translate(0, -sinbadNode->getScale().y / 2 * 10, 0);
	Plano* plane = new Plano(platformNode, "platform", 200, 200, "practica1/yellow");
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

		animationState->addTime(evt.timeSinceLastFrame);
	}
	else {
		sinbad->getAnimationState("IdleBase")->addTime(evt.timeSinceLastFrame);
		sinbad->getAnimationState("IdleTop")->addTime(evt.timeSinceLastFrame);

		if (!msgSent && msgTimer.getMilliseconds() > 5000) {
			msgSent = true;
			sendEvent(EXPLODE, this);
		}
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (aState == WALKING) {
		if (evt.keysym.sym == SDLK_b) {
			quitaEspadas();
			arma(false);
			return true;
		}
		else if (evt.keysym.sym == SDLK_n) {
			cambiaEspada();
			return true;
		}
		else if (evt.keysym.sym == SDLK_v) {
			arma();
			return true;
		}
		else if (evt.keysym.sym == SDLK_q) {
			quitaEspadas();
			return true;
		}
	}

	return false;
}

void Sinbad::arma(bool izq) {
	if (izq) {
		espIzq = mSM->createEntity("Sword.mesh");
		sinbad->attachObjectToBone("Handle.L", espIzq);
		swState = LEFT;
	}
	else {
		espDer = mSM->createEntity("Sword.mesh");
		sinbad->attachObjectToBone("Handle.R", espDer);
		swState = RIGHT;
	}
}

void Sinbad::arma() {
	arma(true); arma(false);
	swState = BOTH;
}

void Sinbad::cambiaEspada() {
	if (swState == LEFT) {
		sinbad->detachObjectFromBone(espIzq);
		swState = RIGHT;
		asignaEspadas();
	}
	else if (swState == RIGHT) {
		sinbad->detachObjectFromBone(espDer);
		swState = LEFT;
		asignaEspadas();
	}
}

void Sinbad::quitaEspadas() {
	sinbad->detachObjectFromBone(espIzq);
	sinbad->detachObjectFromBone(espDer);
	swState = NONE;
}

void Sinbad::asignaEspadas() {
	switch (swState) {
		case LEFT: arma(true); break;
		case RIGHT: arma(false); break;
		case BOTH: arma(); break;
		case NONE: quitaEspadas(); break;
	}
}

void Sinbad::createMovementAnimation(Vector3 posFin) {
	// --- ANIMACIÓN ---
	int duracion = 10, longDesplazamiento = 30;

	Animation* animation = mSM->createAnimation("viajesito", duracion);
	sinbadNode->setInitialState();
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(sinbadNode);
	Vector3 keyframePos = sinbadNode->getPosition();
	Radian keyFrameYaw = Radian(0);
	Real durPaso = duracion / 5.0;
	TransformKeyFrame* kf;

	// Keyframe 0 : mirando a Z positiva
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));
	kf->setTranslate(keyframePos);

	// Keyframe 1 : mirando hacia el plano rojo
	kf = track->createNodeKeyFrame(durPaso * 1);
	Vector3 v = posFin - center;
	Degree angle = v.angleBetween(Vector3::UNIT_Z);
	keyFrameYaw = Radian(angle);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));
	kf->setTranslate(keyframePos);

	// Keyframe 2 : hasta el molino
	kf = track->createNodeKeyFrame(durPaso * 2);
	keyframePos = posFin - center;
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));
	kf->setTranslate(keyframePos);

	// Keyframe 3 : mirando hacia posición inicial
	kf = track->createNodeKeyFrame(durPaso * 3);
	keyFrameYaw += Radian(Degree(180));
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 4 : hasta la posición inicial
	kf = track->createNodeKeyFrame(durPaso * 4);
	keyframePos = sinbadNode->getPosition();
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 5 : mirando al frente
	kf = track->createNodeKeyFrame(durPaso * 5);
	keyframePos = sinbadNode->getPosition();
	keyFrameYaw = 0;
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Crear animationState
	animationState = mSM->createAnimationState("viajesito");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Sinbad::killSinbad() {
	msgTimer.reset();
	quitaEspadas();
	aState = IDLE;
	sinbadNode->pitch(Degree(-90));
	sinbadNode->translate(Vector3(0, -sinbadNode->getScale().y / 2 * 9, 0));
	animationState->setEnabled(false);
}

void Sinbad::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (msg == EXPLODE && dynamic_cast<Avion*>(entidad) != nullptr) {
		killSinbad();
	}
}