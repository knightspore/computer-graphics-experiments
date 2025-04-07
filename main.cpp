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
float GLOBE_SIZE = 20.0f;

Player *p;
Globe *g;

void update() {
    if (IsKeyPressed(KEY_BACKSLASH)) DEBUG = !DEBUG;
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
        BeginMode3D(p->cam);
        DrawGrid(100, 100.0f);
        DrawLine3D(Vector3{-10000, 0, 0}, Vector3{10000, 0, 0}, RED); // X-axis
        DrawLine3D(Vector3{0, 0, -10000}, Vector3{0, 0, 10000}, GREEN); // Y-axis
        DrawLine3D(Vector3{0, -10000, 0}, Vector3{0, 10000, 0}, BLUE); // Z-axis
        EndMode3D();
        DrawGrid(100, 1.0f);
        if (IsCursorHidden()) {
            ShowCursor();
        }
        rlImGuiBegin();
        bool open = false;
        if (ImGui::Begin("Settings", &DEBUG)) {
            ImGui::SliderFloat("Globe Size", &GLOBE_SIZE, 1.0, 500.0);
            ImGui::Text("Camera [%.2f, %.2f, %.2f]", p->cam.position.x, p->cam.position.y, p->cam.position.z);
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
        DrawFPS(10, 10);
    }

    CleanupGlobe(g);
    CleanupPlayer(p);

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
