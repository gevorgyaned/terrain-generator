#ifndef SHADER_H
#define SHADER_H

#include "../../external/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <variant>

#include "utility.h"

class Shader {
public:
    static std::variant<Shader, std::string> create(const char *vertex_source, const char *fragment_shader);

    static std::variant<Shader, std::string> create(const std::string& vertex_source, const std::string& fragment_shader);

public:
	GLuint get_id() const;
	void use() const;

	void set_float(const std::vector<float>& value, const std::string& name);
	void set_int(const std::vector<int>& value, const std::string& name);
    void set_matrix(const glm::mat4&, const std::string& name);

private:
    Shader(GLuint program_id) : m_id { program_id } { }

private:
    static std::variant<GLuint, std::string> compile_shader(const std::string&, GLenum shader_type);
    static std::variant<GLuint, std::string> create_program(GLuint frag_shader, GLuint vert_shader);

private:
	GLuint m_id;
};

#endif /* SHADER_H */
