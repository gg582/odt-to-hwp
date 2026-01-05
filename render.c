#include "render.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

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

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        // 기본 폰트 사용 시도
        font = TTF_OpenFont("DejaVuSans.ttf", 24);
        if (!font) {
            // 폰트 로드 실패 시 함수 종료
            return;
        }
    }
    
    SDL_Color color = {r, g, b, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        TTF_CloseFont(font);
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }
    
    SDL_Rect textRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void render_gui(SDL_Renderer* renderer, int ball_count, float fps) {
    // 활성화된 객체 수 표시
    char text[100];
    snprintf(text, sizeof(text), "활성 객체: %d개", ball_count);
    render_text(renderer, text, 10, 10, 255, 255, 255);
    
    // FPS 표시
    snprintf(text, sizeof(text), "평균 FPS: %.1f", fps);
    render_text(renderer, text, 10, 30, 255, 255, 255);
}
