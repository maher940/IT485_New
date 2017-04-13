#include "testload.h"


#include <vector>
#include "simple_logger.h"
#include <glm\vec3.hpp>
#include <string>

bool TestScene(const char * path)
{

	char buf[512];

	std::vector<char[256]>temp_models;

	std::vector<glm::vec3>temp_position;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	
	while (fscanf(file, "%[^\n]\n", buf) != EOF)
	{
		
		glm::vec3 pos;

		//char str[256];
		

		//slog(str);

		if (buf[0] == 'c')
		{
			slog("Here");
		}

		

		//char str;

		//str = malloc(200 * sizeof(char));
		
		//std::string str;1
		//sscanf(buf, "%s %f %f %f", &pos.x, &pos.y, &pos.x);
		
		//sscanf(buf, "%[^\t\n] %f %f %f");

		//temp_models.push_back(str);
		//temp_position.push_back(pos);
		//scene.models.push_back(str);
		//scene.positions.push_back(pos);
		
	}
	


}



