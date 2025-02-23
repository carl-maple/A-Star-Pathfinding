#include "AStarNode.h"

#ifdef NEW_ASTAR_IMPL

AStarNode::AStarNode(const uint32 InSize)
{
	Cost.resize(InSize);
	State.resize(InSize);
	Parent.resize(InSize);
}

void AStarNode::Reset()
{
	std::fill(std::begin(State), std::end(State), EAStarNodeState::NONE);
	std::fill(std::begin(Cost), std::end(Cost), std::numeric_limits<float>::max());
	std::fill(std::begin(Parent), std::end(Parent), NStarNodeDefs::INVALID_INDEX);
}

#endif