#version 460 core
out vec4 FragColor;
  
uniform float vertexColor; 

void main()
{
    FragColor = vec4(1.0f, vertexColor, 1.0f, 1.0f);
} 