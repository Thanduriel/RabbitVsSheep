#include "playercontrol.hpp"
#include "../graphics/resources.hpp"
#include <engine/input/keyboardInterface.hpp>
#include <engine/utils/meshLoader.hpp>
#include <engine/graphics/resources.hpp>

namespace game {
namespace systems {

	PlayerSpawn::PlayerSpawn(const input::InputInterface& _inputs1, const input::InputInterface& _inputs2)
		: m_inputs1(_inputs1), m_inputs2(_inputs2)
		, m_mesh(*utils::MeshLoader::get("models/playership.obj"))
	{}

	void PlayerSpawn::update(Components _comps, EntityCreator& _creator, const MapBoundaries& _boundaries) const
	{
		static const graphics::Texture2D& texture = *graphics::Texture2DManager::get(
			"textures/playership.png", graphics::Resources::getSampler(graphics::Resources::Samplers::LINEAR));

		static bool init = false;
		if (!init)
		{
			init = true;
			namespace comps = components;

			CreateComponents(_comps, _creator.create())
				.add<comps::Position>(_boundaries.areas[0].center())
				.add<comps::Rotation>(glm::identity<glm::quat>())
				.add<comps::Scale>(glm::vec3(0.75f))
				.add<comps::Velocity>(glm::vec3(0.f))
				.add<comps::PlayerController>(m_inputs1)
				.add<comps::Transform>()
				.add<comps::Model>(m_mesh, texture, glm::identity<glm::mat4>())
				.add<comps::SphereCollider>(1.f, CollisionType::Player)
				.add<comps::AreaRestriction>(comps::AreaRestriction::Areas::Left)
				.add<comps::AngularVelocity>();
		}
	}

	void PlayerControl::update(Components _comps, float _deltaTime) const
	{
		using namespace input;
		_comps.execute([&](const components::PlayerController& _controller
			, components::Velocity& _velocity)
			{
				const InputInterface& inp = *_controller.inputs;

				// acceleration based on player input
				glm::vec2 direction(inp.getAxis(Axes::MOVE_L_R), -inp.getAxis(Axes::MOVE_U_D));
				_velocity.value += glm::vec3(direction * 256.f * _deltaTime, 0.f);
			});
	}

}
}