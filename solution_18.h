#pragma once
#ifndef _SOLUTION_18_H
#define _SOLUTION_18_H
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class solution18_1_1 {
public:
	void operator()() {
		cout << "孩子数为1变成链表"
			<< endl;
	}
};

class solution18_1_2 {
public:
	void operator()() {
		cout << "t=2,3"
			<< endl;
	}
};

class solution18_1_4 {
public:
	void operator()() {
		cout << "(2t)^(i+1)-1"
			<< endl;
	}
};

class solution18_1_5 {
public:
	void operator()() {
		cout << "每个黑色节点可能有1,2个红色节点，所以吸收每个节点可能有\n"
			<< "2,3个关键字，所以是2-3树"
			<< endl; 
	}
};
////////////////////////
struct bNode;
typedef shared_ptr<bNode> pt_b;
struct bNode {
	int n;
	bool leaf;
	vector<int>key;
	vector<pt_b>c;
};

class b_tree {
public:
	b_tree(int t=2):t(t){}
	void b_tree_spilt_child(pt_b x, int i) {
		auto y = x->c[i];

		x->key.resize(x->n + 1);
		for (int j = x->n-1; j >= i; --j)
			x->key[j + 1] = x->key[j];
		x->key[i] = y->key[t - 1];
	//	cout << "flag" << endl;////////////////////

		auto z = shared_ptr<bNode>(new bNode);
		z->n = t - 1;
		z->leaf = y->leaf;
		z->key.resize(t - 1);
		for (int j = 0; j < t - 1; ++j)
			z->key[j] = y->key[j + t];

		if (!y->leaf) {
			z->c.resize(t);
			for (int j = 0; j < t; ++j)
				z->c[j] = y->c[j + t];
			y->c.resize(t);
		}

		y->key.resize(t - 1);
		y->n = t - 1;

		x->c.resize(x->n + 2);
		for (int j = x->n; j > i; --j)
			x->c[j + 1] = x->c[j];
		x->c[i + 1] = z;
		x->n += 1;
		disk_write("x");
		disk_write("y");
		disk_write("z");
	}
	void b_tree_insert(int k) {
		auto rt = root;
		if (!root) {
			auto t = shared_ptr<bNode>(new bNode);
			root = t;
			t->key.push_back(k);
			t->n = 1;
			t->leaf = true;
			return;
		}
		if (rt->n == 2 * t - 1) {
			auto t = shared_ptr<bNode>(new bNode);
			root = t;
			t->n = 0;
			t->leaf = false;
			t->c.push_back(rt);
			b_tree_spilt_child(t, 0);
			b_tree_insert_nonfull(t, k);
		}
		else
			b_tree_insert_nonfull(rt, k);
	}
	void b_tree_insert_nonfull(pt_b rt, int k) {
		int i = rt->n-1;
		if (rt->leaf) {
			rt->n += 1;
			rt->key.resize(rt->n);
			while (i >= 0 && k < rt->key[i]) {
				rt->key[i + 1] = rt->key[i];
				--i;
			}
			rt->key[i + 1] = k;
			disk_write("rt");
		}
		else {
			while (i >= 0 && k < rt->key[i])
				--i;
			i += 1;
			disk_read("ci");
			if (rt->c[i]->n == 2 * t - 1) {
				b_tree_spilt_child(rt, i);
				if (rt->key[i] < k)
					i += 1;
			}
			b_tree_insert_nonfull(rt->c[i], k);
		}
	}
	pt_b maxiumn(pt_b rt) {//返回接受根节点的最小值所在
		if (rt->leaf)
			return rt;
		else
			return maxiumn(rt->c.back());
	}
	pt_b miniumn(pt_b rt) {
		if (rt->leaf)
			return rt;
		else
			return miniumn(rt->c.front());
	}
	void b_tree_merge(pt_b rt, int i) {//合并rt[i]和rt[i+1]
		auto pre = rt->c[i];//由于情况限制，两个节点的关键字大小都为t-1
		auto suc = rt->c[i + 1];
		pre->key.resize(2 * t - 1);
		pre->n = 2 * t - 1;
		for (int j = 0; j < t - 1; ++j)
			pre->key[j + t] = suc->key[j];
		pre->key[t - 1] = rt->key[i];

		if (!pre->leaf) {
			pre->c.resize(2 * t);
			for (int j = 0; j < t; ++j)
				pre->c[j + t] = suc->c[j];
		}
		suc.~suc();
		for (int j = i; j < rt->n-1; ++j) 
			rt->key[j] = rt->key[j + 1];
		rt->key.resize(rt->n - 1);

		for (int j = i + 1; j < rt->n; ++j)
			rt->c[j] = rt->c[j + 1];
		rt->n -= 1;
		rt->c.resize(rt->n+1);
	}

