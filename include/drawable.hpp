#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "shader.hpp"
#include "usings.hpp"

class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void draw(Shader shader) const = 0;

    virtual std::string get_shader_name() const = 0;
};

#endif /* DRAWABLE_HPP */

