#include "shader.h"

std::variant<GLuint, std::string> Shader::compile_shader(const std::string& contents, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);
    const char *ptr = contents.c_str();
	glShaderSource(shader, 1, &ptr, nullptr);
	glCompileShader(shader);

    if (auto err_msg = check_compile_errors(shader)) {
        return *err_msg;
    }

	return shader;
}

std::variant<GLuint, std::string> Shader::create_program(GLuint frag_shader, GLuint vert_shader)
{
	GLuint id = glCreateProgram();
	glAttachShader(id, frag_shader);	
	glAttachShader(id, vert_shader);
	glLinkProgram(id);

    if (auto err_msg = check_program_errors(id)) {
        return *err_msg;
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

	return id;
}

Shader& Shader::set_float3(const glm::vec3& value, std::string_view name)
{
    glUniform3f(glGetUniformLocation(m_id, name.data()), value[0], value[1], value[2]);
	return *this;
}

Shader& Shader::set_int3(const glm::ivec3& value, std::string_view name)
{
    glUniform3i(glGetUniformLocation(m_id, name.data()), value[0], value[1], value[2]);
	return *this;
}

Shader& Shader::set_matrix4(const glm::mat4& matrix, std::string_view name)
{
    const GLint uniform_loc = glGetUniformLocation(m_id, name.data());
    glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(matrix));
	return *this;
}

Shader& Shader::set_matrix3(const glm::mat3& matrix, const std::string_view name)
{
    const GLint uniform_loc = glGetUniformLocation(m_id, name.data());
    glUniformMatrix3fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(matrix));
	return *this;
}

std::variant<Shader, std::string> Shader::create(std::string_view vertex_filename, const char *fragment_filename)
{
    std::string vertex_source = read_to_string(vertex_filename);
    std::string fragment_source = read_to_string(fragment_filename);

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

    const auto program = create_program(vertex_shader, fragment_shader);
    if (const auto *err_value = std::get_if<std::string>(&program)) {
        return *err_value + "linking error";
    }

    return Shader(std::get<GLuint>(program));
}

std::optional<std::string> Shader::check_compile_errors(GLuint program)
{
    int success;
    std::string log_info(512, '\0');

	glGetShaderiv(program, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(program, 512, nullptr, const_cast<GLchar *>(log_info.c_str()));
        return log_info;
	}

    return std::nullopt;
}

std::optional<std::string> Shader::check_program_errors(GLuint program)
{
    int success;
    std::string log_info(512, '\0');

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        glGetProgramInfoLog(program, 512, nullptr, const_cast<GLchar *>(log_info.c_str()));
        return log_info;
    }

    return std::nullopt;
}

std::string read_to_string(std::string_view filename)
{
    std::ifstream stream(filename.data());

    std::string result;
    std::string line;
    while (std::getline(stream, line)) {
        result += line;
        result.push_back('\n');
    }
    
    stream.close();
    return result;
}

void Shader::use() const  { glUseProgram(m_id); }

GLuint Shader::get_id() const { return m_id; }

