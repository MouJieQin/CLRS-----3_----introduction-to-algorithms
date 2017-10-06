#pragma once
#ifndef _SOLUTION_23_H_
#define _SOLUTION_23_H_
#include<iostream>
#include<vector>
#include<memory>
#include<map>
using namespace std;

class solution23_1_1 {
public:
	void operator()() {
		cout << "将u作为集合s切割"
			<< endl;
	}
};

class solution23_1_3 {
public:
	void operator()() {
		cout << "如果不是轻量级边可以用轻量级边取代它，生成一个更小的最小生成树与假设矛盾"
			<< endl;
	}
};

class solution23_1_5 {
public:
	void operator()() {
		cout << "环路不需要最大权重边联通"
			<< endl;
	}
};

class solution23_1_6 {
public:
	void operator()() {
		cout << "每次都取唯一轻量级边才能生成最小生成树T,不然生成的树没有T小\n"
			<< "对于只存在三个节点的连通图，两条边的权重相同，第一次选取的是中间连接另外两个节点的节点"
			<< endl;
	}
};

class solution23_1_7{
public:
	void operator()() {
		cout << "对于正权重，如果集合中如果有环，可与去掉环路上最大权重的边，集合仍然联通且权重减少，所以最小权重集合没有环\n"
			<< "对于负权重，如果原图中的环都是负权重，同理最小权重集合一定有环"
			<< endl;
	}
};

class solution23_1_8 {
public:
	void operator()() {
		cout << "假设不是，T'的权重表必定至少有一个权重值比T中的大，而T中有一个对应连接两个连通图的轻量级边\n"
			<< "和T'是最小生成树矛盾"
			<< endl;
	}
};

class solution23_1_9 {
public:
	void operator()() {
		cout << "减少权重后仍然是最轻量边"
			<< endl;
	}
};

class solution23_1_10 {
public:
	void operator()() {
		cout << "找到T中从u到v的最后一条边，如果该边的权重大于减少后的权重，换之"
			<< endl;
	}
};

class solution23_2_1 {
public:
	void operator()() {
		cout << "稳定排序，如快排，插入"
			<< endl;
	}
};

class solution23_2_2 {
public:
	void operator()() {
		cout << "将邻接矩阵扫描进优先队列即可"
			<< endl;
	}
};

class solution23_2_3 {
public:
	void operator()() {
		cout << "斐波那契堆当图稠密时运行更快,|E|=Θ(V^(1+ε）），0<ε<=1"
			<< endl;
	}
};

class solution23_2_4 {
public:
	void operator()() {
		cout << "使用计数排序将常数系数减少"
			<< endl;
	}
};

class solution23_2_6 {
public:
	void operator()() {
		cout << "桶排序，kruskal减少到Eα（V)"
			<< endl;
	}
};

class solution23_2_7 {
public:
	void operator()() {
		cout << "首先选择新加入的最小边将新加入的节点加进最小生成树，\n"
			<< "然后检测每一个与新加入的节点相连的节点v，检测v每一个在生成树中的与其相连的节点的边e的权重\n"
			<< "如果大于新加入的边，如果断开e后的节点v与新节点不在同一连通分量中用新边代替e"
			<<"最多检测O(|v|)条边，运行时间为O(|v|)"
			<< endl;
	}
};

class solution23_2_8 {
public:
	void operator()() {
		cout << "不正确，连接两个最小树的只能是一条边，对于某个最小树的某个节点，可能横跨切割的边才属于整体真正的最小树"
			<< endl;
	}
};
////////////////////////

struct edge {
	edge(int u, int v, int weight) :
		u(u), v(v), weight(weight) {}
	bool operator<(const edge&rhs) { return weight < rhs.weight; }
	int u;
	int v;
	int weight;
}; 
struct graphNode;
typedef shared_ptr<graphNode>pt_g;

struct graphNode {
	graphNode(int u, int v, int weight,pt_g n=nullptr) :
		u(u), v(v), weight(weight),next(n) {}
	bool operator<(const edge&rhs) { return weight < rhs.weight; }
	int u;
	int v;
	int weight;
	pt_g next;
};

struct rnode;
typedef shared_ptr<rnode> pt_rnode;
struct rnode {
	rnode(int key, int rank = 0, pt_rnode p = nullptr, pt_rnode b = nullptr) :
		key(key), rank(rank), p(p), b(b) {}
	int key;
	int rank;
	pt_rnode p;
	pt_rnode b;/////////////
};

