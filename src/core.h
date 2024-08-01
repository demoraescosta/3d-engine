#pragma once
#include "types.h"
#include <raylib.h>

#define COUNT_OF(arr) (size_t)(sizeof(arr)/sizeof(arr[0]))

// ----------
// types
// ----------

typedef Vector2 vec2d;
typedef Vector3 vec3d;

typedef struct mat4x4 
{
    f64 m[4][4];
} mat4x4;

// --------------
// vector stuff
// --------------

void vec2d_scale(vec2d* v, f32 factor);

// --------------
// matrix stuff
// --------------

// get rotation matrix from axis and angle
mat4x4 mat4x4_rotation(vec3d axis, f32 angle);

// get x-rotation matrix
mat4x4 mat4x4_rotation_X(f32 angle);

// get y-rotation matrix
mat4x4 mat4x4_rotation_Y(f32 angle);

// get z-rotation matrix
mat4x4 mat4x4_rotation_Z(f32 angle);

// -----------------------------
// matrix / vec arithmetic
// -----------------------------

// takes input (vec3d) i, multiplies it by matrix (mat4x4) m and outputs to buffer (vec3d) o
void multiply_vec_by_mat(vec3d* i, mat4x4* m, vec3d* o);

// ---------
// tri stuff
// ---------

typedef struct tri 
{
    vec3d p[3]; // points
} tri;

void tri_print(tri t);
void tri_draw(tri t);

// ----------
// mesh stuff
// ----------

typedef struct mesh 
{
    tri* tris;
    size_t tri_count;
} mesh;

void _mesh_print(mesh mesh, const char* mesh_name);
mesh mesh_cube(void);

#define mesh_print(mesh) _mesh_print(mesh, #mesh)
