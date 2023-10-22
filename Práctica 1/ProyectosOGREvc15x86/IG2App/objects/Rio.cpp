#include "Rio.h"
#include "Molino.h"

Rio::Rio(SceneNode* m, std::string name, int anch, int alt) : Plano(m, name, anch, alt, "waterTexture") {}

Rio::~Rio() {

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
};