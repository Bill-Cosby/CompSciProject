#include "RSL.h"

namespace RSL
{
std::string getStringData(std::string fileName, std::string dataToGet)
{
    std::mt19937 generator(rand()%rand()%1000000);
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool inArray = false;

    std::vector<std::string> colorContainer;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '}'){
                        inArray = false;
                        continue;
                    }

                    if (_c == '{' and foundDataMember == true){
                        inArray = true;
                        continue;
                    }

                    if (inArray == true){
                        if (_c == ':'){
                            colorContainer.push_back(LINE_READING);
                            LINE_READING.clear();
                            continue;
                        }
                    }

                    if (foundDataMember == true and _c == ';'){
                        if (colorContainer.size()!=0){
                            std::uniform_real_distribution<float> distributor(0,(colorContainer.size()));
                            return colorContainer[distributor(generator)];
                        }
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
    return "no";
}

int getIntData(std::string fileName, std::string dataToGet,int positionInArray)
{
    bool foundDatatype = false;
    bool foundDataMember = false;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);

    int whatever = 0;

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){

                    if (_c == '\t'){
                        continue;
                    }
                    if (foundDataMember == true and _c == ':' and whatever == positionInArray){

                        std::stringstream ss;
                        int convertedInt;
                        ss << LINE_READING;
                        ss>>convertedInt;
                        return convertedInt;
                    }
                    if (_c == ':' and foundDataMember == true)whatever++;
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

bodyPart* getBodyData(std::string fileName, std::string dataToGet, int &weight, sf::Color color)
{
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool foundId = false;
    bool foundConnected = false;
    std::vector<bodyPart*> body;
    std::string id;
    std::string connectedTo;

    bool left=false;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT


    std::string line;
    std::ifstream loadFile(fileName);

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (foundDataMember == true){
                        if (_c == ','){
                            std::stringstream ss;
                            ss << LINE_READING;
                            if (foundId == false){
                                id = LINE_READING;
                                foundId = true;
                            }
                            else if(foundConnected == false){
                                connectedTo = LINE_READING;
                                foundConnected = true;
                            }
                            else{
                                ss >> weight;
                                foundId = false;
                                foundConnected = false;
                            }
                            LINE_READING.clear();
                            continue;
                        }
                        else if (_c == 'L'){
                            left = true;
                            continue;
                        }
                        else if(_c == ':'){
                                if (LINE_READING == "head"){body.push_back(new head(dataType,weight,id, connectedTo, color));}
                                else if (LINE_READING =="eye"){body.push_back(new eye(dataType,weight,id, connectedTo, left, color));}
                                else if (LINE_READING == "neck"){body.push_back(new neck(dataType,weight,id, connectedTo, color));}
                                else if (LINE_READING=="torso"){body.push_back(new torso(dataType,weight,id, connectedTo, color));}
                                else if (LINE_READING =="arm"){body.push_back(new arm(dataType,weight, id, connectedTo, left, color));}
                                else if (LINE_READING =="leg"){body.push_back(new leg(dataType,weight, id, connectedTo, left, color));}
                                else if (LINE_READING == "hand"){body.push_back(new hand(dataType,weight,id, connectedTo, left, color));}
                                else if (LINE_READING == "foot"){body.push_back(new foot(dataType,weight,id, connectedTo, left, color));}
                            left = false;
                            LINE_READING.clear();
                            continue;
                        }
                    }
                    if (foundDataMember == true and _c == ';'){
                        for (bodyPart * _b : body){
                            for (bodyPart * _b2 : body){
                                if (_b2 == _b)continue;
                                if (_b->connectedTo == _b2->ID){
                                    _b2->attachedParts.push_back(_b);
                                }
                            }
                        }
                        for (bodyPart * _b : body){
                            if (_b->ID == "00")return _b;
                        }
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

                    if (foundDatatype==true and foundDataMember == false){
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

std::vector<std::string> getSpecies(std::string fileName, std::string dataToGet)
{
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT


    std::string line;
    std::ifstream loadFile(fileName);
    std::vector<std::string> species;

    bool foundSpecies = false;

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (LINE_READING == dataMember){
                        foundSpecies = true;
                        LINE_READING.clear();
                    }
                    if (foundSpecies == true){
                        if (_c == ';'){
                            species.push_back(LINE_READING);
                            foundSpecies = false;
                            break;
                        }
                    }

                    LINE_READING+=_c;
                }
            }
        }
    }
    return species;
}

