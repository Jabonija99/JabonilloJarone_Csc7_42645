
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Entity.h"

using namespace std;


class Prize: public Entity {
public:
Prize();
int getScoreUpdate(int timeDelay);
string say();

protected:
int prizeLevel;
sf::Sound prizeSound;
};