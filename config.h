#ifndef CONFIG_H
#define CONFIG_H

// 물리 상수
#define GRAVITY_Y 9.8f
#define FLOOR_Y 600.0f
#define WALL_X 800.0f
#define RESTITUTION 0.7f
#define BALL_RADIUS 20.0f
#define MAX_BALLS 100

// 화면 설정
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// FPS 설정
#define TARGET_FPS 60
#define TIME_STEP 1.0f / 60.0f

#endif // CONFIG_H
