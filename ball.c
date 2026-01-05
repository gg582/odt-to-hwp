#include "ball.h"
#include "config.h"
#include <math.h>

void init_ball(Ball* ball, float x, float y, float vx, float vy, float mass) {
    ball->x = x;
    ball->y = y;
    ball->vx = vx;
    ball->vy = vy;
    ball->mass = mass;
    ball->radius = BALL_RADIUS;
}

void update_ball(Ball* ball, float dt) {
    // 중력 적용
    ball->vy += GRAVITY_Y * dt;
    
    // 위치 업데이트
    ball->x += ball->vx * dt;
    ball->y += ball->vy * dt;
}

void check_collision_with_walls(Ball* ball) {
    if (ball->x - ball->radius <= 0 || ball->x + ball->radius >= WALL_X) {
        ball->vx *= -RESTITUTION;
    }
}

void check_collision_with_floor(Ball* ball) {
    if (ball->y + ball->radius >= FLOOR_Y) {
        ball->y = FLOOR_Y - ball->radius;
        ball->vy *= -RESTITUTION;
        if (fabsf(ball->vy) < 0.01f) {
            ball->vy = 0.0f; // 정지 상태 처리
        }
    }
}

void check_ball_collisions(Ball* balls, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            Ball* a = &balls[i];
            Ball* b = &balls[j];
            
            // 두 공 사이의 거리 계산
            float dx = b->x - a->x;
            float dy = b->y - a->y;
            float distance = sqrtf(dx*dx + dy*dy);
            
            // 충돌 검사
            if (distance < (a->radius + b->radius)) {
                // 충돌 지점 계산
                float nx = dx / distance;
                float ny = dy / distance;
                
                // 상대 속도 계산
                float rvx = b->vx - a->vx;
                float rvy = b->vy - a->vy;
                
                // 충돌 지점에서의 상대 속도
                float v_dot_n = rvx * nx + rvy * ny;
                
                // 반발 계수 적용
                float j = (2.0f * a->mass * b->mass * v_dot_n) / 
                         (a->mass + b->mass);
                
                // 충격량 적용
                float impulse = j * RESTITUTION;
                
                // 속도 업데이트
                a->vx += (impulse * nx) / a->mass;
                a->vy += (impulse * ny) / a->mass;
                b->vx -= (impulse * nx) / b->mass;
                b->vy -= (impulse * ny) / b->mass;
                
                // 위치 조정 (겹침 방지)
                float overlap = 0.5f * (a->radius + b->radius - distance);
                a->x -= overlap * nx;
                a->y -= overlap * ny;
                b->x += overlap * nx;
                b->y += overlap * ny;
            }
        }
    }
}
