#pragma once

#include "EntidadIG.h"

class Baliza : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* barrelNode = nullptr;
	Entity* cuerpo;
	AnimationState* animationState;
	bool playAnim = true;

public:
	Baliza(SceneNode* m, Vector3 pos, Vector3 size);
	//~Baliza();

	virtual void frameRendered(const FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void createUpDownAnim();
};