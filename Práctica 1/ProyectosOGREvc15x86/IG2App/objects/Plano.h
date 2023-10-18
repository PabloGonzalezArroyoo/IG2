#pragma once

#include "EntidadIG.h"

class Plano : public EntidadIG {
protected:


public:
	Plano(SceneNode* m, std::string name, int anch, int alt, std::string material);
	virtual ~Plano() {};
};

