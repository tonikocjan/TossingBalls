#include "TossingBalls.h"
#include <vector>

TossingBalls* TossingBalls::instance = new TossingBalls();

bool validateCfg(const map<string, float>& cfg);

TossingBalls::TossingBalls() {
	IO::CreateLogFile();

	// nalo�imo cfg
	t_cfg cfg = IO::LoadCfg();
	if(!validateCfg(cfg)) {
		IO::AppendToLogFile("<error>Napaka pri nalaganju konfiguracijske datoteke!</error>");
		OnExit();
	}

	data = new WindowData("Tossing Balls - izdelek za maturo", cfg.at("width"), cfg.at("height"));

	context.world = new WorldContext(
			cfg.at("timeStep"),
			cfg.at("velIterations"),
			cfg.at("posIterations"),
			cfg.at("gravity"),
			cfg.at("width"),
			cfg.at("height"));

	// postavimo vse spremenljivke na privzete vrednosti
	gamePos   		= EGS_intro;
	refCamera 		= context.world->camera;
	refWorld  		= context.world->world;
	world	 		= context.world;
	cameraX 		= 0;
	cameraY 		= 0;
	cameraZ 		= 0;
	delta			= 0;
	current 		= 0;
	brightness		= 100;
	dragging 		= false;
	cannonRotation	= false;
	fireInAHole 	= false;
	scaleX = scaleY = 1;
	defaultHeight	= 600;
	defaultWidth	= 950;
	gameOver 		= false;
	freeze			= false;

	shootingDelay.msTimeToWait	= 4000;
	intro.msTimeToWait 			= 200;
	addPath.msTimeToWait 		= 500;
	//_____________________________________________________

	SetupRC();

	{
		// intro
		loadAnim = new TBSprite(data->getWidth() * 0.5, data->getHeight() * 0.5, 5, 50, 50, 0);
		TBImageAnimator* anim = new TBImageAnimator();
		anim->setLoop(true);
		anim->setFPS(8);
		anim->createAnimation(PATH_IMAGE + "loading.png", 8);
		loadAnim->setAnimator(anim);
	}

	// NALO�IMO VSE ZADEVE ZA IGRO
	IO::AppendToLogFile("Scale factor: " + NumberToString(1));

	// load level select menu
	IO::loadGUIFromXML(levelSelect, "data/gui/levelSelect.lvl.xml", refCamera, 1);
	if(levelSelect.size() > 0)
		IO::AppendToLogFile("Grafi�ni vmesnik: \"<i>levelSelect.lvl</i>\" uspe�no nalo�en!");
	else
		IO::AppendToLogFile("<error>Napaka pri odpiranju datoteke: \"<i>levelSelect.lvl</i>\"</error>");

	// load main menu
	IO::loadGUIFromXML(mainMenu, "data/gui/mainMenu.lvl.xml", refCamera, 1);
	if(mainMenu.size() > 0)
		IO::AppendToLogFile("Grafi�ni vmesnik: \"<i>mainMenu.lvl</i>\" uspe�no nalo�en!");
	else
		IO::AppendToLogFile("<error>Napaka pri odpiranju datoteke: \"<i>mainMenu.lvl</i>\"</error>");

    // nastavimo mi�kin kazalec
    if(!cfg.at("showCursor"))
    	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    cursorTexture 		= TextureLoader::LoadTex(PATH_IMAGE + "cursor.png");
    cursorClickTexture 	= TextureLoader::LoadTex(PATH_IMAGE + "cursor2.png");

    // nalo�imo zvoke
//	SoundSample::Init();
//	SoundSample::LoadSound(PATH_SOUND + "intro2.wav", true);
//	SoundSample::LoadSound(PATH_SOUND + "onClick.wav");
//	SoundSample::LoadSound(PATH_SOUND + "onClick2.wav");
//	SoundSample::LoadSound(PATH_SOUND + "fire.wav");
//
//	if(!(arial = dtx_open_font("C:/WINDOWS/fonts/Arial.ttf", 20))) {
//		IO::AppendToLogFile("<error> Font ni bil nalo�en!</error>");
//	}
//	if(!(junebug = dtx_open_font("data/junebug.ttf", 100))) {
//		IO::AppendToLogFile("<error> Font ni bil nalo�en!</error>");
//	}

	// kreiramo dialog (ob koncu igre)
	{
		uint32 texture = TextureLoader::LoadTex(PATH_IMAGE + "dialog.png");

		dialogGameOver = new TBDialog(data->getWidth() / 2, data->getHeight() / 2, 10, 400, 220, texture);
		dialogGameOver->setVisible(false);
		// dodamo dva gumba in tekst
		gButton* reload, *next; // ponovno nalo�i isti level ali pa pojdi na naslednjega
		reload 		= new gButton(130, 70, 20, 60, 60, 0);
		next 		= new gButton(230, 70, 20, 60, 60, 0);
//		dialogText1 = new TBText(280, 170, 20, 20, 0, 0, TBColor3f::Black, arial);
//		dialogText1->setText("Congratulations!");

		dialogGameOver->addChild(next);
		dialogGameOver->addChild(reload);
//		dialogGameOver->addChild(dialogText1);

		// kreiramo dialog (pavza)
		dialogPause = new TBDialog(data->getWidth() / 2, data->getHeight() / 2, 10, 400, 220, texture);
		dialogPause->setVisible(false);
		// dodamo dva gumba in tekst
		gButton* back; // ponovno nalo�i isti level ali pa pojdi na naslednjega
		reload 		= new gButton(130, 70, 20, 60, 60, 0);
		back 		= new gButton(230, 70, 20, 60, 60, 0);
//		dialogText2 = new TBText(200, 200, 20, 20, 0, 0, TBColor3f::Black, arial);
//		dialogText2->setText("Pause");

		dialogPause->addChild(back);
		dialogPause->addChild(reload);
//		dialogPause->addChild(dialogText2);
	}
}

