#include "player.h"
#include "raylib.h"
#include <cstdio>
#include <stdlib.h>

Player *NewPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));

    p->cam.position = Vector3{5.0f, 50.0f, 5.0f};
    p->cam.target = Vector3{0.0f, 0.0f, 0.0f};
    p->cam.up = Vector3{0.0f, 0.0f, -1.0f};
    p->cam.fovy = 60.0f;
    p->cam.projection = CAMERA_PERSPECTIVE;

    p->crosshairTexture = LoadTexture("resources/textures/reticle.png");
    p->hPosTexture = LoadTexture("resources/textures/h_indicator_bottom.png");
    p->vPosTexture = LoadTexture("resources/textures/v_indicator.png");

    return p;
}

void CleanupPlayer(Player *p) {
    UnloadTexture(p->crosshairTexture);
    UnloadTexture(p->hPosTexture);
    UnloadTexture(p->vPosTexture);
    free(p);
}

void UpdatePlayer(Player *p) {

    // DRIFT
    // p->cam.position = Vector3Add(p->cam.position, DRIFT_VECTOR);
    // p->cam.target = Vector3Add(p->cam.target, DRIFT_VECTOR);

    // Player movement
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

    RayCollision collision = GetRayCollisionSphere(GetScreenToWorldRay(GetMousePosition(), p->cam), Vector3{0}, 10.0);
    if (collision.hit) p->crosshair = collision.point;
    p->crosshairScreen = Vector2Clamp(GetWorldToScreen(p->crosshair, p->cam), Vector2{SCREEN_RECT.x, SCREEN_RECT.y}, Vector2{SCREEN_RECT.width, SCREEN_RECT.height});
}

void DrawPlayerUI(Player *p) {

    // Draw Horizontal Indicator Top
    Vector2 dxTop = {p->crosshairScreen.x, SCREEN_RECT.y};
    DrawCircleLines(dxTop.x, dxTop.y + GAP / 2.0, GAP / 4.0, RAYWHITE);
    DrawText(TextFormat("[ %.2f ]", p->crosshair.x), dxTop.x + GAP, dxTop.y, GAP, RAYWHITE);

    // Draw Horizontal Indicator Bottom
    Vector2 dxTextureBtm = {p->crosshairScreen.x - p->hPosTexture.width / 4.0f, GetScreenHeight() - (p->hPosTexture.height / 2.0f + GAP)};
    DrawTextureEx(p->hPosTexture, dxTextureBtm, 0.0, 0.5, RAYWHITE);

    // Draw Vertical Indicator Left / Right
    Vector2 dyLeft = {float(GAP), p->crosshairScreen.y - p->vPosTexture.height / 4.0f};
    DrawTextureEx(p->vPosTexture, dyLeft, 0.0, 0.5, RAYWHITE);
    Vector2 dyRight = {GetScreenWidth() - (p->vPosTexture.width / 2.0f + GAP), p->crosshairScreen.y + p->vPosTexture.height / 4.0f};
    DrawTextureEx(p->vPosTexture, dyRight, 270.0, 0.5, RAYWHITE);

    // Draw Crosshair
    Vector2 cross = {p->crosshairScreen.x, p->crosshairScreen.y};
    DrawTexturePro(p->crosshairTexture,
                   Rectangle{0.0f, 0.0f, float(p->crosshairTexture.width), float(p->crosshairTexture.height)},
                   Rectangle{cross.x, cross.y, p->crosshairTexture.width / 2.0f, p->crosshairTexture.height / 2.0f},
                   Vector2{p->crosshairTexture.width / 4.0f, p->crosshairTexture.height / 4.0f},
                   0.0f,
                   RAYWHITE);
}
