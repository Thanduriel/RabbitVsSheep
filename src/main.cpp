#include "gamestates/gsplay.hpp"
#include <engine/game/core/game.hpp>

int main()
{
	game::Game game;
	game.run(std::make_unique<rvs::GSPlay>());
}