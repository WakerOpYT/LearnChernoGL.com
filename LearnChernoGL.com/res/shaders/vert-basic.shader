#version 330 core

layout(location = 0) in vec4 position;

out vec4 vertex_color;

void main()
{
    gl_Position = position;
    vertex_color = position;
}