#pragma once

#ifndef MAINCAMERA
#define MAINCAMERA

#include "libgame.h"
#include "libgameDebug.h"

namespace libgame {

	class DefaultCamera : public Camera {
	public:

		~DefaultCamera() override = default;

		Matrix4 Projection() override {
			return glm::perspective(60.0f, (float)VIEWPORT_WIDTH / (float)VIEWPORT_HEIGHT, 0.1f, 100.0f);
		}

		void Update() override {
		}

		void FixedUpdate() override {

		}

		void Draw() override {

		}

		void Start() override {
			forward = Vector3(0, 0, 0);
			up = Vector3(0, 1, 0);
			transform.position = Vector3(0, 0, 1.5);

		}
	};
}

#endif