#include "libgameGraphics.h"
#include "libgameDebug.h"
namespace libgame {

	Texture2D::Texture2D(const std::string& path) {
		Load(path);
	}

	void Texture2D::Load(const std::string& path) {
		UINT8* _data;
		auto __img_handle = OIIO::ImageInput::open(path);
		Debug::Assert(__img_handle != nullptr, "Failed to open texture at path: %s\n", path.c_str());
		const OIIO::ImageSpec& __spec = __img_handle->spec();
		width = __spec.width;
		height = __spec.height;
		channels = __spec.nchannels;
		__img_handle->read_image(OIIO::TypeDesc::UINT8, _data);
		__img_handle->close();
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
		glGenerateMipmap(GL_TEXTURE_2D);
		delete _data;


	}

	Texture2D::~Texture2D() {

	}
}