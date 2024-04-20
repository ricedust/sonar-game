#pragma once

#include <cstddef>

#include "Renderer.h"
#include "Scene.h"
#include "Transform.h"
#include "ofMain.h"

class RenderSystem {
	Scene& scene;
	EntityView<Renderer, Transform> view{scene.getEntities()};
	std::array<ofImage, totalSprites> images{};

   public:
	bool primitiveMode{false};
	
	RenderSystem(Scene& scene);

	/// @brief Draws renderable entities inside a draw radius. Culls all
	/// entities outside.
	/// @param origin The origin of the render circle.
	/// @param drawRadius The radius of the render circle.
	void draw(const glm::vec3& origin, float drawRadius);
};