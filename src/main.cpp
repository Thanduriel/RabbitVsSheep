#include "gamestates/gsplay.hpp"
#include <engine/game/core/game.hpp>

int main()
{
	using namespace game;

	Game game;
	game.run(std::make_unique<GSPlay>());
}