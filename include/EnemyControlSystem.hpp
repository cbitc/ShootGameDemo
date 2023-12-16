#pragma once

#include"PublicHeader.hpp"
#include"Utility.hpp"
#include<cmath>

struct EnemyControlSystem final
{
    static void update(ECS::Registry registry) {

        auto view = registry.view<EnemySign>();
        for (ECS::Entity entity : view) {
            handleCollision(registry,entity);
            setVelocity(registry,entity);
        }
    }
private:
    static void handleCollision(ECS::Registry registry,ECS::Entity entity) {
        BeCollision* col = registry.try_get<BeCollision>(entity);
        if (col) {
            registry.get_or_emplace<BeDestroySign>(entity)->twice++;
            registry.remove<BeCollision>(entity);
        }
        
    }


    static void setVelocity(ECS::Registry registry,ECS::Entity entity) {
        static constexpr float EnemySpeed = 0.05f;
        auto [type,transform,velocity] =
            registry.get<EnemySign,Transform,Velocity>(entity);
        
        const Vec2<float> playerPos = Utility::queryPlayerPosition(registry);
        float tx = playerPos.x - transform->position.x,
            ty = playerPos.y - transform->position.y;
        velocity->vel = Vec2<float>{ tx,ty }.normal() * EnemySpeed;
    }
};