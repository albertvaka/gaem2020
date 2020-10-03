#pragma once 

#include "vec.h"

struct FxManager {

	static inline void StartScreenshake(float time, veci amplitude, vec speed) {
		if (time >= screenshakeTime) {
			screenshakeTime = time;
			screenshakeAmplitude = amplitude;
			screenshakeSpeed = speed;
		}
	}
	enum class ScreenShakePreset {
		Earthquake,
		LittleStomp,
		Stomp,
		Electroshok,
	};
	static inline void StartScreenshakePreset(ScreenShakePreset preset) {
		switch (preset) {
		case ScreenShakePreset::Earthquake: // Call repeatedly for a sustained effect
			StartScreenshake(0.1f, veci(2,2), vec(35.f,45.f));
			break;
		case ScreenShakePreset::LittleStomp:
			StartScreenshake(0.17f, veci(0, 2), vec(0.f, 47.f));
			break;
		case ScreenShakePreset::Stomp:
			StartScreenshake(0.17f, veci(0, 3), vec(0.f, 47.f));
			break;
		case ScreenShakePreset::Electroshok:
			StartScreenshake(0.157f, veci(8, 2), vec(86.7f, 14.1f));
			break;
		}
	}

	static void Update(float dt);

	static void BeginDraw();

	static void EndDraw();

	static inline const vec& GetScreenshake() {
		return screenshake;
	}

	static void DrawImgui();

private:
	static inline vec screenshake = vec();

	static inline float screenshakeTime;
	static inline veci screenshakeAmplitude = veci(0, 0);
	static inline vec screenshakeSpeed = veci(0, 0);
};