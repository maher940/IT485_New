#version 330
//in vec4 theColor;
//out vec4 outputColor;

in vec2 UV;


out vec3 outputColor;

uniform sampler2D myText;

void main()
{
	outputColor = texture( myText, UV ).rgb;
}
