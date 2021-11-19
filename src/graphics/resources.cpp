#include "resources.hpp"
#include <engine/graphics/core/sampler.hpp>
#include <engine/graphics/core/device.hpp>
#include <engine/graphics/renderer/sprite.hpp>
#include <spdlog/fmt/fmt.h>
#include <array>

namespace graphics {

	static std::array<std::unique_ptr<Sampler>,
		static_cast<size_t>(Resources::Samplers::COUNT) > s_samplers = {};

	const Sampler& Resources::getSampler(Samplers _sampler)
	{
		if (!s_samplers.front())
		{
			s_samplers[static_cast<size_t>(Samplers::POINT)] =
				std::make_unique<Sampler>(Sampler::Filter::POINT, Sampler::Filter::POINT, Sampler::Filter::POINT, Sampler::Border::CLAMP);
			s_samplers[static_cast<size_t>(Samplers::LINEAR)] =
				std::make_unique<Sampler>(Sampler::Filter::LINEAR, Sampler::Filter::LINEAR, Sampler::Filter::LINEAR, Sampler::Border::CLAMP);
			Device::registerResources([]() 
				{
					for (auto& sampler : s_samplers)
						sampler.reset(nullptr);
				});
		}
		
		return *s_samplers[static_cast<size_t>(_sampler)];
	}
}