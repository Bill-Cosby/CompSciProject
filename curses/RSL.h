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


namespace RSL
{
    std::string getStringData(std::string fileName, std::string dataToRecieve);
    std::string GET_FORMATTED_TYPE(std::string* typeToFix);

    int getIntData(std::string fileName, std::string dataToRecieve);

    std::vector<int> getBuildingData(std::string fileName, std::string dataToRecieve);
    std::vector<std::string> getSpecies(std::string fileName, std::string dataToRecieve);
    std::vector<std::string> unloadColors(std::string fileName, std::string dataToRecieve);

    sf::Texture getTextureData(std::string fileName, std::string dataToRecieve);

    bodyPart* getBodyData(std::string fileName, std::string dataToRecieve, int &weight, sf::Color color);
    //MENU FUNCTIONS
}


#endif // RSL_H_INCLUDED