void TossingBalls::StartGame() {
	// limitiramo fps-je
	const float fps = 4000;
	float msTimeToWait = 1 / fps * 1000;
	float previous = 0;

    while (!glfwWindowShouldClose(window)) {
    	float msTime = glfwGetTime() * 1000;
		float delta = msTime - previous;

		if(delta > msTimeToWait) {
			calcFPS(0.1, data->getName());
			OnLoop();
			OnRender();

		//	glfwSwapInterval(1);
			glfwSwapBuffers(window);
			glfwPollEvents();
			previous = msTime;
		}
    }
    OnExit();
}

void TossingBalls::SetupRC() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
        IO::AppendToLogFile("<error>Napaka pri inicializaciji GLFW!</error>");
    }

    window = glfwCreateWindow(defaultWidth, defaultHeight, data->getName().c_str(), NULL, NULL);
    OnResize(window, data->getWidth(), data->getHeight());

	IO::AppendToLogFile("�irina okna: " + NumberToString(data->getWidth()) +
						"\nVi�ina okna: " + NumberToString(data->getHeight()) +
						"\nIme: " + data->getName());

    if (!window)
    {
        IO::AppendToLogFile("<error>Napaka pri inicializaciji GLFW!</error>");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    IO::AppendToLogFile("GLFW uspe�no inicializiran!");

    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 100, 100);
    glfwSetMouseButtonCallback(window, sMouseEvent);
    glfwSetCursorPosCallback(window, sMouseMove);
    glfwSetWindowSizeCallback(window, sOnResize);
    glfwSetKeyCallback(window, sKeyboardEvent);
    glfwSetScrollCallback(window, sOnScroll);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

    glViewport(0, 0, data->getWidth(), data->getHeight());
    setProjection(false);

    IO::AppendToLogFile("OpenGL uspe�no inicializiran!");

//	if(SDL_Init(SDL_INIT_AUDIO) != 0) IO::AppendToLogFile("<error>Neuspe�na inicializacija SDL: " + string(SDL_GetError()) + "</error>");
//	else							  IO::AppendToLogFile("SDL uspe�no inicializiran!");
}

void TossingBalls::OnResize(GLFWwindow* from, int width, int height) {
	data->setSize(width, height);
	refCamera->screenMax.x = width;
	refCamera->screenMax.y = height;

    glViewport(0, 0, width, height);
    setProjection(false);

	// izra�unamo faktor za katerega se je okno pove�alo oz. zmanj�alo
	// ta faktor uporabimo pri premikanju mi�ke
	scaleX = (float)width  / (float)defaultWidth;
	scaleY = (float)height / (float)defaultHeight;
}

