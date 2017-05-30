#include "stdafx.h"
#include "Heap.h"
#include <iostream>
#include <vector>

using namespace std;


Heap::Heap(){}



Heap::Heap(vector<int> &incoming_vector)
{
	//build a max heap
	for (unsigned int i = 0; i < incoming_vector.size(); i++)
	{
		heap_vector.push_back(incoming_vector[i]);
		trickle_up(i);
	}
}

Heap::~Heap()
{
}

void Heap::print_heap()
{
	for (unsigned i = 0; i < heap_vector.size(); i++)
		cout << heap_vector[i] << endl;
}

int Heap::get_max()
{
	return heap_vector[0];
}

int Heap::get_size()
{
	return heap_vector.size();
}

bool Heap::is_empty()
{
	return heap_vector.size() == 0;
}

void Heap::heap_sort()
{
	vector<int> tmp;
	/*
	Must store in a counter variable, otherwise heap_vector.size(); would change 
	on every iteration of the loop
	*/
	int heap_size = heap_vector.size();
	for (int i = 0; i < heap_size; i++)
	{
		/*
		Each iteration of the loop will grap the largest element from heap_vector, and place
		it at the begining of the tmp vector, then a remove method is called to remove that element
		from the heap_vector
		*/
		tmp.insert(tmp.begin(), heap_vector[0]);
		remove(heap_vector[0]);
	}
	heap_vector = tmp; //Reset heap_vector to tmp, which is now sorted
}

void Heap::reheap(vector<int> &v)
{
	vector<int> tmp;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		tmp.push_back(v[i]);
		trickle_up(i);
	}
	heap_vector = tmp;
}
void Heap::remove(int value)
{
	/*The first if, checks to see if the heap vector has been sorted, we must reheap
	back into a max heap before adding / removing more elements*/
	if (heap_vector.size() > 1 && heap_vector[0] < heap_vector[1])
		reheap(heap_vector);
	if (heap_vector[heap_vector.size() - 1] == value ) // if what we are trying to remove is the last elmement
	{
		heap_vector.pop_back();
		return;
	}
	int removal_index = get_node_index(value);
	swap(heap_vector[removal_index], heap_vector[heap_vector.size() - 1]); // swap value to remove with last index
	trickle_down(removal_index);
	heap_vector.pop_back(); // remove last item
}

void Heap::add(int value)
{
	/*The first if, checks to see if the heap vector has been sorted, we must reheap
	back into a max heap before adding / removing more elements*/
	if (heap_vector.size() > 1 && heap_vector[0] < heap_vector[1])
		reheap(heap_vector);
	heap_vector.push_back(value);
	trickle_up(heap_vector.size() - 1);
}



void Heap::trickle_up(int child)
{
	//if the child is the root, this is our first stopping condition
	if (child == 0)
		return;
	int parent = get_parent_index(child);
	//if the child is less than the parent, this is our second stopping condition
	if (heap_vector[child] < heap_vector[parent])
		return;
	//continue swapping child and parent until stopping condition is met
	swap(heap_vector[child], heap_vector[parent]);
	trickle_up(parent);
}
void Heap::trickle_down(int parent)
{
	int left_child = get_left_child_index(parent);
	int right_child = get_right_child_index(parent);

	//if parent node is a leaf, this is our  first stopping condition
	//****theres a bug here
	if (left_child >= heap_vector.size() || right_child >= heap_vector.size())
		return;


	//if both children are less than the parent, this is our second stopping condition
	if (heap_vector[left_child] < heap_vector[parent] && heap_vector[right_child] < heap_vector[parent])
		return;
	

	//if both children are larger than the parent
	if (heap_vector[left_child] > heap_vector[parent] && heap_vector[right_child] > heap_vector[parent])
	{
		//if the right child is the end index, then we don't want to touch it since it's getting removed
		if (right_child == heap_vector.size() - 1)
		{
			swap(heap_vector[parent], heap_vector[left_child]);
			return;
		}
		//find the max child, swap and continue
		int max_child = get_max_child(left_child, right_child);
		swap(heap_vector[parent], heap_vector[max_child]);
		trickle_down(max_child);
		return;
	}

	//if we get here we know one child is larger than the parent, so we find out which one and swap
	if (heap_vector[right_child] > heap_vector[parent]) //check right child
	{
		swap(heap_vector[right_child], heap_vector[parent]);
		trickle_down(right_child);
		return;
	}
	else { //if we get here we know left child is larger
		swap(heap_vector[left_child], heap_vector[parent]);
		trickle_down(left_child);
	}
}
void Heap::swap(int & parent, int & child)
{
	int temp = parent;
	parent = child;
	child = temp;
}
int Heap::get_parent_index(int child)
{
	//child is at an even index
	if (child % 2 == 0)
		return (child - 2) / 2;

		//child is at an odd index
	return floor((child - 1) / 2);
}

int Heap::get_left_child_index(int parent)
{
	return (2 * parent) + 1;
}

int Heap::get_right_child_index(int parent)
{
	return (2 * parent) + 2;
}

int Heap::get_node_index(int value)
{
	for (unsigned int i = 0; i < heap_vector.size(); i++)
	{
		if (heap_vector[i] == value)
			return i;
	}

	return -1;
}

int Heap::get_max_child(int left_child, int right_child)
{
	return (heap_vector[left_child] > heap_vector[right_child]) ? left_child : right_child;
}




