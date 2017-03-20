#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Entity.h"

using namespace std;

class Trap : public Entity {
public:
	Trap();
	int getScoreUpdate(int timeDelay);
	string say();

protected:
	int penaltyLevel;
	sf::Sound trapSound;
};