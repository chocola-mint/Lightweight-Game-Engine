#include "libgameRendering.h"
#include "libgameDebug.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
namespace libgame {
	Shader::Shader() : programID(0), matrixID(0) {};
	void Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << VertexShaderStream.rdbuf();
			VertexShaderCode = sstr.str();
			VertexShaderStream.close();
		}
		else {
			Debug::Assert(false, "Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
			exit(-1);
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << FragmentShaderStream.rdbuf();
			FragmentShaderCode = sstr.str();
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		
		Debug::Log("Compiling shader : %s\n", vertex_file_path);
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			Debug::Assert(false, "%s\n", &VertexShaderErrorMessage[0]);
		}

		// Compile Fragment Shader
		Debug::Log("Compiling shader : %s\n", fragment_file_path);
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			Debug::Assert(false, "%s\n", &FragmentShaderErrorMessage[0]);
		}

		// Link the program
		Debug::Log("Linking program\n");
		programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		glGetProgramiv(programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			Debug::Assert(false, "%s\n", &ProgramErrorMessage[0]);
		}

		glDetachShader(programID, VertexShaderID);
		glDetachShader(programID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		matrixID = glGetUniformLocation(programID, "MVP");
	}
	Shader::Shader(const char* vertex_file_path, const char* fragment_file_path) {
		LoadShaders(vertex_file_path, fragment_file_path);
	}

	void Shader::Use() {
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
		glUseProgram(programID);
	}

	Shader::~Shader() {
		glDeleteProgram(programID);
	}
}