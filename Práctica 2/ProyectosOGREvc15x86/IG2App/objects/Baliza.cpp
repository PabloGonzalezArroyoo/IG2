#include "Baliza.h"
#include "Sinbad.h"

Baliza::Baliza(SceneNode* m, Vector3 pos, Vector3 size, std::string txt) : EntidadIG(m), playAnim(true), explosion(false) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Baliza
	cuerpo = mSM->createEntity("uv_sphere.mesh");
	cuerpo->setMaterialName(txt);
	barrelNode = ficticioNode->createChildSceneNode();
	barrelNode->attachObject(cuerpo);
	barrelNode->setScale(size.x, size.y, size.z);

	createUpDownAnim();
}

void Baliza::createUpDownAnim() {
	// --- ANIMACIÓN ---
	int duracion = 4, longDesplazamiento = 50;

	Animation* animation = mSM->createAnimation("animVV", duracion);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	barrelNode->setInitialState();
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(barrelNode);
	Vector3 keyframePos(barrelNode->getPosition());
	Radian keyFrameYaw = Radian(0);
	Real durPaso = duracion / 4.0;

	// Keyframe 0 : origen
	TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 1 : arriba
	kf = track->createNodeKeyFrame(durPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
	keyFrameYaw += Radian(Degree(45));
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 2 : origen
	kf = track->createNodeKeyFrame(durPaso * 2);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	keyFrameYaw -= Radian(Degree(45));
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 3 : abajo
	kf = track->createNodeKeyFrame(durPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	keyFrameYaw -= Radian(Degree(45));
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Keyframe 4 : origen
	kf = track->createNodeKeyFrame(durPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
	keyFrameYaw += Radian(Degree(45));
	kf->setTranslate(keyframePos);
	kf->setRotation(Quaternion(keyFrameYaw, Vector3::UNIT_Y));

	// Crear animationState
	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Baliza::frameRendered(const FrameEvent& evt) {
	if (playAnim) animationState->addTime(evt.timeSinceLastFrame);
}

bool Baliza::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_t) {
		sendEvent(TECLA_T, this);
		playAnim = false;
		return true;
	}

	return false;
}

void Baliza::createExplosion() {
	explosion = true; playAnim = false;

	Vector3 pos = ficticioNode->getPosition();
	animationState->setEnabled(false);
	ficticioNode->removeAndDestroyAllChildren();
	explosionNode = ficticioNode->createChildSceneNode();

	pSys = mSM->createParticleSystem("explosionBaliza", "practica1/explosionBaliza");
	pSys->setEmitting(true);
	explosionNode->attachObject(pSys);
}

void Baliza::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (msg == EXPLODE && dynamic_cast<Sinbad*>(entidad) != nullptr) {
		createExplosion();
	}
};