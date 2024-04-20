#include "AudioSystem.h"

std::array<ofSoundPlayer, soundCount> AudioSystem::sounds{};

void AudioSystem::setup() {
	sounds[Sound::environment].load("audio/environment-loop.mp3");
	sounds[Sound::environment].setLoop(true);

	sounds[Sound::soundtrack].load("audio/soundtrack.mp3");
	sounds[Sound::soundtrack].setLoop(true);

	sounds[Sound::motor].load("audio/motor-loop.mp3");
	sounds[Sound::motor].setLoop(true);

	sounds[Sound::damaged].load("audio/damaged.mp3");
	sounds[Sound::damaged].setMultiPlay(true);

	sounds[Sound::explosion].load("audio/explosion.mp3");
	sounds[Sound::explosion].setMultiPlay(true);

	sounds[Sound::ping].load("audio/ping.mp3");
	sounds[Sound::ping].setMultiPlay(true);

	sounds[Sound::shoot].load("audio/shoot.mp3");
	sounds[Sound::shoot].setMultiPlay(true);
}

bool AudioSystem::isLoaded() {
	for (auto& sound : sounds) {
		if (!sound.isLoaded()) return false;
	}
	return true;
}

void AudioSystem::play(Sound sound) { sounds[sound].play(); }

void AudioSystem::stop(Sound sound) { sounds[sound].stop(); }
