#version 330 core

layout (location = 0) in vec3 aPos;   // Posição do vértice
layout (location = 1) in vec3 aColor; // Cor do vértice

out vec3 vertexColor; // Envia a cor para o fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor; // Corrigido: faltava o ponto e vírgula aqui
}
