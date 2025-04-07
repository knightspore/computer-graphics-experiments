#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

float TRACKING_SPEED = 0.025f;
float PLAYER_HEIGHT = (6378.0f + 2000.0f) * (1.0f / 100.0f); // @TODO: Clean up all the magic numbers

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
    return p;
}

void CleanupPlayer(Player *p) {
    free(p);
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_W)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{-1, 0, 0}, TRACKING_SPEED);
    if (IsKeyDown(KEY_S)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{1, 0, 0}, TRACKING_SPEED);
    if (IsKeyDown(KEY_A)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, 1}, TRACKING_SPEED);
    if (IsKeyDown(KEY_D)) p->cam.position = Vector3RotateByAxisAngle(p->cam.position, Vector3{0, 0, -1}, TRACKING_SPEED);
    if (IsKeyDown(KEY_LEFT_BRACKET) && p->cam.fovy <= 180.f) p->cam.fovy += 1.f;
    if (IsKeyDown(KEY_RIGHT_BRACKET) && p->cam.fovy >= 5.f) p->cam.fovy -= 1.f;
    p->crosshair = GetGlobeCollision(GetScreenToWorldRay(GetMousePosition(), p->cam));
}

void DrawPlayerCrosshair3D(Player *p) {
    Vector3 end = Vector3Scale(p->crosshair, 1.1f);
    DrawCylinderEx(p->crosshair, end, 0.0, 1.0, 4, RAYWHITE);
    DrawCylinderWiresEx(p->crosshair, end, 0.0, 1.0, 4, BLACK);
}
