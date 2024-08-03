#include "viewport.h"

#include <math.h>
#include <string.h>

void viewport_create(viewport* v,
                     f32 fov, 
                     f32 aspect_ratio, 
                     f32 far_plane, 
                     f32 near_plane)
{
    v->fov = fov;
    v->aspect_ratio = aspect_ratio;

    v->far_plane = far_plane;
    v->near_plane = near_plane;

    v->fov_rad = (1.0f / tanf(fov * 0.5f / 180.0f * PI));

    memset(&v->projection_matrix, 0, sizeof(mat4x4)); 

    v->projection_matrix.m[0][0] = aspect_ratio * v->fov_rad;
    v->projection_matrix.m[1][1] = v->fov_rad;
    v->projection_matrix.m[2][2] = far_plane / (far_plane - near_plane);
    v->projection_matrix.m[3][2] = (-far_plane * near_plane) / (far_plane - near_plane);
    v->projection_matrix.m[2][3] = 1.0f;
    v->projection_matrix.m[3][3] = 0.0f;
}

void viewport_update(viewport* v)
{
    v->fov_rad = (1.0f / tanf(v->fov * 0.5f / 180.0f * PI));

    v->projection_matrix.m[0][0] = v->aspect_ratio * v->fov_rad;
    v->projection_matrix.m[1][1] = v->fov_rad;
    v->projection_matrix.m[2][2] = v->far_plane / (v->far_plane - v->near_plane);
    v->projection_matrix.m[3][2] = (-v->far_plane * v->near_plane) / (v->far_plane - v->near_plane);
    v->projection_matrix.m[2][3] = 1.0f;
    v->projection_matrix.m[3][3] = 0.0f;
}
