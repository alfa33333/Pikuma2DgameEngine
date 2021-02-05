#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

class RenderSystem: public System {
    public:
        RenderSystem() {
            RequiredComponent<TransformComponent>();
            RequiredComponent<SpriteComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
            
             for (auto entity: GetSystemEntities()){
                 // Update entity based on its velocity.
                 
                 const auto transform = entity.GetComponent<TransformComponent>();
                 const auto sprite = entity.GetComponent<SpriteComponent>();

                 //Set the source rectangle of our original sprite texture
                SDL_Rect srcRect = sprite.srcRect;

                // set the destination rectangle with the x, y position to be renderer
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };


                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(sprite.assetId),
                    &srcRect,
                    &dstRect,
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                 );
                // SDL_Rect objRect = {
                //     static_cast<int>(transform.position.x),
                //     static_cast<int>(transform.position.y),
                //     sprite.width,
                //     sprite.height
                // };
                // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                // SDL_RenderFillRect(renderer, &objRect);


             }
            
        }
};

#endif