
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

const int MAP_WIDTH = 4800;
const int MAP_HEIGHT = 600;

//screen
const int SCREEN_HEIGHT=600   ;//chieu dai cua screen
const int SCREEN_WIDTH=1000 ;//chieu rong cua screen
const int SCREEN_BPP=32;

const int COLOR_KEY_R =0;
const int COLOR_KEY_G =255 ;
const int COLOR_KEY_B =255 ;

const int RENDER_DRAW_COLOR=255;//=255

const double speed_main=1;
#endif


