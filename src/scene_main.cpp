#include "scene_main.h"
#include "input.h"
#ifdef _IMGUI
#include "imgui.h"
#endif
#include "assets.h"
#include "fxmanager.h"
#include "player.h"
#include "shot.h"
#include "powerup.h"
#include "camera.h"
#include "window.h"
#include "rand.h"
#include "tiledexport.h"

void MainScene::EnterScene()
{
	float scale = 1.3f;
	Player* p = new Player(TiledEntities::spawn * scale, 0);

	for (const vec& pos : TiledEntities::obstacle) 
	{
		new PowerUp(pos* scale);
	}

	cameraAngle = -p->angle - 90;

	cameraZoom = 0.5f - 0.3f * (p->speed / p->kMaxSpeed);
	camCenter = p->pos + (p->vel * 0.25f) + FxManager::GetScreenshake();
}

void MainScene::ExitScene()
{
	Entity::DeleteAll();
}


float kCameraRotSpeed = 360.0f;

float cameraZoom = 0.0f;

void MainScene::Update(float dt)
{
	FxManager::Update(dt);

	Player* player = Player::instance();

	float playerAngle = -player->angle - 90.0f;

	if (abs(cameraAngle - playerAngle) <= kCameraRotSpeed*dt) 
	{
		cameraAngle = playerAngle;
	}
	else 
	{
		cameraAngle -= kCameraRotSpeed * vec::FromAngleDegs(playerAngle).Sign(vec::FromAngleDegs(cameraAngle)) * dt;
	}


	Camera::SetRotationDegs(cameraAngle);
	//Camera::SetRotationDegs(playerAngle);
	
	vec targetCenter = player->pos + (player->vel * 0.25) + FxManager::GetScreenshake();
	camCenter.x = camCenter.x + dt * (targetCenter.x - camCenter.x) * 5.0f;
	camCenter.y = camCenter.y + dt * (targetCenter.y - camCenter.y) * 5.0f;
	Camera::SetCenter(camCenter);

	float targetZoom = 0.5f - 0.3f * (player->speed / player->kMaxSpeed);
	cameraZoom = cameraZoom + (targetZoom - cameraZoom) * dt * 5.0f;
	Camera::SetZoom(cameraZoom, true);

	for (Entity* e : SelfRegister<Entity>::GetAll()) 
	{
		e->Update(dt);
	}

	Entity::DeleteNotAlive();

#ifdef _DEBUG
	const SDL_Scancode restart = SDL_SCANCODE_F5;
	if (Keyboard::IsKeyJustPressed(restart)) {
		ExitScene();
		EnterScene();
		return;
	}
#endif
}

void MainScene::Draw()
{
	FxManager::BeginDraw();

	Window::Clear(16, 16, 16);

	for (const PowerUp* e : SelfRegister<PowerUp>::GetAll()) 
	{
		e->Draw();
	}

	Player::instance()->Draw();

	for (const Shot* e : SelfRegister<Shot>::GetAll())
	{
		e->Draw();
	}

#ifdef _IMGUI
	{
		ImGui::Begin("imgui ld47");
		vec m = Mouse::GetPositionInWorld();
		ImGui::Text("Mouse position: %f,%f", m.x, m.y);
		ImGui::Text("F1 frame-by-frame mode");
		ImGui::Text("E to advance frame-by-frame");
		ImGui::Text("F2: debug draw mode");
		ImGui::End();

		ImGui::Begin("car");
		ImGui::SliderFloat("angle", &(Player::instance()->angle), 0, 360);
		ImGui::SliderFloat("angularSpeed", &(Player::instance()->angularSpeed), 0, 360);
		ImGui::SliderFloat("speed", &(Player::instance()->speed), 0, 400);
		ImGui::Text("position: %f,%f", Player::instance()->pos.x, Player::instance()->pos.y);
		ImGui::End();
	}
#endif

	FxManager::EndDraw();
}
