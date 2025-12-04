#include "ErrorHandling.h"

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
    const GLchar* message, const void* userParam
)
{

    std::cout << "[OpenGL Error] " << "type: " << type << "  id: " << id
        << "  severity: " << severity << "\n" << message << "\n\n\n";
    
    exit(-1);

}

int HandleShaderErrors(GLuint shader)
{

    int compilationResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationResult);

    if (compilationResult == GL_FALSE)
    {

        int messageLenght;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLenght);
        char* message = (char*)alloca(messageLenght * sizeof(char));
        glGetShaderInfoLog(shader, messageLenght, &messageLenght, message);

        std::cout << "Error: Failed to compile shader.\n";
        std::cout << message << "\n";

        glDeleteShader(shader);

        return -1;

    }

    return 0;

}