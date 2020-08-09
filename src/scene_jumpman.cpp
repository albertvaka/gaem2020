#include "scene_jumpman.h"
#include "input.h"
#ifdef _IMGUI
#include "imgui.h"
#endif
#include "enemy_door.h"
#include "assets.h"
#include "collide.h"

extern float mainClock;


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

void JumpScene::Update(float dt)
{
	for (EnemyDoor* ed : EnemyDoor::GetAll()) {
		ed->collide = false;
	}
	CollideSelf(EnemyDoor::GetAll(), [](EnemyDoor* a, EnemyDoor* b) {
		a->collide = true;
		b->collide = true;
	});
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


