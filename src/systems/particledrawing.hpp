#pragma once

#include "graphics/particlerenderer.hpp"
#include "graphics/linerenderer.hpp"
#include "components/visual.hpp"
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

		class LineDrawing
		{
		public:
			using Components = ComponentTuple<
				ReadAccess<components::Position>,
				ReadAccess<components::Ray>>;

			void update(Components _comps, const graphics::Camera& _camera);
		private:
			graphics::LineRenderer m_renderer;
		};
	}
}