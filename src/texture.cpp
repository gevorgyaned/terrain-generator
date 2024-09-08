#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.hpp"

Texture2D::Texture2D(std::string_view path) {
    int width, height, channels;
    auto *data = stbi_load(path.data(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "cannot open texture" << std::endl;
    }

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture2D::bind() const 
{
    glBindTexture(1, _id);
}

void Texture2D::unbind() const 
{
    glBindTexture(1, 0);
}
