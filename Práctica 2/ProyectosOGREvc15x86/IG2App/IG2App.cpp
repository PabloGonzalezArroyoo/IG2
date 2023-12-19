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
  
	return true;
}

void IG2App::shutdown()
{
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
	//vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);
 
	//------------------------------------------------------------------------

	// finally something to render

	// ----------- APARTADOS 1 al 14 ----------
	#pragma region SinbadConLaCabezaDeOgre
	//vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
	
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

	// Sinbad
	SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	sb = new Sinbad(sinbadNode, Vector3(-650, -250, 250), 10, Vector3(0, 0, 0), WALKING, NONE);
	sb->createMovementAnimation(molinoNode->getPosition() - Vector3(300, 0, 0));
	addInputListener(sb);

	// Baliza
	SceneNode* balizaNode = mSM->getRootSceneNode()->createChildSceneNode();
	// baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(0.8, 0.8, 0.8), "practica2/naranja");
	// baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(0.8, 0.8, 0.8), "practica2/balizaTeselada");
	// baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(0.8, 0.8, 0.8), "practica2/balizaTeseladaZoom");
	// baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(0.8, 0.8, 0.8), "practica2/balizaEsponja");
	baliza = new Baliza(balizaNode, Vector3(0, -300, 0), Vector3(0.8, 0.8, 0.8), "practica2/balizaIluminadaVertex");
	addInputListener(baliza);
	
	// Añadir listeners
	baliza->addListener(rio);
	avion->addListener(sb);
	sb->addListener(baliza);

	// SkyPlane
	//mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "practica2/space", 1, 1, true, 1.0, 100, 100);
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "practica2/spaceSkyZoom", 0.8, 1, true, 1.0, 100, 100);
	#pragma endregion
	
	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);  
	
	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------
}

void IG2App::frameRendered(const FrameEvent& evt) {
	/*if (automatic) {
		OgreBites::KeyboardEvent key = OgreBites::KeyboardEvent();
		key.keysym.sym = SDLK_h;
		avion->keyPressed(key);
		checkCollisions();
	}*/
}