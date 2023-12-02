#include "Rio.h"
#include "Molino.h"
#include "Baliza.h"

Rio::Rio(SceneNode* m, std::string name, int anch, int alt) : Plano(m, name, anch, alt, "practica1/waterTexture"), timer() {}

Rio::~Rio() {}

void Rio::frameRendered(const FrameEvent& evt) {
	if (count && timer.getMilliseconds() > 5000) {
		plane->setMaterialName("practica1/rockGround");
	}
}

bool Rio::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_r) {
		sendEvent(TECLA_R, this);
		return true;
	}
	else if (evt.keysym.sym == SDLK_t) {
		sendEvent(TECLA_T, this);
		return true;
	}

	return false;
}

void Rio::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (msg == STOP && dynamic_cast<Molino*>(entidad) != nullptr) {
		sendEvent(TECLA_R, this);
	}
	else if (msg == TECLA_T && dynamic_cast<Baliza*>(entidad) != nullptr) {
		timer.reset();
		count = true;
	}
}