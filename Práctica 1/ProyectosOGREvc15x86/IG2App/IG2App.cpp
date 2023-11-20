#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	//else if (evt.keysym.sym == SDLK_???)

	// ----------- APARTADOS 1 al 6 -----------
	#pragma region Reloj
	/*else if (evt.keysym.sym == SDLK_g) {
		clockNode->roll(Ogre::Degree(-2));
	}
	else if (evt.keysym.sym == SDLK_h) {
		hoursNode->roll(Ogre::Degree(-2));
	}*/
		#pragma endregion
	
	// ----------- APARTADOS 32 al 42 -----------
	#pragma region Drones
	/*else if (evt.keysym.sym == SDLK_a) automatic = !automatic;

	else if (evt.keysym.sym == SDLK_h && !automatic) checkCollisions();*/
	#pragma endregion

  
	return true;
}

void IG2App::shutdown()
{
	// Práctica 1 : Apartados 7 al 12
	// delete molino; molino = nullptr;

	// Práctica 1 : Apartados 13 al 16
	// delete dron; dron = nullptr;

	mShaderGenerator->removeSceneManager(mSM);  
	mSM->removeRenderQueueListener(mOverlaySystem);  
					
	mRoot->destroySceneManager(mSM);  

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	srand((unsigned)time);
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();  

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);

	#pragma region Drones
	//dronsUI = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "DronesWidget", "Droncitos vivos", 200, 100);
	//dronsUI->appendText(std::to_string(numDroncitos));
	//dronsUI->setTextAlignment(TextAreaOverlayElement::Center);

	//// Control automatico del avion desactivado
	//automatic = false;
	#pragma endregion

	addInputListener(mTrayMgr);

	addInputListener(this);   
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1); 
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
	
	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);
 
	//------------------------------------------------------------------------

	// finally something to render

	// ----------- APARTADOS 1 al 6 -----------
	#pragma region Reloj
	 //// RELOJ - nodo padre
	 //clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");

	 //// Objeto padre de toda las bolas que tiene como padre al reloj
	 //hoursNode = mSM->createSceneNode("hoursNode");
	 //clockNode->addChild(hoursNode);

	 //// Variable para los grados
	 //int degrees = 0;

	 //// Bucle de creación de bolas
	 //for (int i = 0; i < 12; i++) {
	 // // Crear la entidad con el modelo de la esfera
	 // Ogre::Entity* ent = mSM->createEntity("sphere.mesh");

	 // // Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
	 // Ogre::SceneNode* entNode = mSM->createSceneNode("Hora " + std::to_string(i + 1));
	 // entNode->attachObject(ent);
	 // entNode->setScale(0.4, 0.4, 0.4);

	 // // Apartado 2: escala distinta según si es par o no
	 // // (i % 2 == 0) ? entNode->setScale(0.5, 0.5, 0.5) : entNode->setScale(0.25, 0.25, 0.25);

	 // // Posición de la bola según el grado que reperesenta
	 // entNode->setPosition(Ogre::Math::Cos(Ogre::Math::AngleUnitsToRadians(degrees)) * 350,
		//  Ogre::Math::Sin(Ogre::Math::AngleUnitsToRadians(degrees)) * 350, 0);

	 // // Hacer este nodo hijo del padre creado anteriormente
	 // hoursNode->addChild(entNode);

	 // // Guardar nodo y continuar con el siguiente grado
	 // hours.push_back(entNode);
	 // degrees += 30;
	 //}

	 //handNode = mSM->createSceneNode("handNode");
	 //clockNode->addChild(handNode);

	 //for (int i = 0; i < 3; i++) {
		//  hands.push_back(mSM->createSceneNode("hand" + std::to_string(i)));
		//  hands[i]->setPosition(0, 0, 0);
		//  handNode->addChild(hands[i]);
	 //}


	 //Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
	 //// Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
	 //Ogre::SceneNode* entNode = mSM->createSceneNode("hourHandNode");
	 //entNode->attachObject(ent1);
	 //entNode->setScale(0.2, 1.4, 0.2);
	 //entNode->setPosition(0, 50, 0);
	 //hands[0]->addChild(entNode);
	 //hands[0]->roll(Ogre::Degree(-90));


	 //Ogre::Entity* ent2 = mSM->createEntity("cube.mesh");
	 //// Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
	 //entNode = mSM->createSceneNode("minHandNode");
	 //entNode->attachObject(ent2);
	 //entNode->setScale(0.15, 2.75, 0.15);
	 //entNode->setPosition(0, 100, 0);
	 //hands[1]->addChild(entNode);

	 //Ogre::Entity* ent3 = mSM->createEntity("cube.mesh");
	 //// Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
	 //entNode = mSM->createSceneNode("segHandNode");
	 //entNode->attachObject(ent3);
	 //entNode->setScale(0.05, 3.25, 0.05);
	 //entNode->setPosition(0, 120, 0);
	 //hands[2]->addChild(entNode);
	 //hands[2]->roll(Ogre::Degree(-225));
	#pragma endregion

	// ----------- APARTADOS 6 al 12 ----------
	#pragma region Molino
	/*SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode();
	molino = new Molino(molinoNode);
	addInputListener(molino);*/
	#pragma endregion

	// ----------- APARTADOS 13 al 16 ----------
	#pragma region RotorDron
	/*SceneNode* dronNode = mSM->getRootSceneNode()->createChildSceneNode();
	dron = new Dron(dronNode, Vector3(0, 0, 0), 1, DronType::ORIGINAL);
	addInputListener(dron);*/
	#pragma endregion

	// ----------- APARTADOS 17 al 32 ----------
	#pragma region Avion
	//// Río
	//SceneNode* rioNode = mSM->getRootSceneNode()->createChildSceneNode();
	//rio = new Rio(rioNode, "prueba", 900, 500);
	//rioNode->translate(Vector3(0, -300, 0));
	//addInputListener(rio);

	//// Molino
	//SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode();
	//molino = new Molino(molinoNode);
	//addInputListener(molino);
	//molinoNode->translate(Vector3(0, 0, -400));

	//// Avion
	//SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
	//avion = new Avion(avionNode, rioNode->getPosition(), 0.2);
	//addInputListener(avion);

	//// Añadir listeners
	//rio->addListener(molino);
	//rio->addListener(avion);
	//molino->addListener(rio);
	#pragma endregion

	// ----------- APARTADOS 33 al 42 ----------
	#pragma region Droncitos
	//// Planeta
	//Entity* esf = mSM->createEntity("sphere.mesh");
	//esf->setMaterialName("cyan");
	//SceneNode* planet = mSM->getRootSceneNode()->createChildSceneNode();
	//planet->attachObject(esf);
	//planet->setScale(4, 4, 4);
	//Vector3 pPos = planet->getPosition();
	//Vector3 pOffset = Vector3(0, planet->getScale().x * 100, 0);

	//// Avion
	//SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
	//avion = new Avion(avionNode, pPos, 0.125, pOffset, true);
	//addInputListener(avion);

	//// Nodriza
	//SceneNode* dronNode = mSM->getRootSceneNode()->createChildSceneNode();
	//nodriza = new Dron(dronNode, pPos, 0.04, DronType::MOTHER, 3, 3, pOffset);
	//addInputListener(nodriza);

	//// Droncitos
	//float divisions = 360.0f / numDroncitos;
	//for (int i = 0; i < numDroncitos; i++) {
	//	int random = rand() % 360;
	//	Dron* dr = new Dron(dronNode, pPos, 0.02, DronType::CHILD, 3, 3, pOffset);
	//	dr->rotateDrone(Vector3(90, divisions * i, 0));
	//	dr->rotateDrone(Vector3(0, random, 0));
	//	droncitos.push_back(dr);
	//	addInputListener(dr);
	//}
	#pragma endregion

	// ----------- APARTADOS 43 al 50 ----------
	#pragma region SinbadConLaCabezaDeOgre
	//// Planeta
	//Entity* esf = mSM->createEntity("sphere.mesh");
	//esf->setMaterialName("cyan");
	//SceneNode* planet = mSM->getRootSceneNode()->createChildSceneNode();
	//planet->attachObject(esf);
	//planet->setScale(4, 4, 4);
	//Vector3 pPos = planet->getPosition();
	//Vector3 pOffset = Vector3(0, planet->getScale().x * 100, 0);

	// Sinbad
	//SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	//sb = new Sinbad(sinbadNode, pPos, 10, pOffset);
	//sb->cambiaEspada();
	//addInputListener(sb);

	// Río
	SceneNode* rioNode = mSM->getRootSceneNode()->createChildSceneNode();
	rio = new Rio(rioNode, "prueba", 1500, 700);
	rioNode->translate(Vector3(0, -301, 0));
	addInputListener(rio);

	// Molino
	SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode();
	molino = new Molino(molinoNode);
	addInputListener(molino);
	molinoNode->translate(Vector3(600, 0, -200));

	// Avion
	SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
	avion = new Avion(avionNode, rioNode->getPosition(), 0.2, Vector3(500, 400,  0), true);
	addInputListener(avion);

	// Añadir listeners
	rio->addListener(molino);
	rio->addListener(avion);
	molino->addListener(rio);

	// Sinbad
	SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	sb = new Sinbad(sinbadNode, Vector3(-650, -250, 250), 10, Vector3(0, 0, 0), NOPLANET, WALKING, NONE);
	sb->createMovementAnimation(molinoNode->getPosition() - Vector3(300, 0, 0));
	addInputListener(sb);

	// Baliza
	SceneNode* balizaNode = mSM->getRootSceneNode()->createChildSceneNode();
	baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(15, 18, 15));
	addInputListener(baliza);
	#pragma endregion
	
	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);  
	
	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------
}

