#include "globe.h"
#include "imgui/imgui.h"
#include "player.h"
#include "raylib.h"
#include "rlimgui/rlImGui.h"
#include <stdlib.h>

bool DEBUG = false;
float SCALE = 1.0f / 100.0f;
int W = 800;
int H = 800;

Player *p;
Globe *g;

void update() {
    if (IsKeyPressed(KEY_BACKSLASH)) DEBUG = !DEBUG;
    if (DEBUG) {
        // Free cam
        if (IsKeyDown(KEY_W)) p->cam.position = Vector3Add(p->cam.position, Vector3{0, -1, 0});
        if (IsKeyDown(KEY_A)) p->cam.position = Vector3Add(p->cam.position, Vector3{-1, 0, 0});
        if (IsKeyDown(KEY_S)) p->cam.position = Vector3Add(p->cam.position, Vector3{0, 1, 0});
        if (IsKeyDown(KEY_D)) p->cam.position = Vector3Add(p->cam.position, Vector3{1, 0, 0});
    }
    UpdateGlobe(g);
    UpdatePlayer(p);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    DrawGlobe3D(g);
    DrawPlayerCrosshair3D(p);
    EndMode3D();

    if (DEBUG) {
        // World Debugs
        BeginMode3D(p->cam);

        DrawGrid(100, 100.0f);
        DrawLine3D(Vector3{-10000, 0, 0}, Vector3{10000, 0, 0}, RED);   // X-axis
        DrawLine3D(Vector3{0, 0, -10000}, Vector3{0, 0, 10000}, GREEN); // Y-axis
        DrawLine3D(Vector3{0, -10000, 0}, Vector3{0, 10000, 0}, BLUE);  // Z-axis
        EndMode3D();

        BeginBlendMode(BLEND_ADDITIVE);
        DrawModelWiresEx(g->sphere, Vector3{}, Vector3{0.1, 0, 1}, g->rotation, Vector3{1, 1, 1}, Fade(BLACK, 0.5f));
        EndBlendMode();

        DrawFPS(10, 10);

        if (IsCursorHidden()) {
            ShowCursor();
        }

        // Gui
        rlImGuiBegin();
        bool open = false;
        if (ImGui::Begin("Settings", &DEBUG)) {
            ImGui::Text("Camera [%.2f, %.2f, %.2f]", p->cam.position.x, p->cam.position.y, p->cam.position.z);
            ImGui::SliderFloat("Cam x", &p->cam.position.x, -100.0f, 100.0f);
            ImGui::SliderFloat("Cam y", &p->cam.position.y, -100.0f, 100.0f);
            ImGui::SliderFloat("Cam z", &p->cam.position.z, -100.0f, 100.0f);
            ImGui::SliderFloat("Target x", &p->cam.target.x, -100.0f, 100.0f);
            ImGui::SliderFloat("Target y", &p->cam.target.y, -100.0f, 100.0f);
            ImGui::SliderFloat("Target z", &p->cam.target.z, -100.0f, 100.0f);
            ImGui::SliderFloat("Cam fovy", &p->cam.fovy, 1.0f, 180.0f);
        }
        ImGui::End();
        rlImGuiEnd();

    } else {
        if (!IsCursorHidden()) {
            HideCursor();
        }
    }

    EndDrawing();
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "satellite");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(1000);

    p = NewPlayer();
    g = NewGlobe();

    rlImGuiSetup(true);
    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CleanupGlobe(g);
    CleanupPlayer(p);

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
