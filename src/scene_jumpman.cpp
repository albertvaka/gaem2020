#pragma once

#include "scene_jumpman.h"
#include "input.h"

JumpScene::JumpScene()
	: player(&map)
{

}

void JumpScene::EnterScene() 
{
	Camera::SetZoom(GameData::GAME_ZOOM);
	Camera::SetCameraCenter(vec(GameData::WINDOW_WIDTH / (2*GameData::GAME_ZOOM), GameData::WINDOW_HEIGHT/(2*GameData::GAME_ZOOM)));

	texture.loadFromFile("data/spritesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));

	transition.setTime(2.0f);
	transition.setPos(0.6f* GameData::GAME_ZOOM);
	transition.goPos(GameData::GAME_ZOOM);

	player.pos = vec(160, 160);
	player.Reset();
	map.Init(time(NULL), sf::Vector2i(1000, 25), 16);

	sf::Vector2i pos = map.tilePos(player.pos);
	map.set(pos.x - 1, pos.y + 1, true);
	map.set(pos.x    , pos.y + 1, true);
	map.set(pos.x - 1, pos.y    , false);
	map.set(pos.x    , pos.y    , false);
	map.set(pos.x - 1, pos.y - 1, false);
	map.set(pos.x    , pos.y - 1, false);

}

void JumpScene::ExitScene()  
{
}

void JumpScene::Update(int dtMilis) {
	float dt = dtMilis / 1000.f;
	transition.update(dt);
	player.Update(dt);

	Camera::ChangeZoomWithPlusAndMinus(10.f, dt);
	if (!transition.reached()) {
		Camera::SetZoom(transition.getPos());
	}
	//Camera::MoveCameraWithArrows(50.f, dt);
	vec camPos = player.pos;
	float minY = (Camera::GetCameraBounds().height / 2.f) - (1 * 16);
	float maxY = ((25 + 1) * 16) - (Camera::GetCameraBounds().height / 2.f);
	if (maxY < minY) {
		minY = maxY - 1;
	}
	Mates::Clamp(camPos.y, minY, maxY);
	float minX = (Camera::GetCameraBounds().width / 2.f) - (1 * 16);
	float maxX = ((1000 + 1) * 16) - (Camera::GetCameraBounds().width / 2.f);
	if (maxX < minX) {
		minX = maxX - 1;
	}
	Mates::Clamp(camPos.x, minX, maxX);
	Camera::SetCameraCenter(camPos);

	if (player.grounded && map.tilePos(player.pos + vec(0.1f, 0)).y == 24) {
		EnterScene();
	}
}

void JumpScene::Draw(sf::RenderTarget& window) 
{
	window.clear(sf::Color(255*0.200f, 255 * 0.100f, 255 * 0.100f));

	map.Draw(sprite, window);

	player.Draw(sprite, window);
	//player.bounds().Draw(window);

}
