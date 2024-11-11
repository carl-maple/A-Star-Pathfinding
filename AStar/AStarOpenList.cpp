#include "AStarOpenList.h"
#include "AStarNode.h"
#include "AStarNodeList.h"
#include "AStarWorker.h"
#include "AStarMap.h"

#include <algorithm>

template <class T>
void SwapObjects(T& Lhs, T& Rhs)
{
    T Temp = Lhs;
    Lhs = Rhs;
    Rhs = Temp;
}

AStarOpenList::AStarOpenList(const uint32 InSize, const AStarWorker* const InWorkerOwner)
    :WorkerOwner(InWorkerOwner)
{
    OpenList.resize(InSize);
}

void AStarOpenList::Add(const uint32 InGridIndex)
{
    NumberOfItems++;
    OpenList[NumberOfItems] = InGridIndex;
    
    uint32 ParentNode, NewItem = NumberOfItems;
    
    // Do a rough heap sort until we are number one or we find a node with lower cost
    // The more accurate sorting happens in AStarOpenList::PopFirst
    while (NewItem != 1)
    {
        ParentNode = NewItem / 2;
    
        if (ParentNode == 1)
        {
            break;
        }

        const auto& NodeList = WorkerOwner->GetNodeList();
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
    const auto& NodeList = WorkerOwner->GetNodeList();
    NodeList->CloseNode(GetFirst());

    OpenList[1] = OpenList[NumberOfItems];
    NumberOfItems--;

    uint32 Current = 1;
    uint32 Parent = 0;

    // Binary sorting implementation. 
    // OpenList starts counting from 1 to make the implementation cleaner.
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
            // Check with the if we should move down
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

void AStarOpenList::PopulateNeighbours(const uint32 InGridIndex, const SVector2Di& InGoalPos)
{
    const AStarMap* const Map = WorkerOwner->GetMap();
    const auto& NodeList = WorkerOwner->GetNodeList();

    const SVector2Di TempGridPos = Map->GetGridPosition(InGridIndex);
    SVector2Di TempNeighbourGridPos = SVector2Di();

    for (uint32 NeighbourIndex = 0; NeighbourIndex < NAStarDefs::NUM_OF_NEIGHBOURS; NeighbourIndex++)
    {
        TempNeighbourGridPos = TempGridPos + NeighbourDirections[NeighbourIndex];

        // Check if the position is on the grid
        if (Map->IsGridPositionValid(TempNeighbourGridPos) == false)
        {
            continue;
        }

        const uint32 NeighbourGridIndex = Map->GetGridIndex(TempNeighbourGridPos);

        // Populate the node with data
        if (NodeList->Populate(NeighbourGridIndex, InGridIndex))
        {
            // Add it to the open list
            Add(NeighbourGridIndex);
        }
    }
}