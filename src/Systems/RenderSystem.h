#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL2/SDL.h>

class RenderSystem: public System {
    public:
        RenderSystem() {
            RequiredComponent<TransformComponent>();
            RequiredComponent<SpriteComponent>();
        }

        void Update(SDL_Renderer* renderer) {
            
             for (auto entity: GetSystemEntities()){
                 // Update entity based on its velocity.
                 
                 const auto transform = entity.GetComponent<TransformComponent>();
                 const auto sprite = entity.GetComponent<SpriteComponent>();

                SDL_Rect objRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    sprite.width,
                    sprite.height
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &objRect);
                //  Logger::Log(
                //     "Entity id = " + 
                //     std::to_string(entity.Getid()) + 
                //     " position is now (" + 
                //     std::to_string(transform.position.x) + 
                //     "," + 
                //     std::to_string(transform.position.y) + 
                //     ")");

             }
            
        }
};

#endif