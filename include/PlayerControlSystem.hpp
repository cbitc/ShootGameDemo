#pragma once

#include"PublicHeader.hpp"
#include<cmath>


struct PlayerControlSystem final
{
    static void update(ECS::Registry registry,MouseInput* input,SDL_Renderer* renderer) {
        Vec2<uint16_t> pos = input->getPosition();

        auto view = registry.view<Player>();

        for (ECS::Entity entity : view) {
            Transform* transform = registry.get<Transform>(entity);
            float cx = transform->position.x + 27.5f,cy = transform->position.y + 27.5f;
            transform->rotation = std::atan(float(pos.x - cx) / float(-(pos.y-cy)));
            if (input->hasPress()) {
                createBullet(registry,renderer,
                    transform->position,
                    Vec2<float>{pos.x - cx,pos.y - cy}.normal()*0.05);
            }
        }
    }

private:
    static void createBullet(ECS::Registry registry,SDL_Renderer* renderer,
        const Vec2<float> pos,const Vec2<float> velocity) {
        static constexpr float size = 0.3f;
        ECS::Entity entity = registry.create();
        registry.emplace<Transform>(entity,pos,Vec2<float>{size,size},0.f);
        registry.emplace<Texture>(entity,renderer,BulletPath);
        registry.emplace<Velocity>(entity,velocity);
        registry.emplace<Bullet>(entity,Bullet::Type::NORMAL);
        return;
    }

    static void shoot(ECS::Registry registry,SDL_Renderer* renderer) {
        
    }
};