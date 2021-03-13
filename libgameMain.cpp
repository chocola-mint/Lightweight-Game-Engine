#include "libgame.h"
using namespace libgame;

int main() {
	EngineInit();
	GameInit();
	GameLoop();
	return 0;
}