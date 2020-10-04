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
#include "startline.h"
#include <text.h>

void MainScene::EnterScene()
{
	Player* p = new Player(TiledEntities::spawn, 0);

	const vec* prev = nullptr;
	for (const vec& p : TiledPolygons::outter) {
		if (prev) {
			new PowerUp(p, *prev, false);
		}
		prev = &p;
	}
	new PowerUp(TiledPolygons::outter[0], *prev, false);

	prev = nullptr;
	for (const vec& p : TiledPolygons::inner) {
		if (prev) {
			new PowerUp(p, *prev, true);
		}
		prev = &p;
	}
	new PowerUp(TiledPolygons::inner[0], *prev, true);

	cameraAngle = -p->angle - 90;

	cameraZoom = 0.5f - 0.3f * (p->speed / p->kMaxSpeed);
	camCenter = p->pos + (p->vel * 0.25f) + FxManager::GetScreenshake();

	startLine = new StartLine(TiledAreas::start[0]);
}

void MainScene::ExitScene()
{
	Shot::DeleteAll();
	PowerUp::DeleteAll();
	delete Player::instance();
	delete StartLine::instance();
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

	for (Shot* e : Shot::GetAll())
	{
		e->Update(dt);
	}
	Shot::DeleteNotAlive();

	StartLine::instance()->Update(dt);

	Player::instance()->Update(dt);

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

	for (const PowerUp* e : PowerUp::GetAll()) 
	{
		e->Draw();
	}

	StartLine::instance()->Draw();
	
	Player::instance()->Draw();

	for (const Shot* e : Shot::GetAll())
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

	Camera::GUI::Begin();
	
	if (startLine->HasBestLap())
	{
		timelapText.SetString(startLine->GetBestlapText());
		timelapText.SetFillColor(255, 0, 65);
		timelapText.SetOutlineColor(59, 0, 0);
		Window::Draw(timelapText, 5, 5)
			.withScale(0.2f);
	}

	{
		timelapText.SetString(startLine->GetTimelapText());
		timelapText.SetFillColor(0, 255, 65);
		timelapText.SetOutlineColor(0, 59, 0);
		Window::Draw(timelapText, 5, 15)
			.withScale(0.2f);
	}


	Camera::GUI::End();

}
