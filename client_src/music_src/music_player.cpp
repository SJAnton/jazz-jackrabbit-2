#include "music_player.h"

#define EXITCODE 1
#define CHUNKSIZE 2048
#define MUSIC_LOOPS -1 // -1 = infinito
#define EFFECTS_LOOPS 0
#define EFFECTS_CHANNEL -1

#define CURRENT_FOLDER_LENGTH 6 // "_build"
#define MUSIC_FOLDER "music_src/Music"

#define MENU_MUSIC_PATH "/TitleScreen.mp3"
#define SELECTION_MUSIC_PATH "/Selection.mp3"

namespace fs = std::filesystem;

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
    if (!fs::exists(path)) {
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

void MusicPlayer::play_random_music() {
    std::vector<std::string> music_path;

    std::string path = fs::current_path();

    path.erase(path.length() - CURRENT_FOLDER_LENGTH);
    path += MUSIC_FOLDER;

    for (auto &dir : std::filesystem::directory_iterator(path)) {
        std::string dir_str = dir.path();
        if (dir_str == path + MENU_MUSIC_PATH || dir_str == path + SELECTION_MUSIC_PATH) {
            continue;
        }
        music_path.push_back(dir_str);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, music_path.size() - 1);
    play_music(music_path[distrib(gen)]);
}

void MusicPlayer::stop() {
    Mix_HaltMusic();
}
