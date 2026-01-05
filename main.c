#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "physics.h"
#include "render.h"
#include "ball.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // SDL 초기화
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    SDL_Window* window = SDL_CreateWindow(
        "물리 시뮬레이션",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // 공 배열 초기화
    Ball balls[MAX_BALLS];
    int ball_count = 0;
    
    // 초기 공 생성
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 5; i++) {
        float x = rand() % (int)WALL_X;
        float y = rand() % 200;
        float vx = (rand() % 100) / 20.0f - 2.5f;
        float vy = (rand() % 100) / 20.0f - 2.5f;
        float mass = 1.0f + (rand() % 5);
        
        init_ball(&balls[ball_count++], x, y, vx, vy, mass);
    }
    
    // FPS 계산
    const int num_samples = 10;
    float frame_times[num_samples];
    int sample_index = 0;
    Uint32 last_time = SDL_GetTicks();
    
    // 메인 루프
    int running = 1;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        
        // 시간 계산
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        
        // FPS 샘플 업데이트
        frame_times[sample_index++ % num_samples] = delta_time;
        
        // 물리 업데이트
        update_physics(balls, ball_count, delta_time);
        
        // 렌더링
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        render_balls(renderer, balls, ball_count);
        
        // FPS 계산
        float fps = 0.0f;
        for (int i = 0; i < num_samples; i++) {
            fps += frame_times[i] > 0 ? 1.0f / frame_times[i] : 0;
        }
        fps /= num_samples;
        
        render_gui(renderer, ball_count, fps);
        SDL_RenderPresent(renderer);
    }
    
    // 정리
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
