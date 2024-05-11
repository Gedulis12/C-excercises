#include <SDL2/SDL_scancode.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

void draw_rectangle(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color c)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void draw_bg(SDL_Renderer *renderer, SDL_Color c)
{
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_RenderClear(renderer);
}

SDL_Window* setup()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 test",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      1000, 1000,
                                      0);

    if (!window)
    {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        fprintf(stderr, "SDL_GetWindowSurface failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return NULL;
    }
    return window;

}

int main()
{

    SDL_Color c = {
        .r=220,
        .g=220,
        .b=220,
        .a=255};

    SDL_Color c_bg = {
        .r=25,
        .g=25,
        .b=25,
        .a=255};

    int w = SCREEN_WIDTH/20;
    int h = SCREEN_HEIGHT/20;
    int x = SCREEN_WIDTH/2 - w/2;
    int y = SCREEN_HEIGHT/2 - h/2;

    SDL_Window *win = setup();
    SDL_Renderer *rend = SDL_GetRenderer(win);
    if (!rend || !win) return 1;
    int speed = 5;

    bool keep_window_open = true;

    while(keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                {
                    keep_window_open = false;
                    break;
                }
            }

            const uint8_t *keystate = SDL_GetKeyboardState(NULL);
            if (keystate[SDL_SCANCODE_S])
            {
                y = y+speed;
            }
            if (keystate[SDL_SCANCODE_W])
            {
                y = y-speed;
            }
            if (keystate[SDL_SCANCODE_A])
            {
                x = x-speed;
            }
            if (keystate[SDL_SCANCODE_D])
            {
                x = x+speed;
            }

            draw_bg(rend, c_bg);
            draw_rectangle(rend, x, y, w , h, c);
            SDL_UpdateWindowSurface(win);
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
