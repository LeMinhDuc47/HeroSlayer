#ifndef ENGINE_H
#define ENGINE_H
#include "GameMap.h"
#include "GameObject.h"
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
using namespace std;
class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

         GameMap* GetMap() {return m_LevelMap;}
         bool IsRunning() { return m_IsRunning; }
         SDL_Renderer* GetRenderer() {return m_Renderer;}

    private:
        Engine() {}
        bool m_IsRunning;

        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;

        vector<GameObject*> m_GameObjects;
};

#endif
