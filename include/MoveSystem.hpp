#pragma once

#include"PublicHeader.hpp"


struct MoveSystem final
{
    static void update(ECS::Registry registry) {
        auto view = registry.view<Velocity,Transform>();
        for (ECS::Entity entity : view) {
            auto [velocity,transform] = registry.get<Velocity,Transform>(entity);
            transform->position += velocity->vel;
        }
    }
};