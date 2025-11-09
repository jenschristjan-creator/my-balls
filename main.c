#include "raylib/include/raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define WIDTH 1000
#define HEIGHT 1000
#define TITLE "Balls and their admirers"
#define BALL_COUNT 100
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 20
#define RADIUS_MIN 5

Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};

typedef struct Ball{
  float posx, posy;
  float velx, vely;
  float radius;
  Color color;
  struct Ball *follows;
} Ball;

Ball balls[BALL_COUNT];

void init_ball_random(void) {
  for (size_t i = 0; i < BALL_COUNT; i++) {
    size_t target;
    do {
      target = GetRandomValue(0, BALL_COUNT - 1);
    } while (target == i); // don't follow yourself
    balls[i].follows = &balls[target];
  }
}


// Initialize all `balls`
void init_balls_random() {
  for (size_t i = 0; i < BALL_COUNT; i++) { 
    balls[i].radius = GetRandomValue(RADIUS_MIN, RADIUS_MAX);
    balls[i].posx = GetRandomValue(0 + balls[i].radius, WIDTH - balls[i].radius);
    balls[i].posy = GetRandomValue(0 + balls[i].radius, HEIGHT - balls[i].radius);
    balls[i].color = COLORS [GetRandomValue(0,20)];
    balls[i].velx = GetRandomValue(-VEL_MAX, VEL_MAX);
    balls[i].vely = GetRandomValue(-VEL_MAX, VEL_MAX);
  }
}

void draw_ball(Ball *p) {
  DrawCircle(p->posx, p->posy, p->radius, p->color);
}

void spawn_balls() {
  for (size_t i = 0; i < BALL_COUNT; i++) {
    draw_ball(&balls[i]);
  }
}



//Updates the positions of balls according to their velocities
void update_pos(void) {
  float delta_t = GetFrameTime();

  for (size_t i = 0; i < BALL_COUNT; i++) {

    balls[i].posx += balls[i].velx;
    balls[i].posy += balls[i].vely;

    float dx = balls[i].follows->posx - balls[i].posx;
    float dy = balls[i].follows->posy - balls[i].posy;

    float follow_factor = 0.02f;

    balls[i].velx += dx * follow_factor * delta_t;
    balls[i].vely += dy * follow_factor * delta_t;

    float damping_factor = 0.98f;

    balls[i].velx *= damping_factor;
    balls[i].vely *= damping_factor;

    if (balls[i].posx < balls[i].radius) {
      balls[i].posx = balls[i].radius;
      balls[i].velx = -balls[i].velx;
    }else if (balls[i].posx > WIDTH - balls[i].radius) {
      balls[i].posx = WIDTH - balls[i].radius;
      balls[i].velx = -balls[i].velx;
    }
    if (balls[i].posy < balls[i].radius) {
      balls[i].posy = balls[i].radius;
      balls[i].vely = -balls[i].vely;
    }else if (balls[i].posy > HEIGHT - balls[i].radius) {
      balls[i].posy = HEIGHT - balls[i].radius;
      balls[i].vely = -balls[i].vely;
    }
  }
}


int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  init_balls_random();
    init_ball_random();

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    update_pos();
    BeginDrawing();
   // update_elements();
    ClearBackground(RAYWHITE);
    spawn_balls();
    EndDrawing();
  }
}
