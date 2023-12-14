#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<Common.hpp>
#include<world.hpp>


using namespace std;

const int width = 800,height = 600;
bool isQuit = false;


void logic();
void render(SDL_Renderer* renderer);
void handleEvent(SDL_Event* event);


int WinMain(int argc,char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	SDL_Window* window = SDL_CreateWindow("hello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

	SDL_Texture* texture = IMG_LoadTexture(renderer,"../resource/invite.png");

	SDL_Event event;
	CCGAME::Vec2<int> vec;

	while (!isQuit) {
		handleEvent(&event);

		logic();
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		SDL_Rect rect{ .x = 100,.y = 100,.w = 50,.h = 50 };
		SDL_RenderCopy(renderer,texture,nullptr,&rect);

		SDL_RenderPresent(renderer);

		SDL_Delay(60);
	}



	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}


void logic() {

}


void render(SDL_Renderer* renderer) {

}

void handleEvent(SDL_Event* event) {
	while (SDL_PollEvent(event)) {
		if (event->type == SDL_QUIT) {
			isQuit = true;
		}
	}
}