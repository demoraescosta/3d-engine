#pragma once

#include "types.h"
#include <raylib.h>

#include <raylib.h>
#include <raymath.h>

#define COUNT_OF(arr) (size_t)(sizeof(arr)/sizeof(arr[0]))
#undef bool
typedef unsigned char bool;

// text drawing

static Font GLOBAL_FONT;

static inline 
void draw_text(const char* text, int x, int y, int font_size_px, Color color)
{
    DrawTextEx(GLOBAL_FONT, text, (Vector2) {x, y}, font_size_px, 1.0f, color);
}

// forward declare types

typedef Vector2 vec2d;
typedef Vector3 vec3d;

typedef struct mat4x4 mat4x4;

typedef struct viewport viewport;

// -----------------------------------------------------------------------------
// vector stuff


vec3d vec3d_add(vec3d x, vec3d y); // subtract two vectors and return new vector
vec3d vec3d_sub(vec3d x, vec3d y); // subtract two vectors and return new vector
vec3d vec3d_sub(vec3d x, vec3d y); // subtract two vectors
void vec3d_mul_mat4x4(vec3d i, mat4x4* m, vec3d* o); // takes input multiplies it by matrix and outputs to buffer "o"

// -----------------------------------------------------------------------------
// matrix stuff

typedef struct mat4x4
{
    f64 m[4][4];
} mat4x4;

mat4x4 matrix_rotation_X(f32 angle); // generate x-rotation matrix
mat4x4 matrix_rotation_Y(f32 angle); // generate y-rotation matrix
mat4x4 matrix_rotation_Z(f32 angle); // generate z-rotation matrix

mat4x4 matrix_multiplication(mat4x4* x, mat4x4* y, mat4x4* o); // multiply matrix (mat4x4*) x by matrix y and outputs to buffer o

// -----------------------------------------------------------------------------
// tri stuff

typedef struct tri
{
    vec3d p[3]; // points
} tri;

// rendering

void tri_print(tri t);
void tri_draw(tri t);

// operations

void tri_scale(tri t, f32 factor, tri* o); // scale triangle by "factor" (f32) and outputs the scaled triangle into tri (tri*) "o"
void tri_scale_v(tri t, vec3d vector, tri* o); // scale triangle by vetor and outputs the scaled triangle into &o
void tri_project(tri t, viewport v, tri* o); // projects and draws triangle t, calls tri_draw
void tri_rotate_m(tri t, mat4x4* rm, tri* o); // this is temporary, will replace with an actual rotation function later™
void tri_translate(tri t, vec3d vector, tri* o); // UNIMPLEMENTED: translate by vector (vec3d) and outputs the translated triangle into tri (tri*) "o"
void tri_translate_xyz(tri t, f32 x, f32 y, f32 z, tri* o); // translate triangle "t" (tri) by specified coordinates (f32) and outputs the  // translated triangle into tri (tri*) "o" 
vec3d tri_normal(tri t); // get normal of tri

// -----------------------------------------------------------------------------
// mesh stuff

typedef struct mesh 
{
    tri* tris;
    size_t tri_count;
} mesh;


void _mesh_print(mesh mesh, const char* mesh_name); // internal: prints every tri's x, y, z position of given mesh "mesh"
#define mesh_print(m) _mesh_print(m, #m) // prints every tri's x, y, z position of given mesh "m"

mesh mesh_cube(void); // generates sample cube
void mesh_scale(mesh* m, f32 factor); // scales mesh in all directions by factor

void mesh_render(mesh* mesh, viewport v); // render mesh to viewport (viewport*) "v"


