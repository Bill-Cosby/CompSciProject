#include "RSL.h"

namespace RSL
{
std::string getData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype = false;
    bool foundDataMember = false;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

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

                    if (foundDataMember == true and _c == ';'){
                        return LINE_READING;
                    }

                    LINE_READING+=_c;

                    if (foundDatatype==false){
                        if (_c == ']'){

                            if (LINE_READING == dataType){
                                foundDatatype = true;
                                LINE_READING.clear();
                            }
                        }
                    }

                    if (foundDatatype==true){
                        if (_c == ']'){

                            if (LINE_READING == dataMember){
                                foundDataMember=true;
                                LINE_READING.clear();
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
