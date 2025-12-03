#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
    const GLchar* message, const void* userParam
)
{

    std::cout << "[OpenGL Error] " << "type: " << type << "  id: " << id
        << "  severity: " << severity << "\n" << message << "\n\n\n";
    
    exit(-1);

}

int main()
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    int width = 1280;
    int height = 960;
    
    window = glfwCreateWindow(width, height, "Mandelbrot Set", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "[GLEW Error] Initialization error." << "\n";
    
    std::cout << "\n\nOpenGL version " << glGetString(GL_VERSION) << "\n\n";

    const char* glslVersion = "#version 460";

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleOpenGLErrors, nullptr);

    while (!glfwWindowShouldClose(window))
    {

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

}