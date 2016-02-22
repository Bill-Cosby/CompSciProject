#include "building.h"
#include <iostream>
void building::buildStructure(std::string building)
{
    std::string line;
    std::string constructionLine;
    std::string buildingName;
    int yCounter=0,xCounter=0;
    height=0,width=0;
    bool typeFound=false;
    bool finishedWithType=false;
    bool constructionBool = false;
    bool buildingFound = false;
    std::ifstream BUILDING_FILE("data/buildings/buildings.raw");

    if (BUILDING_FILE.is_open()){
        while (!BUILDING_FILE.eof()){
            while ( getline(BUILDING_FILE, line)){
                    finishedWithType=false;
                std::string type;
                for (char _c : line){
                    if (_c == ']' and typeFound==false){
                        type=constructionLine;
                        constructionLine.clear();
                        typeFound=true;
                        continue;
                    }
                    else if (_c == '[' or _c == '\t' or _c == ','){
                        continue;
                    }
                    if (typeFound==true){
                        if (_c == ']'){
                            if (type == building){
                                buildingName = constructionLine;
                                buildingFound = true;
                            }
                            if (type=="[HEIGHT]" and buildingFound == true){
                                for (int i=constructionLine.size()-1;i>=0;i--){
                                    height+=(constructionLine[i]-'0')*(pow(10,(constructionLine.size()-1)-i));
                                }
                                structure.resize(height);
                            }if (type=="[WIDTH]" and buildingFound == true){
                                for (int i=constructionLine.size()-1;i>=0;i--){
                                    width+=(constructionLine[i]-'0')*(pow(10,(constructionLine.size()-1)-i));
                                }
                                for (int i=0;i<width;i++){
                                    structure[i].resize(width);
                                }
                                constructionBool=true;
                            }
                            typeFound=false;
                            finishedWithType=true;
                            constructionLine.clear();
                        }
                    }
                    if (constructionBool==true and _c!=']'){

//                        if (_c == '0')
//                        {
//                            structure[yCounter][xCounter] = new tile('=',0,wood);
//                        }
//
//                        else if (_c == '1')
//                        {
//                            structure[yCounter][xCounter] = new tile('#',-1,wood);
//                        }
//
//                        else if (_c == '2')
//                        {
//                            structure[yCounter][xCounter] = new door(false,wood);
//                        }
                        xCounter++;
                        if (xCounter==width){
                            yCounter++;
                            xCounter=0;
                            if (yCounter==height){
                                return;
                            }
                        }
                    }
                    if (finishedWithType==true){break;}
                    constructionLine+=_c;
                }
            }
        }
    }

}
