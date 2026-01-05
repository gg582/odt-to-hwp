#include "physics.h"
#include "ball.h"
#include "config.h"

void update_physics(Ball* balls, int count, float dt) {
    // 1. 모든 공의 물리 상태 업데이트
    for (int i = 0; i < count; i++) {
        update_ball(&balls[i], dt);
    }
    
    // 2. 벽 충돌 검사
    for (int i = 0; i < count; i++) {
        check_collision_with_walls(&balls[i]);
    }
    
    // 3. 바닥 충돌 검사
    for (int i = 0; i < count; i++) {
        check_collision_with_floor(&balls[i]);
    }
    
    // 4. 공들 간 충돌 검사
    check_ball_collisions(balls, count);
}
