#version 330
in vec3 theColor;
//out vec4 outputColor;
out vec3 outputColor;




void main()
{
	//outputColor = vec3(1,0,0);
	outputColor = theColor;
}
