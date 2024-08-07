#include "core.h"

#include <stdio.h>

#include <math.h>

#include <raylib.h>

#include "viewport.h"

// -----------------------------------------------------------------------------
// vector stuff

// subtract two vectors
vec3d vec3d_add(vec3d x, vec3d y)
{
    return (vec3d) 
    {
        .x = x.x + y.x,
        .y = x.y + y.y,
        .z = x.z + y.z,
    };
}

// subtract two vectors
vec3d vec3d_min(vec3d x, vec3d y)
{
    return (vec3d) 
    {
        .x = x.x - y.x,
        .y = x.y - y.y,
        .z = x.z - y.z,
    };
}

// subtract two vectors
vec3d vec3d_scale(vec3d v, f32 factor)
{
    return (vec3d) 
    {
        .x = v.x * factor,
        .y = v.y * factor,
        .z = v.z * factor,
    };
}

// takes input (vec3d) i, multiplies it by matrix (mat4x4) m and outputs to buffer (vec3d) o
vec3d vec3d_mul_mat4x4(vec3d i, mat4x4* m)
{   
    vec3d o;
    
    o.x = i.x * m->m[0][0] + i.y * m->m[1][0] + i.z * m->m[2][0] + m->m[3][0];
	o.y = i.x * m->m[0][1] + i.y * m->m[1][1] + i.z * m->m[2][1] + m->m[3][1];
	o.z = i.x * m->m[0][2] + i.y * m->m[1][2] + i.z * m->m[2][2] + m->m[3][2];

	float w = i.x * m->m[0][3] + i.y * m->m[1][3] + i.z * m->m[2][3] + m->m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; 
        o.y /= w; 
        o.z /= w;
	}

    return o;
}
// -----------------------------------------------------------------------------
// matrix stuff

// get x-rotation matrix
mat4x4 matrix_rotation_X(f32 angle)
{
    mat4x4 rotation_mat = 
    { 
        1,     0,            0,            0,
        0, cosf(angle), -sinf(angle),      0,
        0, sinf(angle), cosf(angle),       0,

        0,0,0,0,
    };
    
    return rotation_mat;
}

// get y-rotation matrix
mat4x4 matrix_rotation_Y(f32 angle)
{
    mat4x4 rotation_mat = 
    {
         cosf(angle), 0,  sinf(angle),    0,
              0,      1,       0,         0,
        -sinf(angle), 0,  cosf(angle),    0,

        0,0,0,0
    };

    return rotation_mat;
}

// get z-rotation matrix
mat4x4 matrix_rotation_Z(f32 angle)
{
    mat4x4 rotation_mat = 
    { 
        cosf(angle), -sinf(angle), 0,   0,
        sinf(angle),  cosf(angle), 0,   0,
              0,           0,      1,   0,

        0,0,0,0
    };

    return rotation_mat;
}

// multiply matrix (mat4x4*) x by matrix (mat4x4*) y and outputs to buffer (mat4x4*) o
mat4x4 matrix_multiplication(mat4x4* x, mat4x4* y, mat4x4* o);

// -----------------------------------------------------------------------------
// tri stuff
 
void tri_print(tri t)
{
    printf("\x1B[90m{\x1B[0m");

    for (int i = 0; i < 3; i++)
    {
        printf("\x1B[91m x:\x1B[0m %.2f,", (double)t.p[i].x);
        printf("\x1B[93m y:\x1B[0m %.2f,", (double)t.p[i].y);
        printf("\x1B[94m z:\x1B[0m %.2f", (double)t.p[i].z);
        if (i < 2) printf(" \x1B[90m|\x1B[0m");
    }

    printf(" \x1B[90m}\x1B[0m");
}

void tri_draw(tri t)
{
    // DrawLine(t.p[0].x, t.p[0].y, t.p[1].x, t.p[1].y, WHITE);
    // DrawLine(t.p[1].x, t.p[1].y, t.p[2].x, t.p[2].y, WHITE);
    // DrawLine(t.p[2].x, t.p[2].y, t.p[0].x, t.p[0].y, WHITE);
    
    DrawTriangleLines((Vector2) { t.p[0].x, t.p[0].y }, 
                      (Vector2) { t.p[1].x, t.p[1].y }, 
                      (Vector2) { t.p[2].x, t.p[2].y }, 
                      WHITE);
}

void tri_scale(tri t, f32 factor, tri* o)
{
    for (uint i = 0; i < 3; i += 1)
    {
        o->p[0].x = t.p[0].x * factor;
        o->p[1].y = t.p[1].y * factor;
        o->p[2].z = t.p[2].z * factor;
    }
}

void tri_scale_v(tri t, vec3d vector, tri* o)
{
    for (uint i = 0; i < 3; i += 1)
    {
        o->p[i].x = t.p[i].x * vector.x;
        o->p[i].y = t.p[i].y * vector.y;
        o->p[i].z = t.p[i].z * vector.z;
    }
}