void TossingBalls::OnRender() {
	// DRAWING STUFF
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();

	switch(gamePos) {
	case EGS_intro: {
		loadAnim->Render(0, 0);
		break;
	}
	case EGS_mainMenu: {
		constIter it;
		for(it = mainMenu.begin(); it != mainMenu.end(); it++)
			(*it)->Render(0.0, refCamera);
		break;
	}
	case EGS_levelSelect: {
		constIter it;
		for(it = levelSelect.begin(); it != levelSelect.end(); it++)
			(*it)->Render(0.0, refCamera);

		break;
	}
	case EGS_game: {
		setProjection(false);

		dialogGameOver->Render(0, 0);
		dialogPause->Render(0, 0);

		// nari�emo ozadje
		constIter it;
		for(it = background.begin(); it != background.end(); it++)
			(*it)->Render(0, 0);

		// nari�emo tekst ob za�etku igre
//		levelText->Render(0, 0);

		// tekst - �tevilo nasprotnikov
//		enemiesText->Render(0, 0);

		glPushMatrix();
			setProjection(true);

			// premaknemo kamero (oz. sceno)
			glTranslatef(-cameraX, -cameraY, -cameraZ);

			// nari�emo pot
			for(it = path.begin(); it != path.end(); it++) {
				(*it)->Render(0, 0);
			}

			world->cannon->Render(0, refCamera);

			// nari�emo vsa telesa
			for(it = world->container.begin(); it != world->container.end(); it++)
				(*it)->Render(glfwGetTime(), refCamera);

		glPopMatrix();
		break;
	}
	}

	// nari�emo mi�kin kazaec
	setProjection(false);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (dragging) ? cursorClickTexture : cursorTexture);
		glColor3f(0,0,0);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(mouseX, mouseY - 53, 100);
			glTexCoord2f(1.0, 0.0); glVertex3f(mouseX + 40, mouseY - 53, 100);
			glTexCoord2f(1.0, 1.0); glVertex3f(mouseX + 40, mouseY, 100);
			glTexCoord2f(0.0, 1.0); glVertex3f(mouseX, mouseY, 100);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void TossingBalls::OnLoop() {
//	SDL_PauseAudio(0);

	if(gamePos == EGS_intro) {
		loadAnim->Update(glfwGetTime());
		if(intro.delta(glfwGetTime() * 1000) > intro.msTimeToWait) {
			delete loadAnim;
			gamePos = EGS_mainMenu;
//			SoundSample::PlaySound(PATH_SOUND + "intro2.wav");
		}
	}
	else if(gamePos == EGS_mainMenu) {
		constIter it;
		for(it = mainMenu.begin(); it != mainMenu.end(); it++) {
			(*it)->MouseOver(mouseX, mouseY);
			(*it)->Update(glfwGetTime());
		}
	}
	else if(gamePos == EGS_levelSelect) {
		constIter it;
		for(it = levelSelect.begin(); it != levelSelect.end(); it++) {
			(*it)->MouseOver(mouseX, mouseY);
			(*it)->Update(glfwGetTime());
		}
	}
	else if(gamePos == EGS_game) {
		// tekst
//		levelText->Update(glfwGetTime());
//		if(!levelText->getVisible()) freeze = false;

		dialogGameOver->Update(glfwGetTime());
		dialogGameOver->MouseOver(mouseX, mouseY);

		dialogPause->Update(glfwGetTime());
		dialogPause->MouseOver(mouseX, mouseY);

		if(true) {

			// -------------------------------------- Kamera ----------------------------------------------
			if(fireInAHole) {
				// kamera sledi �ogi
				cameraX = (tb[current]->getX() * refCamera->scaleWorldToScreen.x) - data->getWidth();
			}

			// premaknemo camero (drsenje levo / desno z mi�ko)
			if(delta != 0 && !freeze && !gameOver) {
				cameraX += delta;
				delta = 0;
			}

			// kadar kamera ni na njenem privzetem mestu, jo premaknemo tja
			const float max = -2000.0;

			// kamera naj ne gre preko roba mape
			if(cameraX <= max) cameraX = max;
			else if (cameraX >= 600) cameraX = 600;
			// -------------------------------------- Kamera ----------------------------------------------


			// --------------------------------- Posodabljanje objektov -----------------------------------
			// naslednji korak v fiziki
			world->world->Step(world->timeStep, world->velocityIterations, world->positionIterations);

			// posodobimo lokacijo teles
			constIter it_ = world->container.begin();
			while (it_ != world->container.end()) {
				TBBody* b;
				b = static_cast<TBBody*>(*it_);
				b->Update(glfwGetTime());

				// �e ima telo 0 hp ga uni�imo
				if(b->hp <= 0)
					world->disposeBodies.push_back(b);

				it_++;
			}

			// posodobi top
			if(cannonRotation) {
				int x = mouseX + (cameraX - world->cannon->getX());
				int y = mouseY - 225;
				//(world->cannon->getHeight() + world->cannon->getH2() / 2 + world->groundBody->getHeight());

				double angle = (double)y / (double)x;
				angle = atan(angle);
				if(angle < 0.0) angle += M_PI;
				angle = angle * TODEGREES;
				world->cannon->setAngle(angle);

				// za�etna pozicija �oge
				int xp, yp;
				xp = world->cannon->getW2() * cos(world->cannon->getAngle() * TORAD);
				xp = xp + world->cannon->getX();
				yp = world->cannon->getW2() * sin(world->cannon->getAngle() * TORAD);
				yp += world->cannon->getY2();

				b2Vec2 a(xp, yp);
				a = refCamera->screenToWorld(a);

				tb[current]->setBodyPosition(a.x, a.y, angle * TORAD);
			}

			if(fireInAHole) {
				float delta = shootingDelay.delta(glfwGetTime() * 1000);
				if(delta > shootingDelay.msTimeToWait) {
					fireInAHole = false;
					// na vrsti je naslednja �oga
					current++;
					if(current >= world->countBalls && world->countEnemies != 0)
						gameOver = true;
				}

				// dodajamo pot
				if(addPath.delta(glfwGetTime() * 1000) > addPath.msTimeToWait / abs(tb[current]->getBody()->GetLinearVelocity().x)) {
					addPath.previous = glfwGetTime() * 1000;

					b2Vec2 pos(tb[current]->getX(), tb[current]->getY());
					pos = refCamera->worldToScreen(pos);
					path.push_back(new TBSprite(pos.x, pos.y, 10, 15, 15, pathTexture));
				}
			}
			// --------------------------------- Posodabljanje objektov -----------------------------------


			// ------------------------------------ Logika igre -------------------------------------------
			iter it = world->disposeBodies.begin();
			iter end = world->disposeBodies.end();
			while(it != end) {
				gEntity* dyingEntity = *it;
				bool enemy = (dyingEntity->getType() == EBT_enemy);

				//... and remove it from main list of balls
				iter it_ = std::find(world->container.begin(), world->container.end(), dyingEntity);
				if ( it_ != world->container.end() )
				  world->container.erase(it_);

				//delete ball... physics body is destroyed here
				delete dyingEntity;

				++it;

				// zmanj�amo �tevilo nasprotnikov in posodobimo tekst
				if(enemy) {
//					enemiesText->setText("Stevilo nasprotnikov: " + NumberToString(--world->countEnemies));

					// �e je �tevilo nasprotnikov enako ni� je konec igre
					if(world->countEnemies == 0) {
						gameOver = true;
						victory  = true;
						dialogGameOver->setVisible(true);
					}
				}
			}
			world->disposeBodies.clear();
			// ------------------------------------ Logika igre -------------------------------------------
		}

	}
}

