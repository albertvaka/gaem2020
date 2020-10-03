#include "scene_main.h"
#include "input.h"
#ifdef _IMGUI
#include "imgui.h"
#endif
#include "assets.h"
#include "fxmanager.h"
#include "player.h"
#include "powerup.h"
#include "camera.h"
#include "window.h"
#include "rand.h"
#include "tiledexport.h"

void MainScene::EnterScene()
{
	new Player(TiledEntities::spawn, 0);

	for (const vec& pos : TiledEntities::obstacle) {
		new PowerUp(pos);
	}
}

void MainScene::ExitScene()
{
	Entity::DeleteAll();
}

void MainScene::Update(float dt)
{
	FxManager::Update(dt);

	Player* player = Player::instance();
	
	Camera::SetRotationDegs(-player->angle - 90);
	Camera::SetCenter(player->pos  + (player->vel * 0.25) + FxManager::GetScreenshake());

	float zoomerino = 0.75 - 0.2f * (player->speed / player->kMaxSpeed);

	Camera::SetZoom(zoomerino, true);

	for (Entity* e : SelfRegister<Entity>::GetAll()) {
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

	Window::Clear(30, 80, 30);

	for (const PowerUp* e : SelfRegister<PowerUp>::GetAll()) 
	{
		e->Draw();
	}

	Player::instance()->Draw();

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
