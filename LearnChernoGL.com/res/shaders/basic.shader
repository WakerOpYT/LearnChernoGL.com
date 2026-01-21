#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 vertexColor;

void main()
{
	gl_Position = position;
	vertexColor = vec4(position.x + 0.5, position.y + 0.5, 0.5, 1.0);
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 vertexColor;

void main()
{
	//color = vec4(0.2, 0.3, 0.8, 1.0);
	color = vertexColor;
};