#pragma once

#include <engine/game/core/componentaccess.hpp>
#include <engine/game/core/lifetimeManager2.hpp>
#include <engine/game/components/simpleComponents.hpp>
#include <engine/game/components/model.hpp>
#include <engine/graphics/renderer/mesh.hpp>

namespace game {
namespace systems{

	class UnitSpawn
	{
	public:
		UnitSpawn(float _spawnCycle);

		using Components = ComponentTuple<
			WriteAccess<components::Position>
			, WriteAccess<components::Rotation>
			, WriteAccess<components::Velocity>
			, WriteAccess<components::Transform>
			, WriteAccess<components::Model>>;

		void update(Components _comps, float _deltaTime, EntityCreator& _creator);
	private:
		graphics::Mesh m_mesh;
		float m_spawnCycle;
		float m_spawnCooldown;
	};

}
}