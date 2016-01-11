#include "building.h"
#include <iostream>
void building::buildStructure()
{
    std::string line;
    std::string constructionLine;
    int height=0,width=0, yCounter=0,xCounter=0;
    bool typeFound=false;
    bool finishedWithType=false;
    bool constructionBool = false;
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
                            if (type == "structure"){
                                name = constructionLine;
                            }
                            if (type=="height"){
                                for (int i=constructionLine.size()-1;i>=0;i--){
                                    height+=(constructionLine[i]-'0')*(pow(10,(constructionLine.size()-1)-i));
                                }
                                structure.resize(height);
                            }if (type=="width"){
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
                        structure[yCounter][xCounter]=_c-'0';
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
