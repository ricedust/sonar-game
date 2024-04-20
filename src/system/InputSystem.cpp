#include "InputSystem.h"

enum { forwards, backwards, clockwise, counterClockwise, firing };

void InputSystem::set(int key) {
	switch (key) {
		case 'w':
			if (!keyMask.test(forwards)) AudioSystem::play(Sound::motor);
			keyMask.set(forwards);
			break;
		case 'a':
			keyMask.set(counterClockwise);
			break;
		case 's':
			if (!keyMask.test(backwards)) AudioSystem::play(Sound::motor);
			keyMask.set(backwards);
			break;
		case 'd':
			keyMask.set(clockwise);
			break;
		case ' ':
			keyMask.set(firing);
			break;
		default:
			break;
	}
}

void InputSystem::reset(int key) {
	switch (key) {
		case 'w':
			keyMask.reset(forwards);
			AudioSystem::stop(Sound::motor);
			break;
		case 'a':
			keyMask.reset(counterClockwise);
			break;
		case 's':
			keyMask.reset(backwards);
			AudioSystem::stop(Sound::motor);
			break;
		case 'd':
			keyMask.reset(clockwise);
			break;
		case ' ':
			keyMask.reset(firing);
			break;
		default:
			break;
	}
}

void InputSystem::resetAll() {
	keyMask.reset();
	AudioSystem::stop(Sound::motor);
}

int InputSystem::getForward() const {
	return keyMask[forwards] - keyMask[backwards];
}

int InputSystem::getTurn() const {
	return keyMask[clockwise] - keyMask[counterClockwise];
}

bool InputSystem::isFiring() const { return keyMask.test(firing); }