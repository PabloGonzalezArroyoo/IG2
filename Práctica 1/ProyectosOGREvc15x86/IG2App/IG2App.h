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
#include "objects/Avion.h"
#include "objects/Rio.h"
#include "objects/Sinbad.h"
#include "objects/Baliza.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener {
public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
    virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

    virtual void frameRendered(const FrameEvent& evt);
        
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;    
    Ogre::SceneNode* mLightNode = nullptr;
    Ogre::SceneNode* mCamNode = nullptr;
    Ogre::SceneNode* mSinbadNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;
    
    // Práctica 1 : Apartados 43 al 50
    Sinbad* sb = nullptr;
    Molino* molino = nullptr;
    Avion* avion = nullptr;
    Rio* rio = nullptr;
    Baliza* baliza = nullptr;
};

#endif
