#include "Game/Game.h"

//in earlier version,everything is created in main,that's very hard to read
//if you're interested in how this project is reshaped, see my commits in github repo
//now they're moved to the Class Game, main looks much better now
int main()
{
	Game game{};
	game.init();
	game.run();
}