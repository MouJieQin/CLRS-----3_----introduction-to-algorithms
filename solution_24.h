#pragma once
#ifndef _SOLUTION_24_H_
#define _SOLUTION_24_H_
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

///////////////////
struct graphNode;
typedef shared_ptr<graphNode> pt_graph;
struct adjListNode;
typedef shared_ptr<adjListNode> pt_adj;
struct graphNode {
	graphNode(int k, int w = INT_MAX,pt_adj n=nullptr,int p=INT_MIN):
		key(k),weight(w),next(n),p(p){}
	bool operator<(const graphNode &rhs) { return weight < rhs.weight; }
	int key;
	int weight;
	pt_adj next;
	int p;
};

struct adjListNode {
	adjListNode(int k,int w,pt_adj n=nullptr):
		key(k),weight(w),next(n){}
	int key;
	int weight;
	pt_adj next;
};

class bellman_ford {
public:
	bellman_ford(vector<vector<pair<int,int>>>&vect) {
		for (size_t i = 0; i < vect.size(); ++i)
			graph.push_back(shared_ptr<graphNode>(new graphNode(i)));
		for (size_t i = 0; i < vect.size(); ++i)
			for (size_t j = 0; j < vect[i].size(); ++j)
				insert(i, vect[i][j].first, vect[i][j].second);
	}
	void operator()(int s) {
		start = s;
		graph[start]->weight = 0;
		for(size_t i=1;i<graph.size()-1;++i)
			for (size_t j = 0; j < graph.size(); ++j) {
				auto curr = graph[j]->next;
				while (curr) {
					relax(j, curr->key, curr->weight);
					curr = curr->next;
				}
			}

		check();//���㷨��24.1-4���㷨

		/*for (size_t i = 1; i < graph.size(); ++i) {
			auto curr = graph[i]->next;
			while (curr) {
				if (graph[i]->weight != INT_MIN) {
					if (graph[curr->key]->weight > graph[i]->weight + curr->weight) {
						cout << "ͼ����Ȩ��Ϊ��ֵ�Ļ�·\n" << endl;
						return;
					}
				}
				curr = curr->next;
			}
		}*/

		print();
	}
private:
	void relax(int u, int v,int weight) {
		if (graph[u]->weight != INT_MAX) {
			if (graph[v]->weight > graph[u]->weight + weight) {
				graph[v]->weight = graph[u]->weight + weight;
				graph[v]->p = u;
			}
			
		}
	}
	void check() {
		for (size_t i = 1; i < graph.size(); ++i) {
			
			if (graph[i]->weight != INT_MAX) {
				if (i != start&&graph[i]->weight!=INT_MIN&&graph[graph[i]->p]->weight == INT_MIN) {
					graph[i]->weight = INT_MIN;
					check();
					return;
				}
				else {
					auto curr = graph[i]->next;
					while (curr) {
						if (graph[curr->key]->weight > graph[i]->weight + curr->weight) {
							negative_loop(i);
							check();
						}
						else
							curr = curr->next;
					}
				}
			}
		}
	}
	void insert(int u, int v,int weight) {
		auto t = shared_ptr<adjListNode>(new adjListNode(v, weight,graph[u]->next));
		graph[u]->next = t;
	}
	void print() {
		for (size_t i = 1; i < graph.size();++i) {
			cout << i << "\t" << graph[i]->p << "\t" << graph[i]->weight << endl;
		}
		cout << "\n" << endl;
	}
	void negative_loop(int k) {
		int last = k;
		do{
			graph[k]->weight = INT_MIN;
			k = graph[k]->p;
		}while(k != last);
	}
private:
	vector<pt_graph>graph;
	int start;
};

class test_bellman_ford {
public:
	void operator()() {
		vector<vector<pair<int, int>>>vect{
			{},
			{{2,3},{3,5}},
			{{3,2},{4,6}},
			{{2,1},{4,4},{5,6}},
			{{5,2}},
			{{1,3},{4,7}}
		};
		bellman_ford bf(vect);
		bf(1);
	}
};

