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
		cout << "ǰ������Ϊ\n" << endl;
		print_all_pair_weight(precursor_matrix);

		cout << "���нڵ�����·��Ϊ\n" << endl;
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
				vect[i][j] == INT_MAX ? cout << "��" << "\t" : cout << vect[i][j] << "\t";
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
				cout << " �� " << j;
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
		cout << "�Լ����Ե����Լ���Ȩ��Ϊ0��Ϊ����ֵ������ȷ����"
			<< endl;
	}
};

class solution25_1_3 {
public:
	void operator()() {
		cout << "��Ԫ����"
			<< endl;
	}
};

class solution25_1_5 {
public:
	void operator()() {
		cout << "ΪȨ�ؾ���͵�Դ�����ĳ˻�"
			<< endl;
	}
};

class solution25_1_6 {
public:
	void operator()() {
		cout << "����������" << endl;

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
		cout << "�ҵ��㷨������ôд��"
			<< endl;
	}
};

class solution25_1_9 {
public:
	void operator()() {
		cout << "��extend_shortest_paths()����һ��bool��ȷ�ϴ˴ε����Ƿ����޸�L�����ֵ\n"
			<< "��m>=nʱ������޸ı����и�Ȩ�ػ�"
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
		cout << "ǰ������Ϊ" << endl;
		print_all_pair_weight(precursor_matrix);
	}
private:
	void print_all_pair_weight(const vector<vector<int>>&vect) {
		for (size_t i = 1; i < vect.size(); ++i) {
			for (size_t j = 1; j < vect.size(); ++j)
				vect[i][j] == INT_MAX ? cout << "��" << "\t" : cout << vect[i][j] << "\t";
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
		cout << "��Ȩ�ظ�Ϊ1��������������Ȩ��ͼ�С޲��ܵ�������ܵ���"
			<< endl;
	}
};

class solution25_2_3 {
public:
	void operator()() {
		cout << "�㷨�����棬�����25.2.1"
			<< endl;
	}
};

class solution25_2_4 {
public:
	void operator()() {
		cout << "Ҫ�ô˳��������Ҫ�õ�6�е�ʽ�ұߵ�dij,dik,dkj��kδ�ı��ͬһ�����ѭ��������һ���ڲ�ѭ�����ı�\n"
			<< "dijֻ���ڱ���ѭ���ڱ��ı���������ϴ�ѭ�����ı䣬����dik���ϴ�ѭ�����ı������j'=k,\n"
			<< "dij'=min(dij',dik+dkj'��=min��dij',dij'+dj'j')=dij',�����ì������û���ı䣬dkjͬ���֤"
			<< endl;
	}
};

class solution25_2_6 {
public:
	void operator()() {
		cout << "������һ����㷨�����ֵ�ı�˵���и�Ȩ�ػ�·"
			<< endl;
	}
};

class solution25_2_8 {
public:
	void operator()() {
		cout << "ʹ��v��bfs,O(v^2+VE)"
			<< endl;
	}
};


class solution25_3_2 {
public:
	void operator()() {
		cout << "��ͼ�д��ڸ�Ȩ�ػ�ʱ���ʹ��ԭͼ�еĽڵ����bellmlan_ford�㷨���ܼ�ⲻ����\n"
			<< "��Ϊ����ڵ���ܲ��ܵ��︺��"
			<< endl;
	}
};

class solution25_3_3 {
public:
	void operator()() {
		cout << "���"
			<< endl;
	}
};

class solution25_3_4 {
public:
	void operator()() {
		cout << "����������·�����ܺ����������·������"
			<< endl;
	}
};

class solution25_3_5 {
public:
	void operator()() {
		cout << "��Ϊ�������нڵ��w'>=0,����Ҳ���뱣֤���е�Ȩ�����=0�����>0,ԭͼ�е����·�����԰��������·"
			<< "����ͼ�����ܣ�����w'=0"
			<< endl;
	}
};

class solution25_3_6 {
public:
	void operator()() {
		cout << "���s���ܵ���Ȩ��Ϊ��ֵ�Ļ������᷵�ش�������ǿ��ͨʱ�ܱ�֤���Ե�������ڵ�\n"
			<< "��johson�㷨��ȣ�ԭͼ��Ҳ��һ��Ȩ��Ϊ0�Ľڵ�"
			<< endl;
	}
};

#endif