#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

// WINDOW & CONFIG

int W = 800;
int H = 800;
int FPS = 120;
int GAP = 16;
Vector3 DRIFT = {0.01f, 0.0f, 0.005f};
float TRACKING_SPEED = 0.025f;

void updateScreenSize() {
    if (IsWindowResized()) {
        W = GetScreenWidth();
        H = GetScreenHeight();
    }
}

// PLAYER: Satellite, Target & Trackers

typedef struct {
    Camera3D cam;

    Vector3 crosshair;
    Vector2 crosshairScreen;
    Texture2D crosshairTexture;

    Texture2D hPosTexture;
    Texture2D vPosTexture;

} Player;

Player *newPlayer() {
    Player *p = (Player *)malloc(sizeof(Player));

    p->cam.position = (Vector3){0.0f, 10.0f, 0.0f};
    p->cam.target = (Vector3){0.0f, 0.0f, 0.0f};
    p->cam.up = (Vector3){0.0f, 0.0f, -1.0f};
    p->cam.fovy = 60.0f;
    p->cam.projection = CAMERA_ORTHOGRAPHIC;

    p->crosshairTexture = LoadTexture("resources/textures/reticle.png");
    p->hPosTexture = LoadTexture("resources/textures/h_indicator_bottom.png");
    p->vPosTexture = LoadTexture("resources/textures/v_indicator.png");

    return p;
}

void cleanupPlayer(Player *p) {
    UnloadTexture(p->crosshairTexture);
    UnloadTexture(p->hPosTexture);
    free(p);
}

void updatePlayer(Player *p) {

    // DRIFT
    p->cam.position = Vector3Add(p->cam.position, DRIFT);
    p->cam.target = Vector3Add(p->cam.target, DRIFT);

    // Player tracking

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
        p->cam.fovy += 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT_BRACKET)) {
        p->cam.fovy -= 0.1f;
    }

    p->crosshair = GetScreenToWorldRay(GetMousePosition(), p->cam).position;
    p->crosshairScreen = GetWorldToScreen(p->crosshair, p->cam);
    // Manage bounds
    if (p->crosshairScreen.x < GAP) p->crosshairScreen.x = GAP;
    if (p->crosshairScreen.x > GetScreenWidth() - GAP) p->crosshairScreen.x = GetScreenWidth() - GAP;
    if (p->crosshairScreen.y < GAP) p->crosshairScreen.y = GAP;
    if (p->crosshairScreen.y > GetScreenHeight() - GAP) p->crosshairScreen.y = GetScreenHeight() - GAP;
}

void drawPlayerUI2D(Player *p) {
    Vector2 dxTop = {p->crosshairScreen.x, GAP};
    DrawCircleLines(dxTop.x, dxTop.y + GAP / 2.0, GAP / 4.0, RAYWHITE);
    DrawText(TextFormat("[ %.2f ]", p->crosshair.x), dxTop.x + GAP, dxTop.y, GAP, RAYWHITE);

    Vector2 dyLeft = {GAP, p->crosshairScreen.y - p->vPosTexture.height / 4.0};
    DrawTextureEx(p->vPosTexture, dyLeft, 0.0, 0.5, RAYWHITE);
    Vector2 dyRight = {GetScreenWidth() - (p->vPosTexture.width / 2.0 + GAP), p->crosshairScreen.y + p->vPosTexture.height / 4.0};
    DrawTextureEx(p->vPosTexture, dyRight, 270.0, 0.5, RAYWHITE);

    Vector2 cross = {p->crosshairScreen.x, p->crosshairScreen.y};
    DrawTexturePro(p->crosshairTexture,
                   (Rectangle){0, 0, p->crosshairTexture.width, p->crosshairTexture.height},
                   (Rectangle){cross.x, cross.y, p->crosshairTexture.width / 2.0, p->crosshairTexture.height / 2.0},
                   (Vector2){p->crosshairTexture.width / 4.0, p->crosshairTexture.height / 4.0},
                   sin(GetTime()) * 360, RAYWHITE); // Draw the crosshair texture with a custom rectangle

    Vector2 dxTextureBtm = {p->crosshairScreen.x - p->hPosTexture.width / 4.0, GetScreenHeight() - (p->hPosTexture.height / 2.0 + GAP)};
    DrawTextureEx(p->hPosTexture, dxTextureBtm, 0.0, 0.5, RAYWHITE);
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
    for (float y = -(m->height / 2); y <= (m->height / 2); y++) {
        for (float x = -(m->width / 2); x <= (m->width / 2); x++) {
            DrawPoint3D((Vector3){x, 1.0f, y}, GRAY); // Map placeholder
        }
    }
}

// Main Calls

void update(Player *p) {
    updateScreenSize();
    updatePlayer(p);
}

void draw(Map *m, Player *p) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(p->cam);
    drawMap3D(m);
    EndMode3D();

    drawPlayerUI2D(p);

    EndDrawing();
}

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "satellite");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    HideCursor();
    SetTargetFPS(FPS);

    Map *m = newMap(200.0f, 200.0f);
    Player *p = newPlayer();

    while (!WindowShouldClose()) {
        update(p);
        draw(m, p);
    }

    cleanupPlayer(p);
    cleanupMap(m);
    CloseWindow();

    return 0;
}