class solution24_1_4 {
public:
	void operator()() {
		cout << "check()���ĵ�ǰ�ڵ�ĸ��ڵ��Ȩ��Ϊ-�ޣ��ı䵱ǰ�ڵ��Ȩ��Ϊ-�ޣ�Ȼ��ݹ�check��������Ϊ�ýڵ����Ѽ����ڵ�ĸ��ڵ�\n"
			<< "�����ǰ�ڵ��ڻ�·����ͨ���ݹ齫��·�е�Ȩ�ظ�Ϊ-�ޣ�Ȼ��ݹ�check(),ԭ��ͬ��\n"
			<< "����ʱ��ΪO(k+cE),kΪ��Ȩ�ػ�·�еĵ�ĸ�����cΪ����֮����Ȩ��Ϊ-�޵ĵ����ĸ���"
			<< endl;
		vector<vector<pair<int, int>>>vect{
			{},
			{{2,3},{4,5},{7,2}},
			{{3,-4}},
			{{6,4}},
			{{5,6}},
			{{4,-3},{6,8}},
			{},
			{{8,3}},
			{{7,-6},{6,7}}
		};
		bellman_ford bf(vect);
		bf(1);
	}
};

class solution24_1_5 {
public:
	void operator()() {
		cout << "��ͼ������vΪԴ�ڵ�ʹ��bellman����ford�㷨"
			<< endl;
	}
};

class solution24_1_6 {
public:
	void operator()() {
		cout << "������check()"
			<< endl;
	}
};


//////////////
struct dfsNode;
typedef shared_ptr<dfsNode> pt_dfs;
struct adjNode;
typedef shared_ptr<adjNode> pt_list;

struct dfsNode {
	dfsNode(int key,int weight=INT_MAX,int p=INT_MAX,bool visited=false,int d=INT_MAX,int f=INT_MAX,pt_list next=nullptr):
		key(key),weight(weight),p(p),visited(visited),next(next){}

	int key;
	int weight;
	int p;

	bool visited;
	pt_list next;
};

struct adjNode {
	adjNode(int key,int weight=INT_MAX,pt_list next=nullptr):
		key(key),weight(weight),next(next){}
	int key;
	int weight;
	pt_list next;
};

class dag_shortest_paths {
public:
	dag_shortest_paths(vector<vector<pair<int, int>>>&vect) {
		for (size_t i = 0; i < vect.size(); ++i)
			graph.push_back(shared_ptr<dfsNode>(new dfsNode(i)));
		for (size_t i = 1; i < vect.size(); ++i)
			for (size_t j = 0; j < vect[i].size(); ++j)
				insert(i, vect[i][j].first, vect[i][j].second);
	}
	void operator()(int start) {
		topologically_sort();

		graph[start]->weight = 0;
		for (auto i : topSort) {
			auto curr = graph[i]->next;
			while (curr) {
				relax(i, curr->key, curr->weight);
				curr = curr->next;
			}
		}
		print();
	}
private:
	void insert(int u, int v, int weight) {
		auto t = shared_ptr<adjNode>(new adjNode(v, weight, graph[u]->next));
		graph[u]->next = t;
	}
	
	void topologically_sort() {
		for (size_t i = 1; i < graph.size(); ++i) {
			if (!graph[i]->visited) {
				dfs_visit(i);
			}
		}
	}

	void dfs_visit(int k) {
		time += 1;
		graph[k]->visited = true;

		auto curr = graph[k]->next;
		while (curr) {
			if (!graph[curr->key]->visited)
				dfs_visit(curr->key);

			curr = curr->next;
		}

		time += 1;
		topSort.insert(topSort.begin(),k);
	}
	void relax(int u,int v,int weight) {
		if (graph[u]->weight != INT_MAX) {
			if (graph[u]->weight + weight < graph[v]->weight) {
				graph[v]->weight = graph[u]->weight + weight;
				graph[v]->p = u;
			}
		}
	}
	void print() {
		for (size_t i = 1; i < graph.size(); ++i)
			cout << i << "\t" << graph[i]->p << "\t" << graph[i]->weight << endl;
		cout << "\n" << endl;
	}
private:
	vector<pt_dfs> graph;
	size_t time = 0;
	vector<int>topSort;
};

class solution24_2_1 {
public:
	void operator()() {
		vector<vector<pair<int, int>>>vect{
			{},
			{{3,3},{2,5}},
			{{4,6},{3,2}},
			{{5,4},{6,2},{4,7}},
			{{6,1},{5,-1}},
			{{6,-2}},
			{}
		};
		dag_shortest_paths dsp(vect);
		dsp(1);
		//dsp(2);
	}

};

