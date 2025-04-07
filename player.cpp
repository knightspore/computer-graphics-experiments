#include "player.h"
#include "globe.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <stdlib.h>

float PLAYER_HEIGHT = (6371.0f + 2000.0f) * SCALE;
float TRACKING_SPEED = 0.1f;

Player *NewPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));
    p->cam = Camera{
        .position = Vector3{0.0f, PLAYER_HEIGHT, 0.0f},
        .target = Vector3{0.0f, 0.0f, 0.0f},
        .up = Vector3{0.0f, 0.0f, -1.0f},
        .fovy = 60.0f,
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

    if (IsKeyDown(KEY_W)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{-1, 0, 0}, TRACKING_SPEED);
    if (IsKeyDown(KEY_S)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{1, 0, 0}, TRACKING_SPEED);
    if (IsKeyDown(KEY_A)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, 1}, TRACKING_SPEED);
    if (IsKeyDown(KEY_D)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, -1}, TRACKING_SPEED);
    if (IsKeyDown(KEY_LEFT_BRACKET) && p->cam.fovy <= 180.f) p->cam.fovy += 1.f;
    if (IsKeyDown(KEY_RIGHT_BRACKET) && p->cam.fovy >= 5.f) p->cam.fovy -= 1.f;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        p->cam.target = Vector3MoveTowards(p->cam.target, p->crosshair, TRACKING_SPEED);
    }
}

void DrawPlayerCrosshair3D(Player *p) {
    Vector3 end = GetGlobeSurfaceHeight(p->crosshair, 0.8f);
    float amt = Clamp(std::sin(GetTime() * 4), 0.2, 0.8);
    DrawCylinderEx(p->crosshair, end, 0.8, 0.8, 4, Fade(RED, amt));
    DrawCylinderWiresEx(p->crosshair, end, 0.8, 0.8, 4, RED);
}
