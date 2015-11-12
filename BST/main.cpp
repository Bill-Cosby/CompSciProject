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

int main()
{
    srand(time(NULL));
    std::default_random_engine generator(rand()%12349);
    std::uniform_int_distribution<int> distribution(1,100);
    vector<BST<int> > nodeLibrary;
    for (int i=0;i<distribution(generator);i++)
    {
        nodeLibrary.push_back(BST<int>(distribution(generator)));
        std::cout << nodeLibrary[i].value << std::endl;
    }
    std::cout << "=====================================\n";
    BST<int> baseNode(nodeLibrary[0]);
    for (int i=1;i<nodeLibrary.size();i++)
    {
        baseNode.add(&nodeLibrary[i]);
    }
    for (int i=0;i<nodeLibrary.size();i++)
    {
        baseNode.give();
    }
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
    if (Left==NULL)
    {
        std::cout << item << std::endl;
        if (Right!=NULL){
            if(Parent){
                Parent->Left=Right;
            }
            else{
                std::cout << "here";
            }
        }
        else {
            if(Parent){
                Parent->Left=NULL;
            }
            else{
                std::cout << "here";
            }
        }
    }
    if (Left!=NULL)
    {
        Left->give();
    }
    return item;
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
