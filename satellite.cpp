#include "player.h"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>

// WINDOW & CONFIG

int W = 800;
int H = 800;
float GAP = 16.0;
float TRACKING_SPEED = 0.025f;
Vector3 DRIFT_VECTOR = {0.01f, 0.0f, 0.005f};
Rectangle SCREEN_RECT = {GAP, GAP, W - GAP, H - GAP};

void update(Player *p) {
    // Update screen size
    if (IsWindowResized()) {
        W = GetScreenWidth();
        H = GetScreenHeight();
        SCREEN_RECT = Rectangle{GAP, GAP, W - GAP, H - GAP};
    }
    UpdatePlayer(p);
}

void draw(Player *p) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    DrawSphereWires(Vector3{0}, 10.0f, 10, 10, RAYWHITE);
    EndMode3D();

    DrawPlayerUI(p);

    EndDrawing();
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "satellite");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    HideCursor();
    SetTargetFPS(1000);

    Player *p = NewPlayer();

    while (!WindowShouldClose()) {
        update(p);
        draw(p);
        DrawFPS(10, 10);
    }

    CleanupPlayer(p);
    CloseWindow();

    return 0;
}
