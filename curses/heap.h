#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <vector>
#include <iostream>

template <class T>
class heap
{
public:
    std::vector<T> items;

    int currentItemCount;

    T Add(T item)
    {
        currentItemCount++;
        item.HeapIndex = currentItemCount;
        items.push_back(item);
        SortUp(item);
        return item;
    }

    T RemoveFirst()
    {
        T firstItem = items[0];
        currentItemCount--;
        items[0]=items[currentItemCount];
        items[0].HeapIndex = 0;
        SortDown(items[0]);
        return firstItem;
    }

    int Count()
    {
        return currentItemCount;
    };

    bool Contains(T item)
    {
        for (T _i : items)
        {
            if (_i == item)
            {
                return true;
            }
        }
    }

    void SortDown(T item){
        while (true)
        {
            int childIndexLeft = item.HeapIndex * 2 +1;
            int childIndexRight= item.HeapIndex * 2 +2;
            int swapIndex = 0;

            if (childIndexLeft < currentItemCount)
            {
                swapIndex = childIndexLeft;
                if (childIndexRight < currentItemCount)
                {
                    if (childIndexLeft-childIndexRight<0)
                    {
                        swapIndex = childIndexRight;
                    }
                }
            }

            if (item.HeapIndex-swapIndex<0)
            {
                Swap(item,items[swapIndex]);
            }
            else{return;}
        }
    }

    void SortUp(T item)
    {
        int parentIndex = (item.HeapIndex-1)/2;

        while (true){
            T parentItem = items[parentIndex];
            if (item.HeapIndex+1-parentItem.HeapIndex+1>0)
            {
                Swap(item,parentItem);
            }
            else
            {
                break;
            }
        }
    }

    void Swap(T itemA, T itemB){
        items[itemA.HeapIndex]=itemB;
        items[itemB.HeapIndex]=itemA;
        int itemAIndex = itemA.HeapIndex;
        itemA.HeapIndex = itemB.HeapIndex;
        itemB.HeapIndex = itemAIndex;
    }
};


#endif // HEAP_H_INCLUDED
