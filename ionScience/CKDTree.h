
#if 0

#pragma once

#include <ionMath.h>


struct CKDTreeNeighborSet
{
	u32 const K;
	vec3f const Goal;

	std::vector<std::pair<vec3f, f32> > Set;

	CKDTreeNeighborSet(u32 const k, vec3f const & goal);

	void ConsiderPoint(vec3f const & Point);
	f32 GetWorstDistance() const;
	bool Filled() const;
};

class CKDTreeNode
{

public:

	CKDTreeNode()
		: LeftSide(), RightSide()
	{}

	CKDTreeNode * LeftSide, * RightSide;
	s32 SplitAxis;
	vec3f Position;

	void Split(vec3f * Elements, u32 const Count, s32 const Axis);
	vec3f NearestNeighbor(vec3f const & Point) const;
	void NearestKNeighbors(CKDTreeNeighborSet & Set) const;

};

class CKDTree
{

public:

	CKDTree()
		: Root()
	{}

	void Build(vec3f * Elements, u32 const Count);
	vec3f NearestNeighbor(vec3f const & Point) const;
	CKDTreeNeighborSet NearestKNeighbors(vec3f const & Point, u32 const K) const;

	CKDTreeNode * Root;

};

#endif
