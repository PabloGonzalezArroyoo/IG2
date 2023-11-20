#include "Rio.h"
#include "Molino.h"
#include "Baliza.h"

Rio::Rio(SceneNode* m, std::string name, int anch, int alt) : Plano(m, name, anch, alt, "practica1/waterTexture"), timer() {
	fogIzq = mNode->createChildSceneNode();
	fogDer = mNode->createChildSceneNode();
	fogIzq->translate(Vector3(-anch / 4, 100, alt / 2));
	fogDer->translate(Vector3(anch / 4, 100, alt / 2));
	createFog(fogIzq, true, anch * 1.05);
	createFog(fogDer, false, anch * 1.05);
}

Rio::~Rio() {

}

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

void Rio::createFog(SceneNode* fog, bool izq, int anch) {
	BillboardSet* bbSet = mSM->createBillboardSet("fog" + std::to_string(izq), 20);
	bbSet->setDefaultDimensions(300, 600);
	bbSet->setMaterialName("practica1/smoke");
	
	int dist = anch / 20;
	for (int i = 0; i < 20; i++) {
		bbSet->createBillboard(Vector3(fog->getPosition() + Vector3(rand() % 50 - 25, rand() % 60 - 30, -dist * i)));
	}

	fog->attachObject(bbSet);
}