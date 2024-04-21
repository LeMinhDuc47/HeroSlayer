#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "Animation.h"
#include <bits/stdc++.h>
#include <SDL.h>
using namespace std;
class SpriteAnimation : public Animation
{
    public:
        SpriteAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(string textureID, int spriteRow, int frameCount, int speed);
    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        string m_TextureID;
};

#endif
