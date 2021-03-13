#ifndef RENDERING_H
#define RENDERING_H

#include "libgame.h"

namespace libgame {
	class Shader {
		GLuint programID;
		GLuint matrixID;
	public:
		Shader();
		Shader(const char* vertex_file_path, const char* fragment_file_path);
		void LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
		GLuint GetProgramID() const {
			return programID;
		}
		GLuint GetMatrixID() const {
			return matrixID;
		}

		void Use();

		~Shader();
	};

	class Renderer {
	public:
		virtual void Render() = 0;
	};


}


#endif