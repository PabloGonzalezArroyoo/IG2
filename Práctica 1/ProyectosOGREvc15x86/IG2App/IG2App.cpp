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
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  // RELOJ - nodo padre
  clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");

  // Objeto padre de toda las bolas que tiene como padre al reloj
  hoursNode = mSM->createSceneNode("hoursNode");
  clockNode->addChild(hoursNode);

  // Variable para los grados
  int degrees = 0;

  // Bucle de creación de bolas
  for (int i = 0; i < 12; i++) {
	  // Crear la entidad con el modelo de la esfera
	  Ogre::Entity* ent = mSM->createEntity("sphere.mesh");

	  // Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
	  Ogre::SceneNode* entNode = mSM->createSceneNode("Hora " + std::to_string(i + 1));
	  entNode->attachObject(ent);
	  entNode->setScale(0.5, 0.5, 0.5);

	  // Apartado 2: escala distinta según si es par o no
	  // (i % 2 == 0) ? entNode->setScale(0.5, 0.5, 0.5) : entNode->setScale(0.25, 0.25, 0.25);

	  // Posición de la bola según el grado que reperesenta
	  entNode->setPosition(Ogre::Math::Cos(Ogre::Math::AngleUnitsToRadians(degrees)) * 300, 
		Ogre::Math::Sin(Ogre::Math::AngleUnitsToRadians(degrees)) * 300, 0);

	  // Hacer este nodo hijo del padre creado anteriormente
	  hoursNode->addChild(entNode);

	  // Guardar nodo y continuar con el siguiente grado
	  hours.push_back(entNode);
	  degrees += 30;
  }

  handNode = mSM->createSceneNode("handNode");
  clockNode->addChild(handNode);

  Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
  // Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
  Ogre::SceneNode* entNode = mSM->createSceneNode("hourHandNode");
  entNode->attachObject(ent1);
  entNode->setScale(0.2, 2.8, 0.2);
  entNode->setPosition(0, 70, 0);
  handNode->addChild(entNode);
  entNode->roll(Ogre::Degree(-90));

  //Ogre::Entity* ent2 = mSM->createEntity("cube.mesh");
  //// Crear un nodo en la escena al cual se le agrega la entidad y se le cambia la escala
  //Ogre::SceneNode* entNode = mSM->createSceneNode("hourHandNode");
  //entNode->attachObject(ent1);
  //entNode->setScale(0.2, 2.8, 0.2);
  //entNode->setPosition(0, 70, 0);
  //handNode->addChild(entNode);

  //mSinbadNode->setPosition(400, 100, -300);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

