#version 330
in vec3 theColor;
in vec3 fragnorm;


in vec3 fragpos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

//out vec4 outputColor;
out vec3 outputColor;

void main()
{
	//outputColor = vec3(1,0,0);

	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 norm = normalize(fragnorm);
    vec3 lightDir = normalize(lightPos - fragpos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

	outputColor = result;
}
