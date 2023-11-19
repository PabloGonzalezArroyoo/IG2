#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset, SceneState sc, AnimState as, SwordState ss) : EntidadIG(m),
	turnTimer(), sign(1), turning(false), scState(sc), aState(as), swState(ss), center(pos) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Sinbad
	sinbad = mSM->createEntity("Sinbad.mesh");
	sinbadNode = ficticioNode->createChildSceneNode();
	sinbadNode->attachObject(sinbad);
	sinbadNode->setScale(size, size, size);
	if (scState != NOPLANET) sinbadNode->translate(offset + Vector3(0, sinbadNode->getScale().y * size / 2, 0));

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
	if (scState != NOPLANET) {
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
	else {
		sinbad->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
		sinbad->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);

		animationState->addTime(evt.timeSinceLastFrame);
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
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	sinbadNode->setInitialState();
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(sinbadNode);
	Vector3 keyframePos(sinbadNode->getPosition());
	Radian keyFrameYaw = Radian(0);
	Real durPaso = duracion / 5.0;
	TransformKeyFrame* kf;

	//// Keyframe 0 : mirando a Z positiva
	//kf = track->createNodeKeyFrame(durPaso * 0);
	//kf->setTranslate(Vector3(0, 0, 0));
	//kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	//// Keyframe 1 : mirando hacia el plano rojo
	//kf = track->createNodeKeyFrame(durPaso * 1);
	//Vector3 v = Vector3(0, 0, 1);
	//Vector3 w = (posFin - center).normalisedCopy();
	//float escalar = v.x * w.x + v.y * w.y + v.z * w.z;
	//float angulo = acos(escalar/ (w.normalise() * v.normalise()));
	//keyFrameYaw = Radian(angulo);
	//kf->setTranslate(Vector3(0, 0, 0));
	//kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	//// Keyframe 2 : hasta el molino
	//kf = track->createNodeKeyFrame(durPaso * 2);
	//keyframePos = posFin - ficticioNode->getPosition();
	//keyframePos = Vector3(keyframePos.x, sinbadNode->getPosition().y, keyframePos.z);
	//kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));
	//kf->setTranslate(keyframePos);

	//// Keyframe 3 : mirando hacia posición inicial
	//kf = track->createNodeKeyFrame(durPaso * 3);
	//keyFrameYaw += Radian(Degree(180));
	//kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	//// Keyframe 4 : hasta la posición inicial
	//kf = track->createNodeKeyFrame(durPaso * 4);
	//keyframePos = ficticioNode->getPosition();
	//kf->setTranslate(keyframePos);

	//// Keyframe 5 : mirando al frente
	//kf = track->createNodeKeyFrame(durPaso * 5);
	//keyFrameYaw += Radian(Degree(180 - angulo));
	//kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Crear animationState
	animationState = mSM->createAnimationState("viajesito");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}