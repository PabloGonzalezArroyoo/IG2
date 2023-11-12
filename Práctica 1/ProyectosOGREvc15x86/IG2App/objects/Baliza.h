#pragma once

#include "EntidadIG.h"

class Baliza : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* barrelNode = nullptr;
	Entity* cuerpo;

public:
	Baliza(SceneNode* m, Vector3 pos, float size);
	/*~Baliza();

	virtual void frameRendered(const FrameEvent& evt);*/
};