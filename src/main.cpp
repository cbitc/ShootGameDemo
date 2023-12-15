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
#include<RenderGraphSystem.hpp>
#include<InitSystem.hpp>
#include<HandleInputSystem.hpp>










void destroySystem(ECS::Registry registry);
void clearSystem(ECS::Registry registry);
void logic(ECS::Registry registry);
void Render(ECS::Registry registry);




int WinMain(int argc,char* argv[]) {

	ECS::World world;
	ECS::Registry registry(world);

	InitSystem::init(registry);

	ECS::Entity hero = registry.create();
	registry.emplace<Transform>(hero,Vec2<float>{100.f,100.f},Vec2<float>{1.f,1.f},0.f);
	registry.emplace<GraphInfo>(hero,GraphInfo::Type::ARROW,RGBA{0,255,255,255});


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
	assertm("input is null",input);
	PlayerControlSystem::update(registry,input);
}


void Render(ECS::Registry registry) {
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	GraphContainer* graphs = registry.getResource<GraphContainer>();
	assertm("renderer is null",renderer);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);

	RenderGraphSystem::update(registry,renderer,graphs);



	SDL_RenderPresent(renderer);
}