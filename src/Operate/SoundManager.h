#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include<bits/stdc++.h>
using namespace std;
class SoundManager {
public:
    SoundManager();

    static SoundManager* GetInstance() {
        if (s_Instance != nullptr)
            return s_Instance;
        else
            return s_Instance = new SoundManager();
    }
    void loadSound(const char* filePath, const char* soundName);
    void playSound(const char* soundName);
    void playMusic();
    void setVolume(int volume);
    void UpdateSound();
    void Load();
    void clean();
private:
    static SoundManager* s_Instance;
    map<string, Mix_Chunk*> soundEffects{
        {"run", nullptr},
        {"attack", nullptr},
        {"kamehame", nullptr},
        {"skill", nullptr }

    };
    Mix_Music* music;
};

#endif // SOUNDMANAGER_H
