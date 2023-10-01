#include "Molino.h"

Molino::Molino(SceneNode* m) : mNode(m) {
	// Node padre
	mSM = mNode->getCreator();

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	techoNode = mNode->createChildSceneNode("techoNode");
	techoNode->attachObject(esf);
	techoNode->setScale(1, 1, 1);

	// Cuerpo
	Entity* cuerp = mSM->createEntity("Barrel.mesh");
	cuerpoNode = mNode->createChildSceneNode("cuerpoNode");
	cuerpoNode->attachObject(cuerp);
	cuerpoNode->setScale(40, 50, 40);
	cuerpoNode->setPosition(0, -150, 0);

	// Aspas
	SceneNode* auxNode = mNode->createChildSceneNode("aspasMolinoNode");
	// Opcion 1 : auxNode->setPosition(0, 0, 110);
	// Opcion 2
	aspasNode = new Aspas(auxNode, 6, Vector3(0,0,110));
	
}

Molino::~Molino() {
	delete aspasNode; aspasNode = nullptr;
	delete techoNode; techoNode = nullptr;
	delete cuerpoNode; cuerpoNode = nullptr;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt) {
	aspasNode->keyPressed(evt);
	if (evt.keysym.sym == SDLK_h) {
		// Opcion 1
		// mNode->rotate(Vector3(0, 1, 0), Degree(3));
		// techoNode->rotate(Vector3(0, 1, 0), Degree(-3));
		// cuerpoNode->rotate(Vector3(0, 1, 0), Degree(-3));
		// Opcion 2
		mNode->getChild("aspasMolinoNode")->rotate(Vector3(0, 1, 0), Degree(3));
	}

	return true;
}

bool Molino::keyReleased(const OgreBites::KeyboardEvent& evt) {
	aspasNode->keyReleased(evt);
	return true;
}