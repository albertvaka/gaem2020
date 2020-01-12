#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
struct GamePad {

private:
	GamePad() { }

	const static int JoystickCountMax = 4;

	enum KeyStates { JUST_RELEASED, RELEASED, JUST_PRESSED, PRESSED };

	static KeyStates button_states[JoystickCountMax][sf::Joystick::ButtonCount];
	static int player_to_joystick[JoystickCountMax];

	static KeyStates calculateJustPressed(bool pressed, KeyStates state) {
		if (pressed) {
			if (state == JUST_PRESSED || state == PRESSED) {
				state = PRESSED;
			}
			else {
				state = JUST_PRESSED;
			}
		}
		else {
			if (state == JUST_RELEASED || state == RELEASED) {
				state = RELEASED;
			}
			else {
				state = JUST_RELEASED;
			}
		}
		return state;
	}

public:
	enum Button {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		Select = 6,
		Start = 7
	};

	struct Trigger {
		struct TriggerBase {
			friend struct GamePad;
			bool IsPressed(int player) { return (state[player] == PRESSED || state[player] == JUST_PRESSED); }
			bool IsJustPressed(int player) { return (state[player] == JUST_PRESSED); }
			bool IsReleased(int player) { return (state[player] == RELEASED || state[player] == JUST_RELEASED); }
			bool IsJustReleased(int player) { return (state[player] == JUST_RELEASED); }
		private:
			KeyStates state[JoystickCountMax];
		};
		struct LeftTrigger : public TriggerBase {
			float get(int player) const { //Pos between 0 and 100
				int joystick = player_to_joystick[player];
				if (joystick < 0) return 0;
				float a = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Z);
				return a > 0.1 ? a : 0;
			}
		};
		struct RightTrigger : public TriggerBase {
			float get(int player) const { //Pos between 0 and 100
				int joystick = player_to_joystick[player];
				if (joystick < 0) return 0;
				float a = -sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Z);
				return a > 0.1 ? a : 0;
			}
		};
		static LeftTrigger Left;
		static RightTrigger Right;
	};

	struct AnalogStick {
		const static AnalogStick Left;
		const static AnalogStick Right;
		sf::Vector2f get(int player, float dead_area = 0) const { //Pos between -100 and 100
			int joystick = player_to_joystick[player];
			if (joystick < 0) return sf::Vector2f();
			float a = sf::Joystick::getAxisPosition(joystick, x);
			float b = sf::Joystick::getAxisPosition(joystick, y);
			return sf::Vector2f(abs(a) > dead_area ? a : 0, abs(b) > dead_area ? b : 0);
		}
	private:
		AnalogStick(sf::Joystick::Axis mx, sf::Joystick::Axis my) : x(mx), y(my)
		{ }
		sf::Joystick::Axis x, y;
	};

	static bool IsButtonPressed(int player, GamePad::Button b) { return (button_states[player][b] == PRESSED || button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonJustPressed(int player, GamePad::Button b) { return (button_states[player][b] == JUST_PRESSED); }
	static bool IsButtonReleased(int player, GamePad::Button b) { return (button_states[player][b] == RELEASED || button_states[player][b] == JUST_RELEASED); }
	static bool IsButtonJustReleased(int player, GamePad::Button b) { return (button_states[player][b] == JUST_RELEASED); }

	static void UpdateInputState__MandoSteam(int joy, int player)
	{
		//TODO: Fix this
		for (int i = 0; i < sf::Joystick::ButtonCount; i++)
		{
			bool pressed = (sf::Joystick::isButtonPressed(joy, i));
			button_states[player][i] = calculateJustPressed(pressed, button_states[player][i]);
		}
		{
			bool pressed = (Trigger::Left.get(player) > 50);
			Trigger::Left.state[player] = calculateJustPressed(pressed, Trigger::Left.state[player]);
		}
		{
			bool pressed = (Trigger::Right.get(player) > 50);
			Trigger::Right.state[player] = calculateJustPressed(pressed, Trigger::Right.state[player]);
		}
	}

	static void UpdateInputState__XboxNormal(int joy, int player)
	{
		for (int i = 0; i < sf::Joystick::ButtonCount; i++)
		{
			bool pressed = (sf::Joystick::isButtonPressed(joy, i));
			button_states[player][i] = calculateJustPressed(pressed, button_states[player][i]);
		}
		{
			bool pressed = (Trigger::Left.get(player) > 50);
			Trigger::Left.state[player] = calculateJustPressed(pressed, Trigger::Left.state[player]);
		}
		{
			bool pressed = (Trigger::Right.get(player) > 50);
			Trigger::Right.state[player] = calculateJustPressed(pressed, Trigger::Right.state[player]);
		}
	}

	static void UpdateInputState()
	{
		int player = 0;
		for (int joystick = 0; joystick < JoystickCountMax; ++joystick)
		{
			if (!sf::Joystick::isConnected(joystick))
			{
				continue;
			}
			player_to_joystick[player] = joystick;


			sf::Joystick::Identification id_joy = sf::Joystick::getIdentification(joystick);

			const int ID_MANDO_STEAM = 999999;
			switch (id_joy.productId)
			{
			case ID_MANDO_STEAM:
			{
				UpdateInputState__MandoSteam(joystick, player);
			} break;

			default:
			{
				UpdateInputState__XboxNormal(joystick, player);
			} break;
			}

			player++;

		}

		while (player < JoystickCountMax)
		{
			player_to_joystick[player] = -1;
			for (int i = 0; i < sf::Joystick::ButtonCount; i++)
			{
				button_states[player][i] = calculateJustPressed(false, button_states[player][i]);
			}
			player++;
		}

	}

};
