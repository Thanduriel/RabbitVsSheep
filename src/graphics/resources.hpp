#pragma once

#include <engine/graphics/resources.hpp>

#include <string>
#include <array>
#include <cmath>

namespace graphics {

	class Sampler;

	class Resources
	{
	public:
		enum class Samplers
		{
			POINT,
			LINEAR,
			COUNT
		};

		static const Sampler& getSampler(Samplers _sampler);
	};
}