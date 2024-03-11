#include "Agent.h"

Agent::Agent()
	: SceneObject{Transform{glm::vec3{ofRandom(ofGetWindowWidth()),
									  ofRandom(ofGetWindowHeight()), 0},
							ofRandom(360), glm::vec3{1}},
				  Collider{5}} {}

void Agent::update() {
	auto deltaTime = ofGetLastFrameTime();

	// update time alive
	timeAliveSeconds += deltaTime;

	// determine angle between current direction and target direction
	auto targetDirection = glm::normalize(targetPosition - transform.position);
	auto currentDirection = glm::rotateZ(
		glm::vec3{0, 1, 0}, glm::radians(transform.rotationDegrees));
	auto orientedAngle = glm::orientedAngle(currentDirection, targetDirection,
											glm::vec3(0, 0, 1));

	// turn left or right
	if (orientedAngle > 0) {
		transform.rotationDegrees += rotationSpeed * deltaTime;
	} else
		transform.rotationDegrees -= rotationSpeed * deltaTime;

	// move in direction of rotation
	transform.position +=
		glm::rotateZ(glm::vec3{0, speed, 0},
					 glm::radians(transform.rotationDegrees)) *
		deltaTime;
}

void Agent::draw() {
	ofPushStyle();
	ofSetColor(ofColor::green);

	ofPushMatrix();
	ofMultMatrix(transform.getMatrix());

	// default triangle
	ofDrawTriangle(glm::vec3{0, 10, 0}, glm::vec3{-5, -10, 0},
				   glm::vec3{5, -10, 0});

	ofPopMatrix();

	ofPopStyle();
}

float Agent::getTimeAliveSeconds() const { return timeAliveSeconds; }

void Agent::setTargetPosition(const glm::vec3 &targetPosition) {
	this->targetPosition = targetPosition;
}