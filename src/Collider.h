#pragma once

enum class ColliderType { circle };

struct Collider {
	ColliderType type{ColliderType::circle};
	float radius{0};

	Collider() = default;
	Collider(float radius);
};
