#pragma once

#include "../components/collider.hpp"
#include "../components/visual.hpp"
#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>
#include <engine/game/core/lifetimeManager2.hpp>
#include <engine/math/geometrictypes.hpp>
#include <array>

namespace game {

	struct MapBoundaries
	{
		std::vector<math::AABB3D> areas;
		float size;
	};

namespace systems{

	class BoundaryGrid
	{
	public:
		using Components = ComponentTuple<
			WriteAccess<components::Position>
			, WriteAccess<components::Ray>>;
		void update(Components _comps, EntityCreator& _creator, const MapBoundaries& _boundaries) const;
	private:
	};

	class MapBoundary
	{
	public:
		using Components = ComponentTuple<
			ReadAccess<components::Position>
			, WriteAccess<components::Velocity>
			, ReadAccess<components::AreaRestriction>>;
		void update(Components _comps, float _deltaTime, const MapBoundaries& _boundaries) const;
	private:
	};
}}