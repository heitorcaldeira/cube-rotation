#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>

#define PI           3.14159265358979323846
#define WIDTH        600
#define HEIGHT       600
#define GRID_COUNT   20
#define GRID_PAD     1. / GRID_COUNT
#define GRID_SIZE    ((GRID_COUNT - 1) * GRID_PAD)
#define SQUARE_SIZE  1.

size_t game_running = 1;
static float angle = 0.0;
static int mouseX = 0.0;
static int mouseY = 0.0;

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  if (event.type == SDL_QUIT) {
    game_running = 0;
  }

  if(event.type == SDL_MOUSEMOTION) {
    SDL_GetMouseState(&mouseX, &mouseY);
  }
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface* surface = SDL_GetWindowSurface(window);

  while (game_running) {
    process_input();

    SDL_Rect rect = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(surface, &rect, 0xFF000000);

    float mx = (float)mouseX / WIDTH;
    angle = mx * PI;

    for (int ix = 0; ix < GRID_COUNT; ++ix) {
      for (int iy = 0; iy < GRID_COUNT; ++iy) {
        for (int iz = 0; iz < GRID_COUNT; ++iz) {
          float x = ix * GRID_PAD - GRID_SIZE / 2;
          float y = iy * GRID_PAD - GRID_SIZE / 2;
          float z = .8 + iz * GRID_PAD;

          float cx = 0.0;
          float cz = 0.8 + GRID_SIZE / 2;
          float dx = x - cx;
          float dz = z - cz;

          float a = atan2(dz, dx);
          float m = sqrtf(dx * dx + dz * dz);

          dx = cos(a + angle) * m;
          dz = sin(a + angle) * m;

          x = dx + cx;
          z = dz + cz;

          uint32_t r = ix*255/GRID_SIZE;
          uint32_t g = iy*255/GRID_SIZE;
          uint32_t b = iz*255/GRID_SIZE;
          uint32_t color = 0xFFFF0000 | (r<<0) | (g<<(1*8)) | (b<<(2*8));

          x /= z;
          y /= z;
          SDL_Rect rect = {(x + 1) / 2 * WIDTH, (y + 1) / 2 * HEIGHT, SQUARE_SIZE, SQUARE_SIZE};
          SDL_FillRect(surface, &rect, color);
        }
      }
    }

    SDL_UpdateWindowSurface(window);
  }
}

