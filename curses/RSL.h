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
#include "materials.h"


namespace RSL
{
    std::string getStringData(std::string fileName, std::string dataToRecieve);
    int getIntData(std::string fileName, std::string dataToRecieve);
    std::vector<int> getBuildingData(std::string fileName, std::string dataToRecieve);
    std::vector<material> unloadMaterials(std::string fileName);
    sf::Texture getTextureData(std::string fileName, std::string dataToRecieve);
    std::string GET_FORMATTED_TYPE(std::string* typeToFix);
    bodyPart* getBodyData(std::string fileName, std::string dataToRecieve, int &weight, sf::Color color);
}


#endif // RSL_H_INCLUDED
