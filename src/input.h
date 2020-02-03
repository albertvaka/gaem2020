#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;

enum class GameKeys
{
	UP = 0, DOWN, LEFT, RIGHT,
	ACTION, START,
	SHIFT, CTRL,
	F1, F2, F3, F4, F5, F6, 
	F7, F8, F9, F10, F11, F12,
	C, V,
	COUNT
};


struct InputState
{
	std::map<GameKeys, sf::Keyboard::Key> input_map;
	bool isPressed[(int)GameKeys::COUNT];
	bool wasPressed[(int)GameKeys::COUNT];

	bool wasMousePressed[2];
	bool mousePressed[2];

	bool IsPressed(GameKeys key)
	{
		return isPressed[static_cast<int>(key)];
	}

	bool IsJustPressed(GameKeys key)
	{
		return !wasPressed[static_cast<int>(key)] && isPressed[static_cast<int>(key)];
	}

	bool IsMousePressed(int m)
	{
		return mousePressed[m];
	}

	bool IsJustMousePressed(int m)
	{
		return mousePressed[m] && !wasMousePressed[m];
	}

	bool IsJustMouseReleased(int m)
	{
		return !mousePressed[m] && wasMousePressed[m];
	}

	void RemapInput()
	{
		input_map[GameKeys::UP] = sf::Keyboard::Key::Up;
		input_map[GameKeys::DOWN] = sf::Keyboard::Key::Down;
		input_map[GameKeys::LEFT] = sf::Keyboard::Key::Left;
		input_map[GameKeys::RIGHT] = sf::Keyboard::Key::Right;

		input_map[GameKeys::ACTION] = sf::Keyboard::Key::P;
		input_map[GameKeys::START] = sf::Keyboard::Key::Enter;

		input_map[GameKeys::SHIFT] = sf::Keyboard::Key::LShift;
		input_map[GameKeys::CTRL] = sf::Keyboard::Key::LControl;

		input_map[GameKeys::C] = sf::Keyboard::Key::C;
		input_map[GameKeys::V] = sf::Keyboard::Key::V;


		input_map[GameKeys::F1] = sf::Keyboard::Key::F1;
		input_map[GameKeys::F2] = sf::Keyboard::Key::F2;
		input_map[GameKeys::F3] = sf::Keyboard::Key::F3;
		input_map[GameKeys::F4] = sf::Keyboard::Key::F4;
		input_map[GameKeys::F5] = sf::Keyboard::Key::F5;
		input_map[GameKeys::F6] = sf::Keyboard::Key::F6;

		input_map[GameKeys::F7] = sf::Keyboard::Key::F7;
		input_map[GameKeys::F8] = sf::Keyboard::Key::F8;
		input_map[GameKeys::F9] = sf::Keyboard::Key::F9;
		input_map[GameKeys::F10] = sf::Keyboard::Key::F10;
		input_map[GameKeys::F11] = sf::Keyboard::Key::F11;
		input_map[GameKeys::F12] = sf::Keyboard::Key::F12;
	}

	void UpdateInput()
	{
		for (const auto& kv : input_map)
		{
			int key = (int)kv.first;
			wasPressed[key] = isPressed[key];
			isPressed[key] = sf::Keyboard::isKeyPressed(kv.second);
		}

		wasMousePressed[0] = mousePressed[0];
		mousePressed[0] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		wasMousePressed[1] = mousePressed[1];
		mousePressed[1] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	}
};