#ifndef LIBGAME_H
#define LIBGAME_H

#include "libgame.h"
#include "libgameInputManager.h"
#include "libgameRendering.h"
#include "libgameDebug.h"
namespace libgame {
	std::vector<Object*> startList;
	std::set<Object*> activeList;
	Matrix4 MVP = Matrix4(1.0f);
	Window* window = nullptr;
	Scene* currentScene = nullptr;
	

	void ErrorCallback(int error, const char* description)
	{
		Debug::Assert(false, description);
	}

	 

	void RegisterObject(Object* newObject) {
		startList.push_back(newObject);
	}


	
	void StartObjects() {
		while (!startList.empty()) {
			startList.back()->isActive = true;
			startList.back()->Start();
			activeList.insert(startList.back());
			startList.pop_back();
		}
	}

	std::chrono::time_point<std::chrono::system_clock> lastUpdateTimestamp = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> lastFixedUpdateTimestamp = std::chrono::system_clock::now();
	double deltaTime = 0.0f;
	double fixedDeltaTime = 1 / 60.0f;


	void UpdateObjects() {

		deltaTime = std::chrono::duration<double>(std::chrono::system_clock::now() - lastUpdateTimestamp).count();
		lastUpdateTimestamp = std::chrono::system_clock::now();

		std::vector<std::set<Object*>::iterator> delList;
		for (auto iter = activeList.begin(); iter != activeList.end(); ++iter) {
			if ((*iter)->isActive)
				(*iter)->Update();
		}


		if (std::chrono::duration<double>(std::chrono::system_clock::now() - lastFixedUpdateTimestamp).count() > fixedDeltaTime) {

			for (auto iter = activeList.begin(); iter != activeList.end(); ++iter) {
				if ((*iter)->isActive)
					(*iter)->FixedUpdate();
				else delList.push_back(iter);
			}

			InputManager::Key::StateUpdate();
			lastFixedUpdateTimestamp = std::chrono::system_clock::now();
		}

		for (auto delIter : delList) {
			delete* delIter;
			activeList.erase(delIter);
		}


	}


	void DrawObjects() {
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Matrix4 ViewProjection = currentScene->mainCamera->Projection() * currentScene->mainCamera->View();
		for (auto iter = activeList.begin(); iter != activeList.end(); ++iter) {
			MVP = ViewProjection * (*iter)->transform.Model();
			(*iter)->Draw();
		}
	}
	
	


	void EngineInit() {
		/* Initialize the library */
		if (!glfwInit())
			exit(-1);

		window = glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(-1);
		}

		glfwSetKeyCallback(window, InputManager::Key::Callback);
		glfwSetErrorCallback(ErrorCallback);
		glfwSetMouseButtonCallback(window, InputManager::Mouse::ButtonCallback);
		glfwSetScrollCallback(window, InputManager::Mouse::ScrollCallback);


		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Setup glad */
		gladLoadGL();

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

	}

	void UnloadCurrentScene() {
		if (currentScene != nullptr){
			for (auto _obj : startList)
				delete _obj;
			startList.clear();
			for (auto _obj : activeList)
				delete _obj;
			activeList.clear();
			delete currentScene;
		}
	}

	void LoadScene(Scene* newScene) {
		UnloadCurrentScene();
		currentScene = newScene;
		RegisterObject(currentScene->mainCamera);
	}


	void GameLoop() {

		while (!glfwWindowShouldClose(window)) {
			StartObjects();
			UpdateObjects();
			DrawObjects();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		UnloadCurrentScene();
		glfwTerminate();

	}


}



#endif
