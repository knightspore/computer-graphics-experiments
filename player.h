#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

extern float GAP;
extern Rectangle SCREEN_RECT;
extern Vector3 DRIFT_VECTOR;
extern float TRACKING_SPEED;

typedef struct {
    Camera3D cam;
    Vector3 crosshair;
    Vector2 crosshairScreen;
    Texture2D crosshairTexture;
    Texture2D hPosTexture;
    Texture2D vPosTexture;
} Player;

Player *NewPlayer();
void CleanupPlayer(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayerUI(Player *p);

#endif // PLAYER_H
