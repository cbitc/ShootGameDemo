#pragma once 

#include"PublicHeader.hpp"
#include<cmath>

struct RenderTextureSystem final
{
    static void update(ECS::Registry registry,SDL_Renderer* renderer) {
        auto view = registry.view<Texture>();
        for (ECS::Entity entity : view) {
            auto [texture,transform] = registry.get<Texture,Transform>(entity);
            RenderTexture(renderer,texture->texture,texture->width,texture->height,transform->position.x,transform->position.y,transform->scale.x,transform->scale.y,transform->rotation,texture->rgba);
        }
    }
private:
    static void RenderTexture(SDL_Renderer* renderer,SDL_Texture* texture,
        int width,int height,float x,float y,float scalex,float scaley,
        float rotation,const RGBA& rgba) {

        SDL_FRect rect{ .x = x,.y = y,.w = width * scalex,.h = height * scaley };
        SDL_SetTextureColorMod(texture,rgba.r,rgba.g,rgba.b);
        SDL_SetTextureAlphaMod(texture,rgba.a);
        SDL_RenderCopyExF(renderer,texture,nullptr,
        &rect,ROTTOANG(rotation),nullptr,SDL_FLIP_NONE);
        
    }
};