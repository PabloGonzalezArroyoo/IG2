#pragma once

#include "Aspas.h"
#include "Rio.h"

class Molino : public EntidadIG {
protected:
	bool spin;

	virtual void frameRendered(const FrameEvent& evt);

public:
	SceneNode* techoNode = nullptr;
	SceneNode* cuerpoNode = nullptr;
	Aspas* aspasNode = nullptr;
	SceneNode* nodoFicticio = nullptr;
	Plano* suelo = nullptr;

	Molino(SceneNode* m);
	virtual ~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};