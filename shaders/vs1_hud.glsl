#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;

//out vec4 theColor;

//uniform mat4 MVP;

out vec2 UV;

void main()
{
	gl_Position = position;
	//gl_Position = MVP * vec4(position, 1.0f);
	UV = vertexUV;
}
