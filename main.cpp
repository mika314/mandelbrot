#include <SDL2/SDL.h>
#include <iostream>
#include <complex>

int main()
{
  enum { Width = 1280, Height = 720 };
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init(SDL_INIT_VIDEO)\n";
    return -1;
  }
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_SetWindowPosition(window, 65, 126);

  enum { PaletteSize = 32 };
  int palette[PaletteSize + 1][3];
  for (int i = 0; i <= PaletteSize; ++i)
  {
    palette[i][0] = i < 2 * PaletteSize / 3 ? i * 255 * 3 / (2 * PaletteSize) : 255;
    palette[i][1] = i < PaletteSize / 3 ? 0 : (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
    palette[i][2] = 0;
  }

  for (int y = 0; y < Height; ++y)
    for (int x = 0; x < Width; ++x)
    {
      std::complex<double> c(0.5 * (x - (Width - Height) / 2) / Height * 4.0 - 2.0, 0.5 * y / Height * 4.0 - 2.0);
      std::complex<double> z(0.0, 0.0);
      int cnt = 0;
      while (cnt < PaletteSize)
      {
        z = z * z + c;
        if (abs(z) > 2.0)
          break;
        ++cnt;
      }
      SDL_SetRenderDrawColor(renderer, palette[cnt][0], palette[cnt][1], palette[cnt][2], 0xff);
      SDL_RenderDrawPoint(renderer, x, y);
    }

  SDL_RenderPresent(renderer);
  std::cin.get();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}
