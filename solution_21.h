#pragma once
#ifndef _SOLUTION_21_H_
#define _SOLUTION_21_H_
#include<iostream>
#include<vector>
#include<memory>
#include<map>
using namespace std;

class solution21_1_2 {
public:
	void operator()() {
		cout << "connected-components保证了两个顶点所在集合能够合并当且仅当\n"
			<<"两个顶点所在集合不是同一个集合并且这两个顶点有边相连\n"
			<<"循环不变式保证了初始时每个集合都能到达自身，所以是联通的，所以每次合并前两个集合都是联通的\n"
			<<"合并后的集合本身是联通的"
			<< endl;
	}
};

class solution21_1_3 {
public:
	void operator()() {
		cout << "2|E|,每个联通分量顶点的个数即|V|-k,也就是一个联通分量的联合次数为能把其所有|V|个顶点都联通的\n"
			<<"最少条边数，即|V|-1,假设所有顶点都在一个联通分量中为|V|-1，两个为|V|-2，以此类推"
			<< endl;
	}
};
//////////////////////////
struct node;
typedef shared_ptr<node> pt_node;
struct set {
	set(size_t s,pt_node h = nullptr,pt_node t = nullptr ):
		head(h),tail(t),size(s){}
	size_t size;
	pt_node head;
	pt_node tail;
};
typedef shared_ptr<set>pt_set;

struct node {
	node(int k,pt_set h=nullptr, pt_node t=nullptr) :
		head(h), next(t), key(k) {};
	int key;
	pt_set head;
	pt_node next;
};

class disjoint_set {
public:
	void make_set(int key) {
		auto n = shared_ptr<node>(new node(key));
		auto s = shared_ptr<set>(new set(1, n, n));
		n->head = s;
		mp.insert(make_pair(key, n));
	}
	int find_set(int key) {
		return
			mp[key]->head->head->key;
	}
	void union_set(int lef,int righ) {
		auto lhs = mp[lef]->head;
		auto rhs = mp[righ]->head;
		if (lhs->size > rhs->size)
			lhs.swap(rhs);

		auto curr = lhs->head;
		auto temp = curr;
		while (curr) {
			temp = curr->next;
			curr->head = rhs;
			curr->next = rhs->head;
			rhs->head = curr;
			curr = temp;
		}
		rhs->size += lhs->size;
		lhs = nullptr;
	}
	void print(int key) {
		auto head = mp[key]->head->head;
		while (head) {
			cout << static_cast<char>(head->key) << "\t";
			head = head->next;
		}
		cout << endl;
	}

private:
	map<int, pt_node>mp;
};

class solution21_2_1 {
public:
	void operator()() {
		vector<vector<int>>vect{{'a','b','c','d'},{'e','g','f'}
		,{'h','i'},{'j'} };

		for (auto &i : vect) 
			for (auto j : i) 
				set.make_set(j);

		for (auto &i : vect)
			for (size_t j = 1; j < i.size(); ++j)
				if (set.find_set(i[j]) != set.find_set(i[j - 1]))
					set.union_set(i[j], i[j - 1]);

		for (auto &i : vect)
			set.print(i.front());

	}
private:
	disjoint_set set;
};

class solution21_2_4 {
public:
	void operator()() {
		cout << "Θ（m),每个操作都是O(1）"
			<< endl;
	}
};

class solution22_2_5 {
public:
	void operator()() {
		cout << "可以看到我上面的主要算法中没有tail,下一题同此"
			<< endl;
	}
};
//////////////////////
struct rnode;
typedef shared_ptr<rnode> pt_rnode;
struct rnode {
	rnode(int key, int rank = 0, pt_rnode p = nullptr,pt_rnode b=nullptr) :
		key(key), rank(rank), p(p),b(b) {}
	int key;
	int rank;
	pt_rnode p;
	pt_rnode b;/////////////为打印准备的兄弟节点
};

class disjoint_forest {
public:
	void make_set(int k) {
		mp.insert(make_pair(k,
			shared_ptr<rnode>(new rnode(k))));
		mp[k]->p = mp[k];
		mp[k]->b = mp[k];//////////////
	}
	void union_set(int lhs, int rhs) {
		auto lef = find_set(lhs);
		auto righ = find_set(rhs);
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
	void print_set(pt_rnode rt,pt_rnode root) {
		if (rt!=root) 
			print_set(rt->b,root);

		cout << static_cast<char>(rt->key) << "\t";
	}
private:
	map<int, pt_rnode>mp;
};
////
class solution21_3_2 {
public:
	void operator()() {
		vector<vector<int>>vect{ { 'a','b','c','d' },{ 'e','g','f' }
		,{ 'h','i' },{ 'j' } };

		for (auto &i : vect)
			for (auto j : i)
				set.make_set(j);

		for (auto &i : vect)
			for (size_t j = 1; j < i.size(); ++j)
				if (set.find_set(i[j]) != set.find_set(i[j - 1]))
					set.union_set(i[j], i[j - 1]);

		for(auto &i:vect)
			for (auto j : i) {//打印每个节点的父节点
				cout << static_cast<char>(j) << "→" << static_cast<char>(set.find_set(j)->key) << endl;
			}
		for (auto &i : vect) {
			set.print_set(set.find_set(i.front())->b, set.find_set(i.front()));
			cout << endl;
		}
	}
private:
	disjoint_forest set;
};

class solution21_3_3 {
public:
	void operator()() {
		cout << "前n个是make_set操作，然后是n-1个union操作，且2,4,8,16为合并后集合的元素个数合并\n"
			<< "并且合并时给find_set的两个参数都是根节点，所以不会改变原集合的秩\n"
			<< "树的高度有递归式h(n)=h(n/2)+1,h(n)=Ω（lgn),之后调用find_set\n"
			<< "最坏情况下花费树的高度lgn"
			<< endl;
	}
};

class solution21_3_4 {
public:
	void operator()() {
		cout << "程序如上，每个节点加上一个指针b,指向每一个集合的\n"
			<< "最下面的一个元素，合并时更新\n"
			<< "使用归纳法容易论证基本情况成立，合并前每一个集合都\n"
			<< "可以打印，合并后的集合也可以打印\n"
			<< "每个节点访问一次所以为O(1)"
			<< endl;
	}
};



#endif