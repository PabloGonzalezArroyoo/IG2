#pragma once

#include "EntidadIG.h"

enum SwordState {
	LEFT, RIGHT, BOTH, NONE
};

enum AnimState {
	WALKING, DANCING
};

class Sinbad : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* sinbadNode = nullptr;

	Entity* sinbad;
	Entity* espIzq;
	Entity* espDer;
	Timer turnTimer;
	int sign;
	bool turning;
	SwordState sState;
	AnimState aState;

public:
	Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset = Vector3(0, 0, 0), AnimState as = WALKING, SwordState ss = NONE);
	~Sinbad();

	void arma(bool izq);
	void cambiaEspada();
	void arma();
	void quitaEspadas();
	void asignaEspadas();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const FrameEvent& evt);
};

