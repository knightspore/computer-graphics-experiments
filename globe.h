#ifndef GLOBE_H
#define GLOBE_H

#include "raylib.h"
#include "stdlib.h"

extern float SCALE;
extern bool DEBUG;

typedef struct {
    Model sphere;
    float rotation;
} Globe;

Globe *NewGlobe();
void CleanupGlobe(Globe *g);
void UpdateGlobe(Globe *g);
void DrawGlobe3D(Globe *g);
Vector3 GetGlobeCollision(Ray ray);
Vector3 GetGlobeSurface(Vector3 point);
Vector3 GetGlobeSurfaceHeight(Vector3 point, float height);

#endif // GLOBE_H