void TossingBalls::OnExit() {
    glfwDestroyWindow(window);
    glfwTerminate();
    // izbri�emo log datoteko
    IO::DeleteLogFile();
    exit(EXIT_SUCCESS);
}

void TossingBalls::KeyboardEvent(GLFWwindow* from, int key, int scancode, int action, int mods) {
	// v level selectu se ob kliku na ESC vrnemo v glavni meni
	if (gamePos == EGS_levelSelect) {
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			gamePos = EGS_mainMenu;
	}
	//
	else if(gamePos == EGS_game) {
		if(gameOver) return;

		if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
			freeze = !freeze;
			dialogPause->setVisible(freeze);
		}
		if(action == GLFW_PRESS && GLFW_KEY_SPACE == key) {
			if(!fireInAHole) {
				cannonRotation = true;
			}
		}
		else if(action == GLFW_RELEASE && GLFW_KEY_SPACE == key) {
			cannonRotation = false;
		}
		else if(action == GLFW_PRESS && key == GLFW_KEY_ENTER) {
			// ustreli
			if(!fireInAHole) {
//				SoundSample::PlaySound(PATH_SOUND + "fire.wav");
				fireInAHole = true;

				// vr�emo �ogo pod dolo�enim kotom z dolo�eno silo
				float angle = world->cannon->getAngle();
				const int power = 300;
				b2Vec2 x(cos(angle * TORAD), sin(angle * TORAD));
				x.x *= power;
				x.y *= power;

				tb[current]->getBody()->SetType(b2_dynamicBody);
				tb[current]->getBody()->ApplyLinearImpulse(x, tb[current]->getBody()->GetWorldCenter(), true);

				shootingDelay.previous = glfwGetTime() * 1000;
			}
		}
	}
}

