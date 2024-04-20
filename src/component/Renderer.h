#pragma once

#include <cstddef>

#include "ofMain.h"

enum Sprite { none, bullet, dot, sonar, sonarline, compass };
const size_t totalSprites{6};

struct Renderer {
	Sprite sprite{Sprite::none};
	glm::vec3 origin{};
	int alpha{255};
};
