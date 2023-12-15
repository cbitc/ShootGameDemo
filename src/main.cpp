#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<Common.hpp>
#include<world.hpp>
#include<Component.hpp>
#include<string>
#include<math.h>
#include<random>
#include<ctime>
#include<Resource.hpp>
#include<queue>
#include<PlayerControlSystem.hpp>
#include<InitSystem.hpp>
#include<HandleInputSystem.hpp>
#include<RenderTextureSystem.hpp>
#include<Utility.hpp>
#include<EnemyMoveSystem.hpp>
#include<EnemySpawn.hpp>
#include<MoveSystem.hpp>







void destroySystem(ECS::Registry registry);
void clearSystem(ECS::Registry registry);
void logic(ECS::Registry registry);
void Render(ECS::Registry registry);




int WinMain(int argc,char* argv[]) {

	ECS::World world;
	ECS::Registry registry(world);

	InitSystem::init(registry);

	


	while (!isQuit) {
		HandleInputSystem::update(registry);

		logic(registry);


		Render(registry);

		clearSystem(registry);
	}


	destroySystem(registry);

	return 0;
}
























void destroySystem(ECS::Registry registry) {
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	SDL_Window* window = *registry.getResource<SDL_Window*>();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}


void clearSystem(ECS::Registry registry) {
	MouseInput* input = registry.getResource<MouseInput>();
	input->clear();
}


void logic(ECS::Registry registry) {
	MouseInput* input = registry.getResource<MouseInput>();
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	assertm("resorce is null",input && renderer);
	EnemySpawnSystem::update(registry,renderer);
	EnemyMoveSystem::update(registry);
	MoveSystem::update(registry);
	PlayerControlSystem::update(registry,input,renderer);
}


void Render(ECS::Registry registry) {
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	assertm("renderer is null",renderer);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);


	RenderTextureSystem::update(registry,renderer);

	SDL_RenderPresent(renderer);
}