void TossingBalls::MouseEvent(GLFWwindow* from, int button, int action, int mods) {
	bool buttonClick = false;
	if(gamePos == EGS_intro) {

	}
	else if(gamePos == EGS_mainMenu) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			// play
			if(mainMenu[2]->MouseOver(mouseX, mouseY)) {
				gamePos = EGS_levelSelect;
//				SoundSample::PlaySound(PATH_SOUND + "onClick.wav");
				buttonClick = true;
			}
			// settings
			else if(mainMenu[3]->MouseOver(mouseX, mouseY)) {
				gamePos = EGS_levelSelect;
//				SoundSample::PlaySound(PATH_SOUND + "onClick.wav");
				buttonClick = true;
			}
			// exit
			if(mainMenu[4]->MouseOver(mouseX, mouseY)) {
				buttonClick = true;
				OnExit();
			}
		}
	}
	else if(gamePos == EGS_levelSelect) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			constIter it;
			int i = -1;

			for(it = levelSelect.begin(); it != levelSelect.end(); it++) {
				if ((*it)->MouseOver(mouseX, mouseY)) {
//					SoundSample::PlaySound(PATH_SOUND + "onClick.wav");
					buttonClick = true;
					// nazaj v glavni meni
					if(i == 10) {
						gamePos = EGS_mainMenu;
					}
					// selecting level
					else {
						gamePos = EGS_game;
						currentLevel = i;
						startGame(i);
					}
				}
				i++;
			}
		}
	}
	else if(gamePos == EGS_game && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		// gumbi v dialogGameOveru
		if(dialogGameOver->getVisible()) {
			// ponovno igraj isti level
			if(dialogGameOver->getClickedChild() == 2) {
				startGame(currentLevel);
				dialogGameOver->setVisible(false);
			}
			// naslednji level
			else if(dialogGameOver->getClickedChild() == 1) {
				currentLevel++;
				startGame(currentLevel);
				dialogGameOver->setVisible(false);
			}
		}
		// gumbi v dilaogPause
		else if(dialogPause->getVisible()) {
			// nazaj v level select
			if(dialogPause->getClickedChild() == 2) {
				gamePos = EGS_levelSelect;
				dialogPause->setVisible(false);
			}
			// ponovno nalo�i level
			else if(dialogPause->getClickedChild() == 1) {
				startGame(currentLevel);
				dialogPause->setVisible(false);
			}
		}
	}

	if(action == GLFW_PRESS) {
		dragging = true;
	}
	else {
		dragging = false;
	}

	// v primeru, da ni bil pritisnjen noben gumb in nismo v 'igri'
	// predvajamo zvok mi�kinega klika
//	if(!buttonClick && action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
//		SoundSample::PlaySound(PATH_SOUND + "onClick2.wav");
}

void TossingBalls::MouseMove(GLFWwindow* from, double x, double y) {
	x /= scaleX;

	if(dragging && gamePos == EGS_game && !cannonRotation) {
		double d = mouseX - x;
		float zoom = 1;
		delta = d * zoom;
	}

	mouseX = x;
	mouseY = (data->getHeight() - y);
	mouseY /= scaleY;
}

