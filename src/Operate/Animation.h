#ifndef ANIMATION_H
#define ANIMATION_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include"Engine.h"
using namespace std;
class Animation
{
	public:
		Animation() {};

		void Update();
		void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void SetProps(string textureID, int spriteRow, int frameCount, int speed);
		void Reset();
		int GetCurrentFrame() { return m_CurrentFrame; }
		void DrawKame(float x, float y, int spriteWidth, int spriteHeight, int currentframe, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		int m_Speed;
		int m_SpriteRow;
		int m_FrameCount;
		int m_CurrentFrame;
		string m_TextureID;

};

#endif
