#include "Droncito.h"

Droncito::Droncito(SceneNode* m, Vector3 pos, float size, Vector3 offset) : Dron(m, pos, size, true, 3, 3) {
	centroNode->translate(offset + Vector3(0, centroNode->getScale().y * 100, 0));
	for (int i = 0; i < numBrazos; i++) brazos[i]->getNode()->translate(centroNode->getPosition());
	esf->setMaterialName("smile");
}