void TossingBalls::OnScroll(GLFWwindow* from, double x, double y) {
	if(gamePos != EGS_game) return;

	if(y == 1)
		refCamera->zoomIn();
	else if(y == -1)
		refCamera->zoomOut();
}

/// SOURCE: http://r3dux.org/2012/07/a-simple-glfw-fps-counter/
double TossingBalls::calcFPS(double theTimeInterval, const string& theWindowTitle)
{
	// Static values which only get initialised the first time the function runs
	static double t0Value       = glfwGetTime(); // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps           = 0.0;           // Set the initial FPS value to 0.0

	// Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// If the user specified a window title to append the FPS value to...
		if (theWindowTitle != "NONE")
		{
			// Convert the fps value into a string using an output stringstream
			std::ostringstream stream;
			stream << " FPS | ";
			stream << fps;
			std::string fpsString = stream.str();

			// Append the FPS value to the window title details
			string x = theWindowTitle + fpsString;

			// Convert the new window title to a c_str and set it
			glfwSetWindowTitle(window, x.c_str());
		}
		else // If the user didn't specify a window to append the FPS to then output the FPS to the console
		{
			std::cout << "FPS: " << fps << std::endl;
		}

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}

void TossingBalls::startGame(int n) {
	// resetiramo vse zadeve
	world->resetWorld();
	path.clear();
	tb.clear();

	gameOver = false;
	freeze 	 = false;
	refWorld = world->world;
	current  = 0;
	refWorld->SetContactListener(this);
	//-----------------------------

	pathTexture = TextureLoader::LoadTex(PATH_IMAGE + "path.png");

	// ustavi uvodno pesem
//	SoundSample::StopSound(PATH_SOUND + "intro2.wav");

	// pot do levela
	string level = "data/levels/level" + NumberToString(n) + ".xml";

	// nalo�i level
	if(IO::loadLevelFromXML(context, level, refCamera, context.world->countBalls))
		IO::AppendToLogFile("Level: \"<i>" + level + "</i>\" uspe�no nalo�en");
	else
		IO::AppendToLogFile("<error>Napaka! Datoteka: \"<i>" + level + "</i>\" ne obstaja!");

	// kreiramo tekst za ob za�etku levela
//	levelText = new TBText(
//			data->getWidth() / 2,
//			data->getHeight() / 2,
//			9,
//			100, 0, 0,
//			TBColor3f(0.4, 0.9, 0.33),
//			junebug);
//	levelText->setText("level " + NumberToString(n));
//
//	TBAnimator* anim = new TBFadeAnimator(100, 5, 2000);
//	levelText->setAnimator(anim);
//	anim = new TBStopAnimator(3000);
//	levelText->setAnimator(anim);

	// koliko je nasprotnikov
//	enemiesText = new TBText(
//			300, 500, 9, 20, 0, 0, TBColor3f::Blue, arial);
//	enemiesText->setText("Stevilo nasprotnikov: " + NumberToString(world->countEnemies));

	int width = 5000;
	int position = 500;

	// kreiraj tla
	world->groundBody = context.createGroundObject(
			TBColor3f::Blue,
			position * refCamera->scaleScreenToWorld.x,
			0,
			refCamera->scaleScreenToWorld.x * width,
			refCamera->scaleScreenToWorld.y * 200);

	// kreairaj top
	int w = 280;
	int h = 100;
	int x = -600;
	int y = h + 50;

	uint32 tex1 = TextureLoader::LoadTex("data/images/cannon1.png");
	uint32 tex2 = TextureLoader::LoadTex("data/images/cannon2.png");

	world->cannon = new TBCannon(x, y, 5, w, h, x + 150, y + 70, 380, 60, tex2, tex1);
	world->cannon->setAngle(0);

	// nalo�imo teksturo za '�ogo'
	tex2 = TextureLoader::LoadTex(PATH_IMAGE + "to-normal.png");

	// kreiramo �oge
	b2Vec2 s(80, 80);
	s = refCamera->screenToWorld(s);

	context.world->countBalls = 4;
	for(int i = 0; i < context.world->countBalls; i++) {
		b2Vec2 pos(x - 200 - (i * 100), 155);
		pos = refCamera->screenToWorld(pos);

		TBBody* e = context.createSphere(pos.x, pos.y, 2, s.x, s.y, EBT_tossingBall, tex2, false);
		TBBlinkAnimator* anim = new TBBlinkAnimator(PATH_IMAGE + "to-blink.png");
		e->setAnimator(anim);

		tb.push_back(e);
	}

	// tla in ozadje (oblaki)

	// kreiramo ozadje za tla
	// tla so sestavljena iz ve�ih slik, ena za drugo
	b2Vec2 size(480, 200);
	int count = width / size.x; // dol�ina tal : dol�ina teksture
	uint32 tex = TextureLoader::LoadTex(PATH_IMAGE + "ground.png");
	for(int i = 0; i <= count; i++) {
		b2Vec2 pos(-2000 + (i * size.x) - 10, 0);
		context.createSprite(pos.x, pos.y, 2, size.x + 1, size.y, 0, tex);
	}

	// kreiramo �e oblake
	b2Vec2 s2(280 * 2, 213 * 2);
	y = data->getHeight() - s2.y / 2;
	count = width / s2.x;
	tex = TextureLoader::LoadTex(PATH_IMAGE + "clouds.png");
	for(int i = 0; i < count; i++) {
		b2Vec2 pos(-2000 + (i * s2.x), y);
		TBSprite* s = new TBSprite(pos.x, pos.y, 0, s2.x, s2.y, tex);
		background.push_back(s);
	}
}

