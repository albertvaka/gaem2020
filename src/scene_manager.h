#pragma once

#include <SFML/Graphics.hpp>

struct Scene {
	virtual void Init() = 0;
	virtual void Leave() = 0;
	virtual void Update(int dt) = 0;
	virtual void Draw(sf::RenderTarget& window) = 0;
	virtual ~Scene() { }
};

struct SceneManager
{
	static Scene* currentScene;
	static Scene*& CurrentScene()
	{
		return currentScene;
	}
	static void SetScene(Scene* s)
	{
		currentScene = s;
	}
};

