#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"

struct Utility final
{
    static Vec2<float> queryPlayerPosition(ECS::Registry registry) {
        auto view = registry.view<Player>();
        ECS::Entity hero = view.back();
        Transform* transform = registry.get<Transform>(hero);
        return Vec2<float>{transform->position};
    }
};