#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"
#include<random>

struct EnemySpawnSystem final
{
    static void update(ECS::Registry registry,
        SDL_Renderer* renderer,CollisionGroup* collisionGroup) {
        static int Twice = 0;
        if (Twice++ == 5e3) {
            Twice = 0;
            float x = 100 + rand() % 200,y = rand() % height;
            create(registry,renderer,collisionGroup,x,y,EnemySign::Type::RED);
        }
    }
private:
    static void create(ECS::Registry registry,
        SDL_Renderer* renderer,CollisionGroup* collisionGroup,
        float x,float y,EnemySign::Type type) {
        ECS::Entity entity = registry.create();
        registry.emplace<Transform>(entity,Vec2<float>{x,y},Vec2<float>{0.5f,0.5f},0.f);
        RGBA rgba;
        switch (type)
        {
        case EnemySign::Type::RED:
            rgba = RGBA{ 255,0,0,255 };
            break;
        case EnemySign::Type::GREEN:
            rgba = RGBA{ 0,255,0,255 };
            break;
        case EnemySign::Type::BLUE:
            rgba = RGBA{ 0,0,255,255 };
            break;
        default:
            break;
        }
        registry.emplace<Texture>(entity,renderer,RectPath,rgba);
        registry.emplace<Velocity>(entity,Vec2<float>{});
        registry.emplace<EnemySign>(entity,type);
        registry.emplace<CollisionBox>(entity,(uint8_t)2,
            (uint8_t)((1<<0) | (1<<1)),
            0,0,55,55);
        collisionGroup->setGroup(entity,2);
    }
};