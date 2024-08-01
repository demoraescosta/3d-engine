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

    float scale_factor = 0.2;
    RenderTexture2D renderTexture = LoadRenderTexture((int)(scr_width * scale_factor), (int)(scr_height * scale_factor));

    InitWindow(scr_width, scr_height, "3d renderer");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float angle = 1.0f * GetTime();    

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
                // z axis

                multiply_vec_by_mat(&t.p[0], &rotation_mat_z, &tri_rotated_z.p[0]);
                multiply_vec_by_mat(&t.p[1], &rotation_mat_z, &tri_rotated_z.p[1]);
                multiply_vec_by_mat(&t.p[2], &rotation_mat_z, &tri_rotated_z.p[2]);

                // add x axis

                multiply_vec_by_mat(&tri_rotated_z.p[0], &rotation_mat_x, &tri_rotated_zx.p[0]);
                multiply_vec_by_mat(&tri_rotated_z.p[1], &rotation_mat_x, &tri_rotated_zx.p[1]);
                multiply_vec_by_mat(&tri_rotated_z.p[2], &rotation_mat_x, &tri_rotated_zx.p[2]);

                // offset into screen

                tri_translated = tri_rotated_zx;

                tri_translated.p[0].z = tri_rotated_zx.p[0].z + 3.0f;
                tri_translated.p[1].z = tri_rotated_zx.p[1].z + 3.0f;
                tri_translated.p[2].z = tri_rotated_zx.p[2].z + 3.0f;

                // projection

                multiply_vec_by_mat(&tri_translated.p[0], &projection_matrix, &tri_projected.p[0]);
                multiply_vec_by_mat(&tri_translated.p[1], &projection_matrix, &tri_projected.p[1]);
                multiply_vec_by_mat(&tri_translated.p[2], &projection_matrix, &tri_projected.p[2]);                

                // scale cube

                tri_projected.p[0].x += 1.0f; tri_projected.p[0].y += 1.0f; 
                tri_projected.p[1].x += 1.0f; tri_projected.p[1].y += 1.0f; 
                tri_projected.p[2].x += 1.0f; tri_projected.p[2].y += 1.0f; 

                tri_projected.p[0].x *= 0.5f * (float)scr_width; 
                tri_projected.p[0].y *= 0.5f * (float)scr_height; 
                tri_projected.p[1].x *= 0.5f * (float)scr_width; 
                tri_projected.p[1].y *= 0.5f * (float)scr_height; 
                tri_projected.p[2].x *= 0.5f * (float)scr_width; 
                tri_projected.p[2].y *= 0.5f * (float)scr_height; 

                // draw tri
                tri_draw(tri_projected);
            }

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}


