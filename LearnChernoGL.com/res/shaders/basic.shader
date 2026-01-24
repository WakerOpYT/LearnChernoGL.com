#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 vertex_color;

void main()
{
	gl_Position = position;
	vertex_color = position;
}



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform float u_Rainbow_strength;

in vec4 vertex_color;

void main()
{
	vec3 baseColor = vertex_color.rgb + 0.5;
	color = vec4(baseColor.rg * u_Rainbow_strength, u_Rainbow_strength, 1.0);
}