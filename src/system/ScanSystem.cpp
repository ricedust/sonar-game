#include "ScanSystem.h"

ScanSystem::ScanSystem(Scene& scene) : scene{scene} {}

void ScanSystem::update(EntityIndex trueScannerIndex, const Transform& origin) {
	// increment rotation
	Scanner& scanner{scene.getComponent<Scanner>(trueScannerIndex)};
	scanner.degreesOffset += scanner.degreesPerSecond * ofGetLastFrameTime();

	// apply transform
	Transform& scannerTransform{
		scene.getComponent<Transform>(trueScannerIndex)};
	scannerTransform.rotationDegrees =
		origin.rotationDegrees + scanner.degreesOffset;

	// play ping if revolution reached
	unsigned int currentRevolutions{std::abs(scanner.degreesOffset / 360)};
	if (currentRevolutions > scanner.revolutions) {
		AudioSystem::play(Sound::ping);
		scanner.revolutions = currentRevolutions;
	}

	// move all scanner entities to the origin (includes trail)
	for (EntityIndex i : scannerView) {
		scene.getComponent<Transform>(i).position = origin.position;
	}

	// light up all agents that get scanned
	for (EntityIndex agentIndex : agentView) {
		Transform& agentTransform{scene.getComponent<Transform>(agentIndex)};

		// find two vectors:
		// 1. origin to scanner direction
		// 2. origin to agent direction
		auto scannerDirection{
			glm::rotateZ(glm::vec3{0, 1, 0},
						 glm::radians(scannerTransform.rotationDegrees))};
		auto agentDirection{
			glm::normalize(agentTransform.position - origin.position)};

		// find angle between them
		auto degreesBetween{
			glm::degrees(glm::angle(scannerDirection, agentDirection))};

		// if angle is within threshold, "scan" the agent by maxing alpha
		if (degreesBetween < 5.0f)
			scene.getComponent<Renderer>(agentIndex).alpha = 255;
	}
}