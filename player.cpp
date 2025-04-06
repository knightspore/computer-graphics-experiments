#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

float TRACKING_SPEED = 0.025f;

Player *NewPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));
    p->cam = Camera{
        .position = Vector3{0.0f, 50.0f, 0.0f},
        .target = Vector3{0.0f, 0.0f, 0.0f},
        .up = Vector3{0.0f, 0.0f, -1.0f},
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE,
    };
    p->crosshair = Vector3{0.0f, 0.0f, 0.0f};
    p->crosshairScreen = Vector2{float(W / 2.0f), float(H / 2.0f)};
    return p;
}

void CleanupPlayer(Player *p) {
    free(p);
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_W)) {
        p->cam.position.z -= TRACKING_SPEED;
        p->cam.target.z -= TRACKING_SPEED;
    }
    if (IsKeyDown(KEY_S)) {
        p->cam.position.z += TRACKING_SPEED;
        p->cam.target.z += TRACKING_SPEED;
    }
    if (IsKeyDown(KEY_A)) {
        p->cam.position.x -= TRACKING_SPEED;
        p->cam.target.x -= TRACKING_SPEED;
    }
    if (IsKeyDown(KEY_D)) {
        p->cam.position.x += TRACKING_SPEED;
        p->cam.target.x += TRACKING_SPEED;
    }
    if (IsKeyDown(KEY_LEFT_BRACKET)) {
        if (p->cam.fovy >= 90.f) {
            return;
        }
        p->cam.fovy += 1.f;
    }
    if (IsKeyDown(KEY_RIGHT_BRACKET)) {
        if (p->cam.fovy < 20.f) {
            return;
        }
        p->cam.fovy -= 1.f;
    }

    Ray mouseRay = GetScreenToWorldRay(GetMousePosition(), p->cam);
    RayCollision collision = GetRayCollisionSphere(mouseRay, Vector3{0}, GLOBE_SIZE);
    if (collision.hit)
        p->crosshair = collision.point;
    else {
        p->crosshair = Vector3{0, 0, 0};
    }

    p->crosshairScreen = Vector2Clamp(GetWorldToScreen(p->crosshair, p->cam), {0,0}, {float(GetScreenWidth()), float(GetScreenHeight())});
}

void DrawPlayerCrosshair3D(Player *p) {
    Vector3 end = Vector3Scale(p->crosshair, 1.1f);
    DrawCylinderEx(p->crosshair, end, 0.0, 1.0, 4, RAYWHITE);
    DrawCylinderWiresEx(p->crosshair, end, 0.0, 1.0, 4, BLACK);
}