std::vector<std::string> unloadColors(std::string fileName, std::string dataToGet)
{
    std::string dataType = GET_FORMATTED_TYPE(&dataToGet);
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);
    std::vector<std::string> colors;

    bool foundSpecies = false, foundType = false;

    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }

                    if (LINE_READING == dataType){
                        foundSpecies = true;
                        LINE_READING.clear();
                        continue;
                    }
                    if (foundSpecies == true and foundType == false){
                        if (LINE_READING == dataMember){
                            foundType = true;
                            LINE_READING.clear();
                        }
                    }
                    if (foundType == true){
                        if (_c == ':'){
                            colors.push_back(LINE_READING);
                            LINE_READING.clear();
                            continue;
                        }
                        if (_c == ';'){
                            foundSpecies = false;
                            foundType = false;
                        }
                    }

                    LINE_READING+=_c;
                }
            }
        }
    }
    return colors;
}

sf::Texture getTextureData(std::string fileName, std::string dataToGet)
{
    bool foundDatatype = false;
    bool foundDataMember = false;
    bool foundQuantity = false;
    bool foundTexture = false;
    std::vector<int> intRectangle;

    sf::Texture whatever;


    std::string dataType = GET_FORMATTED_TYPE(&dataToGet); // GET OBJECT NAME (eg: human, goblin)
    std::string dataMember = GET_FORMATTED_TYPE(&dataToGet); // GET MEMBER OF OBJECT

    std::string line;
    std::ifstream loadFile(fileName);
    if ( loadFile.is_open() ){
        while ( !loadFile.eof() ){
            while ( getline( loadFile , line ) ){
                std::string LINE_READING;
                for (char _c : line){

                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (foundDataMember == true){
                        if (_c == ',' and foundTexture == false){
                            fileName = "data/textures/" + LINE_READING;


                            LINE_READING.clear();
                            foundTexture = true;

                            continue;
                        }
                        if (foundTexture == true and _c == ':'){

                            std::stringstream ss;
                            ss << LINE_READING;

                            int temp;
                            ss >> temp;



                            intRectangle.push_back(temp);

                            LINE_READING.clear();
                            continue;
                        }
                    }

                    if (foundDataMember == true and _c == ';'){
                        sf::Texture temp;
                        temp.loadFromFile(fileName,sf::IntRect(intRectangle[1],intRectangle[0],16,16));

                        return temp;
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

                    if (foundDatatype==true and foundDataMember == false){
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

answers getAnswers(std::string fileName, std::string dataToRecieve)
{
    std::string species = GET_FORMATTED_TYPE(&dataToRecieve);
    std::string dataMember = GET_FORMATTED_TYPE(&dataToRecieve);
    std::string dataType = GET_FORMATTED_TYPE(&dataToRecieve);
    std::string stat;
   std::string answer;

    bool foundSpecies = false;
    bool foundDataMember = false;
    bool foundDataType = false;

    std::string line;
    std::ifstream loadFile(fileName);

    if (loadFile.is_open()){
        while (!loadFile.eof()){
            while ( getline (loadFile,line) ){
                std::string LINE_READING;
                for (char _c : line){
                    if (_c == '\t' or _c == '{' or _c == '}'){
                        continue;
                    }
                    if (foundDataType == true){
                        if (_c == ':'){
                            stat = LINE_READING;
                            LINE_READING.clear();
                        }
                        if (_c == ';'){
                            answer = LINE_READING;
                            return answers(answer,stat);
                        }
                    }
                    if (_c != ':')LINE_READING+=_c;


                    if (LINE_READING == species){
                        foundSpecies = true;
                        break;
                    }
                    if (foundSpecies == true and LINE_READING == dataMember){
                        foundDataMember = true;
                        break;
                    }
                    if (foundDataMember == true and LINE_READING == dataType){
                        foundDataType = true;
                        LINE_READING.clear();
                    }

                }
            }
        }
    }
    return answers("no","no");
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
