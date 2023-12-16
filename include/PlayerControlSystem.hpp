#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"
#include<cmath>


struct PlayerControlSystem final
{
    static void update(ECS::Registry registry,
        MouseInput* input,SDL_Renderer* renderer,CollisionGroup* collisionGroup) {
        Vec2<uint16_t> pos = input->getPosition();
        auto view = registry.view<Player>();

        ECS::Entity player = view.back();
        handleCollision(registry,player);

        auto [transform,texture] = registry.get<Transform,Texture>(player);

        const float
            cx = transform->position.x + texture->width * transform->scale.x / 2.f,
            cy = transform->position.y + texture->height * transform->scale.y / 2.f;
        
        float
            dx = pos.x - cx,
            dy = pos.y - cy;
        
        transform->rotation = std::atan(dx / (-dy));
        if (dy > 0)transform->rotation += M_PI;


        if (input->hasPress()) {
            createBullet(registry,renderer,collisionGroup,
                Vec2<float>{cx,cy} + Vec2<float>{dx,dy}.normal() * 50.f,
                Vec2<float>{ pos.x - cx,pos.y - cy }.normal() * 0.05);
        }
    }

private:
    static void createBullet(ECS::Registry registry,
        SDL_Renderer* renderer,CollisionGroup* collisionGroup,
        const Vec2<float> pos,const Vec2<float> velocity) {
        static constexpr float size = 0.3f;
        ECS::Entity entity = registry.create();
        registry.emplace<Transform>(entity,pos,Vec2<float>{size,size},0.f);
        registry.emplace<Texture>(entity,renderer,BulletPath);
        registry.emplace<Velocity>(entity,velocity);
        registry.emplace<Bullet>(entity,Bullet::Type::NORMAL);
        registry.emplace<CollisionBox>(entity,(uint8_t)1,(uint8_t)(1<<2),
            0,0,25,25);
        collisionGroup->setGroup(entity,1);
        return;
    }

    static void handleCollision(ECS::Registry registry,ECS::Entity entity) {
        BeCollision* col = registry.try_get<BeCollision>(entity);
        if (!col)return;
        auto& collisors = col->collisors;
        for (ECS::Entity other : collisors) {
            
        }
        registry.remove<BeCollision>(entity);
    }

};