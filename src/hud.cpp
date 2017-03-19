#include "hud.h"
#include "SDL.h"
#include "SDL_image.h"
#include "graphics3d.h"
#include "SOIL.h"
GLuint HUD_Vertex_buf;
GLuint HUD_UV_buf;
GLuint HUD_Index_buf;
GLuint Texture;
GLuint TextureID;


//extern SDL_Surface *image;
int width, height;
unsigned char* image;
HUD::HUD() {

}
void HUD::Draw_HUD()
{


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HUD_Index_buf);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, HUD_Indices.size() * sizeof(unsigned int), &HUD_Indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, HUD_Vertex_buf);


	glBufferData(GL_ARRAY_BUFFER, HUD_Verts.size() * sizeof(glm::vec3), &HUD_Verts[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, HUD_UV_buf);


	glBufferData(GL_ARRAY_BUFFER, HUD_UVs.size() * sizeof(glm::vec2), &HUD_UVs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, HUD_Vertex_buf);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glEnableVertexAttribArray(1); 

	glBindBuffer(GL_ARRAY_BUFFER, HUD_UV_buf);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HUD_Index_buf);

	glDrawElements(GL_TRIANGLES, HUD_Indices.size(), GL_UNSIGNED_INT, 0);
	/*
	glBindBuffer(GL_ARRAY_BUFFER, HUD_Vertex_buf);
	glBufferData(GL_ARRAY_BUFFER, HUD_Verts.size() *  sizeof(HUD_Verts), &HUD_Verts[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, HUD_UV_buf);
	glBufferData(GL_ARRAY_BUFFER, HUD_UVs.size() * sizeof(HUD_UVs), &HUD_UVs[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); //0 is our index, refer to "location = 0" in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, HUD_Vertex_buf); //bind the buffer we're applying attributes to
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1); //attribute 1 is for vertex color data
	glBindBuffer(GL_ARRAY_BUFFER, HUD_UV_buf);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, HUD_Verts.size());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	*/
}


void HUD::TextureLoad()
{


	Texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
	(
		"Frame.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void HUD::Set_HUD_Points()
{

	
	HUD_Verts.push_back(glm::vec3(0.5, 0.5, 0));
	HUD_Verts.push_back(glm::vec3(0.5, -0.5, 0));
	HUD_Verts.push_back(glm::vec3(-0.5, -0.5, 0));
	HUD_Verts.push_back(glm::vec3(-0.5, 0.5, 0));
	
	
	HUD_UVs.push_back(glm::vec2(1, 1));
	HUD_UVs.push_back(glm::vec2(1, 0));
	HUD_UVs.push_back(glm::vec2(0, 0));
	HUD_UVs.push_back(glm::vec2(0, 1));


	HUD_Indices.push_back(0);
	HUD_Indices.push_back(2);
	HUD_Indices.push_back(1);
	HUD_Indices.push_back(0);
	HUD_Indices.push_back(3);
	HUD_Indices.push_back(2);


	glGenBuffers(1, &HUD_Vertex_buf);

	glGenBuffers(1, &HUD_UV_buf);

	glGenBuffers(1, &HUD_Index_buf);


}

void HUD::TextureSetUp()
{






}


/*
void HUD::TextrueSetUp()
{


	/*
	
	//printf("INhere");

	GLuint TextureID = glGetUniformLocation(graphics3d_get_shader_program2(), "myText");
	
	GLuint texture;

	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int T_WIDTH, T_HEIGHT;
	unsigned char* image = SOIL_load_image("Frame.png", &T_WIDTH, &T_HEIGHT, 0, SOIL_LOAD_RGB);

	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_WIDTH, T_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	
	glBindTexture(GL_TEXTURE_2D, 0);

	

	glUniform1i(TextureID, 0);





	/*
	image = SOIL_load_image("Frame.png", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glUniform1i(glGetUniformLocation(graphics3d_get_shader_program2(), "myText"));
	
	*/

	



	//GLuint Texture = 




//}