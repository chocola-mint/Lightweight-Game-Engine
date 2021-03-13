#pragma once
#ifndef LIBGAME_DEBUG_H
#define LIBGAME_DEBUG_H
#include <iostream>
#include <cstdio>
#include <cstdarg>

namespace libgame {
	namespace Debug {
		extern const bool COUT;
		extern const bool PRINT;
		extern bool PrintOption;
		void SetDebugOption(bool option);
		void Assert(bool condition, const char* message, ...);
		void AssertC(bool condition, const char* message);
		void AssertF(bool condition, const char* message, ...);
		void Log(const char* message, ...);
		void LogC(const char* message);
		void LogF(const char* message, ...);

	}
}

#endif