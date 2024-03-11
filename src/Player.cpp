#include "Player.h"

Player::Player()
	: SceneObject{Transform{glm::vec3{ofGetWindowWidth() / 2,
									  ofGetWindowHeight() / 2, 0},
							0, glm::vec3{1}},
				  Collider{5}} {}

void Player::update() {
	// subtract the input directions from each other to evaluate input axis as
	// -1, 0, or 1
	int forwardAxis =
		inputStates[InputDirection::up] - inputStates[InputDirection::down];
	int turnAxis =
		inputStates[InputDirection::right] - inputStates[InputDirection::left];

	auto deltaTime = ofGetLastFrameTime();

	// turn based on input
	transform.rotationDegrees += turnAxis * rotationSpeed * deltaTime;

	// move based on input in direction of rotation
	transform.position +=
		glm::rotateZ(glm::vec3{0, forwardAxis * -speed, 0},
					 glm::radians(transform.rotationDegrees)) *
		deltaTime;

	// wrap the player to other side of screen if they try to escape
	auto width = ofGetWindowWidth();
	auto height = ofGetWindowHeight();
	// cout << transform << "\n" << width << '\n';
	if (transform.position.x < 0)
		transform.position.x = width;
	else if (transform.position.x > width)
		transform.position.x = 0;
	if (transform.position.y < 0)
		transform.position.y = height;
	else if (transform.position.y > height)
		transform.position.y = 0;

	// update collider radius
	collider.radius = 5 * transform.scale.x;
};

void Player::draw() {
	ofPushStyle();
	ofSetColor(ofColor::yellow);

	ofPushMatrix();
	ofMultMatrix(transform.getMatrix());

	// default triangle
	ofDrawTriangle(glm::vec3{0, -10, 0}, glm::vec3{-10, 10, 0},
				   glm::vec3{10, 10, 0});

	ofPopMatrix();

	ofPopStyle();
};

void Player::setScale(const glm::vec3& scale) { transform.scale = scale; }

void Player::evaluateKeyPress(const int& key) {
	switch (key) {
		case 'w':
			inputStates[InputDirection::up] = true;
			break;
		case 'a':
			inputStates[InputDirection::left] = true;
			break;
		case 's':
			inputStates[InputDirection::down] = true;
			break;
		case 'd':
			inputStates[InputDirection::right] = true;
			break;
	};
}

void Player::evaluateKeyRelease(const int& key) {
	switch (key) {
		case 'w':
			inputStates[InputDirection::up] = false;
			break;
		case 'a':
			inputStates[InputDirection::left] = false;
			break;
		case 's':
			inputStates[InputDirection::down] = false;
			break;
		case 'd':
			inputStates[InputDirection::right] = false;
			break;
	}
}