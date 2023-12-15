#pragma once

#include"PublicHeader.hpp"


struct PlayerControlSystem final
{
    static void update(ECS::Registry registry,MouseInput* input) {
        if (!input->hasMove() && !input->hasPress())return;
        Vec2<uint16_t> pos = input->getPosition();

        SDL_Log("%d %d",pos.x,pos.y);
        auto view = registry.view<Player>();

        for (ECS::Entity entity : view) {
            Transform* transform = registry.get<Transform>(entity);
            if (input->hasPress()) {
                createBullet(registry,transform->position,{ 1.f,1.f },0);
            }
        }
    }

private:
    static void createBullet(ECS::Registry registry,const Vec2<float> pos,
        const Vec2<float> scale,const float rotation) {
        ECS::Entity entity = registry.create();
        registry.emplace<Transform>(entity,pos,scale,rotation);
        registry.emplace<GraphInfo>(entity,GraphInfo::Type::BULLET);
        registry.emplace<Bullet>(entity,Bullet::Type::NORMAL);
        return;
    }
};