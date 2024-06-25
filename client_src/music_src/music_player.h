#ifndef CLIENT_MUSIC_PLAYER_H_
#define CLIENT_MUSIC_PLAYER_H_

#include <random>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>

class MusicPlayer {
    private:
        Mix_Music *music = nullptr;

        Mix_Chunk *effect = nullptr;

    public:
        MusicPlayer(int volume) :  music(nullptr) {
            initialize(volume);
        };

        ~MusicPlayer() {
            if (music != nullptr) {
                Mix_FreeMusic(music);
            }
            if (effect != nullptr) {
                Mix_FreeChunk(effect);
            }
            Mix_CloseAudio();
            SDL_Quit();
        };

        void initialize(int volume);

        void set_volume(int volume);

        void play_music(std::string path);

        void play_effect(std::string path);

        void play_random_music();

        void stop();
};
#endif
