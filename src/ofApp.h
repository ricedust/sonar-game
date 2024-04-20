#pragma once

#include "AgentSystem.h"
#include "AudioSystem.h"
#include "BulletSystem.h"
#include "CameraSystem.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "ControlSystem.h"
#include "EmitterSystem.h"
#include "FadeSystem.h"
#include "GameState.h"
#include "GuiSystem.h"
#include "InputSystem.h"
#include "LifespanSystem.h"
#include "PhysicsSystem.h"
#include "Player.h"
#include "RenderSystem.h"
#include "ScanSystem.h"
#include "Scene.h"
#include "ofMain.h"

const float viewportRadius{1080 / 2};

class ofApp : public ofBaseApp {
	GameState state{GameState::preGame};

	Scene scene{};

	InputSystem inputSystem{};
	CameraSystem cameraSystem{};
	GuiSystem guiSystem{scene};

	PhysicsSystem physicsSystem{scene};
	CollisionSystem collisionSystem{scene};
	FadeSystem fadeSystem{scene};
	RenderSystem renderSystem{scene};
	EmitterSystem emitterSystem{scene};
	LifespanSystem lifespanSystem{scene};

	ControlSystem controlSystem{scene, inputSystem};
	AgentSystem agentSystem{scene, collisionSystem};
	BulletSystem bulletSystem{scene};
	ScanSystem scanSystem{scene};

	EntityIndex playerIndex;
	EntityIndex enemyEmitterIndex;
	EntityIndex sonarIndex;
	EntityIndex compassIndex;
	EntityIndex bulletEmitterIndex;
	EntityIndex scannerIndex;

	void setupPlayer();
	void setupEnemyEmitter();
	void setupHud();
	void setupScanner();
	void setupBulletEmitter();

   public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
