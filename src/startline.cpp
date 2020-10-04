#include "startline.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "assets.h"
#include "anim_lib.h"

extern float mainClock;

std::string StartLine::FormatTimelapText(float t) const
{
	int minutes = (int)(t / 60.0f);
	int seconds = (int)(t) % 60;
	int millis = ((int)(t * 100)) % 100;
	std::string formattedTime = "";
	if (minutes < 10)
	{
		formattedTime += "0";
	}
	formattedTime += std::to_string(minutes);
	formattedTime += ":";
	if (seconds < 10)
	{
		formattedTime += "0";
	}
	formattedTime += std::to_string(seconds);
	formattedTime += ".";
	if (millis < 10)
	{
		formattedTime += "0";
	}
	formattedTime += std::to_string(millis);

	return formattedTime;
}

std::string StartLine::GetTimelapText() const
{
	return FormatTimelapText(timelapTimer);
}

std::string StartLine::GetBestlapText() const
{
	return FormatTimelapText(bestlapTimer);
}

bool StartLine::HasBestLap() const
{
	return bestlapTimer > 0.0f;
}

void StartLine::Update(float dt)
{
	timelapTimer += dt;
}

void StartLine::PlayerCollided()
{
	if (!playerColliding)
	{

		if (bestlapTimer < 0.0f)
		{
			bestlapTimer = timelapTimer;
		}
		else if (timelapTimer < bestlapTimer)
		{
			bestlapTimer = timelapTimer;
		}

		timelapTimer = 0.0f;
	}

	playerColliding = true;
}

void StartLine::Draw() const
{
	if (playerColliding)
	{
		Window::DrawPrimitive::Rectangle(bounds(), -1, 0, 255, 65, 128);
	}
	else
	{
		Window::DrawPrimitive::Rectangle(bounds(), -1, 0, 143, 17, 128);
	}

	if (Debug::Draw) 
	{
		bounds().Draw();
	}
}
