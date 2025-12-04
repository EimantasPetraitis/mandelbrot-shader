#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei lenght, const GLchar* message, const void* userParam
);

int HandleShaderErrors(GLuint shader);