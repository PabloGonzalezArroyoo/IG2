#pragma once

#include "Plano.h"

class Rio : public Plano {
public:
	Rio(SceneNode* m, std::string name, int anch, int alt);
	~Rio();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(MessageType msg, EntidadIG* entidad);
};

