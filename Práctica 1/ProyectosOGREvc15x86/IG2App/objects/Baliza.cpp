#include "Baliza.h"

Baliza::Baliza(SceneNode* m, Vector3 pos, float size) : EntidadIG(m) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Sinbad
	cuerpo = mSM->createEntity("Barrel.mesh");
	cuerpo->setMaterialName("baliza");
	barrelNode = ficticioNode->createChildSceneNode();
	barrelNode->attachObject(cuerpo);
	barrelNode->setScale(size, size * 3, size);
}