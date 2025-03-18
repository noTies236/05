// Libs
#include "iostream"
#include "fstream"
#include "vector"
#include "string"

// Headers
#include "Pipeline.h"

// Global
GLuint VAO;
GLuint VBO;
GLuint gIndexBufferObject = 0;
GLuint gVertexBufferObject = 0;
//GLuint colorVBO;

// Shader program
GLuint gVertex;
GLuint gFragment;

// Program
GLuint gProgramPipeline = 0;

namespace Pipeline {

    // Função para carregar o shader a partir de um arquivo
    std::string LoadShaderAsString(const std::string& fileName)
    {
        std::string result = "";
        std::string line = "";
        std::ifstream myFile(fileName.c_str());

        if (myFile.is_open()) {
            while (std::getline(myFile, line)) {
                result += line + "\n";
            }

            myFile.close();
        }

        return result;
    }

    // Função para configurar a geometria do triângulo
    void VertexSpecification()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<GLfloat> vertexData{
            // 0 - vertex           // colors
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   
            // 1 - vertex 
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
            // 2 - vertex 
            -0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,       
            // 3 - vertex 
            0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,   
        };
        
        // Criar e configurar VBO para posição
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

        const std::vector<GLuint> indexBufferData{2, 0, 1,3, 2, 1};

        // setup the index buffer object (IBO i.e. EBO)
        glGenBuffers(1, &gIndexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
        
        // populate our index buffer
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            indexBufferData.size() * sizeof(GLfloat), 
            indexBufferData.data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 
                              3, 
             GL_FLOAT, GL_FALSE, 
             sizeof(GL_FLOAT)*6, 
                      (void*)0);

        // color information
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, // Índice do atributo (1 corresponde a 'aColor' no shader)
                              3, // O atributo tem 3 componentes (vermelho, verde, azul)
                       GL_FLOAT, // O tipo dos dados é GL_FLOAT (valores de ponto flutuante)
                       GL_FALSE, // Não precisa normalizar os dados (não estamos usando inteiros ou valores em um intervalo)
               sizeof(GL_FLOAT) * 6, //  O 'stride' é a distância entre dois vértices consecutivos (6 valores para cada vértice)
            (GLvoid*)(sizeof(GL_FLOAT) * 3)); // O 'offset' é o ponto onde começa a cor (3 valores para a posição)

        // Desativar VAO depois de configurar tudo
        glBindVertexArray(0);
    }

    // Função para compilar o shader
    GLuint CompileShaderProgram(GLuint type, const std::string& source)
    {
        GLuint shaderObject = glCreateShader(type); // Corrigido para usar o tipo correto

        const char* src = source.c_str();
        glShaderSource(shaderObject, 1, &src, nullptr);
        glCompileShader(shaderObject);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
            std::cout << "Erro na compilação do shader: " << infoLog << std::endl;
        }

        return shaderObject;
    }

    // Função para criar o programa de shader
    GLuint CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
    {
        GLuint programObject = glCreateProgram();

        GLuint myVertexShader = CompileShaderProgram(GL_VERTEX_SHADER, vertexSource); // Corrigido para GL_VERTEX_SHADER
        GLuint myFragmentShader = CompileShaderProgram(GL_FRAGMENT_SHADER, fragmentSource); // Corrigido para GL_FRAGMENT_SHADER

        glAttachShader(programObject, myVertexShader);
        glAttachShader(programObject, myFragmentShader);
        glLinkProgram(programObject);

        return programObject;
    }

    // Função para configurar o pipeline gráfico
    void GraphicsPipeline()
    {
        std::cout << "GraphicsPipeline\n";

        std::string vertexShaderSource = LoadShaderAsString("./Shaders/OpenGL/vert.glsl");
        std::string fragmentShaderSource = LoadShaderAsString("./Shaders/OpenGL/frag.glsl");

        gProgramPipeline = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    // Função para preparar a tela para desenhar
    void PreDraw()
    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glViewport(0, 0, 640, 480);
        glClearColor(0.f, 1.f, 1.f, 1.f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glUseProgram(gProgramPipeline);
    }

    // Função para desenhar o triângulo
    void Draw()
    {
        VertexSpecification();
        GraphicsPipeline();
        PreDraw();

        glUseProgram(gProgramPipeline); // Ativar o shader antes de desenhar
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
