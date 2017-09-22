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
	public:
		void makeSet(int x){
			if (!parent[x]){
				parent[x] = x; 
				rank[x] = 0;
			}
		}
		int find(int x){
			if (parent[x] != x){
				parent[x] = this->find(parent[x]);
			}
			return parent[x];
		}
		//(union)
		void combine(int x, int y){ 
			int x_root = this->find(x);
			int y_root = this->find(y);
			if (x_root == y_root) return;
			if (rank[x_root] > rank[y_root]) parent[y_root] = x_root;
			else parent[x_root] = y_root;
			if (rank[y_root] == rank[x_root]) rank[y_root]++;

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