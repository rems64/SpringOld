#include <SpringEngine/Graphics/Texture.hpp>

namespace SE
{

    Texture::Texture() : m_texture(0), m_imageSize(0), m_width(0), m_height(0), data(nullptr), m_BPP(0)
    {
    }

    Texture::~Texture()
    {
    }

    Texture::Texture(const Texture& src)
    {
        //std::cout << "[INTERNAL INFO] Copying texture" << std::endl;
        m_width = src.m_width;
        m_height = src.m_height;
        m_imageSize = src.m_imageSize;
        m_BPP = src.m_BPP;
        m_texture = src.m_texture;
        data = src.data;
    }

    Texture& Texture::operator=(const Texture& rhs)
    {
        //std::cout << "[INTERNAL INFO] Copying texture from = operator" << std::endl;
        if (this != &rhs)
        {
            m_width = rhs.m_width;
            m_height = rhs.m_height;
            m_imageSize = rhs.m_imageSize;
            m_BPP = rhs.m_BPP;
            m_texture = rhs.m_texture;
            data = rhs.data;
        }
        return *this;
    }

    void Texture::bind(unsigned int slot)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
    }

    void Texture::unbind()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    const unsigned int Texture::get() const
    {
        return m_texture;
    }

    bool Texture::loadBMP(const char* path)
    {
        unsigned char header[54];
        unsigned int dataPos;     // Position in the file where the actual data begins
        // Actual RGB data
        FILE* file = fopen(path, "rb");
        if (!file)
        {
            //printf("Image not loaded");
            SE_CORE_ERROR("BMP texture not found {0}", path);
            return 0;
        }
        if (fread(header, 1, 54, file) != 54)
        {
            //printf("Error with header");
            SE_CORE_ERROR("Error while reading BMP header {0}", path);
            return 0;
        }
        if (header[0] != 'B' || header[1] != 'M')
        {
            //printf("Header error");
            SE_CORE_ERROR("Error with BMP header {0}", path);
            return 0;
        }
        dataPos = *(int*)&(header[0x0A]);
        m_imageSize = *(int*)&(header[0x22]);
        m_width = *(int*)&(header[0x12]);
        m_height = *(int*)&(header[0x16]);

        if (m_imageSize == 0)
        {
            m_imageSize = m_width * m_height * 3; // 3 : one byte for each Red, Green and Blue component
        }
        if (dataPos == 0)
        {
            dataPos = 54; // The BMP header is done that way
        }

        // Create a buffer
        data = new unsigned char[m_imageSize];

        // Read the actual data from the file into the buffer
        fread(data, 1, m_imageSize, file);

        //Everything is in memory now, the file can be closed
        fclose(file);

        GLCall(glGenTextures(1, &m_texture));

        bind();

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        return 1;
    };

    bool Texture::loadPNG(const std::string& path, unsigned int depth, bool invert)
    {
        stbi_set_flip_vertically_on_load(1);
        data = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, STBI_rgb_alpha);
        if (!data)
        {
            SE_CORE_WARN("Unable to laod texture ({0})", path.c_str());
        }

        GLCall(glGenTextures(1, &m_texture));

        bind();

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        if (data)
        {
            stbi_image_free(data);
        }
        return 1;
    };
}