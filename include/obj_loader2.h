#include <SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>


bool loadOBJ( const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
	);
