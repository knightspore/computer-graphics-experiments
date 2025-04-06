#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <stdlib.h>

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
    // else {
    //     collision = GetRayCollisionBox(mouseRay, BoundingBox{Vector3{-GLOBE_SIZE * 10, 0, -GLOBE_SIZE * 10}, Vector3{GLOBE_SIZE * 10, 0, GLOBE_SIZE * 10}});
    //     if (collision.hit) {
    //         p->crosshair = Vector3Scale(collision.point, GLOBE_SIZE);
    //     }
    // }

    p->crosshairScreen = Vector2Clamp(GetWorldToScreen(p->crosshair, p->cam), Vector2{SCREEN_RECT.x, SCREEN_RECT.y}, Vector2{SCREEN_RECT.width, SCREEN_RECT.height});
}

// void DrawPlayerUI2D(Player *p) {
//     // Draw Horizontal Indicator Top
//     Vector2 dxTop = {p->crosshairScreen.x, SCREEN_RECT.y};
//     DrawCircleLines(dxTop.x, dxTop.y + GAP / 2.0, GAP / 4.0, RAYWHITE);
//
//     // Draw Horizontal Indicator Bottom
//     Vector2 dxTextureBtm = {p->crosshairScreen.x - p->hPosTexture.width / 4.0f, GetScreenHeight() - (p->hPosTexture.height / 2.0f + GAP)};
//     DrawTextureEx(p->hPosTexture, dxTextureBtm, 0.0, 0.5, RAYWHITE);
//
//     // Draw Vertical Indicator Left / Right
//     Vector2 dyLeft = {SCREEN_RECT.x, p->crosshairScreen.y - p->vPosTexture.height / 4.0f};
//     DrawTextureEx(p->vPosTexture, dyLeft, 0.0, 0.5, RAYWHITE);
//     Vector2 dyRight = {SCREEN_RECT.width - (p->vPosTexture.width / 2.0f), p->crosshairScreen.y + p->vPosTexture.height / 4.0f};
//     DrawTextureEx(p->vPosTexture, dyRight, 270.0, 0.5, RAYWHITE);
// }

void DrawPlayerCrosshair3D(Player *p) {
    DrawCylinderWiresEx(Vector3Scale(p->crosshair, 1.05f), Vector3Scale(p->crosshair, 1.2f), 1.0, 0.0, 4, RED);
}
