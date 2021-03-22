#pragma once
#ifndef LIBGAME_GRAPHICS_H
#define LIBGAME_GRAPHICS_H
#include "libgame.h"
#include <OpenImageIO/imageio.h>

namespace libgame {
	class Texture2D {
	public:
		int width, height, channels;
		unsigned int textureId;
		Texture2D() = default;
		Texture2D(const std::string & path);
		void Load(const std::string & path);
		~Texture2D();
	};
}

#endif