	void b_tree_delete(pt_b rt, int k) {
		if (!rt)
			return;
		if (rt == root && (!rt->n)) {
			if (rt->c.empty())//树中已空
				return;
			root = rt->c[0];
			rt = root;
		}
		int i = rt->n-1;
		while (i >= 0 && rt->key[i] > k)//找到不大于k的下标
			--i;

		if (rt->leaf && (i < 0 || rt->key[i] != k))//关键字不在树中
			return;

		if (i>=0&&rt->key[i] == k) {//该节点含有关键字
			if (rt->leaf) {//叶节点直接删除，因为递归的关系，叶节点的n一定大于t-1
				for (int j = i; j < rt->n - 1; ++j)
					rt->key[j] = rt->key[j + 1];
				rt->n -= 1;
				rt->key.resize(rt->n);
			}
			else {//关键字在内部节点		
		
				if (rt->c[i]->n > t - 1) {//前一个节点的n大于t-1，找到该关键字的前驱，并递归删除，前驱一定在叶节点中
					auto pre = maxiumn(rt->c[i]);//用前驱替代关键字，后继同理
					int pre_key = pre->key.back();
					b_tree_delete(root, pre_key);
					rt->key[i] = pre_key;
				}
				else if (rt->c[i + 1]->n > t - 1) {//后一个节点的n大于t-1
					auto suc = miniumn(rt->c[i + 1]);
					int suc_key = suc->key.front();
					b_tree_delete(root, suc_key);
					rt->key[i] = suc_key;
				}
				else {//合并前后节点，此时关键字进入前一个节点，递归删除
					b_tree_merge(rt, i);
					b_tree_delete(rt->c[i], k);
				}
			}
		}
		else {//当前节点不包含关键字
			i += 1;
			auto tar = rt->c[i];//关键字所在子树的根节点，如果关键字在树中的话
			
			if (tar->n > t - 1)//根节点的n大于t-1
				b_tree_delete(tar, k);
			else {//根节点的n小于等于t-1
				if (!i) {//i=0,没有前驱节点，下面的前驱是解决点而不是关键字
					auto suc = rt->c[i + 1];
					if (suc->n > t - 1) {//前节点n大于t-1
						left_replace(rt, i);//为书中的3a情况之一
						b_tree_delete(rt->c[i], k);
					}
					else {//前驱n<=t-1,合并
						b_tree_merge(rt, i);
						b_tree_delete(rt->c[i], k);
					}
				}
				else if (i == rt->n) {//没有后继节点，
					auto pre = rt->c[i-1];
					if (pre->n > t - 1) {
						right_replace(rt, i);
						b_tree_delete(rt->c[i], k);
					}
					else {
						b_tree_merge(rt, i - 1);
						b_tree_delete(rt->c[i-1], k);
					}
				}
				else {//有前驱和后继节点
					auto suc = rt->c[i + 1];
					auto pre = rt->c[i-1];
					if (suc->n > t - 1) {
						left_replace(rt, i);
						b_tree_delete(rt->c[i], k);
					}
					else if (pre->n > t - 1) {
						right_replace(rt, i);
						b_tree_delete(rt->c[i], k);
					}
					else {
						b_tree_merge(rt, i);
						b_tree_delete(rt->c[i], k);
					}
				}
			}
		}
	}
	void left_replace(pt_b rt, int i) {
		auto tar = rt->c[i];
		auto suc = rt->c[i + 1];
		tar->key.push_back(rt->key[i]);
		tar->n += 1;

		rt->key[i] = suc->key.front();

		suc->n -= 1;
		for (int j = 0; j < suc->n; ++j)
			suc->key[j] = suc->key[j + 1];
		suc->key.resize(rt->n);

		if (!tar->leaf) {
			tar->c.push_back(suc->c.front());

			for (int j = 0; j <= suc->n; ++j)
				suc->c[j] = suc->c[j + 1];
			suc->c.resize(suc->n+1);
		}
	}
	void right_replace(pt_b rt, int i) {
		auto tar = rt->c[i];
		auto pre = rt->c[i-1];

		tar->key.resize(tar->n + 1);
		tar->n += 1;
		for (int j = tar->n - 1; j > 0; --j)
			tar->key[j] = tar->key[j - 1];
		tar->key[0] = rt->key[i-1];

		rt->key[i-1] = pre->key.back();
		pre->n -= 1;
		pre->key.resize(pre->n);

		if (!tar->leaf) {
			tar->c.resize(tar->n + 1);
			for (int j = tar->n; j > 0; --j)
				tar->c[j] = tar->c[j - 1];
			tar->c[0] = pre->c.back();

			pre->c.resize(pre->n + 1);
		}
	}
	pt_b getRoot() { return root; }
	void print(pt_b rt, int counter = 0) {
		if (rt) {
			for (int i = rt->n; i > rt->n / 2; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}

			for (int n = counter; n != -1; --n)
				cout << "\t";
			for (int i = 0; i < rt->n; ++i)
				cout << static_cast<char>(rt->key[i]);
	//		cout << rt->key.size() << "|" << rt->c.size() << "|" << rt->n << endl;
			cout << endl;

			for (int i = rt->n / 2; i >= 0; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}
		}
	}
private:
	int t;
	pt_b root=nullptr;
	void disk_write(string str) {
		cout << str << "正在写入磁盘....." << endl;
	}
	void disk_read(string str) {
		cout << "正在从磁盘读取" << str << "......" << endl;
	}
};

