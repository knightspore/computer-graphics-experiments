#include "player.h"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>

// WINDOW & CONFIG

int SEED = 1337;
int W = 800;
int H = 800;
int FPS = 1000;
float GAP = 16.0;
float TRACKING_SPEED = 0.025f;
Vector3 DRIFT_VECTOR = {0.01f, 0.0f, 0.005f};
Rectangle SCREEN_RECT = {GAP, GAP, W - GAP, H - GAP};

void updateScreenSize() {
    if (IsWindowResized()) {
        W = GetScreenWidth();
        H = GetScreenHeight();
        SCREEN_RECT = Rectangle{GAP, GAP, W - GAP, H - GAP};
    }
}

typedef struct {
    float width;
    float height;
} Map;

Map *newMap(float w, float h) {
    Map *m = (Map *)malloc(sizeof(Map));
    m->width = w;
    m->height = h;
    return m;
}

void cleanupMap(Map *m) {
    free(m);
}

void drawMap3D(Map *m) {
    for (float y = 0; y <= m->height; y++) {
        for (float x = 0; x <= m->width; x++) {
            Vector3 pos = {x - m->width / 2.0f, 0.0f, y - m->height / 2.0f};
            DrawPoint3D(pos, GRAY);
        }
    }
}

void update(Player *p) {
    updateScreenSize();
    UpdatePlayer(p);
}

void draw(Map *m, Player *p) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    drawMap3D(m);
    EndMode3D();

    DrawPlayerUI(p);

    EndDrawing();
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "satellite");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    HideCursor();
    SetTargetFPS(FPS);

    Map *m = newMap(200.0f, 200.0f);
    Player *p = NewPlayer();

    while (!WindowShouldClose()) {
        update(p);
        draw(m, p);
        DrawFPS(10, 10);
    }

    CleanupPlayer(p);
    cleanupMap(m);
    CloseWindow();

    return 0;
}
