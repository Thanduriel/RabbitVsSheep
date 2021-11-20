#pragma once

#include <engine/game/core/gamestate.hpp>
#include <engine/game/core/world.hpp>
#include <engine/input/inputmanager.hpp>
#include <engine/graphics/camera.hpp>

namespace game {

	class GSPlay : public GameState
	{
	public:
		GSPlay();

		void process(float _deltaTime) override;
		void draw(float _deltaTime) override;

	private:
		World<graphics::Camera> m_world;

		std::unique_ptr<input::InputInterface> m_inputs1;
		std::unique_ptr<input::InputInterface> m_inputs2;
	};
}