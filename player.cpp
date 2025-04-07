#include "player.h"
#include "globe.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <stdlib.h>

float PLAYER_HEIGHT = (6371.0f + 2000.0f) * SCALE;
float TRACKING_SPEED = 0.01f;

Player *NewPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));
    p->cam = Camera{
        .position = Vector3{0.0f, PLAYER_HEIGHT, 0.0f},
        .target = Vector3{0.0f, 0.0f, 0.0f},
        .up = Vector3{0.0f, 0.0f, -1.0f},
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };
    p->crosshair = Vector3{0.0f, 0.0f, 0.0f};
    p->nextTarget = Vector3{0.0f, 0.0f, 0.0f};
    return p;
}

void CleanupPlayer(Player *p) {
    free(p);
}

void UpdatePlayer(Player *p) {
    p->crosshair = GetGlobeCollision(GetScreenToWorldRay(GetMousePosition(), p->cam));
    p->cam.target = Vector3Lerp(p->cam.target, p->nextTarget, TRACKING_SPEED);

    if (IsKeyDown(KEY_W) && p->cam.position.y >= 0) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{-1, 0, 0.0001}, TRACKING_SPEED / 2.0f);
    if (IsKeyDown(KEY_S) && p->cam.position.y >= 0) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{1, 0, 0.0001}, TRACKING_SPEED / 2.0f);
    if (IsKeyDown(KEY_A)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, 1}, TRACKING_SPEED / 2.0f);
    if (IsKeyDown(KEY_D)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, -1}, TRACKING_SPEED / 2.0f);
    if (IsKeyDown(KEY_LEFT_BRACKET) && p->cam.fovy <= 90.f) p->cam.fovy += 1.f;
    if (IsKeyDown(KEY_RIGHT_BRACKET) && p->cam.fovy >= 5.f) p->cam.fovy -= 1.f;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        p->nextTarget = p->crosshair;
    }
}

void drawIndicator3D(Vector3 pos, Color color) {
    Vector3 end = GetGlobeSurfaceHeight(pos, 1.0f);
    float amt = Clamp(std::sin(GetTime() * 4), 0.2, 0.8);
    DrawCylinderEx(pos, end, 0.8, 0.8, 4, Fade(color, amt));
    DrawCylinderWiresEx(pos, end, 0.8, 0.8, 4, color);
}

void DrawPlayerCrosshair3D(Player *p) {
    drawIndicator3D(p->crosshair, RED);
    if (Vector3Distance(p->cam.target, p->nextTarget) > 0.1) {
        drawIndicator3D(p->nextTarget, BLUE);
    }
}
