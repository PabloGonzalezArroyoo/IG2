#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <vector>
#include <list>
#include "objects/Molino.h"
#include "objects/Dron.h"
#include "objects/Avion.h"
#include "objects/Rio.h"
#include "objects/Sinbad.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
    virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    void checkCollisions();
    
    void gameControl();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

    virtual void frameRendered(const FrameEvent& evt);
        
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;    
    Ogre::SceneNode* mLightNode = nullptr;
    Ogre::SceneNode* mCamNode = nullptr;
    Ogre::SceneNode* mSinbadNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;
    
    // Pr�ctica 1 : Apartados 1 al 6
    // std::vector<Ogre::SceneNode*> hours;
    // Ogre::SceneNode* hoursNode = nullptr;
    // Ogre::SceneNode* clockNode = nullptr;
    // std::vector<Ogre::SceneNode*> hands;
    // Ogre::SceneNode* handNode;
    
    // Pr�ctica 1 : Apartados 7 al 12
    // Molino* molino = nullptr;
    // 
    // Pr�ctica 1 : Apartados 13 al 16
    // Dron* dron = nullptr;
    //
    // Pr�ctica 1 : Apartados 17 al 32
    // Molino* molino = nullptr;
    // Avion* avion = nullptr;
    // Rio* rio = nullptr;
    //
    // Pr�ctica 1 : Apartados 33 al 42
    // Avion* avion = nullptr;
    // bool automatic;
    // Dron* nodriza = nullptr;
    // std::list<Dron*> droncitos;
    // int numDroncitos = 400;
    // OgreBites::TextBox* dronsUI;
    // 
    // Pr�ctica 1 : Apartados 43 al 50
    Sinbad* sb = nullptr;
    Molino* molino = nullptr;
    Avion* avion = nullptr;
    Rio* rio = nullptr;
};

#endif
