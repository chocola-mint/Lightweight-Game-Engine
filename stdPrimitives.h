#pragma once
#ifndef STD_PRIMITIVES_H
#define STD_PRIMITIVES_H
#include "libgameRendering.h"
#include "libgameDebug.h"

namespace libgame {
	class TriangleRenderer : public Renderer {
		GLuint vertexBufferId, colorBufferId;
	public:
		TriangleRenderer() : vertexBufferId(0), colorBufferId(0) {}
		TriangleRenderer(GLuint vId, GLuint cId) : vertexBufferId(vId), colorBufferId(cId) {};

		void Render() override {
			// 1st attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			// 2nd attribute buffer : colors
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);

			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 1 * 3); // 1 triangle
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}
	};

	class Triangle : public Object {
	private:
		GLfloat vertices[9];
		GLfloat colors[9];
		GLuint vertexBufferId;
		GLuint colorBufferId;
		TriangleRenderer renderer;
		Shader shader;
	public:
		Triangle() : vertices{ 0, 1, 0, 1, 0, 0, 1, 1, 0 }, colors{ 1, 1, 1, 1, 1, 1, 1, 1, 1 } {
			// Generate 1 buffer, put the resulting identifier in vertexbuffer
			glGenBuffers(1, &vertexBufferId);
			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &colorBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
			renderer = TriangleRenderer(vertexBufferId, colorBufferId);
			shader.LoadShaders("bareVertShader.vert", "bareFragShader.frag");
		};

		void SetVertices(Vector3 vert0, Vector3 vert1, Vector3 vert2) {
			vertices[0] = vert0.x; vertices[1] = vert0.y; vertices[2] = vert0.z;
			vertices[3] = vert1.x; vertices[4] = vert1.y; vertices[5] = vert1.z;
			vertices[6] = vert2.x; vertices[7] = vert2.y; vertices[8] = vert2.z;
			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		}

		void SetColors(Vector3 color0, Vector3 color1, Vector3 color2) {

			colors[0] = color0.x; colors[1] = color0.y; colors[2] = color0.z;
			colors[3] = color1.x; colors[4] = color1.y; colors[5] = color1.z;
			colors[6] = color2.x; colors[7] = color2.y; colors[8] = color2.z;
			glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
		}

		void Start() override {

		}

		void Update() override {
			//transform.rotation.z += deltaTime;
		}

		void FixedUpdate() override {
			transform.Rotate(fixedDeltaTime, Vector3(0, 0, 1));
			//transform.rotation.z += fixedDeltaTime;

		}

		void Draw() override {
			shader.Use();
			renderer.Render();
		}


	};
}

#endif