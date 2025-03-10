#include "commonfunc.h"
#include"baseObject.h"
baseObject g_background;
baseObject g_main;

SDL_Texture* g_main_firing_texture = NULL;
bool is_firing = false;

bool InitData()
{
    bool success=true;
    int ret=SDL_Init(SDL_INIT_VIDEO);
    if(ret<0){std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;return false;}
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_window =SDL_CreateWindow("Game 2D - Producer:NVH",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(g_window==NULL)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        success=false;
    }
    else
    {
        g_screen=SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen==NULL)
        {
            success=false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int     imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&imgFlags))success=false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret =g_background.LoadImg("image/background.png",g_screen);
    if(ret==false)return false;
    return true;
}
bool LoadMain() {
    // Tải texture gốc
    SDL_Surface* loadedSurface = IMG_Load("image/plane_fly.png");
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image plane_fly.png! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    Uint32 colorKey = SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
    SDL_SetColorKey(loadedSurface, SDL_TRUE, colorKey);

    SDL_Texture* planeTexture = SDL_CreateTextureFromSurface(g_screen, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if (planeTexture == nullptr) {
        std::cout << "Unable to create texture from plane_fly.png! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_main.SetTexture(planeTexture);

    // Tải texture "bắn"
    SDL_Surface* firingSurface = IMG_Load("image/plane_fly_bullet.png");
    if (firingSurface == nullptr) {
        std::cout << "Unable to load image plane_fly_bullet.png! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    colorKey = SDL_MapRGB(firingSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
    SDL_SetColorKey(firingSurface, SDL_TRUE, colorKey);

    g_main_firing_texture = SDL_CreateTextureFromSurface(g_screen, firingSurface);
    SDL_FreeSurface(firingSurface);
    if (g_main_firing_texture == nullptr) {
        std::cout << "Unable to create texture from plane_fly_bullet.png! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
void close()
{
    g_background.Free ();
    g_main.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[]) {
    if (!InitData()) return -1;
    if (!LoadBackground()) return -1;
    if (!LoadMain()) return -1;

    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
             if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                if (g_event.button.button == SDL_BUTTON_LEFT) {
                    is_firing = true;
                }
            }
            if (g_event.type == SDL_MOUSEBUTTONUP) {
                if (g_event.button.button == SDL_BUTTON_LEFT) {
                    is_firing = false;
                }
            }
        }


        // Lấy trạng thái bàn phím
      const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

// Kiểm tra phím WASD
if (current_key_states[SDL_SCANCODE_A]) {
    g_main.SetRect(g_main.GetRect().x - speed_main, g_main.GetRect().y);
}
if (current_key_states[SDL_SCANCODE_D]) {
    g_main.SetRect(g_main.GetRect().x + speed_main, g_main.GetRect().y);
}
if (current_key_states[SDL_SCANCODE_W]) {
    g_main.SetRect(g_main.GetRect().x, g_main.GetRect().y - speed_main);
}
if (current_key_states[SDL_SCANCODE_S]) {
    g_main.SetRect(g_main.GetRect().x, g_main.GetRect().y + speed_main);
}

        // Giới hạn vị trí máy bay
        if (g_main.GetRect().x < 0) g_main.SetRect(0, g_main.GetRect().y);
        if (g_main.GetRect().y < 0) g_main.SetRect(g_main.GetRect().x, 0);
        if (g_main.GetRect().x + g_main.GetRect().w > SCREEN_WIDTH) g_main.SetRect(SCREEN_WIDTH - g_main.GetRect().w, g_main.GetRect().y);
        if (g_main.GetRect().y + g_main.GetRect().h > SCREEN_HEIGHT) g_main.SetRect(g_main.GetRect().x, SCREEN_HEIGHT - g_main.GetRect().h);

       SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen);

        // Hiển thị máy bay
        if (is_firing) {
            g_main.SetTexture(g_main_firing_texture);
        } else {
            g_main.LoadImg("image/plane_fly.png", g_screen); // Tải lại texture gốc
        }
        g_main.Render(g_screen);

        SDL_RenderPresent(g_screen);
    }

    SDL_DestroyTexture(g_main_firing_texture);

    close();
    return 0;
}
