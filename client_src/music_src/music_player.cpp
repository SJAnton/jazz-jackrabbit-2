#include "music_player.h"

#define LOOPS -1 // -1 = infinito
#define EXITCODE 1
#define CHUNKSIZE 2048

void MusicPlayer::initialize(int volume) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("Failed to initialize SDL_mixer");
        exit(EXITCODE);
    } else if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE) < 0
    ) {
        throw std::runtime_error("Failed to initialize audio");
        exit(EXITCODE);
    }
    Mix_VolumeMusic(volume);
}

void MusicPlayer::set_volume(int v) {
    Mix_VolumeMusic(v);
}

void MusicPlayer::play(std::string path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Music file does not exist");
    } else if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    music = Mix_LoadMUS(path.c_str());

    if (music == nullptr) {
        throw std::runtime_error("Failed to load music");
    } else if (Mix_PlayMusic(music, LOOPS) < 0) {
        throw std::runtime_error("Failed to play music");
    }
}

void MusicPlayer::stop() {
    Mix_HaltMusic();
}
