#include "globe.h"
#include "raylib.h"

Globe *NewGlobe() {
    Globe *globe = (Globe *)malloc(sizeof(Globe));
    globe->rotation = 0.0;
    globe->sphere = LoadModelFromMesh(GenMeshSphere(GLOBE_SIZE, 16, 16));
    globe->sphere.materials[0].shader = LoadShader("resources/shaders/globe.vert", "resources/shaders/globe.frag");
    globe->scale = 1.0f;
    return globe;
}

void CleanupGlobe(Globe *g) {
    UnloadShader(g->sphere.materials[0].shader);
    UnloadModel(g->sphere);
    free(g);
}

void UpdateGlobe(Globe *g) {
    g->scale = GLOBE_SIZE / 20.0f;
    g->rotation += DRIFT;
}

void DrawGlobe3D(Globe *g) {
    DrawModelEx(
        g->sphere,
        Vector3{},
        Vector3{0.1, 0, 1},
        g->rotation,
        Vector3{g->scale, g->scale, g->scale},
        BLACK);
    BeginBlendMode(BLEND_MULTIPLIED);
    DrawModelWiresEx(
        g->sphere,
        Vector3{},
        Vector3{0.1, 0, 1},
        g->rotation,
        Vector3{g->scale, g->scale, g->scale},
        WHITE);
    EndBlendMode();
}
