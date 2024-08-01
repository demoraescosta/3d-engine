#include "core.h"
#include <string.h>
#include <stdio.h>

#include <raylib.h>

// --------------------
// matrix stuff
// --------------------

mat4x4 mat4x4_initialize(void)
{
    mat4x4 m;

    memset(&m, 0, sizeof(mat4x4));
    return m;
}

void multiply_vec_by_mat(vec3d* i, mat4x4* m, vec3d* o)
{    
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
	o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
	o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];

	float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

	if (w != 0.0f)
	{
		o->x /= w; o->y /= w; o->z /= w;
	}
}

// --------------------
// tri stuff
// --------------------
 
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

void line_draw(vec2d start, vec2d end, Color color)
{
    vec2d v_start = { start.x, start.y };
    vec2d v_end   = { end.x, end.y };   

    DrawLineEx(start, end, 1, color);
}

void tri_draw(tri t)
{
    vec2d v1 = {
        .x = t.p[0].x,
        .y = t.p[0].y,
    };

    vec2d v2 = {
        .x = t.p[1].x,
        .y = t.p[1].y,
    };

    vec2d v3 = {
        .x = t.p[2].x,
        .y = t.p[2].y,
    };

    line_draw(v1, v2, WHITE);
    line_draw(v2, v3, WHITE);
    line_draw(v3, v1, WHITE);
}

// ----------
// cube stuff
// ----------

static tri cube_tris[] = {
	// SOUTH
    { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	// EAST                                                      
	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

	// NORTH                                                     
	{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

	// WEST                                                      
	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

	// TOP                                                       
	{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

	// BOTTOM                                                    
	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
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

