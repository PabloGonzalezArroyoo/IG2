#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode* node) {
	mNode = node;
	mSM = mNode->getCreator();
}

void EntidadIG::sendEvent(MessageType msg, EntidadIG* entidad) {
	for (EntidadIG* e : appListeners) {
		e->receiveEvent(msg, entidad);
	}
}