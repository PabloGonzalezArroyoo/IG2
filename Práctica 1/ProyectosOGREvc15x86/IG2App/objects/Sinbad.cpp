#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* m, Vector3 pos, float size, Vector3 offset) : EntidadIG(m), turnTimer(), sign(1),
	turning(false) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Sinbad
	sinbad = mSM->createEntity("Sinbad.mesh");
	sinbadNode = ficticioNode->createChildSceneNode();
	sinbadNode->attachObject(sinbad);
	sinbadNode->setScale(size, size, size);
	sinbadNode->translate(offset + Vector3(0, sinbadNode->getScale().y * size / 2, 0));

	sinbad->getAnimationState("RunBase")->setEnabled(true);
	sinbad->getAnimationState("RunTop")->setEnabled(true);
	sinbad->getAnimationState("RunBase")->setLoop(true);
	sinbad->getAnimationState("RunTop")->setLoop(true);

	AnimationStateSet* aux = sinbad->getAllAnimationStates(); int i = 1;
	for (auto it = aux->getAnimationStateIterator().begin(); it != aux->getAnimationStateIterator().end(); it++) {
		std::cout << i << " - " <<  it->first << "\n";
		i++;
	}
}

void Sinbad::frameRendered(const FrameEvent& evt) {
	sinbad->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
	sinbad->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);

	ficticioNode->pitch(Degree(0.1));

	if (!turning && turnTimer.getMillisecondsCPU() > 2000) {
		rand() % 2 == 0 ? sign = 1 : sign = -1;
		turnTimer.reset();
		turning = true;
	}

	if (turning) {
		if (turnTimer.getMillisecondsCPU() > 4000) { turning = false; turnTimer.reset(); }
		ficticioNode->yaw(Degree(0.1 * sign));
	}
}