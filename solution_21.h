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
		cout << "connected-components��֤�������������ڼ����ܹ��ϲ����ҽ���\n"
			<<"�����������ڼ��ϲ���ͬһ�����ϲ��������������б�����\n"
			<<"ѭ������ʽ��֤�˳�ʼʱÿ�����϶��ܵ���������������ͨ�ģ�����ÿ�κϲ�ǰ�������϶�����ͨ��\n"
			<<"�ϲ���ļ��ϱ�������ͨ��"
			<< endl;
	}
};

class solution21_1_3 {
public:
	void operator()() {
		cout << "2|E|,ÿ����ͨ��������ĸ�����|V|-k,Ҳ����һ����ͨ���������ϴ���Ϊ�ܰ�������|V|�����㶼��ͨ��\n"
			<<"��������������|V|-1,�������ж��㶼��һ����ͨ������Ϊ|V|-1������Ϊ|V|-2���Դ�����"
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
		cout << "����m),ÿ����������O(1��"
			<< endl;
	}
};

class solution22_2_5 {
public:
	void operator()() {
		cout << "���Կ������������Ҫ�㷨��û��tail,��һ��ͬ��"
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
	pt_rnode b;/////////////Ϊ��ӡ׼�����ֵܽڵ�
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
			for (auto j : i) {//��ӡÿ���ڵ�ĸ��ڵ�
				cout << static_cast<char>(j) << "��" << static_cast<char>(set.find_set(j)->key) << endl;
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
		cout << "ǰn����make_set������Ȼ����n-1��union��������2,4,8,16Ϊ�ϲ��󼯺ϵ�Ԫ�ظ����ϲ�\n"
			<< "���Һϲ�ʱ��find_set�������������Ǹ��ڵ㣬���Բ���ı�ԭ���ϵ���\n"
			<< "���ĸ߶��еݹ�ʽh(n)=h(n/2)+1,h(n)=����lgn),֮�����find_set\n"
			<< "�����»������ĸ߶�lgn"
			<< endl;
	}
};

class solution21_3_4 {
public:
	void operator()() {
		cout << "�������ϣ�ÿ���ڵ����һ��ָ��b,ָ��ÿһ�����ϵ�\n"
			<< "�������һ��Ԫ�أ��ϲ�ʱ����\n"
			<< "ʹ�ù��ɷ�������֤��������������ϲ�ǰÿһ�����϶�\n"
			<< "���Դ�ӡ���ϲ���ļ���Ҳ���Դ�ӡ\n"
			<< "ÿ���ڵ����һ������ΪO(1)"
			<< endl;
	}
};



#endif