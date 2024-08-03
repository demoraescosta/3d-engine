#pragma once

#include "types.h"
#include "core.h"

typedef struct viewport
{
    f32 fov; 
    f32 fov_rad;       // fov in radians
    f32 aspect_ratio;

    f32 far_plane;     // furthest point from viewport
    f32 near_plane;    // nearest point from viewport

    mat4x4 projection_matrix;
} viewport;

void viewport_create(viewport* v,
                     f32 fov, 
                     f32 aspect_ratio, 
                     f32 far_plane, 
                     f32 near_plane);

// update viewport's projection matrix
void viewport_update(viewport* v);
