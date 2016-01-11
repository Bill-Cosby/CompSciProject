#include "building.h"
#include <iostream>
void building::buildStructure()
{
    std::string line;
    std::string constructionLine;
    int height=0,width=0;
    bool typeFound=false;
    bool finishedWithType=false;
    std::ifstream BUILDING_FILE("data/buildings/buildings.raw");

    if (BUILDING_FILE.is_open()){
        while (!BUILDING_FILE.eof()){
            while ( getline(BUILDING_FILE, line)){
                    finishedWithType=false;
                std::string type;
                for (char _c : line){
                    if (_c == '[' or _c == '\t' or _c == ','){
                        continue;
                    }
                    if (_c == ']' and typeFound==false){
                        type=constructionLine;
                        constructionLine.clear();
                        typeFound=true;
                        continue;
                    }
                    if (typeFound==true){
                        if (_c == ']'){
                            if (type == "structure"){
                                name = constructionLine;
                            }
                            if (type=="height"){
                                for (int i=0;i<constructionLine.size();i++){
                                    height+=constructionLine[i]*((i+1))*10;
                                }
                            }if (type=="width"){
                                for (int i=0;i<constructionLine.size();i++){
                                    width+=constructionLine[i]*((i+1)*10);
                                }
                            }
                            typeFound=false;
                            finishedWithType=true;
                            constructionLine.clear();
                        }
                    }
                    if (finishedWithType==true){break;}
                    constructionLine+=_c;
                }
            }
        }
    }
    std::cout << name << ": " << height << "," << width;

}
