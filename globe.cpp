#include "globe.h"

Globe *NewGlobe() {
    Globe *globe = (Globe *)malloc(sizeof(Globe));
    globe->rotation = 0.0;
    globe->sphere = LoadModelFromMesh(GenMeshSphere(GLOBE_SIZE, 16, 16));
    globe->sphere.materials[0].shader = LoadShader("resources/shaders/globe.vert", "resources/shaders/globe.frag");
    return globe;
}

void CleanupGlobe(Globe *g) {
    UnloadShader(g->sphere.materials[0].shader);
    UnloadModel(g->sphere);
    free(g);
}

void UpdateGlobe(Globe *g) {
    g->rotation += DRIFT;
}

void DrawGlobe3D(Globe *g) {
    DrawModelEx(g->sphere, Vector3{0}, Vector3{0, 0, 1}, g->rotation, Vector3{1, 1, 1}, GRAY);
}
