#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Prize.h"

using namespace std;

Prize::Prize() {

}
int Prize::getScoreUpdate(int timeDelay) {
return prizeLevel/timeDelay;

}
string Prize::say() {

}