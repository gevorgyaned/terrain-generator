#include "../include/shader.h"

std::variant<GLuint, std::string> Shader::compile_shader(const std::string& contents, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);
    const char *ptr = contents.c_str();
	glShaderSource(shader, 1, &ptr, NULL);
	glCompileShader(shader);

    std::string log_info(512, '\0');
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader, 512, NULL, const_cast<GLchar *>(log_info.c_str()));
        return log_info;
	}

	return shader;
}

std::variant<GLuint, std::string> Shader::create_program(GLuint frag_shader, GLuint vert_shader)
{
	GLuint id = glCreateProgram();
	glAttachShader(id, frag_shader);	
	glAttachShader(id, vert_shader);
	glLinkProgram(id);

    std::string log_info(512, '\0');
	GLint success;

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(id, 512, NULL, const_cast<GLchar *>(log_info.c_str()));
        return log_info;
	}

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

	return id;
}

void Shader::set_float(const std::vector<float>& value, const std::string& name)
{
	if (value.size() > 4) {
		throw std::runtime_error("too big value");
	}

	GLuint uniform_loc = glGetUniformLocation(m_id, name.c_str());
	switch (value.size()) {
	case 1:
		glUniform1f(uniform_loc, value[0]);
		break;
	case 2:
		glUniform2f(uniform_loc, value[0], value[1]);
		break;
	case 3:
		glUniform3f(uniform_loc, value[0], value[1], value[2]);
		break;
	case 4:
		glUniform4f(uniform_loc, value[0], value[1], value[2], value[3]);
		break;
	}
}

void Shader::set_int(const std::vector<int>& value, const std::string& name)
{
	if (value.size() > 4) {
		throw std::runtime_error("too big value");
	}

	GLuint uniform_loc = glGetUniformLocation(m_id, name.c_str());
	switch (value.size()) {
	case 1:
		glUniform1i(uniform_loc, value[0]);
		break;
	case 2:
		glUniform2i(uniform_loc, value[0], value[1]);
		break;
	case 3:
		glUniform3i(uniform_loc, value[0], value[1], value[2]);
		break;
	case 4:
		glUniform4i(uniform_loc, value[0], value[1], value[2], value[3]);
		break;
	}
}

void Shader::set_matrix(const glm::mat4& matrix, const std::string& name)
{
    GLuint uniform_loc = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

std::variant<Shader, std::string> Shader::create(const char *vertex_filename, const char *fragment_filename)
{
    const std::string vertex_source = util::read_to_string(vertex_filename);
    const std::string fragment_source = util::read_to_string(fragment_filename);

    auto vert_res = compile_shader(vertex_source, GL_VERTEX_SHADER);
    if (const auto *err_value = std::get_if<std::string>(&vert_res)) {
        return *err_value + "vertex shader compile error";  
    }

    auto frag_res = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    if (const auto *err_value = std::get_if<std::string>(&frag_res)) {
        return *err_value + "fragment shader compile error";
    }

    auto vertex_shader = std::get<GLuint>(vert_res);
    auto fragment_shader = std::get<GLuint>(frag_res);

    auto program = create_program(vertex_shader, fragment_shader);
    if (const auto *err_value = std::get_if<std::string>(&program)) {
        return *err_value + "linking error";
    }

    return Shader(std::get<GLuint>(program));
}

void Shader::use() const  { glUseProgram(m_id); }

GLuint Shader::get_id() const { return m_id; }

