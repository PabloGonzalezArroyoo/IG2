#pragma once

#include "Plano.h"

enum RiverType {
	FOGGY, R_NORMAL
};

class Rio : public Plano {
private:
	bool count = false;
	Timer timer;
	SceneNode* fogIzq;
	SceneNode* fogDer;
	RiverType rType;

public:
	Rio(SceneNode* m, std::string name, int anch, int alt, RiverType rt = R_NORMAL);
	~Rio();

	virtual void frameRendered(const FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void createFog(SceneNode* fog, bool izq, int anch);

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};

