
#include "bodyParts.h"

void hand::equip(item* itemToGrasp, bool equipping)
{
    if (inHand==NULL){
        inHand = itemToGrasp;
    }
    else {
        if (inHand == itemToGrasp){
            inHand=NULL;
        }
        else{
            inHand == itemToGrasp;
        }
    }
}
