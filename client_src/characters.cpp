#include <unordered_map>
#include "characters.h"

Characters::Characters(){
	for (const auto& ch : characters) {
    	charMap[ch.symbol] = ch.rect;
	}
}