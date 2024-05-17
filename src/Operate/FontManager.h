#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include<bits/stdc++.h>
using namespace std;
class FontManager {
public:
    FontManager(const string& fontPath, int fontSize);
    ~FontManager();

    bool loadFont();
    void closeFont();
    bool isFontLoaded() const;
    SDL_Texture* renderText(const string& text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
    TTF_Font* getFont() const {
        return m_font;
    }
private:
    string m_fontPath;
    int m_fontSize;
    TTF_Font* m_font = nullptr;
};

#endif
