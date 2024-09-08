#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <string_view>
#include <iostream>

class Texture2D {
public:
    Texture2D(std::string_view path);

    void bind() const;
    void unbind() const;

    GLuint get_texture() const { return _id; }

private:
    GLuint _id;
};

#endif /* TEXTURE_HPP */

