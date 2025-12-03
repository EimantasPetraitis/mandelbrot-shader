#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

float bounds[4];
float offsetX = -0.6f;
float offsetY = 0.0f;
float zoom = 0.0f;
float aspectRatio;

int u_BoundsX;
int u_BoundsY;

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
    const GLchar* message, const void* userParam
)
{

    std::cout << "[OpenGL Error] " << "type: " << type << "  id: " << id
        << "  severity: " << severity << "\n" << message << "\n\n\n";
    
    exit(-1);

}

std::string ReadFile(const std::string& path)
{

    std::ifstream fileStream(path);
    std::ostringstream stringStream;
    stringStream << fileStream.rdbuf();

    return stringStream.str();

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

void RecalculateBounds()
{

    float zoomExp = pow(2.0f, -zoom);

    float Xmin = -aspectRatio * zoomExp + offsetX;
    float Xmax = aspectRatio * zoomExp + offsetX;
    float Ymin = -zoomExp + offsetY;
    float Ymax = zoomExp + offsetY;

    bounds[0] = Xmin;
    bounds[1] = Xmax;
    bounds[2] = Ymin;
    bounds[3] = Ymax;

}

void Redraw()
{

    RecalculateBounds();

    glUniform2f(u_BoundsX, bounds[0], bounds[1]);
    glUniform2f(u_BoundsY, bounds[2], bounds[3]);

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void framebufferResize(
    GLFWwindow* window, int width, int height
)
{

    glViewport(0, 0, width, height);

    aspectRatio = (float)width / (float)height;

    Redraw();

}

int main()
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    int width = 1400;
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

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleOpenGLErrors, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    // Important variable definitions

    float vertices[8] = {
        -1.0f,  1.0f,
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f
    };

    int indices[6] = {
        0, 1, 2,
        0, 2, 3
    };

    std::string vertexShaderPath = "resources/Mandelbrot.vert";
    std::string fragmentShaderPath = "resources/Mandelbrot.frag";

    aspectRatio = (float)width / (float)height;

    // Vertex and index buffers, vertex array

    GLuint vertexArrayId = 0;
    GLuint vertexBufferId = 0;
    GLuint indexBufferId = 0;

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(
        GL_ARRAY_BUFFER, 8 * 4, &vertices, GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0
    );

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 6 * 4, &indices, GL_STATIC_DRAW
    );

    // Shaders

    std::string vertSrcStr = ReadFile(vertexShaderPath);
    const char* vertSrc = vertSrcStr.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, nullptr);
    glCompileShader(vertexShader);

    int result = HandleShaderErrors(vertexShader);
    if (result == -1)
        return -1;

    std::string fragSrcStr = ReadFile(fragmentShaderPath);
    const char* fragSrc = fragSrcStr.c_str();
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
    glCompileShader(fragmentShader);

    result = HandleShaderErrors(fragmentShader);
    if (result == -1)
        return -1;

    // Shader linking

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glValidateProgram(program);

    int validationResult;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &validationResult);

    if (validationResult == GL_FALSE)
    {

        int messageLenght;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &messageLenght);
        char* message = (char*)alloca(messageLenght * sizeof(char));
        glGetProgramInfoLog(program, messageLenght, &messageLenght, message);

        std::cout << "Error: Failed to validate program.\n";
        std::cout << message << "\n";

        glDeleteProgram(program);
        return 0;

    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(program);

    // Uniforms

    u_BoundsX = glGetUniformLocation(program, "u_BoundsX");
    u_BoundsY = glGetUniformLocation(program, "u_BoundsY");

    // Drawing

    glfwSetFramebufferSizeCallback(
        window, framebufferResize
    );

    glBindVertexArray(vertexArrayId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glUseProgram(program);

    RecalculateBounds();

    glUniform2f(u_BoundsX, bounds[0], bounds[1]);
    glUniform2f(u_BoundsY, bounds[2], bounds[3]);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwWaitEvents();

    }

    glfwTerminate();

}