#pragma once
#ifndef _SOLUTION_19_H_
#define _SOLUTION_19_H_
#include<iostream>
#include<vector>
#include<memory>
#include<cmath>
using namespace std;

/////////////////////////////
struct fibNode;
typedef shared_ptr<fibNode> pt_fib;
struct fibNode {
	fibNode(int k, bool m = false, int d = 0,pt_fib par=nullptr,
		pt_fib lef=nullptr,pt_fib righ=nullptr,pt_fib ch=nullptr):
	key(k),mark(m),degree(d),p(par),left(lef),right(righ),child(ch){}
	int key;
	bool mark;
	int degree;
	pt_fib p;
	pt_fib left;
	pt_fib right;
	pt_fib child;
};

class fib_heap {
public:
	fib_heap():n(0),min(nullptr){}
	void fib_heap_insert(int key) {
		pt_fib tar = shared_ptr<fibNode>(new fibNode(key));
		if (!min) {
			tar->left = tar;
			tar->right = tar;
			min = tar;

		}
		else {
			insert_root_list(tar);
			if (min->key > tar -> key)
				min = tar;
		}	
		n += 1;
	}
	void insert_root_list(pt_fib tar) {
		auto righ = min->right;
		min->right = tar;
		tar->left = min;

		tar->right = righ;
		righ->left = tar;
	}

	pt_fib minimum() { return min; }

	fib_heap fib_union(fib_heap &lhs, fib_heap &rhs) {//这个程序没有测试过
		fib_heap result;
		if (!lhs.min) {
			result.min = rhs.min;
			result.n = rhs.n;
		}
		else if(!rhs.min){
			result.min = lhs.min;
			result.n = lhs.n;
		}
		else {
			auto lhs_next = lhs.min->right;
			auto rhs_next = rhs.min->right;

			lhs.min->right = rhs.min;
			rhs.min->left = lhs.min;

			rhs_next->right = lhs_next;
			lhs_next->left = rhs_next;

			result.n = rhs.n + lhs.n;
			result.min = lhs.min->key < rhs.min->key ? lhs.min : rhs.min;
		}

		rhs.min = nullptr;
		lhs.min = nullptr;
		rhs.n = 0;
		lhs.n = 0;

		return result;
	}

	pt_fib fib_heap_extract_min() {
		pt_fib result = min;

		if (result) {
			auto ch = result->child;

			if (ch) {
				do {
					ch->p = nullptr;
					auto temp = ch->right;
					insert_root_list(ch);
					ch = temp;
				} while (ch != result->child);
			}

			out_of_list(result);

			if (result == result->right)
				min = nullptr;
			else {
				min = min->right;
				consolidate();
			}
			n -= 1;
		}

		return result;
	}
	
	void consolidate() {
		vector<pt_fib>vect(static_cast<int>(log(n)/log(1.618)) + 1, nullptr);
		auto temp = min;

		vector<pt_fib>v_root;
		v_root.push_back(temp);

		for (auto t = temp->right; t != min; t = t->right)
			v_root.push_back(t);

		for (auto next : v_root) {
			int d = next->degree;
			while (vect[d]) {	
				if (next->key > vect[d]->key)
					swap(next, vect[d]);
				fib_heap_link(next, vect[d]);
				vect[d] = nullptr;
				d += 1;
			}
			vect[d] = next;
		}
		min = nullptr;

		for (auto i : vect) {
			if (i) {
				if (!min) {
					min = i;
					min->left = min;
					min->right = min;
				}
				else {
					insert_root_list(i);
					if (i->key < min->key)
						min = i;
				}
			}
		}
	}

	void out_of_list(pt_fib tar) {
		if (tar == tar->right) {
			if (tar->p)
				tar->p->child = nullptr;
			else 
				min = nullptr;
			return;
		}
		else {
			if(tar->p)
				tar->p->child = tar->right;
		}
		auto lef = tar->left;
		auto righ = tar->right;
		lef->right = righ;
		righ->left = lef;
	}

