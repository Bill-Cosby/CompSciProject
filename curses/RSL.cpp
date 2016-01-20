#include "RSL.h"

namespace RSL
{
int getData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype;
    bool foundDataMember;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet);
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet);

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t'){
                        continue;
                    }
                    if (foundDataMember==false){
                        LINE_READING+=_c;
                        if (_c == ']'){
                            if (LINE_READING == dataType){
                                foundDatatype = true;
                            }
                            if (foundDatatype == true){
                                std::cout << LINE_READING << std::endl;
                                if (LINE_READING ==  dataMember){
                                    foundDataMember = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

std::string GET_FORMATTED_TYPE(std::string *typeToFix)
{
    std::string tempStorage;
    std::string dataType;
    dataType+="[";
    for (char _c : *typeToFix){
        if (_c!='.'){
            tempStorage+=toupper(_c);
        }
        else if (_c == '.' or _c == ']'){
            break;
        }
    }
    typeToFix->erase(0,tempStorage.size()+1);
    return dataType + tempStorage + ']';
}

}
