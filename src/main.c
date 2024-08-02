// #include <stdlib.h>
// #include <stdlib.h>
// #include <stdio.h>

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include <string.h>

#include "core.h"

int main(int argc, char** argv)
{
    (void)argc; (void)argv;

    const u32 scr_width = 1200;
    const u32 scr_height = 800;

    // sample cube
    const mesh test_cube = mesh_cube();
    
    mesh_print(test_cube);

    // ----------------
    //  sorcery 
    // ----------------

    f32 near_plane =   0.10f;
    f32 far_plane  = 1000.0f;

    f32 fov = 90.0f;

    f32 aspect_ratio = (f32)scr_height / (f32)scr_width;

    // fov in radians 
    f32 fov_rad = (1.0f / tanf(fov * 0.5f / 180.0f * PI));

    mat4x4 projection_matrix;
    memset(&projection_matrix, 0, sizeof(mat4x4)); 

    projection_matrix.m[0][0] = aspect_ratio * fov_rad;
    projection_matrix.m[1][1] = fov_rad;
    projection_matrix.m[2][2] = far_plane / (far_plane - near_plane);
    projection_matrix.m[3][2] = (-far_plane * near_plane) / (far_plane - near_plane);
    projection_matrix.m[2][3] = 1.0f;
    projection_matrix.m[3][3] = 0.0f;

    // --------------------
    // rendering
    // --------------------

    InitWindow(scr_width, scr_height, "3d renderer");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        f32 dt = GetFrameTime();
        f32 elapsed_time = GetTime();

        f32 angle = 1.0f * elapsed_time;

        mat4x4 rotation_mat_x, rotation_mat_z;

        // rotation on the z axis
        rotation_mat_z.m[0][0] = cosf(angle);
		rotation_mat_z.m[0][1] = sinf(angle);
		rotation_mat_z.m[1][0] = -sinf(angle);
		rotation_mat_z.m[1][1] = cosf(angle);
		rotation_mat_z.m[2][2] = 1;
		rotation_mat_z.m[3][3] = 1;

		// rotation on the x axis
		rotation_mat_x.m[0][0] = 1;
		rotation_mat_x.m[1][1] = cosf(angle * 0.5f);
		rotation_mat_x.m[1][2] = sinf(angle * 0.5f);
		rotation_mat_x.m[2][1] = -sinf(angle * 0.5f);
		rotation_mat_x.m[2][2] = cosf(angle * 0.5f);
		rotation_mat_x.m[3][3] = 1;

        // ---------------
        // drawing
        // ---------------

        BeginDrawing();
            ClearBackground(BLACK);

            // draw cube mesh
            for (size_t i = 0; i < test_cube.tri_count; i++)
            {
                tri t = test_cube.tris[i];
                tri tri_projected;

                tri tri_rotated_z, tri_rotated_x;
                tri tri_rotated_zx;

                tri tri_translated;

                // rotate tris
                tri_rotate_m(&t, &rotation_mat_z, &tri_rotated_z);
                tri_rotate_m(&tri_rotated_z, &rotation_mat_x, &tri_rotated_zx);

                // offset into screen

                tri_translate_xyz(&tri_rotated_zx, 0, 0, 2.0f, &tri_translated);

                // projection

                multiply_vec_by_mat(&tri_translated.p[0], &projection_matrix, &tri_projected.p[0]);
                multiply_vec_by_mat(&tri_translated.p[1], &projection_matrix, &tri_projected.p[1]);
                multiply_vec_by_mat(&tri_translated.p[2], &projection_matrix, &tri_projected.p[2]);

                // scale cube

                tri_translate_xyz(&tri_projected, 1.0f, 1.0f, 0.0f, &tri_projected);

                vec3d scale_vector;

                scale_vector.x = 0.5f * (float)scr_width;
                scale_vector.y = 0.5f * (float)scr_height;
                scale_vector.z = 1.0f;

                tri_scale_v(&tri_projected, scale_vector, &tri_projected);

                // draw tri
                tri_draw(tri_projected);
            }

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}


