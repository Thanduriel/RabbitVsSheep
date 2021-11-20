#include "unitspawn.hpp"
#include "../graphics/resources.hpp"
#include <engine/utils/meshLoader.hpp>
#include <engine/graphics/resources.hpp>
#include <engine/math/random.hpp>

namespace game {
namespace systems {

	UnitSpawn::UnitSpawn(float _spawnCycle)
		: m_spawnCycle(_spawnCycle)
		, m_spawnCooldown(_spawnCycle)
		, m_mesh(*utils::MeshLoader::get("models/crate.obj"))
	{
	}

	void UnitSpawn::update(Components _comps, float _deltaTime, EntityCreator& _creator)
	{
		static const graphics::Texture2D& texture = *graphics::Texture2DManager::get(
			"textures/cratetex.png", graphics::Resources::getSampler(graphics::Resources::Samplers::LINEAR));

		m_spawnCooldown -= _deltaTime;

		if (m_spawnCooldown <= 0.f)
		{
			m_spawnCooldown += m_spawnCycle;
			
			for (size_t i = 0; i < 5; ++i)
			{
				namespace comps = components;

				CreateComponents(_comps, _creator.create())
					.add<comps::Position>(glm::vec3(0.f))
					.add<comps::Rotation>(math::random::rotation())
					.add<comps::Velocity>(math::random::direction())
					.add<comps::Transform>(glm::identity<glm::mat4>())
					.add<comps::SphereCollider>(1.f, CollisionType::Enemy)
					.add<comps::AreaRestriction>(comps::AreaRestriction::Areas::Left);
				//	.add<comps::Model>(m_mesh, texture, glm::identity<glm::mat4>());
			}
		}
	}
}
}