#include "startline.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "player.h"
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

void StartLine::Update(float dt)
{
	playerColliding = (bbounds.Collision(Player::instance()->bbounds));
	if (currentCheckpoint >= checkpoints.size()) 
	{
		if (playerColliding) 
		{
			if (!beforeStart) 
			{
				lastlapTimer = timelapTimer;
				lastlapFx = 5.0f;
				if (bestlapTimer < 0.0f)
				{
					bestlapTimer = timelapTimer;
					bestlapFx = 5.0f;
				}
				else if (timelapTimer < bestlapTimer)
				{
					bestlapTimer = timelapTimer;
					bestlapFx = 5.0f;
				}
			}
			beforeStart = false;
			timelapTimer = 0.0f;
			currentCheckpoint = 0;
		}
	}
	else 
	{
		if (checkpoints[currentCheckpoint].Collision(Player::instance()->bbounds)) 
		{
			//Debug::out << "checkpoint " << currentCheckpoint;
			currentCheckpoint++;
		}
	}

	if (!beforeStart) 
	{
		timelapTimer += dt;
	}

	if (bestlapFx > 0.0f)
	{
		bestlapFx -= dt;
	}
	if (lastlapFx > 0.0f)
	{
		lastlapFx -= dt;
	}

}

void StartLine::Draw() const
{
	if (playerColliding)
	{
		Window::DrawPrimitive::Rectangle(bbounds, -1, 0, 255, 65, 128);
	}
	else
	{
		Window::DrawPrimitive::Rectangle(bbounds, -1, 0, 143, 17, 128);
	}

	if (Debug::Draw) 
	{
		bbounds.Draw();

		if (currentCheckpoint < checkpoints.size()) 
		{
			checkpoints[currentCheckpoint].Draw(0,255,0);
		}

	}
}

void StartLine::DrawBestLapText()
{
	timelapText.SetFillColor(0, 255, 65);
	timelapText.SetOutlineColor(0, 59, 0);

	timelapText.SetString("BEST");
	Window::Draw(timelapText, 6, 15)
		.withScale(0.08f);

	timelapText.SetString(GetBestlapText());
	Window::Draw(timelapText, 5, 18)
		.withScale(0.2f);
}

void StartLine::DrawLastLapText()
{
	timelapText.SetFillColor(0, 255, 65);
	timelapText.SetOutlineColor(0, 59, 0);

	timelapText.SetString("LAST");
	Window::Draw(timelapText, 6, 28)
		.withScale(0.08f);

	timelapText.SetString(GetLastlapText());
	Window::Draw(timelapText, 5, 31)
		.withScale(0.2f);
}
