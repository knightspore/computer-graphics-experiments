#include "player.h"
#include "raylib.h"
#include <stdlib.h>

int W = 800;
int H = 800;
float GAP = 16.0;
float TRACKING_SPEED = 0.025f;
float DRIFT = 0.005f;
Rectangle SCREEN_RECT = {GAP, GAP, W - GAP, H - GAP};

typedef struct {
    Model sphere;
    float rotation;
} Globe;

Globe *NewGlobe() {
    Globe *globe = (Globe *)malloc(sizeof(Globe));
    globe->rotation = 0.0;
    globe->sphere = LoadModelFromMesh(GenMeshSphere(10.0, 10, 10));
    return globe;
}

void CleanupGlobe(Globe *g) {
    UnloadModel(g->sphere);
    free(g);
}

void UpdateGlobe(Globe *g) {
    g->rotation += DRIFT;
}

void DrawGlobe3D(Globe *g) {
    DrawModelEx(g->sphere, Vector3{0}, Vector3{0, 0, 1}, g->rotation, Vector3{1, 1, 1}, GRAY);
}

// Game

Player *p;
Globe *g;

void update() {
    if (IsWindowResized()) {
        W = GetScreenWidth();
        H = GetScreenHeight();
        SCREEN_RECT = Rectangle{GAP, GAP, W - GAP, H - GAP};
    }
    UpdateGlobe(g);
    UpdatePlayer(p);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    DrawGlobe3D(g);
    DrawPlayerCursor3D(p);
    EndMode3D();

    DrawPlayerUI2D(p);

    EndDrawing();
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "satellite");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    HideCursor();
    SetTargetFPS(1000);

    p = NewPlayer();
    g = NewGlobe();

    while (!WindowShouldClose()) {
        update();
        draw();
        DrawFPS(10, 10);
    }

    CleanupGlobe(g);
    CleanupPlayer(p);

    CloseWindow();

    return 0;
}
