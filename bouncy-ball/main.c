#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 800

#define MARGIN (WIDTH / 50)

Vector2 playerPos = {WIDTH / 2.0, HEIGHT / 2.0};
enum Dir { N, E, S, W };
bool direction[4] = {false, false, false, false};
Vector2 vel = {0, 0.98};

int main() {
  SetTraceLogLevel(LOG_NONE);
  InitWindow(WIDTH, HEIGHT, "[raylib]");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    // Update //
    playerPos.x += vel.x;
    playerPos.y += vel.y;

    direction[W] = IsKeyDown(KEY_A) ? true : false;
    direction[E] = IsKeyDown(KEY_D) ? true : false;

    if (playerPos.x <= 0) {
      playerPos.x = 0;
      vel.x = -vel.x;
      direction[W] = false;
    }

    if (playerPos.x >= WIDTH) {
      playerPos.x = WIDTH;
      vel.x = -vel.x;
      direction[E] = false;
    }

    if (direction[E])
      if (vel.x < 20)
        vel.x += 0.4;
    if (direction[W])
      if (vel.x > -20)
        vel.x -= 0.4;
    if (!direction[E] && !direction[W])
      vel.x *= 0.9;

    if (IsKeyPressed(KEY_SPACE)) {
      vel.y = -30;
    }
    vel.y += 0.98;

    if (playerPos.y >= HEIGHT) {
      playerPos.y = HEIGHT;
      if (vel.y > 0.98) {
        vel.y = -(vel.y * 0.8);
      } else {
        vel.y = 0;
        playerPos.y = HEIGHT;
      }
    }

    // Draw //

    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = -HEIGHT; y < HEIGHT * 2; y += MARGIN) {
      for (int x = -WIDTH; x < WIDTH * 2; x += MARGIN) {
        float dist = Vector2Distance(playerPos, (Vector2){x, y});
        float invDist = WIDTH - dist;
        Vector2 delta =
            Vector2MoveTowards((Vector2){x, y}, playerPos, invDist / 20.0);
        Color color = ColorLerp(VIOLET, RED, dist / WIDTH);
        DrawPixel(delta.x, delta.y, color);
      }
    }

    DrawCircleV(playerPos, 10, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
