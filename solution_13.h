#pragma once
#ifndef _SOLUTION_13_H_
#define _SOLUTION_13_H_
#include<iostream>
#include<vector>
#include<memory>
#include<ctime>
using namespace std;

class solution13_1_1 {
public:
	void operator()() {
		cout << "完全二叉树，分析根，因为比它大的和比它小的一样多，所以根值为8，然后归纳分析，因为完全二叉树可以看做快速排序最好的情况 \n"
			<< "就是主元是划分序列的中位数，也就是说我们只需要对[1..15]取中位数8，划分成两个区[1..7]，[8...15],然后分别对两个划分区间 \n"
			<< "取中位数4,12，迭代分析最后从上到下从左到右的序列为8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 \n"
			<< "bk=2,假设根在第一层，对2,4层染色成红色，其它为黑色 \n"
			<< "bk=3,对2，3,4，任一层染成红色，其它黑色 \n"
			<< "bk=4,全染成黑色"
			<< endl;
	}
};

class solution13_1_2 {
public:
	void operator()() {
		cout << "根据性质4，只有黑色时是红黑树，否则不是"
			<< endl;
	}
};

class solution13_1_3 {
public:
	void operator()() {
		cout << "是，因为之前满足4个条件，根节点变成黑色后满足五个条件 "
			<< endl;
	}
};

class solution13_1_4 {
public:
	void operator()() {
		cout << "没太理解题目意思"
			<< endl;
	}
};

class solution13_1_5 {
public:
	void operator()() {
		cout << "根据第4条性质可知，对于含有y个红色节点的路径，最少有x=y-1个黑色节点，这种情况是以红色节点起头，每个节点只有一个子节点 \n"
			<< "颜色交替改变，最后一黑色节点以两个红色节点结束， \n"
			<< "要满足条件5，假设黑高为bk,最短路径为bk+1,最长路径只能为bk+1+bk,得证"
			<< endl;
	}
};

