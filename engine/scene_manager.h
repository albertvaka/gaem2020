#pragma once

struct Scene {
	virtual void EnterScene() = 0;
	virtual void ExitScene() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
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

