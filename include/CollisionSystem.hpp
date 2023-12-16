#pragma once

#include"PublicHeader.hpp"
#include"Common.hpp"


struct CollisionSystem final
{
    static void update(ECS::Registry registry,CollisionGroup* collsionGroup) {
        auto view = registry.view<CollisionBox>();
        for (ECS::Entity e1 : view) {
            auto [box1,tsm1] = registry.get<CollisionBox,Transform>(e1);
            for (int i = 0;i < 8;i++) {
                if ((box1->mask & (1 << i)) == 0)continue;
                const auto& group = collsionGroup->getGroup(i);
                for (ECS::Entity e2 : group) {
                    auto [box2,tsm2] = registry.get<CollisionBox,Transform>(e2);
                    SDL_FRect rect1{
                    .x = box1->box.x + tsm1->position.x,
                    .y = box1->box.y + tsm1->position.y,
                    .w = box1->box.w,.h = box1->box.h };

                    SDL_FRect rect2{
                    .x = box2->box.x + tsm2->position.x,
                    .y = box2->box.y + tsm2->position.y,
                    .w = box2->box.w,.h = box2->box.h };

                    if (SDL_HasIntersectionF(&rect1,&rect2)) {
                        BeCollision* col1 = registry.get_or_emplace<BeCollision>(e1);
                        col1->collisors.push_back(e2);
                    }
                }
            }

        }
    }
};