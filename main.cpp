#include "commonfunc.h"
#include"baseObject.h"
#include"game_map.h"
#include"MainObject.h"
baseObject g_background;


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
    bool ret =g_background.LoadImg("img/background1.png",g_screen);
    if(ret==false)return false;
    return true;
}

void close()
{
    g_background.Free ();

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
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img/player_right.png",g_screen);
    p_player.set_clips();
    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            p_player.HandeInputAction(g_event,g_screen);

        }


       SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);


        g_background.Render(g_screen);
      game_map.DrawMap(g_screen);

      Map map_data=game_map.getMap();

      p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
    p_player.DoPlayer(map_data);
       p_player.Show(g_screen);
    game_map.SetMap(map_data);

  // game_map.DrawMap(g_screen);

        SDL_RenderPresent(g_screen);
    }



    close();
    return 0;
}