///////////////////////////////////////////
class solution18_2_1 {
public:
	void operator()() {
		string str = "FSQKCLHTVWMRNPABXYDZE";
		for (auto i : str) {
			bt.b_tree_insert(i);
			print(bt.getRoot());
		}
	}
private:
	b_tree bt;
	void print(pt_b rt, int counter = 0) {
		if (rt) {
			for (int i = rt->n; i > rt->n/2; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}

			for (int n = counter; n != -1; --n)
				cout << "\t";
			for (int i = 0; i < rt->n; ++i)
				cout << static_cast<char>(rt->key[i]);
			cout << endl;

			for (int i = rt->n/2; i >= 0; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}
		}
	}
};

class solution18_2_2 {
public:
	void operator()() {
		cout << "没有"
			<< endl;
	}
};

class solution18_2_3 {
public:
	void operator()() {
		cout << "1.从根节点r开始，如果当前节点是叶节点，返回当前节点的第一个关键字\n"
			<< "2.否则将r->c[0]代入第一步\n"
			<< "首先寻找到该关键字所在节点n，同时记录寻找过程中比它小的关键字k \n"
			<< "如果所在节点n为叶节点，返回k,注意k可能是其祖先节点的关键字也可能是\n"
			<< "同一个叶节点的关键字，\n"
			<< "如果关键字所在节点n不为叶节点，将该关键字前一个孩子指针代入max()\n"
			<< "该函数返回接受指针作为根节点的最大值，寻找最大值与最小值类似\n"
			<< endl;
	}
};

class solution18_2_4 {
public:
	void operator()() {
		cout << "Θ（n)" << endl;//借鉴，分析太长不粘贴
	}
};

class solution18_2_5 {
public:
	void operator()() {
		cout << "插入过程中判断该节点是不是叶节点，使用新的t值判断是否为满"
			<< endl;
	}
};

class solution18_2_6 {
public:
	void operator()() {
		cout << "假设以搜寻叶节点为标准，搜寻时间为（a+bt)log[t,(n+1)/2] \n"
			<< "对式子求导后t=3得最小值"
			<< endl;
	}
};

class solution18_3_2 {
public:
	void operator()() {
		string str = "LKJHGFDSAZXCVBNMPOIUYTREWQ";
		for (auto i : str) 
			bt.b_tree_insert(i);
		print(bt.getRoot());
		cout << "\n-----------------------------\n";
		cout << "删除中...\n";
		string s = "QAZXSWEDCRFVTGBYHNUJMIKOLP";
		for (auto i : s) {
			cout << "删除关键字" << i << endl;
			bt.b_tree_delete(bt.getRoot(), i);
			print(bt.getRoot());
			cout << "\n-----------------------------\n";
		}
	}
private:
	b_tree bt;
	void print(pt_b rt, int counter = 0) {
		if (rt) {
			for (int i = rt->n; i > rt->n / 2; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}

			for (int n = counter; n != -1; --n)
				cout << "\t";
			for (int i = 0; i < rt->n; ++i)
				cout << static_cast<char>(rt->key[i]);
		//	cout << rt->key.size() << "|" << rt->c.size() << "|" << rt->n 
		//		<<"|"<<rt->leaf<< endl;

			cout << endl;

			for (int i = rt->n / 2; i >= 0; --i) {
				if (rt->c.size() > i) {
					print(rt->c[i], counter + 1);
					cout << endl;
				}
			}
		}
	}
};

//思考题
	
class solution18_1 {
public:
	void operator()() {
		cout << "看不太懂"
			<< endl;
	}
};

class solution18_2 {
public:
	solution18_2():bt(4){}
	void operator()() {
		string str = "qazbgtwsxvfredcPLMNKOIJHUYnhujmikolpBGTVFREDCXSWQAZ";
		for (auto i : str)
			bt.b_tree_insert(i);
		bt.print(bt.getRoot());
		cout << "红黑树类似2-3-4树\n"
			<< "a.树的高度的增加和减少都是在根节点的位置改变的， 所以不会改变渐进运行时间\n"
			<< "b.和红黑树的扩张数据结构类似，用类似插入操作在较高的一个树中找到\n"
			<< "x的合适节点，该节点的高度比另一个较小树的高度大1，注意查找过程中\n"
			<< "将满节点分裂，最后用x合并较高树中找到节点的子树和另一个树，然后插入该节点\n"
			<< "因为题目条件限制，x的合适节点不是在最左边就是最右边\n"
			<< "c.在一个节点中查找最后一个小于k的关键字的下标直到找到k,\n"
			<< "这些关键字组成的就是关键集合，关键字左边的集合就是树的集合\n"
			<< "高度之间相差1"
			<< "d.关键字是有序的"
			<< endl;
	}
private:
	b_tree bt;
};
#endif
