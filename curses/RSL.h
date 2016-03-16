#ifndef RSL_H_INCLUDED
#define RSL_H_INCLUDED

#include "bodyParts.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <random>

class answers
{
public:
    std::string answer;
    std::string stat;
    answers(std::string _q, std::string _s){ answer= _q; stat = _s;}
};


namespace RSL
{
    std::string getStringData(std::string fileName, std::string dataToRecieve);
    std::string GET_FORMATTED_TYPE(std::string* typeToFix);

    int getIntData(std::string fileName, std::string dataToRecieve, int positionInArray);

    std::vector<int> getBuildingData(std::string fileName, std::string dataToRecieve);
    std::vector<std::string> getSpecies(std::string fileName, std::string dataToRecieve);
    std::vector<std::string> unloadColors(std::string fileName, std::string dataToRecieve);

    sf::Texture getTextureData(std::string fileName, std::string dataToRecieve);

    bodyPart* getBodyData(std::string fileName, std::string dataToRecieve, int &weight, sf::Color color);
    answers getAnswers(std::string fileName, std::string dataToRecieve);
    //MENU FUNCTIONS
}


#endif // RSL_H_INCLUDED
