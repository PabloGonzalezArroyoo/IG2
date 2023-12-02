#pragma once

#include "EntidadIG.h"

class Baliza : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* barrelNode = nullptr;
	SceneNode* explosionNode = nullptr;
	Entity* cuerpo;
	AnimationState* animationState;
	ParticleSystem* pSys;

	bool playAnim, explosion;

public:
	Baliza(SceneNode* m, Vector3 pos, Vector3 size);
	//~Baliza();

	virtual void frameRendered(const FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void createUpDownAnim();
	void createExplosion();

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};