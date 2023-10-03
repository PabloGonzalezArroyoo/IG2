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
	// Opcion 1
	// aspasNode = new Aspas(auxNode, 6);
	// auxNode->setPosition(0, 0, 110);
	// Opcion 2
	aspasNode = new Aspas(auxNode, 6, Vector3(0,0,110));
	
}

Molino::~Molino() {
	delete aspasNode; aspasNode = nullptr;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_h) {
		// Opcion 0 -> no vale
		// mNode->rotate(Vector3(0, 1, 0), Degree(3));
		// techoNode->rotate(Vector3(0, 1, 0), Degree(-3));
		// cuerpoNode->rotate(Vector3(0, 1, 0), Degree(-3));

		// Opcion 1 -> rotar con yaw en el eje Y del padre
		mNode->getChild("aspasMolinoNode")->yaw(Ogre::Degree(3), Ogre::Node::TS_PARENT);

		// Opcion 2 -> rotar el nodo de las aspas respecto al padre
		//mNode->getChild("aspasMolinoNode")->rotate(Vector3(0, 1, 0), Degree(3));
	}
	else if (evt.keysym.sym == SDLK_j) aspasNode->rotateAspas();
	else if (evt.keysym.sym == SDLK_c) aspasNode->moveCilindro();

	return true;
}

bool Molino::keyReleased(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_c) aspasNode->setCilindroIniPos();

	return true;
}