#pragma once
#include "types.h"
#include <raylib.h>

#define COUNT_OF(arr) (size_t)(sizeof(arr)/sizeof(arr[0]))

// ----------
// types
// ----------

typedef Vector2 vec2d;
typedef Vector3 vec3d;

typedef struct 
{
    f64 m[4][4];
} mat4x4;

typedef struct 
{
    f32 fov; 
    f32 fov_rad;       // fov in radians
    f32 aspect_ratio;

    f32 far_plane;     // furthest point from viewport
    f32 near_plane;    // nearest point from viewport

    mat4x4 projection_matrix;
} viewport;

// --------------
// vector stuff
// --------------

// scale vec2d by a f32 factor
void vec2d_scale(vec2d* v, f32 factor);

// multiply vec2d by vec2d
void vec2d_multiply(vec2d *v, f32 factor);

// takes input (vec3d) i, multiplies it by matrix (mat4x4) m and outputs to buffer (vec3d) o
void multiply_vec_by_mat(vec3d* i, mat4x4* m, vec3d* o);

// --------------
// matrix stuff
// --------------

// get x-rotation matrix
mat4x4 mat4x4_rotation_X(f32 angle);

// get y-rotation matrix
mat4x4 mat4x4_rotation_Y(f32 angle);

// get z-rotation matrix
mat4x4 mat4x4_rotation_Z(f32 angle);

// multiply matrix (mat4x4*) x by matrix (mat4x4*) y and outputs to buffer (mat4x4*) o
mat4x4 matrix_multiplication(mat4x4* x, mat4x4* y, mat4x4* o);

// ---------
// tri stuff
// ---------

typedef struct
{
    vec3d p[3]; // points
} tri;

void tri_print(tri t);
void tri_draw(tri t);

void tri_scale(tri* t, f32 factor, tri* o);

void tri_scale_v(tri* t, vec3d vector, tri* o);

void tri_project(tri* t, mat4x4* pm, tri* o);

void tri_rotate_m(tri* t, mat4x4* rm, tri* o);

void tri_rotate_v(tri* t, vec3d rotation_vector, tri* o);

void tri_translate(tri* t, vec3d vector, tri* o);

void tri_translate_xyz(tri* t, f32 x, f32 y, f32 z, tri* o);

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
