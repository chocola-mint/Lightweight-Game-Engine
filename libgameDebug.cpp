#include "libgameDebug.h"

namespace libgame {
	namespace Debug {
		const bool COUT = false;
		const bool PRINT = true;
		bool PrintOption = COUT;
		void SetDebugOption(bool option) {
			PrintOption = option;
		}

		void Assert(bool condition, const char* message, ...) {
			if (!condition) {
				if (PrintOption == COUT)
					std::cerr << message;
				else {
					va_list args;
					va_start(args, message);
					std::vfprintf(stderr, message, args);
					va_end(args);
				}
				exit(-1);
			}
		}

		void AssertC(bool condition, const char* message) {
			std::cerr << message;
			exit(-1);
		}

		void AssertF(bool condition, const char* message, ...) {
			va_list args;
			va_start(args, message);
			std::vfprintf(stderr, message, args);
			va_end(args);
			exit(-1);
		}

		

		void Log(const char* message) {
			if (PrintOption == COUT)
				std::cout << message;
			else std::fprintf(stdout, message);
		}


		void Log(const char* message, ...) {
			if (PrintOption == COUT)
				std::cout << message;
			else {
				va_list args;
				va_start(args, message);
				std::vfprintf(stdout, message, args);
				va_end(args);
			}
		}

		void LogC(const char* message) {
			std::cout << message;
		}

		void LogF(const char* message, ...) {
			va_list args;
			va_start(args, message);
			std::vfprintf(stdout, message, args);
			va_end(args);
		}
	}
}