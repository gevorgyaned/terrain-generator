#ifndef SHADER_H
#define SHADER_H

#include "../../external/glad/glad.h"
#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <initializer_list>
#include <vector>

#include "utility.h"

class Shader {
public:
	Shader(const char *vert, const char *frag) 
		: m_id { 0 }
	{
        const std::string vert_source = util::read_to_string(vert);
        const std::string frag_source = util::read_to_string(frag);

		try {
			GLuint vert_shader = compile_shader(vert_source, GL_VERTEX_SHADER);
			GLuint frag_shader = compile_shader(frag_source, GL_FRAGMENT_SHADER);

			m_id = create_program(vert_shader, frag_shader);
		} catch (std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			std::abort();
		}
	}

    Shader(const std::string& vert_source, const std::string& frag_source)
        : m_id { 0 }
    {
		try {
			GLuint vert_shader = compile_shader(vert_source, GL_VERTEX_SHADER);
			GLuint frag_shader = compile_shader(frag_source, GL_FRAGMENT_SHADER);

			m_id = create_program(vert_shader, frag_shader);
		} catch (std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			std::abort();
		}
    }

public:
	GLuint get_id() const;
	void use() const;
	GLuint compile_shader(const std::string&, GLenum shader_type) const;
	GLuint create_program(GLuint frag_shader, GLuint vert_shader) const;
	void set_float(const std::vector<float>& value, const std::string& name);
	void set_int(const std::vector<int>& value, const std::string& name);
    void set_matrix(const glm::mat4&, const std::string& name);

private:
	void compile_shader();

private:
	GLuint m_id;
};

#endif /* SHADER_H */
