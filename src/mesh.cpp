#include "mesh.h"
#include <list>
#include <algorithm>
#include "SOIL.h"
extern GLuint vao;
GLuint vertexbuffer;
GLuint normalbuffer;
GLuint UVbuffer;
GLuint IndexVBO;
extern GLuint triangleBufferObject;
GLuint TextureMesh;
bool Iarray::operator==(const Iarray &other)
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) 
{

	//this->vertices = vertices;
	//this->indices = indices;
	//this->Load_Obj();

	//this->Load_Obj("monnkey.obj");


}

Mesh::~Mesh()
{



}


bool Mesh::Load_Obj(const char * path)
{

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	//std::vector< unsigned int> Indices;
	//unsigned int[] 
	//std::list<Vertex> Indices_list;

	//std::list<unsigned int> Indices;


	//std::list<unsigned int [3]> Index_list;

	std::vector<Iarray> Index_list;

	std::vector<unsigned int> Indices;

	std::vector<Iarray>::iterator it;
	std::vector<Iarray>::iterator it2;
	std::vector<Iarray>::iterator it3;

	std::vector < glm::vec3 >  out_vertices;
	std::vector < glm::vec3 >  out_normals;
	std::vector < glm::vec2 > out_uvs;

	Index_list.reserve(100);
	Indices.reserve(100);


	char buf[512];

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
			//buff 512 file
	//fgets(str, 60, fp)

	while (fscanf(file, "%[^\n]\n", buf) != EOF)
	{

		//char lineHeader[128];
		// read the first word of the line
		//int res = fscanf(file, "%s", lineHeader);
		//if (res == EOF)
		//	break;

		if (buf[0] == '#')
		{
			continue;
		}
		if (buf[0] == 'v')
		{
			if (buf[1] == 'n')
			{
				glm::vec3 normal;
				sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}

			else if ( buf[1] == 't') {
				glm::vec2 uv;
				sscanf(buf, "vt %f %f", &uv.x, &uv.y);
				temp_uvs.push_back(uv);


			}
			else {
				glm::vec3 vertex;

				sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			
		}

		


		else if (buf[0] == 'f') {
			//std::string vertex1, vertex2, vertex3;
			//unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			Vertex vertex1, vertex2, vertex3;
			

			//glm::vec3 temp_index;
			//glm::vec3 temp_index2;
			//glm::vec3 temp_index3;

			
			Iarray temp_index[3];
			int matches = sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
				&temp_index[0].x, &temp_index[0].y, &temp_index[0].z, 
				&temp_index[1].x, &temp_index[1].y, &temp_index[1].z, 
				&temp_index[2].x, &temp_index[2].y, &temp_index[2].z);
			
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			
			int i = 0;
			for (int u = 0; u < 3; u++)
			{
				it = find(Index_list.begin(), Index_list.end(), temp_index[u]);

				if (it != Index_list.end())
				{
					//auto pos = std::distance(vec.begin(), it);
					unsigned int pos = std::distance(Index_list.begin(), it);
					pos = pos + 1;
					for (int j = 0; j < Indices.size(); j++)
					{
						if (Indices[j] == pos)
						{
							Indices.push_back(Indices[j]);
							break;
						}
					}
					//Indices.push_back(Indices[pos]);
				}

				else
				{
					Index_list.push_back(temp_index[u]);
					Indices.push_back(Index_list.size());
				}
			}
			//if not store size of list
			//if i dont find it index is index list size pushback
			//contains does this contain send bcak index where it finds it
			//if so index equals that element index 
			//new variable index
			//index size will be index 
			//
		
			// use this
			///Index_list.push_back(temp_index);
			//Index_list.push_back(temp_index2);
			//Index_list.push_back(temp_index3);

	
		}


	}


	for (unsigned int i = 0; i < Indices.size(); i++)
	{


		Indices[i] = Indices[i] - 1;

	}


	for (unsigned int i = 0; i < Indices.size(); i++)
	{

		Vertex temp_vert;
		//unsigned int temp_index[3];
		Iarray temp_array;
		glm::vec3 list_index;
		glm::vec3 temp_pos;
		glm::vec3 temp_nor;
		glm::vec2 temp_uv;

		unsigned int pos;
		unsigned int norm;
		unsigned int uv;

		//temp_x = Index_list[Indices[i]][0];
		//temp_y = Index_list[Indices[i]][1];
		//temp_z = Index_list[Indices[i]][2];

		pos = Index_list[Indices[i]].x;
		norm = Index_list[Indices[i]].z;
		uv = Index_list[Indices[i]].y;
		//temp_index = Index_list[Indices[i]];

		//temp_pos
		//temp_index.push_back(Index_list[Indices[i]]);
		/*
		temp_pos = temp_vertices[temp_index.x];
		temp_nor = temp_normals[temp_index.y];
		temp_uv = temp_uvs[temp_index.z];
		*/
		temp_pos = temp_vertices[pos -1];
		temp_nor = temp_normals[norm -1];
		temp_uv = temp_uvs[uv -1];

		temp_vert.Position = temp_pos;
		temp_vert.Normal = temp_nor;
		temp_vert.Texel = temp_uv;


		vertices.push_back(temp_vert);



	}

	for (unsigned int i = 0; i < Index_list.size(); i++)
	{
		Vertex temp_vert;
		//unsigned int temp_index[3];
		Iarray temp_array;
		glm::vec3 list_index;
		glm::vec3 temp_pos;
		glm::vec3 temp_nor;
		glm::vec2 temp_uv;

		unsigned int pos;
		unsigned int norm;
		unsigned int uv;


		pos = Index_list[i].x;
		norm = Index_list[i].z;
		uv = Index_list[i].y;

		temp_pos = temp_vertices[pos - 1];
		temp_nor = temp_normals[norm - 1];
		temp_uv = temp_uvs[uv - 1];

		temp_vert.Position = temp_pos;
		temp_vert.Normal = temp_nor;
		temp_vert.Texel = temp_uv;


		vertices2.push_back(temp_vert);


	}

	//float temp_x = 0;
	//float temp_y = 0;
	//float temp_z = 0;

	maxX = temp_vertices[0].x;
	minX = temp_vertices[0].x;


	maxY = temp_vertices[0].y;
	minY = temp_vertices[0].y;

	maxZ = temp_vertices[0].z;
	minZ = temp_vertices[0].z;



	for (int i = 0; i < temp_vertices.size(); i++)
	{

		float temp_verx = temp_vertices[i].x;
		float temp_very = temp_vertices[i].y;
		float temp_verz = temp_vertices[i].z;

		if (temp_verx < minX)
		{
			minX = temp_verx;

		}
		else if (temp_verx > maxX)
		{
			maxX = temp_verx;
		}

		if (temp_very < minY)
		{
			minY = temp_very;

		}
		else if (temp_very> maxY)
		{
			maxY = temp_very;
		}

		if (temp_verz < minZ)
		{
			minZ = temp_verz;

		}
		else if (temp_verz > maxZ)
		{
			maxZ = temp_verz;
		}

	}

	xdis = maxX - (minX);
	ydis = maxY - (minY);
	zdis = maxZ - (minZ);

	indices = Indices;
	fclose(file);
	glGenBuffers(1, &IndexVBO);
	glGenBuffers(1, &vertexbuffer);
	//glGenBuffers(1, &normalbuffer);

	return true;

}

Mesh::Mesh()
{}
void Mesh::Draw_Mesh()
{
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(Vertex), &vertices2[0], GL_STATIC_DRAW);



	

	//glBindBuffer(GL_ARRAY_BUFFER, HUD_UV_buf);


	//glBufferData(GL_ARRAY_BUFFER, HUD_UVs.size() * sizeof(glm::vec2), &HUD_UVs[0], GL_STATIC_DRAW);


	//glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);

	//glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(Vertex), &vertices2[1], GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0); 
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBO);
	

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	


	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	
	glDisableVertexAttribArray(0);

}

void Mesh::TextureLoad()
{


	TextureMesh = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
	(
		"bricks.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glBindTexture(GL_TEXTURE_2D, TextureMesh);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}