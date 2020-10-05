#pragma once

#include "vec.h"
#include "entity.h"
#include "singleinstance.h"
#include "assets.h"
#include "text.h"

struct StartLine : SingleInstance<StartLine>
{
	std::vector<RotableBounds> checkpoints;
	int currentCheckpoint = 99999;
	bool beforeStart = true;

	RotableBounds bbounds;

	RotableBounds bounds() { return bbounds; }

	StartLine(const Bounds& start) : bbounds(start), timelapText(Assets::font_30, Assets::font_30_outline) { }
	void Update(float dt);
	void Draw() const;

	Text timelapText;
	void DrawBestLapText();
	void DrawLastLapText();

	std::string GetTimelapText() const
	{
		return FormatTimelapText(timelapTimer);
	}

	std::string GetBestlapText() const
	{
		return FormatTimelapText(bestlapTimer);
	}

	std::string GetLastlapText() const
	{
		return FormatTimelapText(lastlapTimer);
	}

	bool HasBestLap() const { return bestlapTimer > 0.0f; }
	bool HasLastLap() const { return lastlapTimer > 0.0f; };

	void AddPenalization()
	{
		if (!beforeStart)
		{
			timelapTimer += 1.0f;
		}
	}

	bool playerColliding = false;
	float timelapTimer = 0.0f;
	float bestlapTimer = -1.0f;
	float lastlapTimer = -1.0f;

	float bestlapFx = -1.0f;
	float lastlapFx = -1.0f;

private:
	std::string FormatTimelapText(float t) const;
};

