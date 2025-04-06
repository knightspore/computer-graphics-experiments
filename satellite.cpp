#include <stdlib.h>
#include "player.h"
#include "globe.h"
#include "raylib.h"
#include "imgui/imgui.h"
#include "rlimgui/rlImGui.h"

bool DEBUG = false;
int W = 800;
int H = 800;
float GAP = 16.0;
float TRACKING_SPEED = 0.025f;
float DRIFT = 0.005f;
float GLOBE_SIZE = 20.0f;
Rectangle SCREEN_RECT = {GAP, GAP, W - GAP, H - GAP};

Player *p;
Globe *g;

void update() {
    if (IsWindowResized()) {
        W = GetScreenWidth();
        H = GetScreenHeight();
        SCREEN_RECT = Rectangle{GAP, GAP, W - GAP, H - GAP};
    }
    if (IsKeyPressed(KEY_BACKSLASH)) DEBUG = !DEBUG;
    UpdateGlobe(g);
    UpdatePlayer(p);
}

void DrawImGUI() {
    if (DEBUG) {
        if (IsCursorHidden()) {
            ShowCursor();
        }
        rlImGuiBegin();
        bool open = false;
        if (ImGui::Begin("Settings", &open)) {
            ImGui::SliderFloat("Scale", &GLOBE_SIZE, 5.0, 100.0);
            ImGui::SliderFloat("Drift", &DRIFT, 0.0, 0.1);
        }
        ImGui::End();
        rlImGuiEnd();
    } else {
        if (!IsCursorHidden()) {
            HideCursor();
        }
    }
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    DrawGlobe3D(g);
    DrawPlayerCrosshair3D(p);
    EndMode3D();

    DrawImGUI();

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