void tri_project(tri t, viewport v, tri* o)
{
    o->p[0] = vec3d_mul_mat4x4(t.p[0], &v.projection_matrix);
    o->p[1] = vec3d_mul_mat4x4(t.p[1], &v.projection_matrix);
    o->p[2] = vec3d_mul_mat4x4(t.p[2], &v.projection_matrix);
}


// TODO: https://en.wikipedia.org/wiki/Rotation_matrix#General_3D_rotations
void tri_rotate(tri* t, vec3d rotation_vector, tri* o)
{
    (void) t;
    (void) rotation_vector;
    (void) o;

    return;
}

void tri_translate(tri t, vec3d vector, tri* o)
{
    for (uint i = 0; i < 3; i += 1)
    {
        o->p[i].x = t.p[i].x + vector.x;
        o->p[i].y = t.p[i].y + vector.y;
        o->p[i].z = t.p[i].z + vector.z;
    }    
}

void tri_translate_xyz(tri t, f32 x, f32 y, f32 z, tri* o)
{
    for (uint i = 0; i < 3; i += 1)
    {
        o->p[i].x = t.p[i].x + x;
        o->p[i].y = t.p[i].y + y;
        o->p[i].z = t.p[i].z + z;
    }
    
}

// REVIEW: may not need this at all 
void tri_rotate_m(tri t, mat4x4* rm, tri* o)
{
    o->p[0] = vec3d_mul_mat4x4(t.p[0], rm);
    o->p[1] = vec3d_mul_mat4x4(t.p[1], rm);
    o->p[2] = vec3d_mul_mat4x4(t.p[2], rm);
}

// get normal of tri
vec3d tri_normal(tri t)
{
    vec3d u = vec3d_min(t.p[1], t.p[0]); // edge 1
    vec3d v = vec3d_min(t.p[2], t.p[1]); // edge 2

    return (vec3d) // normal
    {
        .x = (u.y * v.z) - (u.z * v.y),
        .y = (u.z * v.x) - (u.x * v.z),
        .z = (u.x * v.y) - (u.y * v.x),
    };
}


// -----------------------------------------------------------------------------
// cube stuff

static tri cube_tris[] = 
{
	// south
    { 0.5f, 0.0f, 0.0f,    0.0f, 0.5f, 0.0f,    0.5f, 0.5f, 0.0f },
	{ 0.0f, 0.0f, 0.0f,    0.5f, 0.5f, 0.0f,    0.5f, 0.0f, 0.0f },

	// east                                                     
	{ 0.5f, 0.0f, 0.0f,    0.5f, 0.5f, 0.0f,    0.5f, 0.5f, 0.5f },
	{ 0.5f, 0.0f, 0.0f,    0.5f, 0.5f, 0.5f,    0.5f, 0.0f, 0.5f },

	// north                                                     
	{ 0.5f, 0.0f, 0.5f,    0.5f, 0.5f, 0.5f,    0.0f, 0.5f, 0.5f },
	{ 0.5f, 0.0f, 0.5f,    0.0f, 0.5f, 0.5f,    0.0f, 0.0f, 0.5f },

	// west                                                     
	{ 0.0f, 0.0f, 0.5f,    0.0f, 0.5f, 0.5f,    0.0f, 0.5f, 0.0f },
	{ 0.0f, 0.0f, 0.5f,    0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 0.0f },

	// top                                                      
	{ 0.0f, 0.5f, 0.0f,    0.0f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f },
	{ 0.0f, 0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.0f },

	// bottom
	{ 0.5f, 0.0f, 0.5f,    0.0f, 0.0f, 0.5f,    0.0f, 0.0f, 0.0f },
	{ 0.5f, 0.0f, 0.5f,    0.0f, 0.0f, 0.0f,    0.5f, 0.0f, 0.0f },
};

static size_t const tri_cube_count = COUNT_OF(cube_tris);

mesh mesh_cube(void)
{
    mesh cube_mesh = {
        .tris = cube_tris,
        .tri_count = tri_cube_count,
    };

    return cube_mesh;
}   

void _mesh_print(mesh m, const char* mesh_name)
{
    printf("mesh: \x1B[90m%s\x1B[0m = \n", mesh_name);

    for (uint i = 0; i < m.tri_count; i++) // foreach tri
    {
        printf("    ");
        tri_print(m.tris[i]);

        printf("\n");
    }
}

void mesh_render(mesh* mesh, viewport v)
{
    for (size_t i = 0; i < mesh->tri_count; i++)
    {
        tri t = mesh->tris[i];
        tri tri_projected;

        // projection
        tri_project(t, v, &tri_projected);

        // draw tri
        tri_draw(tri_projected);
    }
}
