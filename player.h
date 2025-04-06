#ifndef PLAYER_H
#define PLAYER_H

#include "globe.h"
#include "raylib.h"
#include "raymath.h"

extern int W, H;
extern float GAP;
extern float GLOBE_SIZE;
extern Globe* g;

typedef struct {
    Camera3D cam;
    Vector3 crosshair;
    Vector2 crosshairScreen;
} Player;

Player *NewPlayer();
void CleanupPlayer(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayerCrosshair3D(Player *p);

#endif // PLAYER_H
