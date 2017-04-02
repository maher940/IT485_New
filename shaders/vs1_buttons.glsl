#version 330
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 theColor;
uniform mat4 MVP;
void main()
{
	gl_Position = position;
	//gl_Position = MVP * vec4(position, 1.0f);
	theColor = color;
}
