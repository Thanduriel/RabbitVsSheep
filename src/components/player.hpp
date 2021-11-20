#pragma once

#include <engine/input/inputmanager.hpp>

namespace game {
namespace components{

	struct PlayerController
	{
		PlayerController(const input::InputInterface& _inputs) : inputs(&_inputs) {}
		const input::InputInterface* inputs;
	};
}
}