#ifndef KDTREE_H
#define KDTREE_H

#include <map>
#include <list>
#include <vector>
#include "Math/Vector3.h"

template <typename T>
struct HeapNode {
    T* p;
    float dist;
    bool operator <(const HeapNode<T>& rhs) const {
        return dist<rhs.dist;
    }
};


template <typename T>
class KDTree
{
public:
    KDTree();
    ~KDTree();


    void Build(std::list<T*>&);
    std::list<T*> FindClosest(const Vector3& point, float maxRadius, int maxPhotons);


private:
    void RecurseBuild(std::list<T*>&, int nodeIndex, int depth);
    void RecurseSearch(const Vector3&, float& maxRadiusSq, int nodeIndex, int maxPhotons, std::list<HeapNode<T>>& result);
	
    std::vector<T*> tree;
	
    T* Median(std::list<T*>&, int axis);
};


template <typename T>
KDTree<T>::KDTree()
{
}

template <typename T>
KDTree<T>::~KDTree() {
	auto treeIt = tree.begin();
	auto treeEnd = tree.end();
	for(treeIt; treeIt != treeEnd; ++treeIt)
	{
		delete (*treeIt);
	}
    tree.clear();
}

template <typename T>
T* KDTree<T>::Median(std::list<T*> &photons, int axis) {
    std::map<float, T*> list;

	auto photonsIt = photons.begin();
	auto photonsEnd = photons.end();
	for(photonsIt; photonsIt != photonsEnd; ++photonsIt)
	{
		list[((float*)(*photonsIt)->position)[axis]] = (*photonsIt);
	}
	std::vector<int> keys;
	auto listIt = list.begin();
	auto listEnd = list.end();
	int i = 0;
	T* toRet = nullptr;
	for(listIt; listIt != listEnd; ++listIt, ++i)
	{
		if(i == list.size() / 2)
		{
			toRet = (*listIt).second;
			break;
		}
	}
    return toRet;
}

template <typename T>
void KDTree<T>::Build(std::list<T *> &photons) {
    int size=1;

    while(size<photons.size())
        size*=2;

	tree.resize(size);

    RecurseBuild(photons, 0, 0);
}

template <typename T>
void KDTree<T>::RecurseBuild(std::list<T*> &photons, int nodeIndex, int depth) {
    if(photons.size()==0 || nodeIndex>=tree.size())return;

    int axis = depth % 3;

    T* median = Median(photons, axis);

    std::list<T*> leftList;
    std::list<T*> rightList;

	photons.remove(median);

	auto photonsIt = photons.begin();
	auto photonsEnd = photons.end();
	for(photonsIt; photonsIt != photonsEnd; ++photonsIt)
	{
        if(((float*)(*photonsIt)->position)[axis]<((float*)median->position)[axis])
            leftList.push_back(*photonsIt);
        else
            rightList.push_back(*photonsIt);
    }

    tree[nodeIndex] = median;
    median->divisionAxis = axis;

    RecurseBuild(leftList, 2*nodeIndex+1, depth+1);

    RecurseBuild(rightList, 2*nodeIndex+2, depth+1);
}


template <typename T>
std::list<T*> KDTree<T>::FindClosest(const Vector3& point, float maxRadius, int maxPhotons) {
	std::list<T*> result;
	std::list<HeapNode<T>> heap;

    float maxRadiusSq = maxRadius*maxRadius;

    RecurseSearch(point, maxRadiusSq, maxPhotons, 0, heap);

	auto heapIt = heap.begin();
	auto heapEnd = heap.end();
    for(heapIt; heapIt != heapEnd; ++heapIt)
       result.push_back((*heapIt).p);

    return result;
}

template <typename T>
void KDTree<T>::RecurseSearch(const Vector3 &point, float& maxRadiusSq, int maxPhotons, int nodeIndex, std::list<HeapNode<T> >& result) {
    if(nodeIndex>=tree.size() || tree.at(nodeIndex)==0) return;


    int axis = tree.at(nodeIndex)->divisionAxis;

    float dist = ((float*)point)[axis] - ((float*)tree.at(nodeIndex))[axis];

    if(dist<0) {
        RecurseSearch(point, maxRadiusSq, maxPhotons, 2*nodeIndex+1, result);

        if(dist*dist<maxRadiusSq)
            RecurseSearch(point, maxRadiusSq, maxPhotons, 2*nodeIndex+2, result);
    }
    else {
        RecurseSearch(point, maxRadiusSq, maxPhotons, 2*nodeIndex+2, result);

        if(dist*dist<maxRadiusSq)
            RecurseSearch(point, maxRadiusSq, maxPhotons, 2*nodeIndex+1, result);
    }

    float distToPhoton = (point-tree.at(nodeIndex)->position).GetSquaredLength();

    if(distToPhoton<maxRadiusSq) {
        HeapNode<T> hn;
        hn.p = tree.at(nodeIndex);
        hn.dist = distToPhoton;

        result.push_back(hn);

        int index = result.size()-1;
        while(index!=0) {
            int parentIndex = index/2;
			auto resultAtParentIndex = result.begin();
			auto resultAtIndex = result.begin();
			std::advance(resultAtParentIndex, parentIndex);
			std::advance(resultAtIndex, index);
            if((*resultAtParentIndex)<(*resultAtIndex)) 
			{
                HeapNode<T> temp = (*resultAtIndex);
                (*resultAtIndex) = (*resultAtParentIndex);
                (*resultAtParentIndex) = temp;
                index = parentIndex;
            }
            else break;
        }

        if(result.size()>=maxPhotons)
		{
            result.front() = result.back();
			result.pop_back();

            int index = 0;
            while(1) 
			{
                if(2*index+2 >= result.size()) break;

                int largerChild = 2*index+1;
				auto resultIt = result.begin();
				auto resultIt2 = result.begin();
				std::advance(resultIt, 2 * index + 1);
				std::advance(resultIt2, 2 * index + 2);
                if((*resultIt)<(*resultIt2))
                    largerChild = 2*index+2;
				
				auto resultAtIndex = result.begin();
				auto resultAtLargerChild = result.begin();
				std::advance(resultAtIndex, index);
				std::advance(resultAtLargerChild, largerChild);
                if((*resultAtIndex) < (*resultAtLargerChild)) 
				{
                    HeapNode<T> temp = (*resultAtIndex);
                    (*resultAtIndex) = (*resultAtLargerChild);
                    (*resultAtLargerChild) = temp;
                    index = largerChild;
                }
                else break;

            }
            maxRadiusSq = result.front().dist;
        }
    }
}

#endif // KDTREE_H
