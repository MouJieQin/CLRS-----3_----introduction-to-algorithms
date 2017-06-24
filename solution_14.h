#pragma once
#ifndef _SOLUTION_14_H_
#define _SOLUTION_14_H_
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

////////////////////////////
struct os_rbt_node;
typedef shared_ptr<os_rbt_node> pt_rbt;
struct os_rbt_node {
	os_rbt_node(int k,bool col=false,int s=1,pt_rbt par=nullptr,pt_rbt lef = nullptr,pt_rbt righ = nullptr):
		key(k),color(col),size(s),p(par),left(lef),right(righ){}
	int key;
	bool color;
	int size;
	pt_rbt p;
	pt_rbt left;
	pt_rbt right;
};

class os_rbt {
public:
	void left_rotate(pt_rbt target) {
		auto taRight = target->right;
		if (target->p == nil)
			root = taRight;
		else if (target == target->p->left)
			target->p->left = taRight;
		else
			target->p->right = taRight;
		taRight->p = target->p;

		if(taRight->left!=nil)
			taRight->left->p = target;
		target->right = taRight->left;

		taRight->left = target;
		target->p = taRight;

		taRight->size = target->size;
		target->size = target->left->size + target->right->size + 1;
	}
	void right_rotate(pt_rbt target) {
		auto tarLeft = target->left;
		if (target->p == nil)
			root = tarLeft;
		else if (target == target->p->left)
			target->p->left = tarLeft;
		else
			target->p->right = tarLeft;
		tarLeft->p = target->p;

		if(tarLeft->right!=nil)
			tarLeft->right->p = target;
		target->left = tarLeft->right;

		target->p = tarLeft;
		tarLeft->right = target;

		tarLeft->size = target->size;
		target->size = target->left->size + target->right->size + 1;
	}

