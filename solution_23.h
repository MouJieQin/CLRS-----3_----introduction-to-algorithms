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
		cout << "��u��Ϊ����s�и�"
			<< endl;
	}
};

class solution23_1_3 {
public:
	void operator()() {
		cout << "��������������߿�������������ȡ����������һ����С����С�����������ì��"
			<< endl;
	}
};

class solution23_1_5 {
public:
	void operator()() {
		cout << "��·����Ҫ���Ȩ�ر���ͨ"
			<< endl;
	}
};

class solution23_1_6 {
public:
	void operator()() {
		cout << "ÿ�ζ�ȡΨһ�������߲���������С������T,��Ȼ���ɵ���û��TС\n"
			<< "����ֻ���������ڵ����ͨͼ�������ߵ�Ȩ����ͬ����һ��ѡȡ�����м��������������ڵ�Ľڵ�"
			<< endl;
	}
};

class solution23_1_7{
public:
	void operator()() {
		cout << "������Ȩ�أ��������������л�������ȥ����·�����Ȩ�صıߣ�������Ȼ��ͨ��Ȩ�ؼ��٣�������СȨ�ؼ���û�л�\n"
			<< "���ڸ�Ȩ�أ����ԭͼ�еĻ����Ǹ�Ȩ�أ�ͬ����СȨ�ؼ���һ���л�"
			<< endl;
	}
};

class solution23_1_8 {
public:
	void operator()() {
		cout << "���費�ǣ�T'��Ȩ�ر�ض�������һ��Ȩ��ֵ��T�еĴ󣬶�T����һ����Ӧ����������ͨͼ����������\n"
			<< "��T'����С������ì��"
			<< endl;
	}
};

class solution23_1_9 {
public:
	void operator()() {
		cout << "����Ȩ�غ���Ȼ����������"
			<< endl;
	}
};

class solution23_1_10 {
public:
	void operator()() {
		cout << "�ҵ�T�д�u��v�����һ���ߣ�����ñߵ�Ȩ�ش��ڼ��ٺ��Ȩ�أ���֮"
			<< endl;
	}
};

class solution23_2_1 {
public:
	void operator()() {
		cout << "�ȶ���������ţ�����"
			<< endl;
	}
};

class solution23_2_2 {
public:
	void operator()() {
		cout << "���ڽӾ���ɨ������ȶ��м���"
			<< endl;
	}
};

class solution23_2_3 {
public:
	void operator()() {
		cout << "쳲������ѵ�ͼ����ʱ���и���,|E|=��(V^(1+�ţ�����0<��<=1"
			<< endl;
	}
};

class solution23_2_4 {
public:
	void operator()() {
		cout << "ʹ�ü������򽫳���ϵ������"
			<< endl;
	}
};

class solution23_2_6 {
public:
	void operator()() {
		cout << "Ͱ����kruskal���ٵ�E����V)"
			<< endl;
	}
};

class solution23_2_7 {
public:
	void operator()() {
		cout << "����ѡ���¼������С�߽��¼���Ľڵ�ӽ���С��������\n"
			<< "Ȼ����ÿһ�����¼���Ľڵ������Ľڵ�v�����vÿһ�����������е����������Ľڵ�ı�e��Ȩ��\n"
			<< "��������¼���ıߣ�����Ͽ�e��Ľڵ�v���½ڵ㲻��ͬһ��ͨ���������±ߴ���e"
			<<"�����O(|v|)���ߣ�����ʱ��ΪO(|v|)"
			<< endl;
	}
};

class solution23_2_8 {
public:
	void operator()() {
		cout << "����ȷ������������С����ֻ����һ���ߣ�����ĳ����С����ĳ���ڵ㣬���ܺ���и�ı߲�����������������С��"
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
			cout << "(��" << i.u << " " << i.v << " )" << i.weight << endl;
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
