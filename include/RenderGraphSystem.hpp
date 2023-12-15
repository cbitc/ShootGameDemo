#pragma once

#include"PublicHeader.hpp"

struct RenderGraphSystem final
{

    static void update(ECS::Registry registry,SDL_Renderer* renderer,GraphContainer* graphs) {
        auto view = registry.view<GraphInfo,Transform>();
        for (ECS::Entity entity : view) {
            auto [graphInfo,transform] = registry.get<GraphInfo,Transform>(entity);
            Graph* graph = graphs->get(graphInfo->type);
            assertm("graph is nullptr",graph);
            RenderGraphSearch(renderer,*graph,graphInfo->rgba,transform);
        }
    }

private:
    static void RenderGrpahDraw(SDL_Renderer* renderer,const RGBA& rgba,
        Vec2<float> p1,Vec2<float>p2,Transform* transform) {
        const float dx = transform->position.x,dy = transform->position.y;
        const float scalx = transform->scale.x,scaly = transform->scale.y;
        const float rotation = transform->angle;

        float x1 = p1.x * scalx + dx,
            y1 = p1.y * scaly + dy;

        float x2 = p2.x * scalx + dx,
            y2 = p2.y * scaly + dy;

        SDL_SetRenderDrawColor(renderer,rgba.r,rgba.g,rgba.b,rgba.a);
        SDL_RenderDrawLineF(renderer,x1,y1,x2,y2);
    }


    
    static void RenderGraphSearch(SDL_Renderer* renderer,const Graph& graph,
        const RGBA& rgba,Transform* transform) {
        std::vector<std::vector<int>> vis = graph.neibs;
        for (int i = 0;i < vis.size();i++) {
            for (int j = 0;j < vis[0].size();j++) {
                if (vis[i][j]) {
                    RenderGrpahDraw(renderer,rgba,graph.vertexs[i],graph.vertexs[j],transform);
                    vis[i][j] = vis[j][i] = 0;
                }
            }
        }
    }
    
};