class disjoint_forest {
public:
	void make_set(int k) {
			mp.insert(make_pair(k,
				shared_ptr<rnode>(new rnode(k))));
			mp[k]->p = mp[k];
			mp[k]->b = mp[k];//////////////
	}
	void union_set(pt_rnode& lef, pt_rnode& righ) {
			if (lef->rank > righ->rank) {
				righ->p = lef;

				auto temp = righ->b;
				righ->b = lef->b;/////
				lef->b = temp;/////////////
			}
			else {
				auto temp = lef->b;
				lef->b = righ->b;
				righ->b = temp;

				lef->p = righ;
				if (lef->rank = righ->rank)
					righ->rank += 1;
			}
	}
	/*pt_rnode find_set(int k) {
	if (mp[k]->p != mp[k])
	mp[k]->p = find_set(mp[k]->p->key);
	return mp[k]->p;
	}*/
	pt_rnode find_set(int k) {
		auto t = mp[k];
		auto curr = t;
		while (curr != curr->p)
			curr = curr->p;
		while (t != curr) {
			t->p = curr;
			t = t->p;
		}
		return curr;
	}
	void print_set(pt_rnode rt, pt_rnode root) {
		if (rt != root)
			print_set(rt->b, root);

		cout << static_cast<char>(rt->key) << "\t";
	}
private:
	map<int, pt_rnode>mp;
};

class mst_kruskal{
public:
	mst_kruskal(vector<edge>&vect,int max):edges(vect){
		for (int i=1;i<=max;++i)
			disjoint_set.make_set(i);

		sort(edges.begin(), edges.end());
	}
	void operator()() {
		vector<edge>mst; 
		for (auto &i : edges) {
			auto lef = disjoint_set.find_set(i.u);
			auto righ = disjoint_set.find_set(i.v);
			if (lef != righ) {
				disjoint_set.union_set(lef, righ);
				mst.push_back(edge(i));
			}
		}
		for (auto &i : mst)
			cout << "(　" << i.u << " " << i.v << " )" << i.weight << endl;
	}

private:
	vector<edge>edges;
	disjoint_forest disjoint_set;
};

class test_kruskal {
public:
	void operator()() {
		vector<edge>vect{
			{1,2,4},{1,8,8},{2,8,11},{2,3,8},{8,9,7},{8,7,1},{3,9,2},{3,4,7},{3,6,4},
			{7,9,6},{7,6,2},{4,5,9},{4,6,14},{5,6,10}
		};
		mst_kruskal mst(vect,9);
		mst();
	}
};
////////////////////////////
//class heap {
//public:
//	heap(int max){
//		for (int i = 1; i <= max;++max) {
//			mp.insert({ i, edge(INT_MIN,i,INT_MAX) });
//			hp.push_back(i);
//		}
//		mp[1].weight = 0;
//	}
//	void bulid_min_heap() {
//		size_t s = hp.size() - 1;
//		for (size_t i = (s-1) / 2; i != 0;--i) {
//			min_heapify(i);
//		}
//	}
//	size_t parent(int k) { return (k-1) / 2; }
//	size_t left(int k) { return 2 * k+1 ; }
//	size_t right(int k) { return 2 * k + 2; }
//	void min_heapify(int k) {
//		auto lef = left(k);
//		auto righ = right(k);
//		size_t smallest = k;
//		if (lef < hp.size() && mp[hp[lef]]< mp[hp[k]]) {
//			smallest = lef;
//		}
//		if (righ < hp.size() && mp[hp[righ]] < mp[hp[k]]) {
//			smallest = righ;
//		}
//		if (smallest != k) {
//			swap(hp[smallest], hp[k]);
//			min_heapify(k);
//		}
//	}
//	size_t extract_min() {
//		int min = mp[hp[0]].v;
//
//		hp[0] = hp.back();
//		hp.pop_back();
//		min_heapify(0);
//	}
//	void heap_decrease(int k, int key) {
//		mp[hp[k]].weight = key;
//
//		while (k > 0 && mp[hp[k]] < mp[hp[parent(k)]]) {
//			swap(hp[parent(k)], hp[k]);
//			k = parent(k);
//		}
//	}
//	void  belong_and_less(int k,int weight) {
//
//		if (mp.find(k) != mp.end()&&weight<mp[k].weight) {
//			mp[k].weight = weight;
//		}
//	}
//	bool nonempty() {
//		return !hp.empty();
//	}
//private:
//	map<size_t, edge>mp;
//	vector<int>hp;
//};
//
//class mst_prim {
//public:
//	void operator()() {
//		vector<edge>vect{
//			{ 1,2,4 },{ 1,8,8 },{ 2,8,11 },{ 2,3,8 },{ 8,9,7 },{ 8,7,1 },{ 3,9,2 },{ 3,4,7 },{ 3,6,4 },
//			{ 7,9,6 },{ 7,6,2 },{ 4,5,9 },{ 4,6,14 },{ 5,6,10 }
//		};
//		heap hp(14);
//		vector<pt_g>graph(15);
//		for (auto &i : vect) {
//			auto t = shared_ptr<graphNode>(new graphNode(i.u, i.v, i.weight, graph[i.u]->next));
//			graph[i.u]->next = t;
//		}
//		while (hp.nonempty()) {
//			int e = hp.extract_min();
//			
//			auto curr = graph[e]->next;
//			while (curr) {
//				int  k = curr->v;
//
//			//	if()
//			}
//		}
//
//	}
//
//};

#endif
