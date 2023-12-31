#pragma once

#include "Plano.h"

class Rio : public Plano {
private:
	bool count = false;
	Timer timer;

public:
	Rio(SceneNode* m, std::string name, int anch, int alt);
	~Rio();

	virtual void frameRendered(const FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};

