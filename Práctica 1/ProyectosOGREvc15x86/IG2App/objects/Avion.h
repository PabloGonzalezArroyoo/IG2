#pragma once

#include "Molino.h"

class Avion : public EntidadIG {
protected:
	float counter;
	bool spin, stop;

	SceneNode* cuerpoNode = nullptr;
	SceneNode* alaINode = nullptr;
	SceneNode* alaDNode = nullptr;
	SceneNode* frenteNode = nullptr;
	SceneNode* pilotoNode = nullptr;
	SceneNode* ficticioNode = nullptr;
	SceneNode* focoNode = nullptr;
	Aspas** helicesNode;

	virtual void frameRendered(const FrameEvent& evt);

public:
	Avion(SceneNode* m, Vector3 pos, float size, Vector3 offset, bool txt = false);
	virtual ~Avion();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};

