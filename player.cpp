#include "player.h"
#include "globe.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <stdlib.h>

float PLAYER_HEIGHT = (6371.0f + 2000.0f) * SCALE;
float TRACKING_SPEED = 0.01f;
float FOVS[] = {4.0f, 8.0f, 16.0f, 64.0f};

Player *NewPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));
    p->cam = Camera{
        .position = Vector3{0.0f, PLAYER_HEIGHT, 0.0f},
        .target = Vector3{0.0f, 0.0f, 0.0f},
        .up = Vector3{0.0f, 0.0f, -1.0f},
        .fovy = FOVS[ZOOM_IDX],
        .projection = CAMERA_PERSPECTIVE,
    };
    p->crosshair = Vector3{0.0f, 0.0f, 0.0f};
    p->marker = Vector3{0.0f, 0.0f, 0.0f};
    return p;
}

void CleanupPlayer(Player *p) {
    free(p);
}

void UpdatePlayer(Player *p) {
    p->crosshair = GetGlobeCollision(GetScreenToWorldRay(GetMousePosition(), p->cam));
    p->cam.target = Vector3Lerp(p->cam.target, p->marker, TRACKING_SPEED / 2.0f);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        p->marker = p->crosshair;
    }
    if (IsKeyPressed(KEY_LEFT_BRACKET) && ZOOM_IDX < N_ZOOM_STEP) p->cam.fovy = FOVS[++ZOOM_IDX];
    if (IsKeyPressed(KEY_RIGHT_BRACKET) && ZOOM_IDX > 0) p->cam.fovy = FOVS[--ZOOM_IDX];
}

void drawIndicator3D(Vector3 pos, Color color, bool body = false) {
    Vector3 end = GetGlobeSurface(pos);
    float amt = Clamp(std::sin(GetTime() * 4), 0.2, 0.8);
    if (body) DrawSphereEx(end, 1.0, 8, 8, Fade(color, amt));
    DrawSphereWires(end, 1.0, 8, 8, color);
    DrawLine3D(end, pos, WHITE);
}

void DrawPlayerCrosshair3D(Player *p) {
    drawIndicator3D(p->crosshair, RED);
    if (Vector3Distance(Vector3{}, p->marker) > 0.1) {
        drawIndicator3D(p->marker, BLUE, true);
    }
}
