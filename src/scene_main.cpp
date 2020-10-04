#include "scene_main.h"
#include "input.h"
#ifdef _IMGUI
#include "imgui.h"
#endif
#include "assets.h"
#include "fxmanager.h"
#include "player.h"
#include "shot.h"
#include "wall.h"
#include "camera.h"
#include "window.h"
#include "rand.h"
#include "tiledexport.h"
#include "startline.h"
#include <text.h>

void MainScene::EnterScene()
{
	for (vec p : TiledEntities::oleada) {
		Player* o = new Player(p, 0);
		o->spriteTop.x += 6 * 32;
		o->spriteBottom.x += 6 * 32;
		o->enemy = true;
	}

	Player* p = new Player(TiledEntities::spawn, 180);

	const vec* prev = nullptr;
	for (const vec& p : TiledPolygons::outter) {
		if (prev) {
			new Wall(p, *prev, false);
		}
		prev = &p;
	}
	new Wall(TiledPolygons::outter[0], *prev, false);

	prev = nullptr;
	for (const vec& p : TiledPolygons::inner) {
		if (prev) {
			new Wall(p, *prev, true);
		}
		prev = &p;
	}
	new Wall(TiledPolygons::inner[0], *prev, true);

	cameraAngle = -p->angle - 90;

	cameraZoom = 0.5f - 0.3f * (p->speed / p->kMaxSpeed);
	camCenter = p->pos + (p->vel * 0.25f) + FxManager::GetScreenshake();

	startLine = new StartLine(TiledAreas::start[0]);
	for (const Bounds& b : TiledAreas::checkpoint) {
		startLine->checkpoints.push_back(RotableBounds(b));
	}

}

void MainScene::ExitScene()
{
	Shot::DeleteAll();
	Wall::DeleteAll();
	Player::DeleteAll();
	delete startLine;
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

	startLine->Update(dt);

	for (Player* e : Player::GetAll())
	{
		e->Update(dt);
	}

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

	for (const Wall* e : Wall::GetAll()) 
	{
		e->Draw();
	}

	startLine->Draw();

	for (Player* e : Player::GetAll())
	{
		e->Draw();
	}


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
	

	{
		timelapText.SetString("Time: " + startLine->GetTimelapText());
		timelapText.SetFillColor(0, 255, 65);
		timelapText.SetOutlineColor(0, 59, 0);
		Window::Draw(timelapText, 5, 5)
			.withScale(0.2f);
	}

	if (startLine->HasBestLap())
	{
		timelapText.SetString("Best: " + startLine->GetBestlapText());
		timelapText.SetFillColor(255, 0, 65);
		timelapText.SetOutlineColor(59, 0, 0);
		Window::Draw(timelapText, 5, 15)
			.withScale(0.2f);
	}

	if (startLine->HasLastLap())
	{
		timelapText.SetString("Last: " + startLine->GetLastlapText());
		timelapText.SetFillColor(0, 255, 65);
		timelapText.SetOutlineColor(0, 59, 0);
		Window::Draw(timelapText, 5, 25)
			.withScale(0.2f);
	}


	Camera::GUI::End();

}
