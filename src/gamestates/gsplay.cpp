#include "gsplay.hpp"
#include "../systems/meshdrawnig.hpp"
#include "../systems/unitspawn.hpp"
#include "../systems/physics.hpp"
#include <engine/game/systems/transforms.hpp>

namespace game {

	GSPlay::GSPlay()
		: m_world(graphics::Camera(45, 0.001f, 1000.f))
	{
		m_world.addSystem(std::make_unique<systems::Physics>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::Transforms>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::UnitSpawn>(5.f), SystemGroup::Process);

		m_world.getResource<graphics::Camera>().setView(
			glm::lookAt(glm::vec3(0.f, 0.f, -10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)));

		// rendering
		m_world.addSystem(std::make_unique<systems::MeshDrawing>(), SystemGroup::Draw);
	}

	void GSPlay::process(float _deltaTime)
	{
		m_world.process(SystemGroup::Process, _deltaTime);
	}

	void GSPlay::draw(float _deltaTime)
	{
		m_world.process(SystemGroup::Draw, _deltaTime);
	}
}