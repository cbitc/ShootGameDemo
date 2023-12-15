#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"

struct MoveSystem final
{
    static void update(ECS::Registry registry) {
        auto view = registry.view<Velocity>();
        for (ECS::Entity entity : view) {
            auto [vel,tam] = registry.get<Velocity,Transform>(entity);
            tam->position += vel->vel;
        }
    }
};