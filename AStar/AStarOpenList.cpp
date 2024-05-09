#include "AStarOpenList.h"
#include "AStarNode.h"
#include "AStarNodeList.h"
#include <algorithm>

template <class T>
void SwapObjects(T& Object1, T& Object2)
{
    T Temp = Object1;
    Object1 = Object2;
    Object2 = Temp;
}

AStarOpenList::AStarOpenList(const uint32 InSize, const AStarNodeList* const InNodeList)
    :NodeList(InNodeList)
{
	OpenList = new uint32[InSize];
}

AStarOpenList::~AStarOpenList()
{
	delete[] OpenList;
}

void AStarOpenList::Add(const uint16 InGridIndex)
{
    NumberOfItems++;
    OpenList[NumberOfItems] = InGridIndex;
    
    uint32 ParentNode, NewItem = NumberOfItems;
    
    while (NewItem != 1)
    {
        ParentNode = NewItem / 2;
    
        if (ParentNode == 1)
        {
            break;
        }
    
        if (NodeList->GetAStarNode(NewItem).Cost <= NodeList->GetAStarNode(ParentNode).Cost)
        {
            std::swap(OpenList[ParentNode], OpenList[NewItem]);
            NewItem = ParentNode;
        }
        else
        {
            // Done sorting
            break;
        }
    }
}

void AStarOpenList::PopFirst()
{
    OpenList[1] = OpenList[NumberOfItems];
    NumberOfItems--;

    int32 Current = 1;
    int32 Parent = 0;

    while (true)
    {
        Parent = Current;

        // If we have two children
        if (2 * Parent + 1 <= NumberOfItems)
        {
            // Check with the first child if we should move down
            if (NodeList->GetAStarNode(OpenList[Parent]).Cost >= 
                NodeList->GetAStarNode(OpenList[(Parent * 2)]).Cost)
            {
                Current = Parent * 2;
            }

            // If we are moving down we compare the two children with each other
            // If the cost was higher we compare the other child with the parent
            if (NodeList->GetAStarNode(OpenList[Current]).Cost >= 
                NodeList->GetAStarNode(OpenList[2 * Parent + 1]).Cost)
            {
                Current = Parent * 2 + 1;
            }
        }
        // If we have one child
        else if (2 * Parent <= NumberOfItems)
        {
            // Check with the first child if we should move down
            if (NodeList->GetAStarNode(OpenList[Parent]).Cost >=
                NodeList->GetAStarNode(OpenList[Parent * 2]).Cost)
            {
                Current = Parent * 2;
            }
        }

        // The parents cost is lower then it's child. Swap them.
        if (Current != Parent)
        {
            SwapObjects(OpenList[Parent], OpenList[Current]);
        }
        // The item is now in it's correct position in the list
        else
        {
            break;
        }
    } 
}