void IG2App::checkCollisions() {
	//AxisAlignedBox bAvion = avion->getCuerpoNode()->_getWorldAABB();

	//// Recorrer drones detectando colisiones con el avión
	//std::vector<std::list<Dron*>::iterator> dronsToDelete;
	//for (auto d = droncitos.begin(); d != droncitos.end(); d++) {
	//	Dron* dr = *d;
	//	AxisAlignedBox aabb = bAvion.intersection(dr->getCuerpoNode()->_getWorldAABB());
	//	if (!aabb.isNull() && dr->receiveDamage()) {
	//		dronsToDelete.push_back(d);
	//		gameControl();
	//	}
	//}

	//// Borrar memoria
	//for (auto d : dronsToDelete) {
	//	Dron* dr = *d;
	//	removeInputListener(dr);
	//	droncitos.erase(d);
	//	delete dr;
	//}
	//dronsToDelete.clear();
}

void IG2App::gameControl() {
	/*numDroncitos--;
	if (numDroncitos <= 0) nodriza->setSphereMaterial("yellow");
	dronsUI->setText(std::to_string(numDroncitos));*/
}

void IG2App::frameRendered(const FrameEvent& evt) {
	/*if (automatic) {
		OgreBites::KeyboardEvent key = OgreBites::KeyboardEvent();
		key.keysym.sym = SDLK_h;
		avion->keyPressed(key);
		checkCollisions();
	}*/
}