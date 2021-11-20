#pragma once

#include "../components/player.hpp"
#include "../components/collider.hpp"
#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>
#include <engine/game/components/model.hpp>
#include <engine/game/core/lifetimeManager2.hpp>
#include <engine/graphics/renderer/mesh.hpp>

namespace input {

	enum struct Actions {
		EXIT,
		CHARACTER_SCREEN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		CAST_PRIMARY
	};

	enum struct Axes {
		MOVE_L_R,
		MOVE_U_D
	};
}

namespace game {
namespace systems {

	class PlayerSpawn
	{
	public:
		PlayerSpawn(const input::InputInterface& _inputs1, const input::InputInterface& _inputs2);

		using Components = ComponentTuple<
			WriteAccess<components::Position>,
			WriteAccess<components::Velocity>,
			WriteAccess<components::Rotation>,
			WriteAccess<components::PlayerController>,
			WriteAccess<components::Model>,
			WriteAccess<components::Transform>,
			WriteAccess<components::SphereCollider>,
			WriteAccess<components::AreaRestriction>>;
		void update(Components _comps, EntityCreator& _creator) const;
	private:
		graphics::Mesh m_mesh;
		const input::InputInterface& m_inputs1;
		const input::InputInterface& m_inputs2;
	};

	class PlayerControl
	{
	public:
		using Components = ComponentTuple<
			WriteAccess<components::Velocity>,
			ReadAccess<components::PlayerController>>;
		void update(Components _comps, float _deltaTime) const;
	private:
	};
}
}