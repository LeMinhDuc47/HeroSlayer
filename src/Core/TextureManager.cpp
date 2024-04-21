#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include<bits/stdc++.h>
#include "tinyxml.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(string id,string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());

    if ( surface == nullptr )
    {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);

    if ( texture == nullptr )
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;

    return true;
}

bool TextureManager::ParseTextures(string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if( xml.Error() )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load: %s", source.c_str());
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if( e->Value() == string("texture") )
        {
            string id = e->Attribute("id");
            string src = e->Attribute("source");
            Load(id, src);
        }
    }

    return true;
}

void TextureManager::Draw(string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;
    float w = width * scaleX;
    float h = height * scaleY;
    SDL_Rect dstRect = { x - (int)(cam.X), y - (int)(cam.Y), (int)w, (int)h };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { width * frame, height * row, width, height };
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = { x - (int)(cam.X), y - (int)(cam.Y), width, height };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = { x - (int)(cam.X), y - (int)(cam.Y), tileSize, tileSize };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}


void TextureManager::Drop(string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    map<string, SDL_Texture*>::iterator it;

    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }

    m_TextureMap.clear();

    SDL_Log("Texture map cleaned!");
}
