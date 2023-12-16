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
#include<EnemyControlSystem.hpp>
#include<EnemySpawn.hpp>
#include<MoveSystem.hpp>
#include<CollisionSystem.hpp>
#include<BulletControlSystem.hpp>







void RenderDrawBox(ECS::Registry registry,SDL_Renderer* renderer);
void ResourceFreeSystem(ECS::Registry registry);
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


	ResourceFreeSystem(registry);

	return 0;
}
























void ResourceFreeSystem(ECS::Registry registry) {
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	SDL_Window* window = *registry.getResource<SDL_Window*>();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}


void clearSystem(ECS::Registry registry) {
	MouseInput* input = registry.getResource<MouseInput>();
	CollisionGroup* collisionGroup = registry.getResource<CollisionGroup>();
	input->clear();

	auto view = registry.view<BeDestroySign>();
	for (ECS::Entity entity : view) {
		CollisionBox* box = registry.try_get<CollisionBox>(entity);
		if (box) {
			collisionGroup->remove(entity,box->groupIndex);
		}
		registry.destory(entity);
	}
}


void logic(ECS::Registry registry) {
	MouseInput* input = registry.getResource<MouseInput>();
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	CollisionGroup* collisionGroup = registry.getResource<CollisionGroup>();
	assertm("resorce is null",input && renderer && collisionGroup);
	CollisionSystem::update(registry,collisionGroup);
	EnemySpawnSystem::update(registry,renderer,collisionGroup);
	EnemyControlSystem::update(registry);
	MoveSystem::update(registry);
	PlayerControlSystem::update(registry,input,renderer,collisionGroup);
}


void Render(ECS::Registry registry) {
	SDL_Renderer* renderer = *registry.getResource<SDL_Renderer*>();
	assertm("renderer is null",renderer);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);


	RenderTextureSystem::update(registry,renderer);
	RenderDrawBox(registry,renderer);

	SDL_RenderPresent(renderer);
}



void RenderDrawBox(ECS::Registry registry,SDL_Renderer* renderer) {
	auto view = registry.view<CollisionBox>();
	for (ECS::Entity entity : view) {
		auto [box,tam] = registry.get<CollisionBox,Transform>(entity);
		SDL_Rect rect{
		.x = box->box.x + tam->position.x,
		.y = box->box.y + tam->position.y,
		.w = box->box.w,.h = box->box.h };
		SDL_SetRenderDrawColor(renderer,255,0,0,255);
		SDL_RenderDrawRect(renderer,&rect);
	}
}