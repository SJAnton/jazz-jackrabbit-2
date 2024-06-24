#include "music_player.h"

#define EXITCODE 1
#define CHUNKSIZE 2048
#define MUSIC_LOOPS -1 // -1 = infinito
#define EFFECTS_LOOPS 0
#define EFFECTS_CHANNEL -1

void MusicPlayer::initialize(int volume) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("Failed to initialize SDL_mixer");
    } else if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE) < 0
    ) {
        throw std::runtime_error("Failed to initialize audio");
    }
    Mix_VolumeMusic(volume);
}

void MusicPlayer::set_volume(int v) {
    Mix_VolumeMusic(v);
}

void MusicPlayer::play_music(std::string path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Music file does not exist");
    } else if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    music = Mix_LoadMUS(path.c_str());

    if (music == nullptr) {
        throw std::runtime_error("Failed to load music");
    } else if (Mix_PlayMusic(music, MUSIC_LOOPS) < 0) {
        throw std::runtime_error("Failed to play music");
    }
}

void MusicPlayer::play_effect(std::string path) {
    effect = Mix_LoadWAV(path.c_str());
    if (effect == nullptr) {
        throw std::runtime_error("Failed to load sound effect");
    } else if (Mix_PlayChannel(EFFECTS_CHANNEL, effect, EFFECTS_LOOPS) < 0) {
        Mix_FreeChunk(effect);
        throw std::runtime_error("Failed to play sound effect");
    }
}

void MusicPlayer::stop() {
    Mix_HaltMusic();
}
