#include <stdlib.h>
#include "player.h"
#include "globe.h"
#include "raylib.h"
#include "imgui/imgui.h"
#include "rlimgui/rlImGui.h"

bool DEBUG = false;
int W = 800;
int H = 800;
float DRIFT = 0.005f;
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
        if (IsCursorHidden()) {
            ShowCursor();
        }
        rlImGuiBegin();
        bool open = false;
        if (ImGui::Begin("Settings", &DEBUG)) {
            ImGui::SliderFloat("Drift", &DRIFT, 0.0, 10.0);
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
