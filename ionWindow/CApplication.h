#ifndef _CABBAGECOLLIDER_CAPPLICATION_H_INCLUDED_
#define _CABBAGECOLLIDER_CAPPLICATION_H_INCLUDED_

#include <ionCore.h>
#include <ionScene.h>
#include <ionGUI.h>

#include <SFML/Window.hpp>

class CEventManager;
class CStateManager;

class CApplication
{

    // Managers
    CEventManager * EventManager;
    CStateManager * StateManager;
    CSceneManager * SceneManager;
	CGUIEngine * GUIEngine;

    // Attributes
    SPosition2 WindowSize;

    // Helper functions
    void setupRenderContext();

    // Private ctor - singleton
    CApplication();

    float ElapsedTime;
	float RunTime;

    float Time0, Time1;

	bool Running;

	sf::Clock ApplicationClock;

public:

	sf::Window * App;

    static CApplication & get();

    void init(SPosition2 const & windowSize);

    CEventManager & getEventManager();
    CStateManager & getStateManager();
    CSceneManager & getSceneManager();
	CGUIEngine & getGUIEngine();

    void run();

	void updateTime();
    float const getElapsedTime() const;
    float const getRunTime() const;

    SPosition2 const & getWindowSize() const;
    static float const getAspectRatio();

    void skipElapsedTime();

	bool isShuttingDown() const;
	void close();

	void swapBuffers()
	{
		App->Display();
	}

};

#endif
