#include "Avion.h"

Avion::Avion(SceneNode* m, Vector3 pos, float size, Vector3 offset, bool txt) : EntidadIG(m), spin(false), stop(false), timer(),
	explosion(false) {
	// Nodo ficticio
	ficticioNode = mNode->createChildSceneNode();
	ficticioNode->setPosition(pos);

	// Esfera
	Entity* esf = mSM->createEntity("sphere.mesh");
	cuerpoNode = ficticioNode->createChildSceneNode();
	cuerpoNode->attachObject(esf);
	cuerpoNode->setScale(1.5 * size, 1.5 * size, 1.5 * size);
	cuerpoNode->translate(offset + Vector3(0, cuerpoNode->getScale().y * 100, 0));
	cuerpoNode->yaw(Degree(180));
	
	// Luz
	if (!txt) {
		Light* foco = mSM->createLight("focoAvion");
		foco->setType(Light::LT_SPOTLIGHT);
		foco->setDiffuseColour(0.75, 0.75, 0.75);
		focoNode = cuerpoNode->createChildSceneNode();
		focoNode->attachObject(foco);
		focoNode->setDirection(Vector3(0, -1, 0));
	}

	// Piloto
	Entity* piloto = mSM->createEntity("ninja.mesh");
	pilotoNode = cuerpoNode->createChildSceneNode();
	pilotoNode->attachObject(piloto);
	pilotoNode->setScale(0.5, 0.5, 0.5);
	pilotoNode->translate(Vector3(0, 40, 0));
	pilotoNode->yaw(Degree(180));

	// Alas
	Entity* alaI = mSM->createEntity("cube.mesh");
	alaINode = cuerpoNode->createChildSceneNode();
	alaINode->attachObject(alaI);
	alaINode->setScale(2.5, 0.15, 1);
	alaINode->translate(Vector3(-200, 0, 0));
	Entity* alaD = mSM->createEntity("cube.mesh");
	alaDNode = cuerpoNode->createChildSceneNode();
	alaDNode->attachObject(alaD);
	alaDNode->setScale(2.5, 0.15, 1);
	alaDNode->translate(Vector3(200, 0, 0));

	// Frente
	Entity* fnt = mSM->createEntity("Barrel.mesh");
	frenteNode = cuerpoNode->createChildSceneNode();
	frenteNode->attachObject(fnt);
	frenteNode->setScale(8, 2, 8);
	frenteNode->translate(Vector3(0, 0, 100));
	frenteNode->pitch(Degree(90));

	// Helices
	helicesNode = new Aspas*[2];
	for (int i = 0; i < 2; i++) {
		SceneNode* node = cuerpoNode->createChildSceneNode();
		Aspas* aux = new Aspas(node, 0.6, 5, txt);
		helicesNode[i] = aux;
		if (i == 0) node->translate(Vector3(200, 0, 53));
		else if (i == 1) node->translate(Vector3(-200, 0, 53));
	}

	// Points
	BillboardSet* bbSet = mSM->createBillboardSet("points", 1);
	bbSet->setMaterialName("practica1/points");
	bbSet->setDefaultDimensions(100, 50);
	planoNode = cuerpoNode->createChildSceneNode();
	planoNode->translate(Vector3(0, 0, -70));
	planoNode->attachObject(bbSet);
	bbSet->createBillboard(planoNode->getPosition());

	// ParticleSystem
	pSysNode = cuerpoNode->createChildSceneNode();
	pSysNode->translate(Vector3(0, -15, -90));
	ParticleSystem* pSys = mSM->createParticleSystem("psSmoke", "practica1/smoke");
	pSys->setEmitting(true);
	pSysNode->attachObject(pSys);

	if (txt) {
		esf->setMaterialName("practica1/red");
		piloto->setMaterialName("practica1/yellow");
		alaI->setMaterialName("practica1/alas");
		alaD->setMaterialName("practica1/alas");
		fnt->setMaterialName("practica1/orange");
	}
}

Avion::~Avion() {
	ficticioNode->removeAndDestroyAllChildren();
	delete helicesNode; helicesNode = nullptr;
}

void Avion::rotateHelices() {
	for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
}

void Avion::createExplosion() {
	spin = false; stop = false; timer.reset();
	explosion = true;
	
	Vector3 pos = cuerpoNode->getPosition();
	ficticioNode->removeAndDestroyAllChildren();
	explosionNode = ficticioNode->createChildSceneNode();
	explosionNode->setPosition(pos);

	ParticleSystem* pSys = mSM->createParticleSystem("explosionSmoke", "practica1/explosion");
	pSys->setEmitting(true);
	explosionNode->attachObject(pSys);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (!explosion) {
		if (evt.keysym.sym == SDLK_g) {
			rotateHelices();
			return true;
		}
		else if (evt.keysym.sym == SDLK_f) {
			if (!stop) spin = !spin;
			else { stop = false; spin = true; }
			return true;
		}
		else if (evt.keysym.sym == SDLK_h) {
			ficticioNode->pitch(Degree(1));
			rotateHelices();
			return true;
		}
		else if (evt.keysym.sym == SDLK_j) {
			ficticioNode->yaw(Degree(-1));
			rotateHelices();
			return true;
		}
		else if (evt.keysym.sym == SDLK_k) {
			ficticioNode->yaw(Degree(1));
			rotateHelices();
			return true;
		}
		else if (evt.keysym.sym == SDLK_r) {
			createExplosion();
			return true;
		}
	}

	return false;
}

void Avion::frameRendered(const FrameEvent& evt) {
	if (spin) {
		ficticioNode->yaw(Degree(0.5));
		for (int i = 0; i < 2; i++) helicesNode[i]->rotateAspas();
	}
	if (stop) {
		if (timer.getMilliseconds() >= 5000) {
			spin = false;
			timer.reset();
			stop = false;
		}
	}
};

void Avion::receiveEvent(MessageType msg, EntidadIG* entidad) {
	if (spin && msg == TECLA_R && dynamic_cast<Rio*>(entidad) != nullptr) {
		stop = true; 
		timer.reset();
	}
};