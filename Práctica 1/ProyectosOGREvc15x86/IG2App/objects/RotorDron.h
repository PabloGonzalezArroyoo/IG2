#pragma once

#include "Aspas.h"

enum DronType {
	ORIGINAL, MOTHER, CHILD
};

class RotorDron : public EntidadIG {
protected:
	int numHelices;
	int ident;

public:
	Aspas* helicesNode = nullptr;
	SceneNode* esferaNode = nullptr;

	RotorDron(SceneNode* m, float size, bool txt, int nh, int id, bool adorno = false);
	virtual ~RotorDron() {};

	void mueveHelices(int sign = 1);
};