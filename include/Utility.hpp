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


    static Vec2<int> getWindowSize(ECS::Registry registry) {
        return Vec2<int>{width,height};
    }


    static bool hasOutofRange(ECS::Registry registry,const Vec2<float> position) {
        static constexpr float delta = 50.f;
        const Vec2<int> windowSize = getWindowSize(registry);
        return position.x<-delta || position.x>windowSize.x + delta ||
               position.y<-delta || position.y> windowSize.y + delta;
    }
};