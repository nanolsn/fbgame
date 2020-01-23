#include "shader.h"

#include <fstream>
#include <stdexcept>

using namespace engine;

static std::string read_file(const char *file) {
    std::ifstream ifs(file);
    return std::string(
            (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>())
    );
}

static void check_error(GLuint shader_handler) {
    GLint success;
    GLchar info_log[512];
    glGetShaderiv(shader_handler, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader_handler, 512, nullptr, info_log);
        std::string info("shader compilation failed\n");
        info.append(info_log);

        throw std::runtime_error(info);
    }
}

static GLuint create_shader(const char *file, GLenum shader_type) {
    GLuint shader_handler = glCreateShader(shader_type);
    std::string code = read_file(file);
    const char *code_ptr = code.c_str();

    glShaderSource(shader_handler, 1, &code_ptr, nullptr);
    glCompileShader(shader_handler);

    check_error(shader_handler);

    return shader_handler;
}

shader::shader(const char *vs_file, const char *fs_file) {
    GLuint vertex_shader = create_shader(vs_file, GL_VERTEX_SHADER);
    GLuint fragment_shader = create_shader(fs_file, GL_FRAGMENT_SHADER);

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint success;
    GLchar info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::string info("shader program building failed\n");
        info.append(info_log);

        throw std::runtime_error(info);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void shader::use() const {
    glUseProgram(shader_program);
}