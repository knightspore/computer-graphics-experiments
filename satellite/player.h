#ifndef PLAYER_H
#define PLAYER_H

#include "globe.h"
#include "raylib.h"
#include "raymath.h"

extern size_t ZOOM_IDX;
extern size_t N_ZOOM_STEP;
extern Globe* g;

typedef struct {
    Camera3D cam;
    Vector3 crosshair;
    Vector3 marker;
} Player;

Player *NewPlayer();
void CleanupPlayer(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayerCrosshair3D(Player *p);

#endif // PLAYER_H
