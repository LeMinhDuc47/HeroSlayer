#include "Engine.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include"TextureManager.h"
#include"Input.h"
#include<Vector2D.h>
#include<Warrior.h>
#include"Timer.h"
#include"MapParser.h"
#include"GameMap.h"
using namespace std;
Engine* Engine::s_Instance = nullptr;
Warrior* player=nullptr;
bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }
    if(MapParser::GetInstance()->Load()){
        cout <<"Failed to load map"<<endl;
    }
    m_LevelMap=MapParser::GetInstance()->GetMap("MAP");
    TextureManager::GetInstance()->Load("player","assets/attack .png");
     TextureManager::GetInstance()->Load("player_run","assets/Run.png");
    player= new Warrior(new Properties("player", 100, 200,97, 90 ));
    Transform tf;
    tf.Log();
   return m_IsRunning = true;
}

void Engine::Update() {
float dt = Timer::GetInstance()->GetDeltaTime();
m_LevelMap->Update();
player->Update(dt);

}



void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218,254, 255);
    SDL_RenderClear(m_Renderer);
    m_LevelMap->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {

    Input::GetInstance()->Listen();
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit() {
    m_IsRunning = false;
}


