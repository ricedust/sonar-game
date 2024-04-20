#pragma once

#include <array>
#include <cstddef>

#include "ofMain.h"

enum Sound { damaged, environment, explosion, motor, ping, shoot, soundtrack };
const size_t soundCount{7};

class AudioSystem {
	static std::array<ofSoundPlayer, soundCount> sounds;

   public:
	AudioSystem() = delete;
	static void setup();
	static bool isLoaded();
	static void play(Sound sound);
	static void stop(Sound sound);
};