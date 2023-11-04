#pragma once

#include "RotorDron.h"

class BrazoDron : public EntidadIG {
public:
	RotorDron* rotorNode = nullptr;
	SceneNode* cilindroNode = nullptr;

	BrazoDron(SceneNode* m, bool txt, int id, int nh, bool adorno = false);
	virtual ~BrazoDron() {};

	void mueveHelices(int sign = 1);
};