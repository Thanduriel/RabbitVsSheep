#pragma once

#include <glm/glm.hpp>

namespace game {
namespace components{

	struct Ray 
	{
		Ray(const glm::vec3& _target, const glm::vec4& _color, float _thickness)
			: target(_target), color(_color), thickness(_thickness)
		{}

		glm::vec3 target;
		glm::vec4 color;
		float thickness;
	};
}
}