	void fib_heap_link(pt_fib par, pt_fib ch) {
		out_of_list(ch);

		auto c = par->child;
		if (!c) {
			par->child = ch;
			ch->left = ch;
			ch->right = ch;
		}
		else {
			auto next = c->right;

			c->right = ch;
			ch->left = c;

			ch->right = next;
			next->left = ch;

		}

		ch->p = par;
		par->degree += 1;
	}
	void fib_heap_decrease_key(pt_fib tar, int k) {
		if (k > tar->key) {
			cout << "k比原来的关键字大" << endl;
			return;
		}
		tar->key = k;
		auto par = tar->p;
		if (par&&par->key > k) {
			cut(tar);
			cascading_cut(par);
		}
		if (k < min->key)
			min = tar;
	}
	
	void cut(pt_fib tar) {
		tar->p->degree -= 1;
		tar->mark = false;
		out_of_list(tar);
		tar->p = nullptr;
		insert_root_list(tar);
	}

	void cascading_cut(pt_fib tar) {
		auto par = tar->p;
		if (par) {
			if (!par->mark) {
				par->mark = true;
			}
			else {
				cut(tar);
				cascading_cut(par);
			}
		}
	}
	void fib_heap_delete(pt_fib tar) {
		fib_heap_decrease_key(tar, INT_MIN);
		fib_heap_extract_min();
	}
	void print(pt_fib rt,int counter=0) {
		if (rt) {
			auto next = rt;
			do {
				print(next->child, counter + 1);

				cout << "\n" << endl;
				for (int n = counter; n != -1; --n)
					cout << "\t";
				cout << next->key << "|";
				next->mark ? cout << "T" : cout << "F" << endl;

				next = next->right;
			} while (next != rt);
		}
	}
private:
	pt_fib min;
	int n;
};
/////////////////////////////////////
class solution19_2_1 {
public:
	void operator()() {
		vector<int>vect{ 23,3,7,17,24,18,52,38,30,26,46,39,41,35 };
		cout << "\n-----------------------------------------\n";
		cout << "插入中..." << endl;
		for (auto i : vect) {
			fib.fib_heap_insert(i);
			fib.print(fib.minimum());
			cout << "\n-----------------------------------------\n";
		}

		int n = vect.size();
		while (n) {
			auto t = fib.fib_heap_extract_min();
			if(t)
				cout << "提取最小值为" << t->key << endl;
			fib.print(fib.minimum());
			cout << "\n-----------------------------------------\n";
			--n;
		}
		cout << "假设打印出来每个节点在坐标系中，具有相同x坐标的在同一深度\n"
			<< "深度相同的两节点之间的所有节点为具有较小y坐标的节点的孩子\n"
			<< endl;
	}
private:
	fib_heap fib;
};

class solution19_3_1 {
public:
	void operator()() {
		cout<<"A root in the heap became marked because it at some point had a child"
			<<"whose key was decreased.It doesn’t add the potential for having to do any"
			<< "more actual work for it to be marked.This is because the only time that"
			<< "markedness is checked is in line 3 of cascading cut.This however is only ever"
			<< "run on nodes whose parent is non NIL.Since every root has NIL as it parent,"
			<< "line 3 of cascading cut will never be run on this marked root.It will still cause"
			<< "the potential function to be larger than needed, but that extra computation"
			<< "that was paid in to get the potential function higher will never be used up later."
			
	}
};

class solution19_3_2 {
public:
	void operator()() {
		cout << "每次的操作运行时间是consolidate的迭代次数，每次迭代\n"
			<< "都至少会有一个节点进入根链表，当所有节点都进入根链表后\n"
			<< "该操作的运行时间为O(1)，所以n次操作的总运行时间为O(n),\n"
			<< "平摊每次运行时间为O(1)"
			<< endl;
	}
};

class solution19_4_1 {
public:
	void operator()() {
		cout << "从空堆开始，n个操作都只是插入元素"
			<< endl;
	}
};

class solution19_4_2 {
public:
	void operator()() {
		cout << "常数"
			<< endl;
	}
};
#endif
