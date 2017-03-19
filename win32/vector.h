#ifndef __VECTOR_H__
#define __VECTOR_H__

//data type that has 3 floats in in.
//typedef struct
//{
	//float x, y, z;
//}vec3d;

//typedef float vec3d[3];
//union 
typedef union
{
	struct
	{
		float x, y;
	
	};
	float v[2];
}Vector2D;

typedef union
{
	struct
	{
		float x, y, z;
	};
	float v[3];
}Vector3D;

#define vector3d_add(a,b,c) (a.x = b.x +c.x, a.y = b.y + c.y, a.z = b.z + c.z)
#define vector3d_set(a,b,c) (a.x = b, a.y = c, a.z =d)

#define vector2d_add(a,b,c) (a.x = b.x +c.x, a.y = b.y + c.y)
#define vector2d_set(a,b,c) (a.x = b, a.y = c)

#endif
