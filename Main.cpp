// Default lib C++
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

// Lib
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

// VAO
GLuint VAO;
GLuint VBO;
GLuint VBO2;

std::string LoadShaderAsString(const std::string& filename);
void CreateGraphicsPipelile();
GLuint CompileShaderProgram(GLuint type, const std::string& source);
void VertexSpecification();
GLuint CreateShaderProgram(const std::string& vertexshadersource, const std::string& framentshadersource);
void Draw();
void PreDraw();

// Global
GLuint gGraphicsPipelineShaderProgram = 0;

std::string LoadShaderAsString(const std::string& filename)
{   // resulting shader program loaded as a single string
    std::string result = "";

    std::string line = "";
    std::ifstream myFile(filename.c_str());
    
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + "\n";
        }
        myFile.close();
    }

    std::cout << result;

    return result;
}

void VertexSpecification()
{
    glGenVertexArrays(1, &VAO); // Gera um buffer e armazena seu ID em VBO
    glBindVertexArray(VAO);

    std::vector<GLfloat> vertexPosition = {
        // Triângulo 1
        0.5f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        // Triângulo 2
        -0.5f, -0.8f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        // Triângulo 3
        1.0f, 1.0f, 0.0f,  // Ponto // Ponto 1 do terceiro triângulo
        0.0f, 0.5f, 0.4f,  // Ponto 2 do terceiro triângulo
        1.0f, 0.0f, 1.0f   // Ponto 3 do terceiro triângulo
    };

    std::vector<GLfloat> vertexColor = {
        // Cores para o Triângulo 1
        1.0f, 0.0f, 0.0f, // Vermelho
        0.0f, 1.0f, 0.0f, // Verde
        0.0f, 0.0f, 1.0f, // Azul

        // Cores para o Triângulo 2
        1.0f, 1.0f, 0.0f, // Amarelo
        0.0f, 1.0f, 1.0f, // Ciano
        1.0f, 0.0f, 1.0f, // Magenta

        // Cores para o Triângulo 3
        1.0f, 0.0f, 0.0f, // Magenta
        0.0f, 1.0f, 0.0f, // Roxo
        0.0f, 0.0f, 1.0f  // Verde escuro
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW); // Enviar dados para a GPU
    glBufferData(GL_ARRAY_BUFFER, vertexColor.size() * sizeof(GLfloat), vertexColor.data(), GL_STATIC_DRAW); // Enviar dados para a GPU

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

GLuint CompileShaderProgram(GLuint type, const std::string& source)
{
    GLuint shaderObject;
        
    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }

    if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexshadersource, const std::string& framentshadersource)
{
    GLuint programObject = glCreateProgram();
    GLuint myVertexShader = CompileShaderProgram(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShaderProgram(GL_FRAGMENT_SHADER, framentshadersource);

    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);
    glValidateProgram(programObject);

    return programObject;
}

void CreateGraphicsPipelile()
{
    std::string vertexShaderSource    = LoadShaderAsString("./Shaders/vert.glsl");
    std::string fragmentShaderSource  = LoadShaderAsString("./Shaders/frag.glsl");

    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, 640, 480);
    glClearColor(0.f, 1.f, 1.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(gGraphicsPipelineShaderProgram);
}

int i = 0;
void Draw()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    
    std::cout << "---->" << i << "\n";
    i++;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criar janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "03", NULL, NULL);
    if (!window) {
        std::cout << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Tornar o contexto OpenGL atual
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    VertexSpecification();
    
    CreateGraphicsPipelile();
   
    while (!glfwWindowShouldClose(window)) {
        PreDraw();
        Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
        //glClearColor(1.f, 1.f, 0.f, 1.f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }
}
