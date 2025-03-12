
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <SDL_mixer.h>
#include<iostream>
#include <vector>
using namespace std;
extern SDL_Renderer* g_renderer;
static SDL_Window* g_window=NULL;
static SDL_Renderer*g_screen=NULL;
static SDL_Event g_event ;


//screen
const int SCREEN_HEIGHT=600  ;//chieu dai cua screen
const int SCREEN_WIDTH=1280 ;//chieu rong cua screen
const int SCREEN_BPP=32;

const int COLOR_KEY_R =167;
const int COLOR_KEY_G =175 ;
const int COLOR_KEY_B =180 ;

const int RENDER_DRAW_COLOR=255;//=255

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0
typedef struct Input {
int left_;
int right_;
int up_;
int down_;
int jump_;
}Input;
typedef struct Map
{
  int start_x_;
  int start_y_;
  int max_x_;
  int max_y_;
  int tile[MAX_MAP_Y][MAX_MAP_X];  // MAX_MAP_Y = 10, MAX_MAP_X = 400
  char* file_name_;
} Map;
#endif


