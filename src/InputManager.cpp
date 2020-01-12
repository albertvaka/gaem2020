#include "InputManager.h"

GamePad::KeyStates GamePad::button_states[GamePad::JoystickCountMax][sf::Joystick::ButtonCount];

int GamePad::player_to_joystick[GamePad::JoystickCountMax];

const GamePad::AnalogStick GamePad::AnalogStick::Left(sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
const GamePad::AnalogStick GamePad::AnalogStick::Right(sf::Joystick::Axis::U, sf::Joystick::Axis::V);


GamePad::Trigger::LeftTrigger GamePad::Trigger::Left;
GamePad::Trigger::RightTrigger GamePad::Trigger::Right;
