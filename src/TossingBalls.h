#ifndef TOSSINGBALLS_H_
#define TOSSINGBALLS_H_

#define PATH_IMAGE string("data/images/")
#define PATH_LVL string("data/levels/")
#define PATH_SOUND string("data/sounds/")
#define PATH_GUI string("data/gui/")

//#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string>
#include <iostream>
#include <map>

#include "ICallbacks.h"
//#include "libdrawtext-0.1/src/drawtext.h"
#include "TBWindow.h"
#include "TBWorld.h"
#include "entities/TBDialog.h"
#include "Camera.h"
#include "IO.h"
#include "SoundLoader.h"
#include "utility.h"
#include "entities/TBText.h"

//typedef dtx_font* t_font;

enum E_GAME_STATE {
	EGS_intro,
	EGS_mainMenu,
	EGS_levelSelect,
	EGS_game
};

struct Timer {
	float msTimeToWait;
	float previous;
	float delta(float msCurrent) {
		return msCurrent - previous;
	}
	Timer() {
		msTimeToWait = 0;
		previous	 = 0;
	}
};

class TossingBalls : ICallbacks, b2ContactListener {
	public:
		TossingBalls();
		void StartGame();

	private:
		GLFWwindow* 	window;
		WindowData* 	data;

		// font
//		t_font 			junebug;
//		t_font			arial;

		// intro
		TBSprite* 		loadAnim;

		// razne zadeve
		std::vector<gEntity*> background; // ozadje, ki je sestavljeno iz ve�ih slik
		std::vector<gEntity*> path; // pot, po kateri je potovala '�oga'

		// svetlost
		int 			brightness;

		// kje se nahajamo v igri
		E_GAME_STATE 	gamePos;

		int    	mouseX; 			// pozicija mi�ke
		int    	mouseY; 			// pozicija mi�ke

		float  	scaleX; 			// razmerje med za�etno velikostjo zaslona in trenutno
		float  	scaleY; 			// razmerje med za�etno velikostjo zaslona in trenutno

		int    	defaultWidth;  		// privzeta dol�ina
		int    	defaultHeight; 		// privzeta vi�ina

		float  	cameraX; 			// pozicija kamere
		float  	cameraY; 			// pozicija kamere
		float  	cameraZ; 			// pozicija kamere

		double 	delta;   			// za koliko naj se kamera premakne na x-osi

		uint32 	cursorTexture; 		// tekstura kazalca
		uint32 	cursorClickTexture; // tekstura kazalca ob kliku
		uint32	pathTexture; 		// tekstura pik za pot

	private:
		// podatki za igro
		bool 	dragging; 			// premikanje levo / desno z mi�ko
		bool  	cannonRotation; 	// true ko rotiramo top
		bool  	fireInAHole; 		// ko ustrelimo je true
		bool	gameOver;			// ali je igre konec
		bool	victory; 			// true �e je igralec zmagal (false �e je zmanjkalo �og)
		bool 	freeze; 			// zamernemo igro (ob pritisku na esc in pa na za�etku igre dokler prikazujemo tekst)

		// timerji
		Timer 	shootingDelay; 		// premor med streli
		Timer 	intro; 				// koliko �asa traja intro
		Timer 	addPath; 			// vsake koliko �asa naj se doda to�ka pot

		// menuja
		std::vector<gEntity*> 	levelSelect;
		std::vector<gEntity*> 	mainMenu;
		std::string				onClick; 	// zvok ob kliku na gumb
		std::string				onClick2; 	// zvok ob mi�kinem kliku

		// teksti
//		TBText*			levelText;
//		TBText* 		enemiesText;
//
//		// dialogi
		TBDialog* 		dialogGameOver; 	// dialog v igri za izhod iz igre oz. nadaljevanje
//		TBText*			dialogText1; 		// tekst na dialogu (ali je igralec zmagal oz. izgubil)
		TBDialog*		dialogPause;		// dialog ob pritisku na esc v igri
//		TBText*			dialogText2;

		// mapa
		TBWorld   		context;
		WorldContext* 	world;
		// referenci iz TBWorld
		Camera* 		refCamera;
		b2World* 		refWorld;

		// �oge
		std::vector<TBBody*> 	tb;
		int 					current;

		int 					currentLevel;

	private:
		// implementacija ICallbacks
		virtual void SetupRC();
		virtual void OnLoop();
		virtual void OnRender();
		virtual void OnExit();

		virtual void OnResize(GLFWwindow* from, int width, int height);
		virtual void KeyboardEvent(GLFWwindow* from, int key, int scancode, int action, int mods);
		virtual void MouseEvent(GLFWwindow* from, int button, int action, int mods);
		virtual void MouseMove(GLFWwindow* from, double x, double y);
		virtual void OnScroll(GLFWwindow* from, double x, double y);

		// b2contactlistener
		void BeginContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
		void EndContact(b2Contact* contact);

		// static references to callback methods
		static void sKeyboardEvent(GLFWwindow* from, int key, int scancode, int action, int mods) {
  			instance->KeyboardEvent(from, key, scancode, action, mods);
		}
		static void sMouseEvent(GLFWwindow* from, int key, int action, int mods) {
			instance->MouseEvent(from, key, action, mods);
		}
		static void sMouseMove(GLFWwindow* from, double x, double y) {
			instance->MouseMove(from, x, y);
		}
		static void sOnResize(GLFWwindow* from, int width, int height) {
			instance->OnResize(from, width, height);
		}
		static void sOnScroll(GLFWwindow* from, double x, double y) {
			instance->OnScroll(from, x, y);
		}

	private:
		static TossingBalls* instance;
		double calcFPS(double, const std::string&);
		void   setProjection(bool);
		void   startGame(int);

	public:
		static TossingBalls* getInstance() { return instance; }
};

#endif /* TOSSINGBALLS_H_ */
