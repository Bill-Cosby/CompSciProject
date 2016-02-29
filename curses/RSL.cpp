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
}

int getIntData(std::string fileName, std::string dataToGet)
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
                        std::stringstream ss;
                        int convertedInt;
                        ss << LINE_READING;
                        ss>>convertedInt;
                        return convertedInt;
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

    std::cout << dataType << std::endl;

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
                                std::cout << LINE_READING << std::endl;
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
    std::cout << dataType << "." << dataMember << std::endl;
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

std::vector<menu_button> getButtons(std::string fileName)
    {
        bool startButtonList = false;
        bool buttonName = false;
        bool foundButton = false;
        bool x = false,y=false;
        std::vector<menu_button> buttons;

        menu_button temp;

        std::string line;
        std::ifstream loadFile(fileName);

        if ( loadFile.is_open()){
            while ( !loadFile.eof() ){
                while ( getline( loadFile,line ) ){
                    std::string LINE_READING;

                    for (char _c : line){
                        if (_c == '\t')continue;
                        if (_c == ':'){
                            buttonName = true;
                            continue;
                        }
                        if (LINE_READING == "[STARTBUTTONS]"){
                            LINE_READING.clear();
                            startButtonList = true;
                            continue;
                        }
                        else if (LINE_READING == "[ENDBUTTONS]"){
                            LINE_READING.clear();
                            return buttons;
                        }
                        else if (LINE_READING == "[BUTTON]"){
                            LINE_READING.clear();
                            continue;
                        }

                        if (startButtonList == true){
                            if (buttonName == true){
                                temp.name = LINE_READING;
                                buttonName = false;
                                LINE_READING.clear();
                            }
                            else if (x==false){
                                if (_c == ','){
                                    std::stringstream ss;
                                    ss << LINE_READING;
                                    ss>>temp.x;
                                    LINE_READING.clear();
                                    x = true;
                                    continue;
                                }
                            }
                            else if (y == false){
                                if (_c == ';'){
                                    std::stringstream ss;
                                    ss << LINE_READING;
                                    ss>>temp.y;
                                    LINE_READING.clear();
                                    y = true;
                                    break;
                                }
                            }
                            if (buttonName == false and x == true and y == true){
                                x = false;
                                y = false;
                                buttons.push_back(temp);
                            }
                        }
                        if (_c == ';'){
                            LINE_READING.clear();
                            break;
                        }
                        LINE_READING+=_c;
                    }
                    if (y == true)break;
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
