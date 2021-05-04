#pragma once

#include <string>
#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "external/stb_image.h"

#include <SpringEngine/core.hpp>


namespace SE
{
	class SE_API Texture
	{
	public:
		Texture();
		~Texture();
		Texture(const Texture& src);
		Texture& operator=(const Texture& rhs);
		bool loadBMP(const char*);
		bool loadPNG(const std::string&, unsigned int, bool);
		void bind(unsigned int slot = 0);
		void unbind();
		const unsigned int get() const;
		void setFlipped(bool flipped) { m_flipped = flipped; };

	protected:
		int m_width;
		int m_height;
		int m_imageSize;
		int m_BPP;
		bool m_flipped;
		unsigned int m_texture;
		unsigned char* data;
	};
};