#ifndef __MESH_H__
#define __MESH_H__
#include "vector.h"

typedef struct
{
	unsigned int v; /**<vertex index for the corner*/
	unsigned int vn;/**<normal index for the corner*/
	unsigned int vt;/**<texel index for the corner*/


}TriCorner;
typedef struct
{
	TriCorner c[3]; /**<the triangle corners for the triangles*/
}Triangle;
typedef struct
{
	Vector3D *vertices;
	Vector2D *texels;
	Vector3D *normals;
	Triangle *tris;
}Mesh;

/**
	@brief  load an obj file into mesh data type
	@param filename the path to the obj file to load
	@paramreturns NULL on error or an alloacated mesh data structure
*/
//void mesh_load_from_obj(Mesh *mesh, char * filename);
Mesh * mesh_load_from_obj(char * filename);
;

/**
@brief  frees the data associated with the mesh

*/
void mesh_free(Mesh **mesh);
#endif