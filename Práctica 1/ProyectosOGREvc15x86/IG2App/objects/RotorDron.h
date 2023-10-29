#pragma once

#include "Aspas.h"

class RotorDron : public EntidadIG {
protected:
	int numHelices;
	int ident;

public:
	Aspas* helicesNode = nullptr;
	SceneNode* esferaNode = nullptr;

	RotorDron(SceneNode* m, int nh, int id, bool adorno = false);
	virtual ~RotorDron() {};

	void mueveHelices(int sign = 1);
};