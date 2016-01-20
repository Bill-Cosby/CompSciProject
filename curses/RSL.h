#ifndef RSL_H_INCLUDED
#define RSL_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>

namespace RSL
{
    int getData(std::string fileName, std::string dataToRecieve);
    std::string GET_FORMATTED_TYPE(std::string* typeToFix);
}

#endif // RSL_H_INCLUDED
