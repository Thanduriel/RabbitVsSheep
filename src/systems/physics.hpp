#pragma once

#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>

namespace game {
namespace systems {

	class Physics
	{
	public:
		using Components = ComponentTuple<
			WriteAccess<components::Position>
			, ReadAccess<components::Velocity>
			, WriteAccess<components::TransformNeedsUpdate>>;

		void update(Components _comps, float _deltaTime);
	};
}
}