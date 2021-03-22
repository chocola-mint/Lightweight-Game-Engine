#pragma once

#ifndef STD_RENDERERS_H
#define STD_RENDERERS_H

#include "libgameRendering.h"
#include "libgameGraphics.h"

namespace libgame {

	class TextureRenderer : Renderer {
		Texture2D _tex;
	public:
		void Render() override;

	};

}

#endif