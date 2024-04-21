#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

#include "Engine.h"
#include "Vector2D.h"

class Camera
{
    public:
        void Update(float dt);
         SDL_Rect GetViewBox() { return m_ViewBox; }
         Vector2D GetPosition() { return m_Position; }
         void SetTarget(Point* target) { m_Target = target; }

         static Camera* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
        }

    private:
        Camera()
        {
            m_ViewBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        }

        Point* m_Target;
        Vector2D m_Position;

        SDL_Rect m_ViewBox;
        static Camera* s_Instance;
};

#endif
