#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

typedef struct {
    float x, y;      // 위치
    float vx, vy;    // 속도
    float mass;      // 질량
    float radius;    // 반지름
} Ball;

void init_ball(Ball* ball, float x, float y, float vx, float vy, float mass);
void update_ball(Ball* ball, float dt);
void check_collision_with_walls(Ball* ball);
void check_collision_with_floor(Ball* ball);
void check_ball_collisions(Ball* balls, int count);

#endif // BALL_H
