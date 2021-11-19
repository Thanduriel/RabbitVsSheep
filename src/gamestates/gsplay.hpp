#pragma once

#include <engine/game/core/gamestate.hpp>
#include <engine/game/core/world.hpp>
#include <engine/input/inputmanager.hpp>
#include <engine/graphics/camera.hpp>

namespace rvs {

	class GSPlay : public game::GameState
	{
	public:
		GSPlay();

		void process(float _deltaTime) override;
		void draw(float _deltaTime) override;

	private:
		game::World<graphics::Camera> m_world;

		std::unique_ptr<input::InputInterface> m_inputs;
	};
}