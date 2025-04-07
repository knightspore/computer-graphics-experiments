#include "globe.h"
#include "raylib.h"
#include "raymath.h"

float EARTH_RADIUS = 6371.0f * SCALE;
float EARTH_ROTATION = 1.600f * SCALE;
float GLOBE_LOD = 32;

Globe *NewGlobe() {
    Globe *globe = (Globe *)malloc(sizeof(Globe));
    globe->rotation = 0.0;
    globe->sphere = LoadModelFromMesh(GenMeshSphere(EARTH_RADIUS, GLOBE_LOD, GLOBE_LOD));
    globe->sphere.materials[0].shader = LoadShader("resources/shaders/globe.vert", "resources/shaders/globe.frag");
    Image texImg = LoadImage("resources/textures/2k_earth_daymap.jpg");
    ImageFlipVertical(&texImg);
    ImageRotate(&texImg, -90);
    globe->sphere.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(texImg);
    UnloadImage(texImg);
    return globe;
}

void CleanupGlobe(Globe *g) {
    UnloadTexture(g->sphere.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture);
    UnloadShader(g->sphere.materials[0].shader);
    UnloadModel(g->sphere);
    free(g);
}

void UpdateGlobe(Globe *g) {
    g->rotation += EARTH_ROTATION * GetFrameTime();
    if (g->rotation > 360.0f) {
        g->rotation -= 360.0f;
    }
}

void DrawGlobe3D(Globe *g) {
    DrawModelEx(
        g->sphere,
        Vector3{},
        Vector3{0.1, 0, 1},
        g->rotation,
        Vector3{1, 1, 1},
        BLACK);
}

Vector3 GetGlobeCollision(Ray ray) {
    RayCollision collision = GetRayCollisionSphere(ray, Vector3{0}, EARTH_RADIUS);
    return collision.hit ? collision.point : Vector3{0, 0, 0};
}

Vector3 GetGlobeSurface(Vector3 point) {
    Vector3 surface = Vector3Normalize(point);
    return Vector3Scale(surface, EARTH_RADIUS);
}

Vector3 GetGlobeSurfaceHeight(Vector3 point, float height) {
    Vector3 surface = Vector3Normalize(point);
    Vector3 distantDir = Vector3Scale(surface, 1.5f);
    return Vector3MoveTowards(surface, distantDir, height);
}
