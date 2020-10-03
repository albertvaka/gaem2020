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

void MainScene::EnterScene()
{
	new Player(vec(Window::GAME_WIDTH/2, Window::GAME_HEIGHT/2), 0);

	for (int i = 0; i < 10; i++) {
		new PowerUp(Rand::rollf(0, Window::GAME_WIDTH), Rand::rollf(0, Window::GAME_HEIGHT));
	}
}

void MainScene::ExitScene()
{
	Entity::DeleteAll();
}

void MainScene::Update(float dt)
{
	FxManager::Update(dt);

	vec camPos = vec(Window::GAME_WIDTH / 2, Window::GAME_HEIGHT / 2);
	Camera::SetCenter(camPos + FxManager::GetScreenshake());

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

	Window::Clear(0, 0, 0);

	for (const PowerUp* e : SelfRegister<PowerUp>::GetAll()) {
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
		ImGui::SliderFloat("speed", &(Player::instance()->speed), 0, 200);
		ImGui::End();
	}
#endif

	FxManager::EndDraw();
}
