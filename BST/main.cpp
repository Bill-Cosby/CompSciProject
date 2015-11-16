#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>
#include <time.h>


using namespace std;
template <class T>

class BST
{
public:

    T value;

    BST* Left;
    BST* Right;

    BST* Parent;
//  constructor
    BST(T item);
//  methods
    void add(BST* item);
    T give();
};

template <class T>
struct baseNode
{
    BST<T>* child;
};

int main()
{
    baseNode<int> mainNode;
    srand(time(NULL));
    std::default_random_engine generator(rand()%12349);
    std::uniform_int_distribution<int> distribution(800,1000);
    std::uniform_int_distribution<int> ewew(1,1000);

    vector<BST<int> > nodeLibrary;
    vector<int> closedValues;

    for (int i=0;i<distribution(generator);i++)
    {
        nodeLibrary.push_back(BST<int>(ewew(generator)));
        std::cout << nodeLibrary[i].value << std::endl;
    }
    std::cout << "=====================================\n";
    mainNode.child=&nodeLibrary[0];
    for (int i=1;i<nodeLibrary.size();i++)
    {
        mainNode.child->add(&nodeLibrary[i]);
    }
    return 0;
    for (int i=0;i<nodeLibrary.size();i++)
    {
        closedValues.push_back(mainNode.child->give());
        if (mainNode.child->Left==NULL and mainNode.child->Right!=NULL)
        {
            closedValues.push_back(mainNode.child->value);
            mainNode.child=mainNode.child->Right;
        }
    }
    for (int i=0;i<closedValues.size();i++)
    {
        std::cout << closedValues[i] << std::endl;
    }
    std::cout << nodeLibrary.size() << ":" << closedValues.size() << std::endl;
}


template <class T>
BST<T>::BST(T item)
{
    value=item;
    Left=NULL;
    Right=NULL;

}

template <class T>
T BST<T>::give()
{
    T item;
    item=value;
    if (Left!=NULL)
    {
        if (Left->Left==NULL)
        {
            item=Left->value;
            if (Left->Right!=NULL){
                Left=Left->Right;
            }
            else{
                Left=NULL;
            }
            return item;
        }
        else{
            Left->give();
        }
    }
    else
    {
        return item;
    }

}

template <class T>
void BST<T>::add(BST* item)
{
    std::cout << item->value << " : ";
    std::cout << value << endl;
    if (item->value<=value)
    {
        if (Left==NULL)
        {
            Left=item;
            Left->Parent=this;
        }
        else
        {
            Left->add(item);
        }
    }
    if (item->value>value)
    {
        if (Right==NULL)
        {
            Right=item;
            Right->Parent=this;
        }
        else
        {
            Right->add(item);
        }
    }
}
