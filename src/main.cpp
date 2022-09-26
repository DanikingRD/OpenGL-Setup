#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int compileShader(unsigned int type, const std::string& src)
{
    unsigned int shaderId = glCreateShader(type);
    const char *src_ptr = src.c_str();
    glShaderSource(shaderId, 1, &src_ptr, nullptr);
    glCompileShader(shaderId);
    int res;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &len);
        char *message = new char();
        glGetShaderInfoLog(shaderId, len, &len, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment" ) << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shaderId);
        return 0;
    }
    return shaderId;
}
static int createProgram(const std::string& vShader, const std::string& fShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vShader);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!\n";
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    const unsigned int bufferLength = 6;
    float vertexBufferData[bufferLength] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f,
             
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferLength, vertexBufferData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
    // Shaders
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec4 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos);\n"
    "}";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fColor;\n"
    "void main()\n"
    "{\n"
    "   fColor = vec4(0.4f, 0.6f, 0.9f, 1.0f);\n"
    "}";

   unsigned int program = createProgram(vertexShaderSource, fragmentShaderSource);
   glUseProgram(program);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}