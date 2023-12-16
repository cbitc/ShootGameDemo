#pragma once

#include"PublicHeader.hpp"

#include<ctime>

struct InitSystem final
{
    static void init(ECS::Registry registry) {
        std::srand(std::time(nullptr));
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        SDL_Window* window = SDL_CreateWindow("hello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);

        SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

        registry.createResource<SDL_Renderer*>(renderer);
        registry.createResource<SDL_Window*>(window);
        registry.createResource<MouseInput>();
        CollisionGroup* group = registry.createResource<CollisionGroup>();

        ECS::Entity player = registry.create();
        registry.emplace<Transform>(player,Vec2<float>{300,300},
            Vec2<float>{0.5f,0.5f},ANGTOROT(30));
        registry.emplace<Texture>(player,renderer,TrianglePath,RGBA{0,255,255,255});
        registry.emplace<Player>(player,100);
        registry.emplace<CollisionBox>(player,(uint8_t)0,(uint8_t)(1<<2),
            0,0,55,55);
        group->setGroup(player,0);
    }

private:
    
};