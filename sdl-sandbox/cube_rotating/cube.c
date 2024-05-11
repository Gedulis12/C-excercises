#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_scancode.h>

#define ARRAY_LENGTH(x) ((float)sizeof(x) / (float)sizeof((x)[0]))
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define BACKGROUND_COLOR {25,25,25,255}
#define FPS 60
#define TICK_INTERVAL 1000/FPS
#define CUBE_SIZE 350

bool keep_window_open = false;
uint32_t next_time;

typedef struct {
    float x,y,z;
} Vec3;

uint32_t time_left()
{
    uint32_t now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

void rotate(Vec3 *point, float x, float y, float z)
{
    float rad = 0;
    rad = x;
    float tmp_y = point->y;
    float tmp_x = point->x;

    tmp_y = cosf(rad) * point->y - sinf(rad) * point->z;
    point->z = sinf(rad) * point->y + cosf(rad) * point->z;
    point->y = tmp_y;

    rad = y;
    tmp_x = cosf(rad) * point->x + sinf(rad) * point->z;
    point->z = -sinf(rad) * point->x + cosf(rad) * point->z;
    point->x = tmp_x;

    rad = z;
    point->x = cosf(rad) * point->x - sinf(rad) * point->y;
    point->y = sinf(rad) * point->x + cosf(rad) * point->y;
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

    SDL_Window *window = SDL_CreateWindow("Rotating Cube",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      SCREEN_WIDTH, SCREEN_HEIGHT,
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

int gcd (int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

float lcm(float a, float b)
{
    int int_a = a*1000000;
    int int_b = b*1000000;

    int int_gcd = gcd(int_a, int_b);
    float lcm = (float)((int_a * int_b) / int_gcd) / 1000000;
    return lcm;
}

float lcm3(float a, float b, float c)
{
    float lcm_ab = lcm(a, b);
    float lcm_abc = lcm(lcm_ab, c);
    return lcm_abc;
}

float min3(float a, float b, float c)
{
    float min_ab;
    float min_abc;
    if (a < b)
    {
        min_ab = a;
    }
    else
    {
        min_ab = b;
    }

    if (min_ab < c)
    {
        return min_ab;
    }
    return c;
}

int main()
{
    SDL_Window *win = setup();
    SDL_Renderer *rend = SDL_GetRenderer(win);
    if (!rend || !win)
    {
        return 1;
    }
    else
    {
        keep_window_open = true;
    }

    SDL_Color bg = BACKGROUND_COLOR;

    int width_center = SCREEN_WIDTH/2;
    int height_center = SCREEN_HEIGHT/2;
    int cube_offset = CUBE_SIZE/2;

    Vec3 points[] = {
        {.x = width_center - cube_offset, .y = height_center - cube_offset, .z = height_center - cube_offset},
        {.x = width_center - cube_offset, .y = height_center + cube_offset, .z = height_center-cube_offset},
        {.x = width_center + cube_offset, .y = height_center + cube_offset, .z = height_center-cube_offset},
        {.x = width_center + cube_offset, .y = height_center - cube_offset, .z = height_center-cube_offset},

        {.x = width_center - cube_offset, .y = height_center - cube_offset, .z = height_center + cube_offset},
        {.x = width_center - cube_offset, .y = height_center + cube_offset, .z = height_center + cube_offset},
        {.x = width_center + cube_offset, .y = height_center + cube_offset, .z = height_center + cube_offset},
        {.x = width_center + cube_offset, .y = height_center - cube_offset, .z = height_center + cube_offset},
    };

    Vec3 points_orig[(size_t)ARRAY_LENGTH(points)];
    for (size_t i = 0; i < (size_t)ARRAY_LENGTH(points); i++)
    {
        points_orig[i] = points[i];
    }

    Vec3 centr = {0,0,0};
    for (int i = 0; i < ARRAY_LENGTH(points); i++)
    {
        centr.x += points[i].x;
        centr.y += points[i].y;
        centr.z += points[i].z;
    }
    centr.x /= ARRAY_LENGTH(points);
    centr.y /= ARRAY_LENGTH(points);
    centr.z /= ARRAY_LENGTH(points);

    float rx = 0.0002f;
    float ry = 0.0001f;
    float rz = 0.0004f;
    float r_lcm = lcm3(rx, ry, rz);
    float r_min = min3(rx, ry, rz);
    double deg360 = 2*M_PI;
    int full_rotation_c = deg360/r_min;
    int c = 0;

    next_time = SDL_GetTicks() + TICK_INTERVAL;
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
        }
        draw_bg(rend, bg);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        c++;
        if (c >= full_rotation_c)
        {
            c = 0;
            for (int i = 0; i < ARRAY_LENGTH(points); i++)
            {
                points[i] = points_orig[i];
            }
        }
        for (int i = 0; i < ARRAY_LENGTH(points); i++)
        {
            points[i].x -= centr.x;
            points[i].y -= centr.y;
            points[i].z -= centr.z;
            rotate(&points[i], rx, ry, rz);
            points[i].x += centr.x;
            points[i].y += centr.y;
            points[i].z += centr.z;
        }

        for (int i = 0; i < ARRAY_LENGTH(points); i++)
        {
            SDL_RenderDrawPointF(rend, points[i].x, points[i].y);
        }
        SDL_RenderDrawLineF(rend, points[0].x, points[0].y, points[1].x, points[1].y);
        SDL_RenderDrawLineF(rend, points[1].x, points[1].y, points[2].x, points[2].y);
        SDL_RenderDrawLineF(rend, points[2].x, points[2].y, points[3].x, points[3].y);
        SDL_RenderDrawLineF(rend, points[3].x, points[3].y, points[0].x, points[0].y);
        SDL_RenderDrawLineF(rend, points[0].x, points[0].y, points[4].x, points[4].y);
        SDL_RenderDrawLineF(rend, points[1].x, points[1].y, points[5].x, points[5].y);
        SDL_RenderDrawLineF(rend, points[2].x, points[2].y, points[6].x, points[6].y);
        SDL_RenderDrawLineF(rend, points[3].x, points[3].y, points[7].x, points[7].y);
        SDL_RenderDrawLineF(rend, points[4].x, points[4].y, points[5].x, points[5].y);
        SDL_RenderDrawLineF(rend, points[5].x, points[5].y, points[6].x, points[6].y);
        SDL_RenderDrawLineF(rend, points[6].x, points[6].y, points[7].x, points[7].y);
        SDL_RenderDrawLineF(rend, points[7].x, points[7].y, points[4].x, points[4].y);
        SDL_RenderPresent(rend);

//        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
