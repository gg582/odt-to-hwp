#include "render.h"
#include "ball.h"
#include "config.h"
#include <SDL2/SDL.h>

void render_balls(SDL_Renderer* renderer, Ball* balls, int count) {
    for (int i = 0; i < count; i++) {
        SDL_Rect rect = {
            (int)(balls[i].x - balls[i].radius),
            (int)(balls[i].y - balls[i].radius),
            (int)(2 * balls[i].radius),
            (int)(2 * balls[i].radius)
        };
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void render_gui(SDL_Renderer* renderer, int ball_count, float fps) {
    char text[100];
    
    // 활성화된 객체 수 표시
    snprintf(text, sizeof(text), "활성 객체: %d개", ball_count);
    render_text(renderer, text, 10, 10, 255, 255, 255);
    
    // FPS 표시
    snprintf(text, sizeof(text), "평균 FPS: %.1f", fps);
    render_text(renderer, text, 10, 30, 255, 255, 255);
}

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    // SDL_ttf를 사용한 텍스트 렌더링 구현 필요
    // 이 예제에서는 생략
}
