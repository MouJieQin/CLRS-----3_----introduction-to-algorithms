#pragma once
#ifndef _SOLUTION_25_H_
#define _SOLUTION_25_H_
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class all_pairs_shortest_paths {
public:
	all_pairs_shortest_paths(vector<vector<pair<int, int>>>&vect):graph_weight(vect.size(),vector<int>(vect.size(),INT_MAX)),
	precursor_matrix(graph_weight){
		for (size_t i = 0; i < vect.size(); ++i) {
			graph_weight[i][i] = 0;
			precursor_matrix[i][i] = i;
			for (size_t j = 0; j < vect[i].size(); ++j) {
				graph_weight[i][vect[i][j].first] = vect[i][j].second;
				precursor_matrix[i][vect[i][j].first] = i;
			}
		}
	}
	
	void slow_all_pairs_shortest_paths() {
		vector<vector<int>>curr(graph_weight);
		vector<vector<int>>last(graph_weight);

		for (size_t i = 2; i < graph_weight.size(); ++i) {
			last.swap(curr);
			extend_shortest_paths(curr, last, graph_weight);
		}
		//25.1-6
		find_precursor_matrix(curr);
	}

	void faster_all_pair_shortest_paths() {
		vector<vector<int>>curr(graph_weight);
		vector<vector<int>>last(graph_weight);

		size_t m = 1;
		size_t n = graph_weight.size() - 1;

		while (m < n) {
			extend_shortest_paths(curr, last, last);
			last.swap(curr);
			m = m * 2;
		}
	}

	//25.1-6
	void find_precursor_matrix(vector<vector<int>>&weight_matrix) {
		for(size_t i=1;i<graph_weight.size();++i)
			for (size_t j = 1; j < graph_weight.size(); ++j) {

				if (weight_matrix[i][j] != INT_MAX) {
					for (size_t k = 1; k < graph_weight.size(); ++k) {
						if (k!=j&&weight_matrix[i][k]!=INT_MAX&&graph_weight[k][j]!=INT_MAX&&
							weight_matrix[i][j] == weight_matrix[i][k] + graph_weight[k][j]) {
							precursor_matrix[i][j] = k;
						}
					}
				}
			}
		cout << "前驱矩阵为\n" << endl;
		print_all_pair_weight(precursor_matrix);

		cout << "所有节点的最短路径为\n" << endl;
		for (size_t i = 1; i < graph_weight.size(); ++i) 
			for (size_t j = 1; j < graph_weight.size(); ++j) 
				if (i != j) {
					print_all_pairs_shortest_path(i, j);
					cout << endl;
				}
			
		cout << "\n-----------------------------\n" << endl;
	}
private:
	void extend_shortest_paths(vector<vector<int>>&curr, vector<vector<int>>&last, vector<vector<int>>&weight) {
		for (size_t i = 1; i < weight.size(); ++i) {
			for (size_t j = 1; j < weight.size(); ++j) {
				curr[i][j] = INT_MAX;
				for (size_t k = 1; k < weight.size(); ++k) {
					if (last[i][k] != INT_MAX&&weight[k][j]!=INT_MAX) {
						if (last[i][k] + weight[k][j] < curr[i][j])
							curr[i][j] = last[i][k] + weight[k][j];
					}
				}
			}
		}
		print_all_pair_weight(curr);//
	}
	void print_all_pair_weight(const vector<vector<int>>&vect) {
		for (size_t i = 1; i < vect.size(); ++i) {
			for (size_t j = 1; j < vect.size(); ++j)
				vect[i][j] == INT_MAX ? cout << "∞" << "\t" : cout << vect[i][j] << "\t";
			cout << endl;
		}
		cout << "\n\n" << endl;
	}

	void print_all_pairs_shortest_path(int i, int j) {
		if (precursor_matrix[i][j] == INT_MAX) {
			cout << "No path from " << i << " to " << j << " exists";
		}
		else {
			if (i == j)
				cout << i << " ";
			else {
				print_all_pairs_shortest_path(i, precursor_matrix[i][j]);
				cout << " → " << j;
			}
		}
	}
private:
	vector<vector<int>>graph_weight;
	vector<vector<int>>precursor_matrix;
	vector<vector<int>>p;
};


class solution25_1_1 {
public:
	void operator()() {
		vector<vector<pair<int, int>>>vect{
			{},
			{{5,-1}},
			{{1,1}, {4,2}},
			{{2,2},{6,-8}},
			{{1,-4},{5,3}},
			{{2,7}},
			{{2,5},{3,10}}
		};
	   all_pairs_shortest_paths apsp(vect);
	   apsp.slow_all_pairs_shortest_paths();

	   cout << "\n--------------------------" << endl;
	   apsp.faster_all_pair_shortest_paths();
	}
};

class solution25_1_2 {
public:
	void operator()() {
		cout << "自己可以到达自己且权重为0，为其它值不能正确计算"
			<< endl;
	}
};

class solution25_1_3 {
public:
	void operator()() {
		cout << "单元矩阵"
			<< endl;
	}
};

class solution25_1_5 {
public:
	void operator()() {
		cout << "为权重矩阵和单源向量的乘积"
			<< endl;
	}
};

