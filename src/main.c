// #include <stdlib.h>
// #include <stdlib.h>
// #include <stdio.h>

#include <raylib.h>
#include <stdio.h>

#include "core.h"
#include "viewport.h"

int main(int argc, char** argv)
{
    (void)argc; (void)argv;

    const char* dir = GetWorkingDirectory();


    // const u32 scr_width  = 1920;
    // const u32 scr_height = 1080;

    u32 scr_width  = 1920;
    u32 scr_height = 1080;

    // const f32 scr_scale = 0.5f;

    InitWindow(scr_width, scr_height, "3d renderer");

    const mesh test_cube = mesh_cube();
    mesh_print(test_cube);

    int monitor_id = GetCurrentMonitor();

    int monitor_width = GetMonitorWidth(monitor_id);
    int monitor_height = GetMonitorHeight(monitor_id);

    int monitor_refresh_rate = GetMonitorRefreshRate(monitor_id);

    printf("%d / %d, m = %d, rs = %d\n", monitor_width, monitor_height, monitor_id, monitor_refresh_rate);

    f32 fov = 90.0f;
    f32 aspect_ratio = (f32)scr_height / (f32)scr_width;
    
    f32 far_plane  = 1000.0f;
    f32 near_plane =   0.10f;

    viewport v = { 0 };

    viewport_create(&v, fov, aspect_ratio, far_plane, near_plane);

    // -------------------------------------------------------------------------
    // rendering

    // RenderTexture2D target = LoadRenderTexture(scr_width, scr_height);

    GLOBAL_FONT = LoadFont(TextFormat("%s%s", dir, "/res/petme/PetMe64.ttf"));

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        viewport_update(&v);

        f32 dt = GetFrameTime();
        f32 elapsed_time = GetTime();

        f32 angle = 1.0f * elapsed_time;

        float mwheel = (float)(GetMouseWheelMove()*2.0f);
        if (v.fov - mwheel > 0)
            v.fov -= mwheel;    
        
        // ---------------------------------------------------------------------
        // drawing

        bool show_debug = true;

        BeginDrawing();
            ClearBackground(BLACK);

            // debug data

            const char* debug_info = "viewport data:\n fov: %.1f\n fov rad: %.1f \n near plane: %.2f \n far plane: %.2f";

            if (show_debug)
            {
                draw_text(TextFormat("fps: %d", GetFPS()),   
                          16, 16, // x, y
                          16, WHITE);
                draw_text(TextFormat("%.2fs", elapsed_time),  
                          16, 32, 
                          16, WHITE);
                draw_text(TextFormat("ft: %.2fms", dt*1000), 
                          16, 48, 
                          16, WHITE);
                draw_text(TextFormat(debug_info, v.fov, v.fov_rad, v.near_plane, v.far_plane), 
                          16, 96, 
                          16, WHITE);
                draw_text(TextFormat("monitor data: %d / %d, m_id = %d, rs = %d", monitor_width, monitor_height, monitor_id, monitor_refresh_rate),
                          16, 0, 
                          16, WHITE);
            }


            // draw cube mesh
            for (size_t i = 0; i < test_cube.tri_count; i++)
            {
                tri t = test_cube.tris[i];
                tri tri_projected;

                // rotate tris
                mat4x4 rotation_mat_x = matrix_rotation_X(angle);
                mat4x4 rotation_mat_z = matrix_rotation_Z(angle);

                tri_rotate_m(t, &rotation_mat_z, &t);
                tri_rotate_m(t, &rotation_mat_x, &t);

                // offset into screen
                tri_translate_xyz(t, 0, 0, 2.0f, &t);

                // projection
                tri_project(t, v, &tri_projected);

                // scale cube
                tri_translate_xyz(tri_projected, 1.0f, 1.0f, 0.0f, &tri_projected);

                tri_scale_v(tri_projected, 
                            (vec3d) 
                            { 
                                .x = 0.5f * (float)scr_width, 
                                .y = 0.5f * (float)scr_height, 
                            }, 
                            &tri_projected);

                // draw tri
                tri_draw(tri_projected);
            }

        EndDrawing();
    }

    UnloadFont(GLOBAL_FONT);
    CloseWindow();
    
    return 0;
}


