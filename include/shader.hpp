#ifndef SHADER_H
#define SHADER_H

#include <glm/gtc/type_ptr.hpp>

#include <istream>
#include <fstream>
#include <variant>
#include <string_view>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    static std::variant<Shader, std::string> create(std::string_view, const char *fragment_shader);
    static std::variant<Shader, std::string> create(const std::string& vertex_source, const std::string& fragment_shader);

public:
	GLuint get_id() const;
	void use() const;

	Shader& set_float3(const glm::vec3& value, std::string_view name);
	Shader& set_int3(const glm::ivec3& value, std::string_view name);
    Shader& set_matrix4(const glm::mat4&, std::string_view name);
    Shader& set_matrix3(const glm::mat3&, std::string_view name);

    Shader(Shader const &) = default;
    Shader() = default;

    Shader(const GLuint program_id) : m_id { program_id } { }
private:

private:
    static std::variant<GLuint, std::string> compile_shader(const std::string&, GLenum shader_type);
    static std::variant<GLuint, std::string> create_program(GLuint frag_shader, GLuint vert_shader);

    static std::string read_to_string(std::string_view filename);

private:
	GLuint m_id;
};

#endif /* SHADER_H */