class solution13_1_6 {
public:
	void operator()() {
		cout << "最多情况是数是满二叉树，并且树节点颜色交替排列，2^(2^k)-1,最少的情况是全是黑色的单边树，k+1"
			<< endl;
	}
};
class solution13_1_7 {
public:
	void operator()() {
		cout << "根据第4条性质可知，对于含有y个红色节点的路径，最少有x=y-1个黑色节点，这种情况是以红色节点起头，每个节点只有一个子节点 \n"
			<< "颜色交替改变，最后一黑色节点以两个红色节点结束，所以比值为y/(y-1),当y=2时取得最大值2，最小比值为0，节点全为红色 "
			<< endl;
	}
};
//////////////////////////////////////////////////////
struct rbtNode;
typedef shared_ptr<rbtNode> pt_rbt;
struct rbtNode {
	rbtNode(int k ,bool col=false,const pt_rbt &pa=nullptr, const pt_rbt &lef=nullptr,const pt_rbt &righ=nullptr):
		key(k),color(col),p(pa),left(lef),right(righ){}
	int key;
	bool color;//true 代表黑色
	pt_rbt p;
	pt_rbt left;
	pt_rbt right;
};
///////////////////////
class read_black_tree {
public://在红黑树中所有nullptr都被nil代替，nil是自己设置的一个不存贮数据的黑色节点
	void left_rotate(pt_rbt target) {//左旋
		auto taRight = target->right;

		target->right = taRight->left;
		if (taRight->left != nil)
			taRight->left->p = target;

		taRight->p = target->p;
		if (target->p == nil)
			root = taRight;
		else if (target->p->left == target)
			target->p->left = taRight;
		else
			target->p->right = taRight;

		target->p = taRight;
		taRight->left = target;
	}
	void right_rotate(pt_rbt target) {//右旋
		auto tarLeft = target->left;
		target->left = tarLeft->right;
		if (tarLeft->right != nil)
			tarLeft->p = target;

		tarLeft->p = target->p;
		if (target->p == nil)
			root = tarLeft;
		else if (target->p->left == target)
			target->p->left = tarLeft;
		else
			target->p->right = tarLeft;

		tarLeft->right = target;
		target->p = tarLeft;
	}
	void rb_insert(pt_rbt target) {//插入节点
		if (!target)
			return;
		pt_rbt curr = root;
		pt_rbt par = nil;
		while (curr!=nil) {
			par = curr;
			curr = curr->key > target->key ? curr->left : curr->right;
		}
		if (par==nil) {
			root = target;
			target->p = nil;
		}
		else if (par->key > target->key) {
			par->left = target;
			target->p = par;
		}
		else {
			par->right = target;
			target->p = par;
		}
		target->left = nil;
		target->right = nil;
		rb_insert_fixup(target);//插入节点后修复红黑树性质
		print(root);/////////////////////////////////
		cout << "------------------------------------------------------------------"<<endl;/////////////////////////////////
	}
	void rb_insert_fixup(pt_rbt target) {//要想将修复的六种情况都写对，最好自己把六种情况的情形画出来
		while (!target->p->color) {//如果插入节点的父节点的颜色是红色的则需要循环修复
			auto grandpar = target->p->p;//记录爷爷节点
			if (target->p == grandpar->left) {//如果目标节点是爷爷左子树的节点对应情况1,2,3
				if (!grandpar->right->color) {//如果叔节点是红色对应情况1
					grandpar->left->color = true;
					grandpar->right->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {//叔节点是黑色对应情况2,3，如果进入这个控制流执行完后就可以直接退出
					if (target ==target->p->right) {//如果目标节点是父节点的右节点对应情况2，此时目标节点与父节点和爷爷节点不在一条线上
						left_rotate(target->p);//需要左旋父节点使得在一条线上
						target = target->left;
					}
					grandpar->color = false;//情况3对应都在一条线上，此时只需要改变颜色旋转
					grandpar->left->color = true;
					right_rotate(grandpar);
				}
			}
			else {//如果目标节点是爷爷右子树的节点对应情况4,5,6
				if (!grandpar->left->color) {
					grandpar->left->color = true;
					grandpar->right->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {
					if (target == target->p->left) {
						right_rotate(target->p);
						target = target->right;
					}
					grandpar->color = false;
					grandpar->right->color = true;
					left_rotate(grandpar);
				}
			}
		}
		root->color = true;
	}
	void rb_transplant(pt_rbt lhs, pt_rbt rhs) {
		if (lhs->p==nil)
			root = rhs;
		else if (lhs == lhs->p->left) 
			lhs->p->left = rhs;
		else 
			lhs->p->right = rhs;
		rhs->p = lhs->p;
	}
	pt_rbt minimum(pt_rbt target) {
		while (target->left!=nil)
			target = target->left;
		return target;
	}
	void rb_delete(pt_rbt target) {//删除节点
		if (target == nil)
			return;
		pt_rbt y = target;
		bool y_original_color = y->color;
		pt_rbt x;
		if (target->left==nil) {
			x = target->right;
			rb_transplant(target, x);
		}
		else if (target->right==nil) {
			x = target->left;
			rb_transplant(target, x);
		}
		else {
			y = minimum(target->right);
			y_original_color = y->color;
			x = y->right;
			if (y->p == target)
				x->p = y;//当x是哨兵时为删除做准备
			else{
				rb_transplant(y, x);
				y->right = target->right;
				y->right->p = y;
			}
			rb_transplant(target, y);
			y->left = target->left;
			y->left->p = y;
			y->color = target->color;
		}
		if (y_original_color)
			rb_delete_fixup(x);
		print(root);/////////////////////////////////
		cout << "------------------------------------------------------------------" << endl;/////////////////////////////////
	}
	void rb_delete_fixup(pt_rbt x) {
		while (x != root&&x->color) {
			if (x == x->p->left) {
				 pt_rbt w = x->p->right;
				if (!w->color) {//情况1，如果兄弟节点是红色
					x->p->color = false;
					w->color = true;
					left_rotate(x->p);
					w = x->p->right;
				}
				
				if (w->right->color&&w->left->color) {//情况二，兄弟节点的两个子节点都是黑色
					w->color = false;
					x = x->p;
				}
				else if (w->right->color) {//兄弟节点的左节点为红色
					w->color = false;
					w->left->color = true;
					right_rotate(w);
					w = x->p->right;
				}
				if (!w->right->color) {//兄弟节点的右节点为红色
					w->color = x->p->color;
					x->p->color = true;
					w->right->color = true;
					left_rotate(x->p);
					x = root;
				}
			} 
			else {
				pt_rbt  w = x->p->left;
				if (!w->color) {
					x->p->color = false;
					w->color = true;
					right_rotate(x->p);
					w = x->p->left;
				}
				if (w->right->color&&w->left->color) {
					w->color = false;
					x = x->p;
				}
				else if (w->left->color) {
					w->color = false;
					w->right->color = true;
					left_rotate(w);
					w = x->p->left;
				}
				if (!w->left->color) {
					w->color = x->p->color;
					x->p->color = true;
					w->left->color = true;
					right_rotate(x->p);
					x = root;
				}
			}
		}
		x->color = true;
	}
	pt_rbt search(int key) {
		auto rbt = root;
		while (rbt!=nil&&rbt->key != key) {
			if (key < rbt->key)
				rbt = rbt->left;
			else
				rbt = rbt->right;
		}
		return rbt;
	}
	void print(pt_rbt rt,size_t counter_hight=0) {
		if (rt!=nil) {
			print(rt->right, counter_hight + 1);
			for (auto n = counter_hight; n != -1; --n)
				cout << "\t";
			cout << rt->key;
			rt->color ? cout << "黑" << endl : cout << "红" << endl;
			print(rt->left, counter_hight + 1);
		}
	}
	pt_rbt getRoot() { return root; }
	pt_rbt get_nil() { return nil; }
private:
	pt_rbt nil = shared_ptr<rbtNode>(new rbtNode(INT_MIN,true));
	pt_rbt root=nil;
};
/////////////////////////////
class solution13_2_1 {
public:
	void operator()() {
		cout << "已在上面写出"<<endl;
	}
};

class solution13_2_2 {
public:
	void operator()() {
		cout << "从叶节点开始，除根节点外每一个节点都有一个向上的与双亲节点对应的路径，每一条路径都对应一个旋转，所以有n-1种可能的旋转"
			<< endl;
	}
};

class solution13_2_3 {
public:
	void operator()() {
		cout << "a的高度加1，b的高度不变，c的高度减1"
			<< endl;
	}
};
class solution13_2_4 {
public:
	void operator()() {
		cout << "图13-2，经过图中第一次右旋变成右边的形式，然后对节点x右旋，再对y节点右旋 \n"
			<<"任何非右侧伸展链的树的一般形式都可以化成这几种形式的一种 \n"
			<< "经过少于节点数次数既可以将数右旋成右侧伸展链，因为左右旋是对称的，竟然任意形状的树a,b都可以在cn步内转变成右侧伸展链 \n"
			<< "所以a要转化成b只需要先转化成右侧伸展链，然后按照b转化成右侧伸展链的反向步骤转化"
			<< endl;
	}
};

class solution13_2_5 {
public:
	void operator()() {
		cout << "右侧伸展链已经不能右旋，所以右侧伸展链T1不能右旋成任意非右侧伸展链T2 \n"
			<< "T1右旋后的根节点不可能来自右子树，所以需要将左子树的节点转变成T2的根节点需要花费O(n)，递归得到T2 \n"//借鉴
			<< "时间复杂度T(n)=T(nL)+T(nR)+O(n)=O(n^2)，其中nL+nR=n-1。"
			<< endl;
	}
};

class solution13_3_1 {
public:
	void operator()() {
		cout << "会破坏性质5，而如果性质5被破坏最简单的方法就是改变颜色"
			<< endl;
	}
};

class solution13_3_2 {
public:
	void operator()() {
		for (auto i : vect) {
			rbt.rb_insert(shared_ptr<rbtNode>(new rbtNode(i, false, rbt.get_nil(), rbt.get_nil(), rbt.get_nil())));

		}
		rbt.print(rbt.getRoot());
	}
private:
	vector<int>vect{ 41,38,31,12,19,8 };
	//vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,};	
	read_black_tree rbt;
};

class solution13_3_3 {
public:
	void operator()() {
		cout << "麻烦不写"
			<< endl;
	}
};
class solution13_3_4 {
public:
	void operator()() {
		cout << "算法中改变颜色的情况有三种，父节点的颜色，树节点的颜色和爷爷节点的颜色，叔节点和父节点的是平行的，而之所以能进入循环的条件是 \n"
			<< "父节点的颜色是红色的，也就是说父节点和叔节点不可能为nil,如果父节点的颜色是红色，则说明父节点不是根节点，此时爷爷节点也就不可能\n"
			<< "是nil"
			<< endl;
	}
};

class solution13_3_5 {
public:
	void operator()() {
		cout << "假设插入n-1个节点后没有红节点，那么插入第n个节点后一定可以是红节点而不用修复 "
			<< endl;
	}
};

class solution13_3_6 {
public:
	void operator()() {
		cout << " We need to remove line 8 from RB - INSERT and modify RB - INSERT - FIXUP."
			<< "At any point in RB - INSERT - FIXUP we need only keep track of at most 2 ancestors:"
			<< "z.p and z.p.p.We can find and store each of these nodes in log n time"
			<< "and use them for the duration of the call to RB - INSERT - FIXUP.This won’t"
			<< "change the running time of RB - INSERT"
			<< endl;
	}
};


class solution13_4_1 {
public:
	void operator()() {
		cout << "假设要删除的是根节点 ： \n"
			<< "如果根节点有两个孩子，则第20行会将新根节点的颜色置为黑色 \n"
			<< "如果根节点只有一个孩子，x将会成为新的根节点，进入修复程序后\n"
			<< "不会进入循环，第23行被置为黑色 \n"
			<< "如果被删除的节点不是根节点，如果没有进入修复程序\n"
			<< "那么根节点的颜色不会改变，如果进入修复程序 \n"
			<< "只考虑书上提供的四种情况，因为另外四种情况是对称的，\n"
			<< "对于情况1，处理后进入循环2会直接退出，处理后子树的根节点 \n"
			<< "是黑色的，进入情2后不会改变之前根节点的颜色，所以能保证\n"
			<< "真正根节点的颜色是黑色的。除此之外的其它情况都会进入情况4\n"
			<< "才会终止，而情况4终止后x会变成新的根节点并在23行变为黑色 \n"
			<<"所以根节点始终为黑色"
			<< endl;
	}
};

class solution13_4_2 {
public:
	void operator()() {
		cout << "不会进入循环x被直接置为黑色"
			<< endl;
	}
};

class solution13_4_3 {
public:
	void operator()(){
		cout << "插入中......" << endl;
		for (auto i : ins)
			rbt.rb_insert(shared_ptr<rbtNode>(new rbtNode(i,false,rbt.get_nil(), rbt.get_nil(), rbt.get_nil() )));
		cout << "删除中...." << endl;
		for (auto i : del)
			rbt.rb_delete(rbt.search(i));
	}
private:
//	vector<int>ins{ 41,38,31,12,19,8 };
//	vector<int>del{ 8,12,19,31,38,41 };
	vector<int>ins{ 6,206,11,14,15,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,19,58,20 };
	vector<int>del{ 20,58,19,31,15,196,206,117,26,89,44,53,56,57,228,2,34,61,64,253,70,71,6};	

	read_black_tree rbt;
};

class solution13_4_4 {
public:
	void operator()() {
		cout << "x有可能是哨兵，所以程序中所有x成员在赋值符左边， \n"
			<< "x或者x的成员在操作符左右边的都可能会检查或修改哨兵 \n"
			<< endl;
	}
};

class solution13_4_6 {
public:
	void operator()() {
		cout << "因为w是红色的，所以x.p一定是黑色的"
			<< endl;
	}
};

class solution13_4_7 {
public:
	void operator()() {
		cout << "可以看到插入前后不一样" << endl;
		cout << "插入中......" << endl;
		for (auto i : ins)
			rbt.rb_insert(shared_ptr<rbtNode>(new rbtNode(i, false, rbt.get_nil(), rbt.get_nil(), rbt.get_nil())));
		cout << "删除中...." << endl;
		rbt.rb_delete(rbt.search(1));
	}
private:
	vector<int>ins{ 3,2,1 };
	read_black_tree rbt;

};

//思考题

class solution13_1 {
public:
	void operator()() {
		cout << "a.其祖先节点\n"
			<< "b.代码就不写了，自顶向下插入时新建每一个经过的节点，\n"
			<< "每经过一个节点，就复制该节点的全部属性，直到插入新节点\n"
			<< "c.h  \n"
			<< "d.因为每一个节点的p属性都只能指向一个父节点，所以每一个\n"
			<< "节点都要复制一份\n"
			<< "e.因为红黑树可以保证树高为O(lgn) \n"
			<< endl;
	}
};
class solution13_2 {
public:
	void operator()() {
		cout << "a.这两个操作的渐进运行时间为Θ(lgn),每次操作完成后从root计数\n"
			<< "到nil的黑色节点个数也只需要clgn,所以不会增加额外的渐进运行时间\n"
			<< "和额外空间，遇到黑色节点自减即可\n"
			<< "b.维护一个指针，初始时指向T1.root,只要当前节点有right!=nil \n"
			<< "curr就指向右节点，否则指向左节点，并记录节点的黑高直到等于T2.bh \n"
			<< "c.新建以x为关键字的节点，left=Ty,right=T2....\n"
			<< "d.红色，将x放入rb_insert_fixup()中，因为这个程序是用来修复性质2,4的\n"
			<< "e.找T2中黑高为T1.bh的具有最小关键字的黑色节点y \n"
			<< "f.查找，修复都是O(lgn)"
			<< endl;
	}
};
//////////////////////////
struct avlNode;
typedef shared_ptr<avlNode> pt_avl;
struct avlNode {
	avlNode(int k,int h=0,pt_avl lef=nullptr,pt_avl righ=nullptr,pt_avl par=nullptr):
		key(k),height(h),left(lef),right(righ),p(par){}
	int key;
	int height;
	pt_avl left;
	pt_avl right;
	pt_avl p;
};
class solution13_3 {
public:
	void operator()() {
		cout << "a.可以论证只有叶节点的那一层不是满的，不然高度差不会为1 \n"
			<< "不算叶节点的那一层，至少有2^h-1个节点，所以树高O(lgn) \n"
			<< "b.有4种情况，只描述其中两种，另外两种是对称的，根节点\n"
			<<"空节点的高度为-1，根节点的左子树高度减右子树高度为2,左边孙子节点是左儿子的右子树\n"
			<<"通过左旋左儿子得到第2种情况左孙子是左子树的左节点，右旋左儿子\n"
			<<"即可平衡树\n"
			<<"c.见程序,\n"
			<<"d.因为树高为O(lgn)，先是从上到下找到插入节点的位置插入然后递归从下至上维护avl树的高度\n"
			<<"旋转和插入只花费常数时间，所以为O(lgn),需要旋转位置的新节点的高度和之前高度相同，所以其祖先节点不需要旋转\n"
			<<"所以旋转O(1)"
			<< endl;
		vector<int>vect;
		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 1; i <= 20; ++i)
			vect.push_back(rand() % 300 + 1);
		cout << "\n" << "------------------------------------" << endl;
		for (auto i : vect) {
			cout << i << endl;
			avl_insert(root, shared_ptr<avlNode>(new avlNode(i)));
			print(root);
			cout << "\n" << "------------------------------------" << endl;
		}
	}
private:
//	vector<int>vect{ 32,218,8,53,269,8,132,282,144,84,41,99,153,154,133,67,142,54,178,227 };
	pt_avl root;
	int height(pt_avl target) {
		if (!target)//空节点的高度为-1
			return -1;
		return target->height;
	}
	void left_rotate(pt_avl target) {
		auto taRight = target->right;
		if (!target->p)
			root = taRight;
		else if (target == target->p->left)
			target->p->left = taRight;
		else
			target->p->right = taRight;
		taRight->p = target->p;

		if (taRight->left)
			taRight->left->p = target;
		target->right = taRight->left;

		taRight->left = target;
		target->p = taRight;

		target->height = 1 + (height(target->left) > height(target->right) ? height(target->left) : height(target->right));
		taRight->height = 1 + (height(taRight->left) > height(taRight->right) ? height(taRight->left) : height(taRight->right));
	}
	void right_rotate(pt_avl target) {
		auto tarLeft = target->left;
		if (!target->p)
			root = tarLeft;
		else if (target == target->p->left)
			target->p->left = tarLeft;
		else
			target->p->right = tarLeft;
		tarLeft->p = target->p;

		if (tarLeft->right)
			tarLeft->right->p = target;
		target->left = tarLeft->right;

		tarLeft->right = target;
		target->p = tarLeft;

		target->height = 1 + (height(target->left) > height(target->right) ? height(target->left) : height(target->right));
		tarLeft->height = 1 + (height(tarLeft->left) > height(tarLeft->right) ? height(tarLeft->left) : height(tarLeft->right));
	}
	void avl_insert(pt_avl rt,pt_avl target) {//avl树插入
		if (!rt) {
			root = target;
			return;
		}
		if (target->key < rt->key) {
			if (rt->left)
				avl_insert(rt->left, target);
			else {
				rt->left = target;
				target->p = rt;
			}
			if (height(rt->left) - height(rt->right) == 2) {
				if (target->key > rt->left->key)//情况1转变为情况2
					left_rotate(rt->left);
				right_rotate(rt);//处理情况2
			}
		}
		else {
			if (rt->right)
				avl_insert(rt->right, target);
			else {
				rt->right = target;
				target->p = rt;
			}
			if (height(rt->right) - height(rt->left) == 2) {
				if (target->key < rt->right->key)
					right_rotate(rt->right);
				left_rotate(rt);
			}
		}//节点高度为左右子树高度最大者加1
		rt->height = 1 + (height(rt->left) > height(rt->right) ? height(rt->left) : height(rt->right));
	}
	void print(pt_avl rt,int i = 0) {
		if (rt) {
			print(rt->right, i + 1);
			for (int n = i; n != -1; --n)
				cout << "\t";
			cout << rt->key<<"|"<<rt->height << endl;
			cout << endl;
			print(rt->left, i + 1);
		}
	}
};
#endif