	void os_rbt_insert(int key) {
		pt_rbt target = shared_ptr<os_rbt_node>(new os_rbt_node(key, false, 1, nil, nil, nil));
		if (root == nil) {
			root = target;
			target->color = true;
			return;
		}
		pt_rbt curr = root;
		pt_rbt par = curr;
		while (curr != nil) {
			curr->size = curr->size + 1;
			par = curr;
			curr = target->key < curr->key ? curr->left : curr->right;
		}
		if (par->key > target->key)
			par->left = target;
		else
			par->right = target;
		target->p = par;
		if (!target->p->color)
			os_rbt_fixup(target);
	}
	void os_rbt_fixup(pt_rbt target) {
		while (!target->p->color) {
			pt_rbt grandpar = target->p->p;
			if (target->p == grandpar->left) {
				if (!grandpar->right->color) {
					target->p->color = true;
					grandpar->right->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {
					if (target == target->p->right) {
						left_rotate(target->p);
						target = target->left;
					}
					grandpar->color = false;
					target->p->color = true;
					right_rotate(grandpar);
				}
			}
			else {
				if (!grandpar->left->color) {
					target->p->color = true;
					grandpar->left->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {
					if (target == target->p->left) {
						right_rotate(target->p);
						target = target->right;
					}
					grandpar->color = false;
					target->p->color = true;
					left_rotate(grandpar);
				}
			}
		}
		root->color = true;
	}
	pt_rbt search(int k) {
		auto rt = root;
		while (rt != nil&&rt->key != k)
			rt = k < rt->key ? rt->left : rt->right;
		return rt;
	}
	void print(pt_rbt rt,int counter=0) {
		if (rt != nil) {
			print(rt->right, counter + 1);
			for (int n = counter; n != -1; --n)
				cout << "\t";
			cout << rt->key;
			rt->color ? cout << "黑" : cout << "红";
			cout<< rt->size << "\n";
			cout << endl;
			print(rt->left,counter+1);
		}
	}
	pt_rbt get_root() { return root; }
	pt_rbt get_nil() { return nil; }
private:
	pt_rbt nil = shared_ptr<os_rbt_node>(new os_rbt_node(INT_MIN,true, 0));
	pt_rbt root=nil;
};
////////////////////////
class solution14_1_1 {
public:
	void operator()() {
		vector<int>vect{ 32,21,8,8,53,269,8,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
			ost.print(ost.get_root());
			cout << "---------------------------------------\n";
		}
		cout << endl;

		cout << "\n第 10 个顺序统计量为   " << os_select(ost.get_root(), 10)->key<<endl;
	}
private:
	os_rbt ost;
	pt_rbt os_select(pt_rbt rt, int k) {
		int r = rt->left->size + 1;
		cout << rt->key << endl;////////////////
		if (r == k)
			return rt;
		else if (k < r)
			return os_select(rt->left, k);
		else
			return os_select(rt->right, k - r);
	}
};

class solution14_1_2 {
public:
	void operator()() {
		vector<int>vect{ 32,21,8,8,53,269,8,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
			ost.print(ost.get_root());
			cout << "---------------------------------------\n";
		}
		cout << endl;
		cout << "\n关键值为 84 的节点的秩为 " << os_rank(ost.search(84))<<endl;
	}
private:
	os_rbt ost;
	int os_rank(pt_rbt target) {
		auto y = target->p;
		int r = target->left->size + 1;
		while (y != ost.get_nil()) {
			if (target == y->right)
				r += y->left->size + 1;
			cout << y->key << endl;
			target = y;
			y = y->p;
		}
		return r;
	}
};

class solution14_1_3 {
public:
	void operator()() {
		vector<int>vect{ 32,21,8,8,53,269,8,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
			ost.print(ost.get_root());
			cout << "---------------------------------------\n";
		}
		cout << endl;
		cout << "\n第 10 个顺序统计量为   " << os_select(10)->key << endl;

	}
private:
	os_rbt ost;
	pt_rbt os_select(int k) {
		auto rt = ost.get_root();
		int r = rt->left->size + 1;
		while (rt!=ost.get_nil()&&r != k) {
			if (k < r)
				rt = rt->left;
			else {
				rt = rt->right;
				k -= r;
			}
			r = rt->left->size + 1;
		}
		return rt;
	}
};

class solution14_1_4 {
public:
	void operator()() {
		cout << "os_key_rank(T,k)返回以T为根的k的秩，具体见注释"
			<< endl;
		vector<int>vect{ 32,21,8,53,269,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
			ost.print(ost.get_root());
			cout << "---------------------------------------\n";
		}
		cout << endl;
		cout << "\n关键值为 178 的节点的秩为 " <<os_key_rank(ost.get_root(),178) << endl;
	}
private:
	os_rbt ost;
	int os_key_rank(pt_rbt rt, int key) {
		if (rt == ost.get_nil())//如果树中没有改关键字节点，返回小于该关键字节点的总数
			return 0;
		else if (rt->key == key)//如果找到的改关键字，返回小于改关键字节点的个数+1,1是本身
			return rt->left->size + 1;
		else if (rt->key > key)//如果关键字在左子树中继续查找
			return os_key_rank(rt->left, key);
		else//如果关键字在右子树中返回小于它的个数加上继续查找的个数
			return rt->left->size+1+os_key_rank(rt->right, key);
	}
};

class solution14_1_5 {
public:
	void operator()() {
		cout << "首先用search找到该元素的节点rt,花费O(lgn),如果该节点的右子树size>i,\n"
			<<"用os_select(rt->right,i)找到该节点的第i个顺序统计节点返回，否则\n"
			<<"向上寻找第一个大于该子树根节点的节点，递归查找，因为查找这样的节点最多花费O(lgn) \n"
			<<"而一旦找到最多花费O(lgn)便可以返回,所以总花费最多O(lgn)"
			<<"别人答案，OS-SELECT(T,OS-RANK(T,x)+i)."
			<< endl;
		vector<int>vect{ 32,21,8,53,269,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
			ost.print(ost.get_root());
			cout << "---------------------------------------\n";
		}
		cout << endl;
		cout << "84在树中的第7个后继为 " << find_successor(84, 7)->key << endl;
	}
private:
	os_rbt ost;
	pt_rbt find_successor(int key, int n) {
		auto target = ost.search(key);
		return find_successor(target->right, n);
	}
	pt_rbt find_successor(pt_rbt target, int n) {
			int r = target->size;
			if (r >= n)
				return os_select(target, n);
			else {
				auto up = up_larger(target);
				n -= r;//调整需要查找的位数
				if (n == 1)//如果要查找的是第一个大于该节点的节点直接返回
					return up;
				return find_successor(up->right, n-1);
			}
	}
	pt_rbt up_larger(pt_rbt target) {
		while (target != ost.get_nil() && target != target->p->left)
			target = target->p;
		return target->p;
	}
	pt_rbt os_select(pt_rbt rt, int n) {
		int r = rt->left->size + 1;
		if (r == n)
			return rt;
		else if (r > n)
			return os_select(rt->left, n);
		else
			return os_select(rt->right, n - r);
	}
};

class solution14_1_6 {
public:
	void operator()() {
		cout << "插入和删除一个元素时，所有比该元素大的节点的秩都会改变，\n"
			<< "旋转后的元素的秩不会改变"
			<< endl;
	}
};

class solution14_1_7 {
public:
	void operator()() {
		cout << "每当插入的元素向左前进时累加size"
			<< endl;
	}
};

class solution14_1_8 {
public:
	void operator()() {//借鉴
		cout << "在平面上设立坐标系，弦i=(a,b)其中a是i的x轴上靠左的点。"
			<< "弦i与弦j相交当i.a.y - j.a.y与i.b.y - j.b.y反号。"
			<< "故问题转换为了求逆序数问题。更准确的说是求i.b.y中的逆序数，"
			<< "其中i按照i.a.y排序。"
			<< endl;
	}
};

class solution14_2_1 {
public:
	void operator()() {
		cout << "没有经过修复操作的刚插入的节点没有内部节点的左右孩子\n"
			<< "所以前驱和和后继都在\n"
			<< "其祖先节点上，而这正是插入操作经过的节点，所以可以增加两个\n"
			<< "指针指向前驱后后继，删除操作由于总是取前驱或是后继来填补空位\n"
			<< "所以也不会增加删除操作的渐进运行时间"
			<< endl;
	}
};

class soluton14_2_2 {
public:
	void operator()() {
		cout << "不需要修复的插入操作的树不需要改变黑高，旋转和变色操作只需要改变\n"
			<< "一个节点的黑高，删除同理。\n"
			<< "对于深度的维护，如果插入节点后由兄弟节点则不需要改变深度，否则\n"
			<< "从下至上改变祖先节点的深度，然后修复，删除操作也只会改变祖先节点\n"
			<< "的深度，至于修复操作的旋转也只会改变两个节点的深度，"
			<< "所以不会改变渐进运行时间"
			<< endl;
	}
};

class solution14_2_3 {
public:
	void operator()() {
	/*	cout << "After performing the rotate operation, starting at the deeper of the two nodes"
			<< "that were moved by the rotate, say x, set x.f = x.lef t.f ⊗x.a⊗x.right.f.Then"
			<< " the same thing for the higher up node in the rotation.For size, instead set"
			<< "x.size = x.lef t.size + x.right.size + 1 and then do the same for the higher up"
			<< "node after the rotation."
			<< endl;*/
	}
};

class solution14_2_4 {
public:
	void operator()() {
		cout << "如果当前节点符合要求，递归查找左右子树，如果当前节点\n"
			<< "关键字小于a,查找右子树，大于b查找左子树，这样可以保证\n"
			<< "访问的节点数不超过m+2lgn,所以符合要求"
			<< endl;
		vector<int>vect{ 32,21,8,8,53,269,8,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
		cout << "---------------------------------------\n";
		for (auto i : vect) {
			ost.os_rbt_insert(i);
		}
		ost.print(ost.get_root());
		cout << "---------------------------------------\n";
		cout << endl;
		cout << "在 39 和 143 之间的数有" << endl;
		rb_enumerate(ost.get_root(), 39, 143);
		cout << "---------------------------------------\n";
	}
private:
	os_rbt ost;
	void rb_enumerate(pt_rbt rt,int lhs,int rhs){
		if (rt != ost.get_nil()) {
			if (rt->key >= lhs) {
				if (rt->key <= rhs) {
					cout << rt->key << endl;
					rb_enumerate(rt->left, lhs, rhs);
					rb_enumerate(rt->right, lhs, rhs);
				}
				else {
					rb_enumerate(rt->left, lhs, rhs);
				}
			}
			else {
				rb_enumerate(rt->right, lhs, rhs);
			}
		}
	}
};
////////////////////////////////////
struct interNode;
typedef shared_ptr<interNode> pt_int;
struct interNode {
	interNode(bool col = false,int low=INT_MIN, int high=INT_MIN, 
		int max=INT_MIN,  pt_int par = nullptr,
		pt_int lef=nullptr, pt_int righ=nullptr) :
		color(col),low(low), high(high), max(max),  p(par), left(lef), right(righ) {}
	bool color;
	int low;
	int high;
	int max;
	pt_int p;
	pt_int left;
	pt_int right;
};

class interval_tree {
public:
	void get_max(pt_int target) {
		target->max = target->left->max > target->right->max ?
			target->left->max : target->right->max;
		if (target->high > target->max)
			target->max = target->high;
	}
	void left_rotate(pt_int target) {
		auto taRight = target->right;
		if (target->p == nil)
			root = taRight;
		else if (target == target->p->left)
			target->p->left = taRight;
		else
			target->p->right = taRight;
		taRight->p = target->p;

		if (taRight->left != nil)
			taRight->left->p = target;
		target->right = taRight->left;

		taRight->left = target;
		target->p = taRight;

		taRight->max = target->max;
		get_max(target);
	}
	void right_rotate(pt_int target) {
		auto tarLeft = target->left;
		if (target->p == nil)
			root = tarLeft;
		else if (target == target->p->left)
			target->p->left = tarLeft;
		else
			target->p->right = tarLeft;
		tarLeft->p = target->p;

		if (target->right != nil)
			tarLeft->right->p = target;
		target->left = tarLeft->right;

		tarLeft->right = target;
		target->p = tarLeft;

		tarLeft->max = target->max;
		get_max(target);
	}
	void insert(pt_int rt, pt_int target) {
		if (rt->low > target->low) {
			if (rt->left == nil) {
				rt->left = target;
				target->p = rt;
			}
			else {
				insert(rt->left, target);
				get_max(rt);
			}
		}
		else {
			if(rt->right==nil){
				rt->right = target;
				target->p = rt;
			}
			else {
				insert(rt->right, target);
				get_max(rt);
			}
		}
		
	}
	void int_insert(pair<int,int>&tar) {
		pt_int target = shared_ptr<interNode>(new interNode(false, tar.first
			, tar.second, tar.second, nil, nil, nil));
		if (root == nil) {
			root = target;
			target->color = true;
			return;
		}
		
		insert(root, target);
		if (!target->p->color) 
			int_insert_fixup(target);

	}
	void int_insert_fixup(pt_int target) {
		while (!target->p->color) {
			auto grandpar = target->p->p;
			if (target->p == grandpar->left) {
				if (!grandpar->right->color) {
					grandpar->left->color = true;
					grandpar->right->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {
					if (target == target->right) 
						left_rotate(target->p);
					grandpar->color = false;
					grandpar->left->color = true;
					right_rotate(grandpar);
				}
			}
			else {
				if (!grandpar->left->color) {
					grandpar->right->color = true;
					grandpar->left->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {
					if (target == target->left)
						right_rotate(target->p);
					grandpar->color = false;
					grandpar->right->color = true;
					left_rotate(grandpar);
				}
			}
		}
		root->color = true;
	}
	
	void print(pt_int rt, int counter = 0) {
		if (rt != nil) {
			print(rt->right, counter + 1);
			for (int n = counter; n != -1; --n)
				cout << "\t";
			cout << "[" << rt->low << "," << rt->high << "]|" << rt->max;
			rt->color ? cout << "黑" : cout << "红";
			cout << "\n" << endl;
			print(rt->left, counter + 1);
		}
	}
	pt_int getRoot() { return root; }
	pt_int getNil() { return nil; }
private:
	pt_int nil=shared_ptr<interNode>(new interNode(true));
	pt_int root=nil;
};
////////////////////////

class solution14_3_1 {
public:
	void operator()() {
		cout << "旋转后的父节点的max是原父节点的max，新的子节点的max需要更新"
			<< endl;
		vector<pair<int, int>>vect{
			{0,3},{ 5,8 },{ 6,10 },{ 8,9 },{ 15,23 },{ 16,21 },
			{ 17,19 },{ 19,20 },{ 25,30 },{ 26,26 }
		};
		cout << "\n---------------------------------------------\n";
		for (auto &i : vect) {
			intree.int_insert(i);
			intree.print(intree.getRoot());
			cout << "---------------------------------------------\n";
		}
	}
private:
	interval_tree intree;
};

class solution14_3_2 {
public:
	void operator()() {
		cout << "打印出来的红黑树都是闭区间是无关题目的，将原算法的所有\n"
			<< "等于关系去掉即可，还有一点要说名的是书上的证明，当左子树\n"
			<< "有重叠区间时右子树可能也有，但控制流会进入左子树返回一个\n"
			<< "重叠区间"
			<< endl;
		vector<pair<int, int>>vect{
			{ 0,3 },{ 5,8 },{ 6,10 },{ 8,9 },{ 15,23 },{ 16,21 },
			{ 17,19 },{ 19,20 },{ 25,30 },{ 26,26 }
		};
		cout << "\n---------------------------------------------\n";
		for (auto &i : vect) {
			intree.int_insert(i);
		}
		intree.print(intree.getRoot());
		cout << "---------------------------------------------\n";
		cout << "(22,25)的重合区间为 " << endl;
		auto result = interval_search(make_pair<int,int>( 22,25 ),intree.getRoot());
		cout << "(" << result->low << "," << result->high << ")" << endl;
	}
private:
	interval_tree intree;
	pt_int interval_search(pair<int, int>&target, pt_int rt) {//开区间查找
		while (rt != intree.getNil() &&
			!(target.first < rt->high&&rt->low < target.second)) {
			if (rt->left->max > target.first)
				rt = rt->left;
			else
				rt = rt->right;
		}
		return rt;
	}
};

class solution14_3_3 {
public:
	void operator()() {
		cout << "用result记录最小low重叠指针，如果当前节点重合与result比较\n"
			<< "然后继续查找左子树。如果当前节点不重叠，和普通查找类似"
			<< endl;
		vector<pair<int, int>>vect{
			{ 0,3 },{ 5,8 },{ 6,10 },{ 8,9 },{ 15,23 },{ 16,21 },
			{ 17,19 },{ 19,20 },{ 25,30 },{ 26,26 }
		};
		cout << "\n---------------------------------------------\n";
		for (auto &i : vect) {
			intree.int_insert(i);
		}
		intree.print(intree.getRoot());
		cout << "---------------------------------------------\n";
		cout << "[9,27]的重合区间为 " << endl;
		auto result = minlow_interval_search(intree.getRoot(), make_pair(9,27));
		cout << "[" << result->low << "," << result->high << "]" << endl;
	}
private:
	interval_tree intree;
	pt_int minlow_interval_search(pt_int rt, pair<int, int>&target) {
		auto result = shared_ptr<interNode>(new interNode(true, INT_MAX, INT_MAX));
		while (rt != intree.getNil()) {
			if (target.first <= rt->high&&rt->low <= target.second) {
				if (rt->low < result->low)
					result = rt;
				rt = rt->left;
			}
			else if (rt->left->max >= target.first)
				rt = rt->left;
			else {
					rt = rt->right;
			}
		}
		if (result->low != INT_MAX)
			return result;
		else
			return intree.getNil();
	}
};

class solution14_3_4 {
public:
	void operator()() {
		cout << "如果当前节点重叠则压入，然后不管当前节点重叠与否，\n"
			<< "如果当前节点的左子树可能满足要就则递归求解，否则抛弃\n"
			<< "右子树同理，右子树查找可能满足要求的方法是找到第一个\n"
			<< "左端点小于目标右端点的节点递归求解，\n"
			<< "对每一个重叠节点的查找不会超过lgn,每一个节点最多访问一次\n"
			<< endl;
		vector<pair<int, int>>vect{
			{ 0,3 },{ 5,8 },{ 6,10 },{ 8,9 },{ 15,23 },{ 16,21 },
			{ 17,19 },{ 19,20 },{ 25,30 },{ 26,26 }
		};
		cout << "\n---------------------------------------------\n";
		for (auto &i : vect) {
			intree.int_insert(i);
		}
		intree.print(intree.getRoot());
		cout << "---------------------------------------------\n";
		cout << "[9,20]的重合区间为 " << endl;
		vector<pt_int>result;
		get_all_overlap(result, intree.getRoot(), make_pair<int,int>(9, 20));
		for(auto &i:result)
			cout << "[" << i->low << "," << i->high << "]" << endl;
	}
private:
	interval_tree intree;
	void get_all_overlap(vector<pt_int>&result, pt_int rt, pair<int, int>&target) {
		if (rt == intree.getNil())
			return;
		if (target.first <= rt->high&&rt->low <= target.second)
			result.push_back(rt);
		if (rt->left->max >= target.first)
			get_all_overlap(result, rt->left, target);
		rt = rt->right;
		while (rt != intree.getNil() && rt->low > target.second)
			rt = rt->left;
		if (rt == intree.getNil())
			return;
		else
			get_all_overlap(result, rt, target);
	}
};
class solution14_3_5 {
public:
	void operator()() {
		cout << "算法模拟插入过程，遇到相等的左端点则比对"
			<< endl;
	}
};

class solution14_3_6 {
public:
	void operator()() {
		cout << "还是使用红黑树作为基本结构，与一个数最接近的是这个数的前驱\n"
			<< "和后继，对于一个刚插入的节点的前驱和后继在这个节点的插入路径\n"
			<< "上，所以不会增加插入操作的渐进运行时间。\n"
			<< ""
			<< endl;///////////////////////
	}
};

//思考题
class solution14_1 {
public:
	void operator()() {
		cout << "a.将区间想象成一个“凵”,对于一个重叠最多的而不是端点的点来说\n"
			<< "可以向左或是向右移动到一个端点上\n"
			<< ""
			<< endl;
	}
};
#endif