///////////////////////////////////
struct graNode;
typedef shared_ptr<graNode> pt_g;
struct listNode;
typedef shared_ptr<listNode> pt_t;

struct graNode {
	graNode(int key, int index,int weight=INT_MAX,int p=INT_MAX,int d=INT_MAX,int f=INT_MAX,pt_t next=nullptr):
		key(key),index(index),weight(weight),p(p),next(next){}
	bool operator<(graNode&rhs) { return weight < rhs.weight; }
	
	int key;
	int index;
	int weight;
	int p;

	pt_t next;
};

struct listNode {
	listNode(int key,int weight=INT_MAX,pt_t next=nullptr):
		key(key),weight(weight),next(next){}
	int key;
	int weight;
	pt_t next;
};

class min_heap {
public:
	min_heap(vector<pt_g>&graph,int start):heap(graph),graph(graph){
		graph[start]->weight = 0;
		for (int i = parents(graph.size() - 1); i != 0; --i)
			min_heapify(i);
	}
	
	int extract_min() {
		int min = heap[1]->key;

		swap(heap[1], heap.back());
		heap.pop_back();
		min_heapify(1);
		return min;
	}

	void decrease_key(int i, int weight) {
		heap[i]->weight = weight;
		while (i > 1 && heap[i] < heap[parents(i)]) {
			swap(heap[i], heap[parents(i)]);
			i = parents(i);
		}
	}
	bool empty() { return heap.size() == 1; }
private:
	int left(int k) { return 2 * k; }
	int right(int k) { return 2 * k + 1; }
	int parents(int k) { return k / 2; }

	void min_heapify(int k) {
		int lef = left(k);
		int righ = right(k);
		int smallest = k;

		if (size_t(lef) < heap.size() && heap[lef] < heap[smallest])
			smallest = lef;
		if (size_t(righ) < heap.size() && heap[righ] < heap[smallest])
			smallest = righ;

		if (smallest != k) {
			swap(heap[smallest], heap[k]);
			min_heapify(smallest);
		}
	}

	void swap(pt_g&lhs, pt_g&rhs) {
		std::swap(graph[lhs->key]->index, graph[rhs->key]->index);//����ԭͼ����С���е��±�

		std::swap(lhs,rhs);//����ԭͼ����С���е�λ��
	}
private:
	vector<pt_g>heap;//��Ϊ��С��ֻ��Ҫ�ڵ�����ƺ�Ȩ�ؾͿ��ԣ���Ϊ�˷����ֱ�ӿ�����
	vector<pt_g>&graph;//��Ϊԭͼ�����õ�ȫ�ֱ���ʹ��
};

class dijkstra {
public:
	dijkstra(vector<vector<pair<int,int>>>&vect){
		for (size_t i = 0; i < vect.size(); ++i)
			graph.push_back(shared_ptr<graNode>(new graNode(i,i)));
		for (size_t i = 1; i < vect.size(); ++i)
			for (size_t j = 0; j < vect[i].size(); ++j)
				insert(i, vect[i][j].first, vect[i][j].second);
	}
	void operator()(int start) {
		cout << "����dijkstra����һ��֤��������ѡȡ������Сֵ��Ϊ���Ž����һ�����������������һ��·������\n"
			<< "�õ㣬��Ȼ�ᾭ����С���в�Ϊ�޵�ĳһ�㣬����Щ���Ȩ�ض��ȸõ�󣬶�����û�и�Ȩ�أ�����ѡ��õ������Ž�\n"
			<< endl;
		min_heap heap(graph, start);

		while (!heap.empty()) {
			int u = heap.extract_min();

			auto curr = graph[u]->next;
			while (curr) {
				relax(u, curr->key, curr->weight,heap);

				print();//Ϊ24.3-1׼��

				curr = curr->next;
			}
		}
		print();
	}
private:
	void insert(int u, int v, int weight) {
		auto t = shared_ptr<listNode>(new listNode(v, weight, graph[u]->next));
		graph[u]->next = t;
	}
	void relax(int u, int v, int weight,min_heap &heap) {
		if (graph[u]->weight + weight < graph[v]->weight) {
			graph[v]->p = u;
			heap.decrease_key(graph[v]->index, weight + graph[u]->weight);//��С��С���еļ�ֵ
		}
	}
	void print() {
		for (size_t i = 1; i != graph.size(); ++i)
			cout << i << "\tp: " << graph[i]->p << "\tweight: " << graph[i]->weight << "\t index: " << graph[i]->index << endl;
		cout << "\n" << endl;
	}
private:
	vector<pt_g> graph;
};

