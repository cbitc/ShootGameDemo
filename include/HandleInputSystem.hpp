#pragma once

#include"PublicHeader.hpp"

struct HandleInputSystem final
{
    static void update(ECS::Registry registry) {
        SDL_Event event;
        MouseInput* input = registry.getResource<MouseInput>();
        assertm("MouseInput null",input);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                input->press();
                input->setPosition({ event.motion.x,event.motion.y });
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                input->up();
                input->setPosition({ event.motion.x,event.motion.y });
            } else if (event.type == SDL_MOUSEMOTION) {
                input->move();
                input->setPosition({ event.motion.x,event.motion.y });
            }
        }
    }
};