class solution25_1_6 {
public:
	void operator()() {
		cout << "程序在上面" << endl;

		vector<vector<pair<int, int>>>vect{
			{},
			{ { 5,-1 } },
			{ { 1,1 },{ 4,2 } },
			{ { 2,2 },{ 6,-8 } },
			{ { 1,-4 },{ 5,3 } },
			{ { 2,7 } },
			{ { 2,5 },{ 3,10 } }
		};
		all_pairs_shortest_paths apsp(vect);
		apsp.slow_all_pairs_shortest_paths();
	}
};

class solution25_1_8 {
public:
	void operator()() {
		cout << "我的算法就是这么写的"
			<< endl;
	}
};

class solution25_1_9 {
public:
	void operator()() {
		cout << "让extend_shortest_paths()返回一个bool来确认此次调用是否有修改L矩阵的值\n"
			<< "当m>=n时如果被修改表明有负权重环"
			<< endl;
	}
};

class floyd_warshall {
public:
	floyd_warshall(vector<vector<pair<int, int>>>&vect) :graph_weight(vect.size(), vector<int>(vect.size(), INT_MAX))
	,precursor_matrix(graph_weight){
		for (size_t i = 0; i < vect.size(); ++i) {
			graph_weight[i][i] = 0;
			precursor_matrix[i][i] = i;
			for (size_t j = 0; j < vect[i].size(); ++j) {
				graph_weight[i][vect[i][j].first] = vect[i][j].second;
				precursor_matrix[i][vect[i][j].first] = i;
			}
		}
	}
	void operator()() {
		vector<vector<int>>shortest_paths_weight_graph(graph_weight);
		vector<vector<int>>&last(shortest_paths_weight_graph);
		vector<vector<int>>last_precursor_matrix(precursor_matrix);

		for (size_t k = 1; k < graph_weight.size(); ++k) {

			for (size_t i = 1; i < graph_weight.size(); ++i)
				for (size_t j = 1; j < graph_weight.size(); ++j)
					if (last[i][k] != INT_MAX&&last[k][j] != INT_MAX)
						if (last[i][k] + last[k][j] < last[i][j]) {
							shortest_paths_weight_graph[i][j] = last[i][k] + last[k][j];
							precursor_matrix[i][j] = last_precursor_matrix[k][j];
						}

			last_precursor_matrix = precursor_matrix;
			print_all_pair_weight(last);
		}
		cout << "前驱矩阵为" << endl;
		print_all_pair_weight(precursor_matrix);
	}
private:
	void print_all_pair_weight(const vector<vector<int>>&vect) {
		for (size_t i = 1; i < vect.size(); ++i) {
			for (size_t j = 1; j < vect.size(); ++j)
				vect[i][j] == INT_MAX ? cout << "∞" << "\t" : cout << vect[i][j] << "\t";
			cout << endl;
		}
		cout << "\n\n" << endl;
	}
private:
	vector<vector<int>>graph_weight;
	vector<vector<int>>precursor_matrix;
};

class solution25_2_1 {
public:
	void operator()() {
		vector<vector<pair<int, int>>>vect{
			{},
			{ { 5,-1 } },
			{ { 1,1 },{ 4,2 } },
			{ { 2,2 },{ 6,-8 } },
			{ { 1,-4 },{ 5,3 } },
			{ { 2,7 } },
			{ { 2,5 },{ 3,10 } }
		};
		floyd_warshall fws(vect);
		fws();
	}
};

class solution25_2_2 {
public:
	void operator()() {
		cout << "将权重改为1，计算出来的最短权重图中∞不能到达，否则能到达"
			<< endl;
	}
};

class solution25_2_3 {
public:
	void operator()() {
		cout << "算法在上面，结果见25.2.1"
			<< endl;
	}
};

class solution25_2_4 {
public:
	void operator()() {
		cout << "要让此程序出错，就要让第6行等式右边的dij,dik,dkj在k未改变的同一次外层循环内在上一次内层循环被改变\n"
			<< "dij只能在本次循环内被改变而不能在上次循环被改变，假设dik在上次循环被改变过，则j'=k,\n"
			<< "dij'=min(dij',dik+dkj'）=min（dij',dij'+dj'j')=dij',与假设矛盾所以没被改变，dkj同理可证"
			<< endl;
	}
};

class solution25_2_6 {
public:
	void operator()() {
		cout << "再运行一遍该算法如果有值改变说明有负权重环路"
			<< endl;
	}
};

class solution25_2_8 {
public:
	void operator()() {
		cout << "使用v次bfs,O(v^2+VE)"
			<< endl;
	}
};


class solution25_3_2 {
public:
	void operator()() {
		cout << "当图中存在负权重环时如果使用原图中的节点进行bellmlan_ford算法可能检测不出来\n"
			<< "因为这个节点可能不能到达负环"
			<< endl;
	}
};

class solution25_3_3 {
public:
	void operator()() {
		cout << "相等"
			<< endl;
	}
};

class solution25_3_4 {
public:
	void operator()() {
		cout << "计算出的最短路径可能和真正的最短路径不符"
			<< endl;
	}
};

class solution25_3_5 {
public:
	void operator()() {
		cout << "因为环上所有节点的w'>=0,而环也必须保证所有的权重相加=0，如果>0,原图中的最短路径可以包含这个环路"
			<< "而新图中则不能，所以w'=0"
			<< endl;
	}
};

class solution25_3_6 {
public:
	void operator()() {
		cout << "如果s不能到达权重为负值的环，将会返回错误结果，强连通时能保证可以到达任意节点\n"
			<< "和johson算法类比，原图中也有一个权重为0的节点"
			<< endl;
	}
};

#endif