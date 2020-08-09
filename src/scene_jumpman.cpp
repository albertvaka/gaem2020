#include "scene_jumpman.h"
#include "input.h"
#ifdef _IMGUI
#include "imgui.h"
#endif
#include "bullet.h"
#include "enemy_door.h"
#include "assets.h"
#include "simplexnoise.h"
#include "parallax.h"
#include "bat.h"
#include "lava.h"
#include "savestation.h"
#include "debug.h"
#include "rototext.h"

extern float mainClock;

const float batClusterSize = 22.f;
const float chanceAngryBat = 0.2f;
const float camSpeed = 2000;

#ifdef _DEBUG
static int currentPlacingTile = 1;
#endif

const bool random_mode = false;

JumpScene::JumpScene()
{
	
}

void JumpScene::EnterScene() 
{

	int num_entities = 3000;
	for (int i = 0; i < num_entities; i++) {
		new EnemyDoor();
	}
}

void JumpScene::ExitScene()
{
	EnemyDoor::DeleteAll();
}

void callbackerino(EnemyDoor* a, EnemyDoor* b) {
	a->collide = true;
	b->collide = true;
}

void JumpScene::Update(float dt)
{
	for (EnemyDoor* ed : EnemyDoor::GetAll()) {
		ed->collide = false;
	}
	CollideSelf(EnemyDoor::GetAll(), callbackerino);
	for ( EnemyDoor* ed : EnemyDoor::GetAll()) {
		ed->Update(dt);
	}
}

void JumpScene::Draw()
{
	Window::Clear(0, 0, 0);

	for (const EnemyDoor* ed : EnemyDoor::GetAll()) {
		ed->Draw();
	}

}


