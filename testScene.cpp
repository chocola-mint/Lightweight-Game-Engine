
#include "testScene.h"
using namespace libgame;

TestScene::TestScene() {
		
	Debug::Log("Loading scene\n");
	Debug::SetDebugOption(Debug::PRINT);
	mainCamera = new DefaultCamera();
	Triangle* triangle = new Triangle;
	triangle->transform.scale *= 3;
	triangle->SetColors(Vector3(1, 0, 0), Vector3(1, 0, 0), Vector3(1, 0, 0));
	RegisterObject(triangle);
	Debug::Log("End loading scene\n");
}



TestScene::~TestScene() {

}
