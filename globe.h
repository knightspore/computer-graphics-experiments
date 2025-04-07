#ifndef GLOBE_H
#define GLOBE_H

#include "raylib.h"
#include "stdlib.h"

extern float SCALE;

typedef struct {
    Model sphere;
    float rotation;
} Globe;

Globe *NewGlobe();
void CleanupGlobe(Globe *g);
void UpdateGlobe(Globe *g);
void DrawGlobe3D(Globe *g);
Vector3 GetGlobeCollision(Ray ray);

#endif // GLOBE_H
