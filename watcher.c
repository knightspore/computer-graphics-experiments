#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define SEED 1000
#define SIZE 60
#define MD 20
#define SM 10
#define TEXTSIZE 10
#define DELTA_MULT 0.01

typedef struct {
    Color color;
    float yaw, pitch;
} Instruments;

Instruments *newInstruments() {
    Instruments *i = malloc(sizeof(Instruments));
    i->color = RAYWHITE;
    i->yaw = 0.f;
    i->pitch = 0.f;
    return i;
}

void updateInstruments(Instruments *i) {
    Vector2 vd = Vector2Lerp(Vector2Subtract(GetMousePosition(), (Vector2){GetScreenWidth() / 2.0, GetScreenHeight() / 2.0}), (Vector2){i->yaw, i->pitch}, 0.5);
    i->yaw = vd.x;
    i->pitch = vd.y;
}

void drawInstruments(Instruments *i) { // Replace with sprites
    // Target
    Vector2 target = GetMousePosition();
    DrawCircleLinesV(target, SM, i->color);
    DrawLineV((Vector2){target.x, target.y - SM}, (Vector2){target.x, target.y - SM * 4}, i->color);
    DrawLineV((Vector2){target.x - SM, target.y}, (Vector2){target.x - SM * 3, target.y}, i->color);
    DrawLineV((Vector2){target.x + SM, target.y}, (Vector2){target.x + SM * 3, target.y}, i->color);

    // Horizontal Tracking
    Vector2 hStart = {SIZE, GetScreenHeight() / 2.0 + i->pitch};
    Vector2 hEnd = {GetScreenWidth() - SIZE, GetScreenHeight() / 2.0 + i->pitch};
    DrawLineV(hStart, (Vector2){SIZE + MD, GetScreenHeight() / 2.0 + i->pitch}, i->color);
    DrawLineV(hStart, (Vector2){hStart.x, hStart.y + MD}, i->color);
    DrawLineV((Vector2){GetScreenWidth() - SIZE - MD, GetScreenHeight() / 2.0 + i->pitch}, hEnd, i->color);
    DrawLineV(hEnd, (Vector2){hEnd.x, hEnd.y + MD}, i->color);
    DrawText(TextFormat("[ %2.0f ]", i->pitch), GetScreenWidth() - SIZE - MD, GetScreenHeight() / 2.0 + i->pitch - MD, TEXTSIZE, i->color);

    // Vertical Tracking
    DrawLineV((Vector2){GetScreenWidth() / 2.0 + i->yaw, SIZE}, (Vector2){GetScreenWidth() / 2.0 + i->yaw, SIZE + MD}, i->color);
    DrawText(TextFormat("[ %2.0f ]", i->yaw), GetScreenWidth() / 2.0 + TEXTSIZE + i->yaw, SIZE, TEXTSIZE, i->color);
    DrawPolyLines((Vector2){GetScreenWidth() / 2.0 + i->yaw, GetScreenHeight() - SIZE - SM}, 3, SM, -90.0, i->color);
}

typedef struct {
    Vector2 track;
} Map;

Map *newMap() {
    Map *map = malloc(sizeof(Map));
    map->track = Vector2Zero();
    return map;
}

void updateMap(Map *m, Instruments *i) {
    if (i->yaw >= -SIZE) m->track.x += DELTA_MULT * -i->yaw;
    if (i->yaw <= SIZE) m->track.x += DELTA_MULT * -i->yaw;
    if (i->pitch >= -SIZE) m->track.y += DELTA_MULT * -i->pitch;
    if (i->pitch <= -SIZE) m->track.y += DELTA_MULT * -i->pitch;
}

void drawMap(Map *m) {
    for (int y = -GetScreenHeight(); y < GetScreenHeight() * 2.0; y += SM) {
        for (int x = -GetScreenWidth(); x < GetScreenWidth() * 2.0; x += SM) {
            float noise = stb_perlin_noise3_seed((float)x / 200.0f, (float)y / 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, SEED);
            float fade;
            switch ((int)(noise * 10)) {
            case 0:
            case 1:
                fade = 0.1f;
                break;
            case 2:
            case 3:
            case 4:
                fade = 0.3f;
                break;
            case 5:
            case 6:
                fade = 0.5f;
                break;
            case 7:
            case 8:
                fade = 0.7f;
                break;
            default:
                fade = 1.0f;
                break;
            }
            DrawPixel(x + m->track.x, y + m->track.y, Fade(RAYWHITE, fade));
        }
    }
}

int main(void) {
    Instruments *i = newInstruments();
    Map *m = newMap();
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(800, 800, "watcher");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    HideCursor();
    while (!WindowShouldClose()) {
        updateMap(m, i);
        updateInstruments(i);
        BeginDrawing();
        ClearBackground(BLACK);
        drawMap(m);
        drawInstruments(i);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
