#pragma once

#include <bitset>

#include "AudioSystem.h"

/// @brief Converts keypresses into a control axis.
class InputSystem {
	std::bitset<5> keyMask{};

   public:
	void set(int key);
	void reset(int key);
	void resetAll();
	/// @return 1, 0, or -1, where 1 is forwards
	int getForward() const;
	/// @return 1, 0, or -1, where 1 is clockwise
	int getTurn() const;
	bool isFiring() const;
};