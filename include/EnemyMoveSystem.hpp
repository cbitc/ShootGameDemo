#pragma once

#include"PublicHeader.hpp"
#include"Utility.hpp"
#include<cmath>

struct EnemyMoveSystem final
{
    static void update(ECS::Registry registry) {
        static constexpr float EnemySpeed = 0.05f;
        auto view = registry.view<EnemySign>();
        for (ECS::Entity entity : view) {
            auto [type,transform,velocity] =
                registry.get<EnemySign,Transform,Velocity>(entity);
            const Vec2<float> playerPos = Utility::queryPlayerPosition(registry);
            float tx = playerPos.x - transform->position.x,
                ty = playerPos.y - transform->position.y;
            velocity->vel = Vec2<float>{ tx,ty }.normal() * EnemySpeed;
        }
    }
private:
    
};