#pragma once

#include "EntidadIG.h"

enum SwordState {
	LEFT, RIGHT, BOTH, NONE
};

enum AnimState {
	WALKING, DANCING
};

enum SceneState {
	PLANET, NOPLANET
};

class Sinbad : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* sinbadNode = nullptr;

	Vector3 center;
	Entity* sinbad;
	Entity* espIzq;
	Entity* espDer;
	Timer turnTimer;
	int sign;
	bool turning;
	SwordState swState;
	AnimState aState;
	AnimationState* animationState;
	SceneState scState;

public:
	Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset = Vector3(0, 0, 0), SceneState sc = PLANET, AnimState as = WALKING, SwordState ss = NONE);
	~Sinbad();

	void arma(bool izq);
	void cambiaEspada();
	void arma();
	void quitaEspadas();
	void asignaEspadas();

	void createMovementAnimation(Vector3 posFin);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const FrameEvent& evt);
};

