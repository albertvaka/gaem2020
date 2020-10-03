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
	vec playerStartPos = vec(0, 0);

	new PowerUp(vec(0,90));
	
	new Player(playerStartPos, -90);

	float innerRadius = 600;
	float outerRadius = 800;
	float amplitude = 30;
	float freq = 15;
	for (float angle = 0; angle < Angles::FullTurnInRads; angle+=0.05f) {
		{
			vec p;
			p.x += (innerRadius + amplitude * sin(freq * angle)) * cos(angle);
			p.y += (innerRadius + amplitude * sin(freq * angle)) * sin(angle);
			new PowerUp(p);
		}
		{
			vec p;
			p.x += (outerRadius + amplitude * sin(freq * angle)) * cos(angle);
			p.y += (outerRadius + amplitude * sin(freq * angle)) * sin(angle);
			new PowerUp(p);
		}
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
	Camera::SetCenter(player->pos  + (player->vel * 0.25));

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
		ImGui::SliderFloat("angularSpeed", &(Player::instance()->angularSpeed), 0, 360);
		ImGui::SliderFloat("speed", &(Player::instance()->speed), 0, 400);
		ImGui::Text("position: %f,%f", Player::instance()->pos.x, Player::instance()->pos.y);
		ImGui::End();
	}
#endif

	FxManager::EndDraw();
}
