#pragma once

#include "EntidadIG.h"

class Sinbad : public EntidadIG {
private:
	SceneNode* ficticioNode = nullptr;
	SceneNode* sinbadNode = nullptr;

	Entity* sinbad;
	Timer turnTimer;
	int sign;
	bool turning;

public:
	Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset = Vector3(0, 0, 0));

	virtual void frameRendered(const FrameEvent& evt);
};

