#include "RSL.h"

namespace RSL
{
int getData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype;
    bool foundDataMember;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet);
    std::string dataMember;
    std::cout << dataToGet;

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;

            }
        }
    }
}

std::string GET_FORMATTED_TYPE(std::string *typeToFix)
{
    std::string dataType;
    dataType+="[";
    for (char _c : *typeToFix){
        if (_c!='.'){
            dataType+=toupper(_c);
        }
        else{
            dataType+=']';
            return dataType;
        }

    }
}

}
