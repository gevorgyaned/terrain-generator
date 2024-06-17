#include "../include/shader.h"

void Shader::use() const 
{
	glUseProgram(m_id);
}

GLuint Shader::get_id() const 
{
	return m_id;
}

GLuint Shader::compile_shader(const std::string& contents, GLenum shader_type) const
{
	GLuint shader { glCreateShader(shader_type) };
    const char *ptr = contents.c_str();
	glShaderSource(shader, 1, &ptr, NULL);
	glCompileShader(shader);

	char log_info[512];
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader, 512, NULL, log_info);
		throw std::runtime_error(log_info);
	}

	return shader;
}

GLuint Shader::create_program(GLuint frag_shader, GLuint vert_shader) const
{
	GLuint id = glCreateProgram();
	glAttachShader(id, frag_shader);	
	glAttachShader(id, vert_shader);
	glLinkProgram(id);

	char log_info[512];
	GLint success;

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(id, 512, NULL, log_info);
		throw std::runtime_error(log_info);;
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

