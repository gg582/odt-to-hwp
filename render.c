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

void render_gui(SDL_Renderer* renderer, int ball_count, float fps) {
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        // 기본 폰트 사용
        font = TTF_GetFontFromTTF_String("default", 24);
    }
    
    // 활성화된 객체 수 표시
    char text[100];
    snprintf(text, sizeof(text), "활성 객체: %d개", ball_count);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect textRect = {10, 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    
    // FPS 표시
    snprintf(text, sizeof(text), "평균 FPS: %.1f", fps);
    surface = TTF_RenderText_Solid(font, text, white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    textRect = {10, 30, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
