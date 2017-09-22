#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <set>

#ifndef DisjointSet_H
#define DisjointSet_H

class DisjointSet {
	std::map<int,int> parent;
	std::map<int,int> rank;
	std::map<int,int> size;
	public:
		void makeSet(int x){
			if (!parent[x]){
				parent[x] = x; 
				rank[x] = 0;
				size[x] = 1;
			}
		}
		int find(int x){
			if (parent[x] != x){
				parent[x] = this->find(parent[x]);
			}
			return parent[x];
		}
		//(union) Unspecified if x and/or y are not elements in any set
		void combine(int x, int y){ 
			int x_root = this->find(x);
			int y_root = this->find(y);
			if (x_root == y_root) return;
			if (rank[x_root] > rank[y_root]) {
				size[x_root]+=size[y_root];
				parent[y_root] = x_root;
			}
			else {
				size[y_root]+=size[x_root];
				parent[x_root] = y_root;
			}
			if (rank[y_root] == rank[x_root]) rank[y_root]++;
		}
		//int x: Returns the number of elements in the set which contains x
		int getSize(int x){
			return size[this->find(x)];
		}
		void print(){
			std::map<int,std::set<int>> sets;
			for (std::pair<int,int> ele : parent){
				if (!(&sets[this->find(ele.first)])) sets[ele.first];
				sets[this->find(ele.first)].insert(ele.first);
			}
			for (std::pair<int,std::set<int>> ele : sets){
				std::cout << ele.first << ": ";
				for (int x: ele.second){
					std::cout << x << " ";
				}
				std::cout << "\n";
			}
		}
};
#endif