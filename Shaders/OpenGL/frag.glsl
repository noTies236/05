#version 330 core

in vec3 vertexColor; // Cor recebida do vertex shader
out vec4 FragColor;  // Saída da cor final do pixel

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Define a cor do pixel
}
