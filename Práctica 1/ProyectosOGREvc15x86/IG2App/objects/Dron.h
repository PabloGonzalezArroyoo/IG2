#pragma once

#include "BrazoDron.h"

enum DronType {
	ORIGINAL, MOTHER, CHILD
};

const int MAX_LIFE = 5;

class Dron : public EntidadIG {
protected:
	BrazoDron** brazos = nullptr;
	SceneNode* ficticioNode = nullptr;
	SceneNode* centroNode = nullptr;

	Entity* esf;
	DronType type;
	int numHelices = 12, numBrazos = 8, life = MAX_LIFE, sign;
	float timer, dmgTimer;
	bool stop, damage;

public:
	Dron(SceneNode* m, Vector3 pos, float size, DronType t, int nh = 12, int nb = 8, Vector3 offset = Vector3(0, 0, 0), bool adorno = false);
	virtual ~Dron();

	void rotateDrone(Vector3 v);
	bool receiveDamage();

	void spinHelices();

	inline int getLife() { return life; }
	inline SceneNode* getCuerpoNode() { return centroNode; }
	inline void setSphereMaterial(std::string mat) { esf->setMaterialName(mat); }
	inline void setLife(int l) { life = l; }

	virtual void frameRendered(const FrameEvent& evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

