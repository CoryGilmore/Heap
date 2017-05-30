#pragma once
#ifndef HEAP_H
#define HEAP_H
#include <vector>

class Heap
{
	
public:
	Heap();
	Heap(std::vector<int> &incoming_vector);
	~Heap();
	void print_heap();
	int get_max();
	int get_size();
	bool is_empty();
	void heap_sort();
	void remove(int value);
	void add(int value);


private:
	int get_parent_index(int child);
	int get_left_child_index(int parent);
	int get_right_child_index(int parent);
	int get_node_index(int value);
	int get_max_child(int left_child, int right_child);
	void reheap(std::vector<int> &v);
	std::vector<int> heap_vector;
	void trickle_up(int child);
	void trickle_down(int parent);
	void swap(int &parent, int &child); 
};

#endif