#ifndef CLIENT_MUSIC_PLAYER_H_
#define CLIENT_MUSIC_PLAYER_H_

#include <string>
#include <stdexcept>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>

class MusicPlayer {
    private:
        Mix_Music *music;

    public:
        MusicPlayer(int volume) :  music(nullptr) {
            initialize(volume);
        };

        ~MusicPlayer() {
            if (music != nullptr) {
                Mix_FreeMusic(music);
            }
            Mix_CloseAudio();
            SDL_Quit();
        };

        void initialize(int volume);

        void set_volume(int volume);

        void play(std::string path);

        void stop();
};
#endif
