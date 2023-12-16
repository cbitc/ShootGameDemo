#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"


struct BulletControlSystem final
{
    static void update(ECS::Registry registry) {
        auto view = registry.view<Bullet>();
        for (ECS::Entity entity : view) {
            hanleOutSide(registry,entity);
            handleCollision(registry,entity);
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


    static void hanleOutSide(ECS::Registry registry,ECS::Entity entity) {
        Transform* transform = registry.get<Transform>(entity);
        if (Utility::hasOutofRange(registry,transform->position)) {
            registry.get_or_emplace<BeDestroySign>(entity)->twice++;
        }
    }
};