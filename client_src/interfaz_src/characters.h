#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <unordered_map>
#include <SDL.h>

#define SIZE_CHARACTER 64
struct Character {
    char symbol;
    SDL_Rect rect;
};

class Characters{
	public:
		Characters();
		Character characters[46] = {
		    {'-', {0, 0, 64, 64}},
		    {'.', {64, 0, 64, 64}},
		    {'!', {128, 0, 64, 64}},
		    {'0', {192, 0, 64, 64}},
		    {'1', {256, 0, 64, 64}},
		    {'2', {320, 0, 64, 64}},
		    {'3', {384, 0, 64, 64}},
		    {'4', {448, 0, 64, 64}},
		    {'5', {512, 0, 64, 64}},
		    {'6', {576, 0, 64, 64}},
		    {'7', {640, 0, 64, 64}},
		    {'8', {704, 0, 64, 64}},
		    {'9', {768, 0, 64, 64}},
		    {':', {0, 64, 64, 64}},
		    {';', {64, 64, 64, 64}},
		    {'"', {128, 64, 64, 64}},
		    {'=', {192, 64, 64, 64}},
		    {'$', {256, 64, 64, 64}},
		    {'?', {320, 64, 64, 64}},
		    {'A', {384, 64, 64, 64}},
		    {'B', {448, 64, 64, 64}},
		    {'C', {512, 64, 64, 64}},
		    {'D', {576, 64, 64, 64}},
		    {'E', {640, 64, 64, 64}},
		    {'F', {704, 64, 64, 64}},
		    {'G', {768, 64, 64, 64}},
		    {'H', {0, 128, 64, 64}},
		    {'I', {64, 128, 64, 64}},
		    {'J', {128, 128, 64, 64}},
		    {'K', {192, 128, 64, 64}},
		    {'L', {256, 128, 64, 64}},
		    {'M', {320, 128, 64, 64}},
		    {'N', {384, 128, 64, 64}},
		    {'O', {448, 128, 64, 64}},
		    {'P', {512, 128, 64, 64}},
		    {'Q', {576, 128, 64, 64}},
		    {'R', {640, 128, 64, 64}},
		    {'S', {704, 128, 64, 64}},
		    {'T', {768, 128, 64, 64}},
		    {'U', {0, 192, 64, 64}},
		    {'V', {64, 192, 64, 64}},
		    {'W', {128, 192, 64, 64}},
		    {'X', {192, 192, 64, 64}},
		    {'Y', {256, 192, 64, 64}},
		    {'Z', {320, 192, 64, 64}},
		    {' ', {384, 192, 64, 64}}
		};
		std::unordered_map<char, SDL_Rect> charMap;
};


#endif