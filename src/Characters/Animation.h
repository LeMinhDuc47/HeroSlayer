#ifndef ANIMATION_H
#define ANIMATION_H
#include <bits/stdc++.h>
#include <SDL.h>
using namespace std;
class Animation
{
public:
	Animation() {};

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps( string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_SpriteRow, m_SpriteFrame;
	int m_AnimSpeed, m_FrameCount;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
};
#endif
