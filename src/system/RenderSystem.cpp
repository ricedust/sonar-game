#include "RenderSystem.h"

RenderSystem::RenderSystem(Scene& scene) : scene{scene} {
	images[Sprite::dot].load("sprite/dot.png");
	images[Sprite::sonar].load("sprite/sonar.png");
	images[Sprite::compass].load("sprite/compass.png");
	images[Sprite::bullet].load("sprite/bullet.png");
	images[Sprite::sonarline].load("sprite/sonarline.png");
};

void renderPrimitive(const Transform& transform) {
	ofPushStyle();
	ofSetColor(ofColor::yellow);

	ofPushMatrix();
	ofMultMatrix(getMatrix(transform));

	// default triangle
	ofDrawTriangle(glm::vec3{0, 10, 0}, glm::vec3{-10, -10, 0},
				   glm::vec3{10, -10, 0});

	ofPopMatrix();

	ofPopStyle();
}

void renderSprite(const Transform& transform, const ofImage& image,
				  const Renderer& renderer) {
	ofPushMatrix();

	ofMultMatrix(getMatrix(transform));
	ofMultMatrix(glm::translate(-renderer.origin));

	ofPushStyle();
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255, renderer.alpha);
	image.draw(0, 0);
	
	ofDisableAlphaBlending();
	ofPopStyle();
	ofPopMatrix();
}

void RenderSystem::draw(const glm::vec3& origin, float drawRadius) {
	for (EntityIndex i : view) {
		// check if the entity should be culled
		Transform& transform = scene.getComponent<Transform>(i);
		if (glm::distance(origin, transform.position) > drawRadius) continue;

		Renderer& renderer = scene.getComponent<Renderer>(i);

		// pick rendering method
		if (primitiveMode) {
			renderPrimitive(transform);
		} else {
			renderSprite(transform, images[renderer.sprite], renderer);
		}
	}
}