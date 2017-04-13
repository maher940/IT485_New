#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
out vec4 theColor;
uniform mat4 Model;
uniform mat4 VP;
void main()
{
	//gl_Position = position;
	gl_Position =  VP * Model * vec4(position, 1.0f);
	theColor = color;
}