class solution24_3_1 {
public:

	void operator()() {
		vector<vector<pair<int, int>>>vect{
			{},
			{ { 2,3 },{ 3,5 } },
			{ { 3,2 },{ 4,6 } },
			{ { 2,1 },{ 4,4 },{ 5,6 } },
			{ { 5,2 } },
			{ { 1,3 },{ 4,7 } }
		};

		dijkstra dijks(vect);
		dijks(1);
	}
};

class solution24_3_2 {
public:
	void operator()() {
		cout << "dijkstra���õ���̰���㷨����ѡ���˾ֲ����Ž⣬���ھֲ�֮��������ڸ�ֵ�ֲ����Ž�Ͳ���ȫ�����Ž�"
			<< endl;
	}
};

class solution24_3_3 {
public:
	void operator()() {
		cout << "��ȷ�����һ���Ѿ�ȷ�������ɳ�"
			<< endl;
	}
};

class solution24_3_5 {
public:
	void operator()() {
		cout << "ͼ24-6�Ѿ�˵��"
			<< endl;
	}
};

class solution24_3_6 {
public:
	void operator()() {
		cout << "��������dijkstra�㷨�����ɳڸ�Ϊ�˷��ʹ��ںţ�����С�Ѹ�Ϊ����\n"
			<< "����̰���㷨��֤���������Ҷ�dijkstra����һ��֤������Ϊ0<=r<=1,�������������ڵ��·��һ����\n"
			<< "̰���㷨��·��С\n"
			<< endl;
	}
};

class solution24_3_8 {
public:
	void operator()() {
		cout << "��Ϊd[u]��ֵ������(|V|-1)*W��ʹ����ô��������¼d��ֵ��\n"
			<< "V������Сֵ�����(|V|-1)*W��ÿ��decrease-key��O(1)ʱ�䡣�ܹ�ʱ��O(WV+E)��"
			<< endl;
	}
};

class solution24_3_9 {
public:
	void operator()() {
		cout << "veb��"
			<< endl;
	}
};

class solution24_3_10 {
public:
	void operator()() {
		cout << "ʹ�����������һ��֤����ʽ,�޹������Ȩ��"
			<< endl;
	}
};

class solution24_4_1 {
public:
	void operator()() {
		vector<vector<pair<int, int>>> vect{
			{ { 1,0 },{ 2,0 },{ 3,0 },{ 4,0 },{ 5,0 },{ 6,0 } },
			{ { 5,-1 } },
			{ { 1,1 },{ 4,2 } },
			{ { 2,2 },{ 6,-8 } },
			{ { 1,-4 },{ 5,3 } },
			{ { 2,7 } },
			{ { 2,5 },{ 3,10 } }
		};
		bellman_ford bfd(vect);
		bfd(0);
	}
}; 

class solution24_4_2 {
public:
	void operator()() {
		vector<vector<pair<int, int>>> vect{
			{ { 1,0 },{ 2,0 },{ 3,0 },{ 4,0 },{ 5,0 }},
			{{4,3}},
			{{1,4},{3,1}},
			{{4,5},{5,-4}},
			{{2,-6},{5,-8}},
			{{1,5},{4,10}}
		};
		bellman_ford bfd(vect);
		bfd(0);
		cout << "�޿��н�" << endl;
	}
};

class solution24_4_3 {
public:
	void operator()() {
		cout << "�����ܣ���Ϊv0ֱ�ӵ����ڵ��Ȩ��Ϊ0"
			<< endl;
	}
};

class solution24_4_4 {
public:
	void operator()() {
		cout << "ת��Ϊ��Դ���·���⣬���ڿ����л��ֿ����и�ֵ��ͼ���ܱ������ÿһ���ڵ�"
			<< endl;
	}
};

class solution24_4_5 {
public:
	void operator()() {
		cout << "�����v0,�����нڵ��Ȩ�س�ʼ��Ϊ0����Ϊ�ض���һ���ڵ��Ȩ�ص����·��Ϊ0��ʹ��bellman_ford \n"
			<< "�ɳ�mn��"
			<< endl;
	}
};

class solution24_4_6 {
public:
	void operator()() {
		cout << "'<=' + '>=' = '='"
			<< endl;
	}
};

//˼����



#endif