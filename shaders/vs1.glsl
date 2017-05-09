#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texel;


out vec3 fragnorm;

out vec3 fragpos;

out vec2 texels;

out vec3 theColor;
uniform mat4 Model;
uniform mat4 VP;
uniform vec3 incolor;
void main()
{
	//gl_Position = position;
	gl_Position =  VP * Model * vec4(position, 1.0f);

	fragnorm = normal;

	
	fragpos = vec3(Model * vec4(position, 1.0f));


	//theColor = incolor;
}
