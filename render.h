#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "ball.h"

void render_balls(SDL_Renderer* renderer, Ball* balls, int count);
void render_gui(SDL_Renderer* renderer, int ball_count, float fps);
void render_text(SDL_Renderer* renderer, const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b);

#endif // RENDER_H
