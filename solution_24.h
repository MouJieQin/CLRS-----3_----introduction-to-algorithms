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

		check();//该算法是24.1-4的算法

		/*for (size_t i = 1; i < graph.size(); ++i) {
			auto curr = graph[i]->next;
			while (curr) {
				if (graph[i]->weight != INT_MIN) {
					if (graph[curr->key]->weight > graph[i]->weight + curr->weight) {
						cout << "图中有权重为负值的环路\n" << endl;
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
		cout << "check()检测的当前节点的父节点的权重为-∞，改变当前节点的权重为-∞，然后递归check（），因为该节点是已检查过节点的父节点\n"
			<< "如果当前节点在环路中则通过递归将环路中的权重改为-∞，然后递归check(),原因同上\n"
			<< "运行时间为O(k+cE),k为负权重环路中的点的个数，c为除此之外点的权重为-∞的点数的个数"
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
		cout << "将图反向，以v为源节点使用bellman——ford算法"
			<< endl;
	}
};

class solution24_1_6 {
public:
	void operator()() {
		cout << "类似于check()"
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
		std::swap(graph[lhs->key]->index, graph[rhs->key]->index);//交换原图在最小堆中的下标

		std::swap(lhs,rhs);//交换原图在最小堆中的位置
	}
private:
	vector<pt_g>heap;//作为最小堆只需要节点的名称和权重就可以，但为了方便就直接拷贝了
	vector<pt_g>&graph;//作为原图的引用当全局变量使用
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
		cout << "关于dijkstra的另一种证明，对于选取堆中最小值作为最优解的另一个解释是如果经过另一各路径到达\n"
			<< "该点，必然会经过最小堆中不为∞的某一点，而这些点的权重都比该点大，而后面没有负权重，所以选择该点是最优解\n"
			<< endl;
		min_heap heap(graph, start);

		while (!heap.empty()) {
			int u = heap.extract_min();

			auto curr = graph[u]->next;
			while (curr) {
				relax(u, curr->key, curr->weight,heap);

				print();//为24.3-1准备

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
			heap.decrease_key(graph[v]->index, weight + graph[u]->weight);//减小最小堆中的键值
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
		cout << "dijkstra采用的是贪心算法，先选择了局部最优解，对于局部之外如果存在负值局部最优解就不是全局最优解"
			<< endl;
	}
};

class solution24_3_3 {
public:
	void operator()() {
		cout << "正确，最后一点已经确定不用松弛"
			<< endl;
	}
};

class solution24_3_5 {
public:
	void operator()() {
		cout << "图24-6已经说明"
			<< endl;
	}
};

class solution24_3_6 {
public:
	void operator()() {
		cout << "采用类似dijkstra算法，将松弛改为乘法和大于号，将最小堆改为最大堆\n"
			<< "对于贪心算法的证明，类似我对dijkstra的另一种证明，因为0<=r<=1,经过堆中其它节点的路径一定比\n"
			<< "贪心算法的路径小\n"
			<< endl;
	}
};

class solution24_3_8 {
public:
	void operator()() {
		cout << "因为d[u]的值不超过(|V|-1)*W，使用这么大的链表记录d的值。\n"
			<< "V次找最小值最多用(|V|-1)*W，每次decrease-key用O(1)时间。总共时间O(WV+E)。"
			<< endl;
	}
};

class solution24_3_9 {
public:
	void operator()() {
		cout << "veb树"
			<< endl;
	}
};

class solution24_3_10 {
public:
	void operator()() {
		cout << "使用我上面的另一种证明方式,无关最初的权重"
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
		cout << "无可行解" << endl;
	}
};

class solution24_4_3 {
public:
	void operator()() {
		cout << "不可能，因为v0直接到各节点的权重为0"
			<< endl;
	}
};

class solution24_4_4 {
public:
	void operator()() {
		cout << "转换为单源最短路问题，对于可能有环又可能有负值的图可能必须访问每一个节点"
			<< endl;
	}
};

class solution24_4_5 {
public:
	void operator()() {
		cout << "不添加v0,将所有节点的权重初始化为0，因为必定有一个节点的权重的最短路径为0，使用bellman_ford \n"
			<< "松弛mn次"
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

//思考题



#endif