#include <jansson.h>
#include "simple_logger.h"
/*
json_t *model_json_load(char * filename)
{

	json_t *root = NULL;
	json_error_t error;


	root = json_load_file(filename, JSON_DECODE_ANY, &error);

	return root;

}


float *model_json_get_vertices(json_t *model)
{

	float * vertices = NULL;

	json_t *vertarray = NULL;

	int count = 0;

	if (!model)
	{
		slog("no model");
		return NULL;
	}
	
	vertarray = json_object_get(model, "vertices");

	if (!vertarray)
	{
		slog("Model no verts");
		return NULL;
	}

	count = json_array_size(vertarray);
	if (!count)
	{
		slog("Model no verts data");
		return NULL;
	}

	vertices = (float *)malloc(sizeof(float)*count);
	if (!vertices)
	{
		slog("failed to allocate datat");
		return NULL;
	}

	for (int i = 0; i < count; i++)
	{

		vertices[i] = json_real_value(json_array_get(vertarray, 1));

	}
	return vertices;
}



float *model_json_get_uvs(json_t *model)
{

	float * uvs = NULL;

	json_t *uvarray = NULL;

	int count = 0;

	if (!model)
	{
		slog("no model");
		return NULL;
	}

	uvarray = json_object_get(model, "uvs");

	if (!uvarray)
	{
		slog("Model no verts");
		return NULL;
	}

	count = json_array_size(uvarray);
	if (!count)
	{
		slog("Model no verts data");
		return NULL;
	}

	uvs = (float *)malloc(sizeof(float)*count);
	if (!uvs)
	{
		slog("failed to allocate datat");
		return NULL;
	}

	for (int i = 0; i < count; i++)
	{

		uvs[i] = json_real_value(json_array_get(uvarray, 1));

	}

	return uvs;
}





int *model_json_get_faces(json_t *model)
{

	int * faces = NULL;

	json_t *facearray = NULL;

	int count = 0;

	if (!model)
	{
		slog("no model");
		return NULL;
	}

	facearray = json_object_get(model, "faces");

	if (!facearray)
	{
		slog("Model no verts");
		return NULL;
	}

	count = json_array_size(facearray);
	if (!count)
	{
		slog("Model no verts data");
		return NULL;
	}

	faces = (int *)malloc(sizeof(int)*count);
	if (!faces)
	{
		slog("failed to allocate datat");
		return NULL;
	}

	for (int i = 0; i < count; i++)
	{

		faces[i] = json_real_value(json_array_get(facearray, 1));

	}

	return faces;
}
*/