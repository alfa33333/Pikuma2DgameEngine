#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>


Game::Game() {
    isRunning = false;
    registry = std::make_unique<Registry>();
    assetStore =std::make_unique<AssetStore>();
    Logger::Log("Game constructor called");
}

Game::~Game() {
    Logger::Log("Game destructor called");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        Logger::Err("Error initializing SDL.");
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS    
    );
    if (!window){
        Logger::Err("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(window,-1, 0);
    if (!renderer) {
        Logger::Err("Error creating SDL renderer");
    }

    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::Run() {
    Setup();
    while(isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
            break;
        }
    }
}

void Game::LoadLevel(int level){
   //Add the systems that ned to be processed in our game
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();

    //adding assets to the asset store
    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");

    //TODO:
    //Load the tilemap
    //We need to load the tile map texture from ./asssets/tilemaps/jungle.png
    assetStore->AddTexture(renderer, "jungle-tilemap", "./assets/tilemaps/jungle.png");
    //We need to load the file ./assets/tilemaps/jungle.map
    // TIP: You can use the idea of the source rectangle
    //Tip: consider creating one entity per tile

    // Create some entities
    Entity tank = registry->CreateEntity();
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0,1.0), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0,0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32);

    Entity truck = registry->CreateEntity();
    truck.AddComponent<TransformComponent>(glm::vec2(50.0, 100.0), glm::vec2(1.0,1.0), 0.0);
    truck.AddComponent<RigidBodyComponent>(glm::vec2(0.0,50.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32);

    Entity tilemap = registry->CreateEntity();
    tilemap.AddComponent<TransformComponent>(glm::vec2(0.0, 0.0), glm::vec2(1.0,1.0), 0.0);
    tilemap.AddComponent<SpriteComponent>("jungle-tilemap", 32, 32, 0, 0);
}


void Game::Setup() {
    LoadLevel(1);
}

void Game::Update() {
    //while (!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME));
    int timeTowait =  MILLISECS_PER_FRAME - (SDL_GetTicks()-millisecsPreviousFrame);    
    if (timeTowait > 0 &&  timeTowait <= MILLISECS_PER_FRAME){
        SDL_Delay(timeTowait);
    }

    //The differences in ticks since the last frame converted to seconds.
    double deltaTime = (SDL_GetTicks()- millisecsPreviousFrame)/1000.0;

    
    millisecsPreviousFrame = SDL_GetTicks();

    registry->Update();
    //Ask all the system to update
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    //TODO:
    // CollisionSystem.Update();
    // DamageSystem.Update();

    //Update the registry to process the entitis that are waiting to be created/deleted

    

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);
    //TODO:
    // //Draw a PNG texture
    // SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);

    // //What is the destination 
    // SDL_Rect dstRect = {
    //     static_cast<int>(playerPosition.x), 
    //     static_cast<int>(playerPosition.y), 
    //     32, 
    //     32
    //     };

    // SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    // SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}