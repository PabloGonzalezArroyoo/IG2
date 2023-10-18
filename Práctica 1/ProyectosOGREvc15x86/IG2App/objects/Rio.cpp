#include "Rio.h"

Rio::Rio(SceneNode* m, std::string name, int anch, int alt) : Plano(m, name, anch, alt, "waterTexture") {}

Rio::~Rio() {

}

bool Rio::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_r) {
		sendEvent(TECLA_R, this);
		return true;
	}

	return false;
}