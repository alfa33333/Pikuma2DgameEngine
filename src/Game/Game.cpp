#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>


Game::Game() {
    isRunning = false;
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



void Game::Setup() {
    //TODO:
    // Entity tank = registry.CreateEntity();
    // tank.AddComponent<TransformComponent>();
    // tank.AddComponent<BoxColliderComponent>();
    // tank.AddComponent<SpriteComponent>("./assets/images/tank.png");
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

    //TODO:
    // MovementSystem.Update();
    // CollisionSystem.Update();
    // DamageSystem.Update();
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

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