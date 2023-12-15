#pragma once

#include"PublicHeader.hpp"

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
        initGraphsSystem(registry);
    }

private:
    static void initGraphsSystem(ECS::Registry registry) {
        registry.createResource<GraphContainer>();
        GraphContainer* graphs = registry.getResource<GraphContainer>();
        graphs->add(GraphInfo::Type::TRIANGLE,GraphContainer::createTriangleVertexs(50));
        graphs->add(GraphInfo::Type::ARROW,GraphContainer::createArrowVertexs(PlayerSize));
        graphs->add(GraphInfo::Type::BULLET,GraphContainer::createBulletVertexs(BulletSize));
    }
};