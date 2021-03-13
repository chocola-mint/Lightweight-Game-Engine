#include "libgame.h"
#include "libgameDebug.h"
#include "testScene.h"
namespace libgame {
	void GameInit() {
		Debug::Log("Init game\n");
		LoadScene(new TestScene());
	}
}