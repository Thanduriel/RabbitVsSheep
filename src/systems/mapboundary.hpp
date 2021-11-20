#pragma once

#include "../components/collider.hpp"
#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>
#include <engine/math/geometrictypes.hpp>
#include <array>

namespace game {
namespace systems{

	class MapBoundary
	{
	public:
		MapBoundary(std::vector<math::AABB3D> _areas);

		using Components = ComponentTuple<
			ReadAccess<components::Position>
			, WriteAccess<components::Velocity>
			, ReadAccess<components::AreaRestriction>>;
		void update(Components _comps) const;
	private:
		std::vector<math::AABB3D> m_areas;
	};
}}