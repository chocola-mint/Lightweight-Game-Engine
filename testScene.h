#include "libgame.h"
#include "defaultCamera.h"
#include "primitives.h"
#ifndef TESTSCENE
#define TESTSCENE
namespace libgame {
	class TestScene : public Scene {
	public:
		TestScene();
		~TestScene();
	};
}

#endif