void TossingBalls::setProjection(bool zoom) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(!zoom) {
		glOrtho(refCamera->screenMin.x,
				refCamera->screenMax.x,
				refCamera->screenMin.y,
				refCamera->screenMax.y,
				-100.0, 100.0);
	}
	else {
		glOrtho(refCamera->screenMinInWorld.x,
				refCamera->screenMaxInWorld.x,
				refCamera->screenMinInWorld.y,
				refCamera->screenMaxInWorld.y,
				-100.0, 100.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void TossingBalls::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();

	TBBody* a = static_cast<TBBody*>(body1->GetUserData());
	TBBody* b = static_cast<TBBody*>(body2->GetUserData());

	if(a && b) {

//		if(a->getType() == EBT_enemy && b->getType() == EBT_tossingBall) {
//			world->disposeBodies.push_back(a);
//		}
//		else if(b->getType() == EBT_enemy && a->getType() == EBT_tossingBall) {
//			world->disposeBodies.push_back(b);
//		}

		if(a->getType() != EBT_groundObject) {
			a->collision = true;
		}
		if(b->getType() != EBT_groundObject) {
			b->collision = true;
		}
	}
}

void TossingBalls::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void TossingBalls::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();

	TBBody* a = static_cast<TBBody*>(body1->GetUserData());
	TBBody* b = static_cast<TBBody*>(body2->GetUserData());

	if(a && b) {
		if(a->collision) {
			a->force = impulse->normalImpulses[0];
			a->collision = false;
		}
		if(b->collision) {
			b->force = impulse->normalImpulses[0];
			b->collision = false;
		}
	}
}

void TossingBalls::EndContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();

	TBBody* a = static_cast<TBBody*>(body1->GetUserData());
	TBBody* b = static_cast<TBBody*>(body2->GetUserData());

	if(a && b) {

		if(a->getType() != EBT_tossingBall)
			a->hp -= a->force;
		if(b->getType() != EBT_tossingBall)
			b->hp -= b->force;

		a->force = b->force = 0;

		// zvok
//		SoundSample::PlaySound(PATH_SOUND + a->getOnImpactSound());
//		SoundSample::PlaySound(PATH_SOUND + b->getOnImpactSound());
	}
}

// preveri, ali cfg datoteka vsebuje vse podatke
inline bool validateCfg(const map<string, float>& cfg) {
	if(cfg.find("height") == cfg.end()) return false;
	if(cfg.find("width") == cfg.end()) return false;
	if(cfg.find("timeStep") == cfg.end()) return false;
	if(cfg.find("velIterations") == cfg.end()) return false;
	if(cfg.find("posIterations") == cfg.end()) return false;
	return true;
}

