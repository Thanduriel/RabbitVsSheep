#pragma once

#include "graphics/particlerenderer.hpp"
#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>

namespace game {
	namespace systems {

		class ParticleDrawing
		{
		public:
			using Components = ComponentTuple<
				ReadAccess<components::Position>,
				ReadAccess<components::Rotation>>;

			void update(Components _comps, const graphics::Camera& _camera);
		private:
			graphics::ParticleRenderer m_renderer;
		};
	}
}