#include "Camera.h"
#include<bits/stdc++.h>

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt) {
    if (m_Target != nullptr) {
        int MAP_WIDTH = 1920, MAP_HEIGHT = 640;
        SDL_Rect mapBounds = { 0, 0, MAP_WIDTH, MAP_HEIGHT };

        int visibleX = max(mapBounds.x, min(static_cast<int>(m_Target->X) - SCREEN_WIDTH / 2, mapBounds.x + mapBounds.w - SCREEN_WIDTH));
        int visibleY = max(mapBounds.y, min(static_cast<int>(m_Target->Y) - SCREEN_HEIGHT / 2, mapBounds.y + mapBounds.h - SCREEN_HEIGHT));

        m_ViewBox.x = visibleX;
        m_ViewBox.y = visibleY;
        m_ViewBox.w = SCREEN_WIDTH;
        m_ViewBox.h = SCREEN_HEIGHT;

        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}
