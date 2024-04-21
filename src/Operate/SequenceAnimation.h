#ifndef SEQUENCEANIMATION_H
#define SEQUENCEANIMATION_H

#include "Animation.h"
#include<bits/stdc++.h>
#include <SDL.h>

struct Sequence
{
    int Speed;
    int FrameCount;
    int Width, Height;
    vector<string> TextureIDs;
};

class SequenceAnimation : public Animation
{
    public:
        SequenceAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Parse(string source);
        void SetCurrentSequence(string seqID);
        void SetRepeat(bool repeat) { m_Repeat = repeat; }
        void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSequence;
        map<string, Sequence> m_SeqMap;
};

#endif
