#pragma once

#include "RotorDron.h"

class BrazoDron : public EntidadIG {
public:
	RotorDron* rotorNode = nullptr;
	SceneNode* cilindroNode = nullptr;

	BrazoDron(SceneNode* m, int id, int nh);
	virtual ~BrazoDron() {};

	void mueveHelices(int sign = 1);
};