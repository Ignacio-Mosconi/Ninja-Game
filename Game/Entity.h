#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Definitions.h"
using namespace std;
using namespace sf;

class Entity
{
protected:
	Texture _texture;
	Sprite _sprite;

public:
	Entity(int x, int y, const string& imagePath);
	inline Sprite getSprite() { return _sprite; }
};

#endif