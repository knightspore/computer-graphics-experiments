#ifndef GLOBE_H
#define GLOBE_H

#include "raylib.h"
#include "stdlib.h"

extern float DRIFT;
extern float GLOBE_SIZE;

typedef struct {
    Model sphere;
    float rotation;
    float scale;
} Globe;

Globe *NewGlobe();
void CleanupGlobe(Globe *g);
void UpdateGlobe(Globe *g);
void DrawGlobe3D(Globe *g);

#endif // GLOBE_H
