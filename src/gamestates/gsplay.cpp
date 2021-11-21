#include "gsplay.hpp"
#include "../systems/meshdrawnig.hpp"
#include "../systems/unitspawn.hpp"
#include "../systems/physics.hpp"
#include "../systems/particledrawing.hpp"
#include "../systems/playercontrol.hpp"
#include "../systems/mapboundary.hpp"
#include <engine/game/systems/transforms.hpp>
#include <engine/graphics/core/device.hpp>
#include <engine/utils/config.hpp>
#include <engine/input/keyboardInterface.hpp>

namespace game {

	GSPlay::GSPlay()
		: m_world(graphics::Camera(45.f, 0.001f, 1000.f))
	{
		using namespace input;
		// inputs
		m_inputs1 = std::unique_ptr<InputInterface>(
			new KeyboardInterface(utils::Config::get()["inputs"]["keyboard1"],
				{ {"exit", Key::ESCAPE},
				{"characterScreen", Key::TAB},
				{"moveLeft", Key::A},
				{"moveRight", Key::D},
				{"moveUp", Key::W},
				{"moveDown", Key::S},
				{"castPrimary", MouseButton::LEFT} },
				{ {Actions::MOVE_LEFT, Actions::MOVE_RIGHT}, {Actions::MOVE_UP, Actions::MOVE_DOWN} }));

		m_inputs2 = std::unique_ptr<InputInterface>(
			new KeyboardInterface(utils::Config::get()["inputs"]["keyboard2"],
				{ {"exit", Key::ESCAPE},
				{"characterScreen", Key::TAB},
				{"moveLeft", Key::A},
				{"moveRight", Key::D},
				{"moveUp", Key::W},
				{"moveDown", Key::S},
				{"castPrimary", MouseButton::LEFT} },
				{ {Actions::MOVE_LEFT, Actions::MOVE_RIGHT}, {Actions::MOVE_UP, Actions::MOVE_DOWN} }));

		constexpr float mapX = 30.f;
		constexpr float mapY = 40.f / 2.f;
		constexpr float voidZone = 5.f;
		m_world.addResource<MapBoundaries>(std::vector{ 
			math::AABB3D(glm::vec3(-voidZone - mapX, -mapY, -5.f), glm::vec3(-voidZone, mapY, 5.f))
			, math::AABB3D(glm::vec3(voidZone, -mapY, -5.f), glm::vec3(voidZone + mapX, mapY, 5.f)) }, 2.f);
		
		m_world.addSystem(std::make_unique<systems::PlayerSpawn>(*m_inputs1, *m_inputs2), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::BoundaryGrid>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::Physics>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::Transforms>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::UnitSpawn>(2.f), SystemGroup::Process);
		m_world.addSystem(std::make_unique <systems::PlayerControl>(), SystemGroup::Process);
		m_world.addSystem(std::make_unique<systems::MapBoundary>(), SystemGroup::Process);

		m_world.getResource<graphics::Camera>().setView(
			glm::lookAt(glm::vec3(0.f, 0.f, 50.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)));

		// rendering
		m_world.addSystem(std::make_unique<systems::MeshDrawing>(), SystemGroup::Draw);
		m_world.addSystem(std::make_unique<systems::LineDrawing>(), SystemGroup::Draw);
		m_world.addSystem(std::make_unique<systems::ParticleDrawing>(), SystemGroup::Draw);
	}

	void GSPlay::process(float _deltaTime)
	{
		m_world.process(SystemGroup::Process, _deltaTime);

		if (input::InputManager::isKeyPressed(input::Key::ESCAPE))
			finish();
	}

	void GSPlay::draw(float _deltaTime)
	{
		m_world.process(SystemGroup::Draw, _deltaTime);
	}
}