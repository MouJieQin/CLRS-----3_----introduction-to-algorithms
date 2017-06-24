#pragma once
#ifndef _SOLUTION_12_H_
#define	_SOLUTION_12_H_
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class solution12_1_1 {
public:
	void operator()() {
		cout << "太麻烦省略"
			<< endl;
	}
};

class solution12_1_2 {
public:
	void operator()() {
		cout << "二叉搜索树是对于任一节点x,x.left->key<=x.key<=x.right->key,而最小堆是对于任一节点，x.key<=x.right->key,x.key<=x.left->key \n"
			<< "可以看到书上的三种遍历方法只用到了树的性质，所以可以在O(n)的时间内输出最小堆"
			<< endl;
	}
};
///////////////////////////////////////
struct treeNode {
	treeNode(const int k,const shared_ptr<treeNode>& pa=nullptr,const shared_ptr<treeNode>&lhs=nullptr,const shared_ptr<treeNode>&rhs=nullptr):
		key(k),p(pa),left(lhs),right(rhs){}
	int key;
	shared_ptr<treeNode>p;
	shared_ptr<treeNode>left;
	shared_ptr<treeNode>right;
};

class tree {
public:
	friend class solution12_1_3;
	friend class solution12_1_4;
	tree() {
		auto left_ = shared_ptr<treeNode>(new treeNode(5, nullptr, shared_ptr<treeNode>(new treeNode(2)), shared_ptr<treeNode>(new treeNode(5))));
		auto right_ = shared_ptr<treeNode>(new treeNode(7, nullptr, nullptr, shared_ptr<treeNode>(new treeNode(8))));

		left_->left->p = left_;
		left_->right->p = left_;
		right_->right = shared_ptr<treeNode>(new treeNode(9, nullptr, shared_ptr<treeNode>(new treeNode(8)), shared_ptr<treeNode>(new treeNode(10))));
		right_->right->p = right_;
		right_->right->left->p = right_->right;
		right_->right->right->p = right_->right;
		root = shared_ptr<treeNode>(new treeNode(6, nullptr, left_, right_));
		left_->p = root;
		right_->p = root;
	}
	void recursion_inorder_walk( shared_ptr<treeNode>pt) {//递归中序遍历
		if (pt) {
			recursion_inorder_walk(pt->left);
			cout << pt->key << endl;
			recursion_inorder_walk(pt->right);
		}
	}
	void stack_inorder_walk(shared_ptr<treeNode>pt) {//模仿递归的非递归以栈辅助的中序遍历
		vector<shared_ptr<treeNode>>stack;
		shared_ptr<treeNode>last=pt;
		shared_ptr<treeNode>next;
		do {
			while (last) {
				stack.push_back(last);
				last = last->left;
			}

			next = pop(stack);
			cout << next->key << endl;
			last = next->right;
		
		} while (!stack.empty()||last);
	}
	shared_ptr<treeNode>minimum(shared_ptr<treeNode>pt) {
		while (pt->left) {
			pt = pt->left;
		}
		return pt;
	}
	shared_ptr<treeNode> successor(shared_ptr<treeNode>pt) {
		if (pt->right) {
			return
				minimum(pt->right);
		}
		while (pt->p&&pt!=pt->p->left) {
			pt = pt->p;
		}
		return pt->p;
	}
	void inorder_walk(shared_ptr<treeNode>pt) {//非递归且不用栈的递归算法，找到最小值后不断取其后继
		shared_ptr<treeNode>succ= minimum(pt);
		while (succ) {
			cout << succ->key << endl;
			succ = successor(succ);
		}
	}
	void recursion_preorder_walk(shared_ptr<treeNode>pt) {//递归先序遍历
		if (pt) {
			cout << pt->key << endl;
			recursion_preorder_walk(pt->left);
			recursion_preorder_walk(pt->right);
		}
	}
	void stack_preorder_walk(shared_ptr<treeNode>pt) {//模仿递归的非递归以栈辅助的先序遍历
		vector<shared_ptr<treeNode>>stack;
		shared_ptr<treeNode>curr = pt;
		shared_ptr<treeNode> next;
		do {
			while (curr) {
				cout << curr->key << endl;
				stack.push_back(curr);
				curr = curr->left;
			}

			curr = pop(stack)->right;

		} while (!stack.empty()||curr);
	}

	void recursion_postorder_walk(shared_ptr<treeNode>pt) {
		if (pt) {
			recursion_postorder_walk(pt->left);
			recursion_postorder_walk(pt->right);
			cout << pt->key<<endl;
		}
	}
	void stack_postorder_walk(shared_ptr<treeNode>pt) {
		vector<shared_ptr<treeNode>>stack;
		shared_ptr<treeNode>curr=pt;
		shared_ptr<treeNode>next;
		do {
			////////////////////////////////////////////
		} while (!stack.empty());
	}
private:
	shared_ptr<treeNode>root;
	shared_ptr<treeNode>  pop(vector<shared_ptr<treeNode>>&vect) {
		auto result = vect.back();
		vect.pop_back();
		return result;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////
class solution12_1_3 {
public:
	void operator()() {
		tr.recursion_inorder_walk(tr.root);
		cout << "\n" << endl;
		tr.stack_inorder_walk(tr.root);
		cout << "\n" << endl;
		tr.inorder_walk(tr.root);
		cout << "\n" << endl;
	}
private:
	tree tr;
};

class solution12_1_4 {
public:
	void operator()() {
		tr.recursion_preorder_walk(tr.root);
		cout << "\n" << endl;
		tr.stack_preorder_walk(tr.root);
		cout << "\n" << endl;
		tr.recursion_postorder_walk(tr.root);
		cout << "\n" << endl;
		tr.stack_postorder_walk(tr.root);
		cout << "\n" << endl;
	}
private:
	tree tr;
};
/////////////////////////////////////////////////////
struct bstNode;
typedef shared_ptr<bstNode> pt_bst;

struct bstNode {
	bstNode(int k,bool f=true,pt_bst pa=nullptr,pt_bst lef=nullptr,pt_bst righ=nullptr):
		key(k),flag(f),p(pa),left(lef),right(righ){}
	int key;
	bool flag;
	pt_bst p;
	pt_bst left;
	pt_bst right;
};

class bstree {
public:
	pt_bst getRoot() {
		return root;
	}
	void insert(pt_bst target) {
		auto curr = root;
		auto par = curr;
		while (curr) {
			par = curr;
			curr = curr->key > target->key ? curr->left : curr->right;
		}
		if (!par) {
			root = target;
		}
		else if(par->key > target->key) {
			par->left = target;
			target->p = par;
		}
		else {
			par->right = target;
			target->p = par;
		}
	}
	void print(pt_bst rt, size_t counter_hight = 0) {
		if (rt) {
			print(rt->right, counter_hight + 1);
			for (int i = counter_hight; i != -1; --i)
				cout << "\t";
			cout << rt->key << endl;
			print(rt->left, counter_hight + 1);
		}
	}
	void inordor_walk(pt_bst rt) {
		if (rt) {
			inordor_walk(rt->left);
			cout << rt->key << endl;
			inordor_walk(rt->right);
		}
	}
	void inordor_tree_walk(pt_bst curr) {//使用标记的非递归中序遍历
		while (curr) {
			while (curr&&curr->left&&curr->left->flag)//确保即将打印的节点没有左子树，或者左子树已经打印过
				curr = curr->left;
			if (curr->flag) {//如果当前节点没有打印，则打印当前节点，并改变标记
				cout << curr->key << endl;
				curr->flag = false;
			}
			if (curr&&curr->right&&curr->right->flag)//如果节点有右子树并且右子树没有打印过
				curr = curr->right;
			else//没有右子树或者右子树已经打印过了则将当前节点上移
				curr = curr->p;
		}//每个节点都只访问常数次，所以花费Θ(n)
	}
	void preordor_walk(pt_bst rt) {
		if (rt) {
			cout << rt->key << endl;
			preordor_walk(rt->left);
			preordor_walk(rt->right);
		}
	}
	void preordor_tree_walk(pt_bst curr) {//使用标记的非递归先序遍历
		while (curr) {
			while (curr&&curr->left&&curr->flag) {//如果当前节点有左子树并且未被输出过则输出当前节点
				cout << curr->key << endl;
				curr->flag = false;
				curr = curr->left;
			}
			if (!curr->left&&curr->flag) {//如果当前节点没有左子树且未被输出过则输出当前节点
				cout << curr->key << endl;
				curr->flag = false;
			}
			if (curr&&curr->right&&curr->right->flag)//如果当前节点的右子树没有被输出过则将控制流节点指向右节点
				curr=curr->right;
			else//否则上移当前节点
				curr = curr->p;
		}
	}
	void postordor_walk(pt_bst rt) {
		if (rt) {
			postordor_walk(rt->left);
			postordor_walk(rt->right);
			cout << rt->key << endl;
		}
	}
	void postordor_tree_walk(pt_bst curr) {//使用标记的非递归后序遍历
		while (curr) {
			while (curr&&curr->left&&curr->left->flag)//如果当前节点的左节点未输出则将当前节点指向左节点
				curr = curr->left;
			if (curr&&curr->right&&curr->right->flag)//如果当前节点的右节点未输出则将当前节点指向右节点
				curr = curr->right;
			else {//进入这个控制流的要么没有左节点或者左节点已经输出 并且 没有右节点或是右节点已经输出
				cout << curr->key << endl;
				curr->flag = false;//此时输出该节点满足后续遍历的定义
				curr = curr->p;//如果当前节点已经输出则说明以该节点的所有子树都已经输出，可以上移节点
			}
		}
	}
private:
	pt_bst root;
};
class test {
public:
	void operator()() {
		for (auto i : vect)
			bst.insert(shared_ptr<bstNode>(new bstNode(i)));
		bst.print(bst.getRoot());
		/*cout << "----------------------------" << endl;
		bst.inordor_walk(bst.getRoot());
		cout << "----------------------------" << endl;
		bst.inordor_tree_walk(bst.getRoot());*/

		/*cout << "----------------------------" << endl;
		bst.preordor_walk(bst.getRoot());
		cout << "----------------------------" << endl;
		bst.preordor_tree_walk(bst.getRoot());*/

		cout << "----------------------------" << endl;
		bst.postordor_walk(bst.getRoot());
		cout << "----------------------------" << endl;
		bst.postordor_tree_walk(bst.getRoot());
	}
private:
	vector<int>vect{ 8,4,12,2,6,10,14,1,3,5,7,9,11,13,15,16,17 };
	bstree bst;
};
/////////////////////////////////////////////////
class solution12_1_5 {
public:
	void operator()() {
		cout << "最坏情况的二叉搜索树可以是只有右孩子或只有左孩子的树，这种树的节点是有序序列，类似于比较排序模型"
			<< endl;
	}
};

class solution12_2_1 {
public:
	void operator()() {
		cout << "c,e,可以自己画搜索路径图，c中911并不比912大，e中347并不比299小"
			<< endl;
	}
};
///////////////////////////////////////
class bin_tree {
public:
	friend class solution12_2_2;
	bin_tree() {
		auto left_ = shared_ptr<treeNode>(new treeNode(5, nullptr, shared_ptr<treeNode>(new treeNode(2)), shared_ptr<treeNode>(new treeNode(5))));
		auto right_ = shared_ptr<treeNode>(new treeNode(7, nullptr, nullptr, shared_ptr<treeNode>(new treeNode(8))));

		left_->left->p = left_;
		left_->right->p = left_;
		right_->right = shared_ptr<treeNode>(new treeNode(9, nullptr, shared_ptr<treeNode>(new treeNode(8)), shared_ptr<treeNode>(new treeNode(10))));
		right_->right->p = right_;
		right_->right->left->p = right_->right;
		right_->right->right->p = right_->right;
		root = shared_ptr<treeNode>(new treeNode(6, nullptr, left_, right_));
		left_->p = root;
		right_->p = root;
	}
	shared_ptr<treeNode>tree_search( int k,shared_ptr<treeNode>pt) {
		while (pt&&pt->key!=k) 
			pt = k > pt->key ? pt->right : pt->left;
		return pt;
	}
	shared_ptr<treeNode> tree_minimum(shared_ptr<treeNode>pt) {
		if (pt->left)
			return tree_minimum(pt->left);
		return pt;
	}
	shared_ptr<treeNode>tree_maximum(shared_ptr<treeNode>pt) {
		if (pt->right)
			return tree_maximum(pt->right);
		return pt;
	}
	shared_ptr<treeNode>tree_predecessor(shared_ptr<treeNode>pt) {
		if (pt->left)
			return tree_maximum(pt->left);
		auto pa = pt->p;
		while (pa&&pa->left == pt) {
			pt = pa;
			pa = pt->p;
		}
		return pa;
	}
private:
	shared_ptr<treeNode>root;
};
class solution12_2_2 {
public:
	void operator()() {
		cout << "min is " << endl;
		cout << tree.tree_minimum(tree.root)->key << endl;
		cout << "max is " << endl;
		cout << tree.tree_maximum(tree.root) ->key<< endl;
		cout << "predecessor of 8 is " << endl;
		cout << tree.tree_predecessor(tree.tree_search(8, tree.root))->key<<endl;
	}
private:
	bin_tree tree;
};
class solution12_2_4 {
public:
	void operator()() {
		cout << "如图12-2，假设查找的关键字是2，而右边的4显然小于搜索路径上的6"
			<< endl;
	}
};

class solution12_2_5 {
public:
	void operator()() {
		cout << "这个节点的后继一定是该节点右子树的最小值的节点，如果该节点有左孩子，则该节点不是最小值 \n"
			<< "这个节点的前驱是该节点的左子树的最大值，如果该节点有右孩子，则该节点不是最大值 \n"
			<< endl;
	}
};
class solution12_2_6 {
public:
	void operator()(){
		cout << "这段话翻译的不好，特别是在原文中，我是看了代码之后才理解的，自行理解就是如果一个节点x没有右子树，那么这个节点的后继节点y满足，第一个 \n"
			<< "左孩子是x祖先的节点，这个单靠文字描述有点不好证明，根据要证明的定义可知，对于x和y之间还有a1,a2...an个节点，x是a1的右节点，a1是a2的右节点...但an是y的左节点"
			<< "这些节点的左节点还可以连接其他的子树，但可以证明这些子树上的节点不用考虑，比如a1的左子树最大的节点的关键字k必定小于a1->key,而a1->key<x->key |n"
			<< "y->key>x->key,满足后继的必要条件，我们已经证明了以x,a1,a2,a3....an作为祖先节点的节点都不满足条件，还有机会和y竞争的只有y的祖先，假设有一个祖先比y节点更适合当后继 \n"
			<< "可以推测这个节点g满足条件x->key<=g->key<=y-<key,要满足x->key<=g->key，y必定是g的左子树的某个节点，然而要满足key<=y-<key，y必须是g的右子树的某个节点 \n"
			<< "很显然这样的g节点不存在"
			<< endl;
	}
};
class solution12_2_7 {
public:
	void operator()() {
		cout<<"因为x是叶节点所以x没有子节点，如果x的前驱不是y，那么x必定是y的左节点，此时y是x的后继，反之y是x的前驱"
			<<endl;
	}
};
//////////////////////////////////////////
class binary_tree {
	typedef shared_ptr<treeNode> pt_treeNode;
public:
	void tree_insert(pt_treeNode &rt, pt_treeNode & target) {
		pt_treeNode root = rt;
		pt_treeNode pa = root;
		while (root) {
		    pa = root;
			root = target->key > root->key ? root->right : root->left;				
		}
		target->p = pa;
		if (pa) 
			target->key > pa->key ? pa->right = target : pa->left = target;
		else
			rt = target;
	}
	void recursion_tree_insert(pt_treeNode rt, pt_treeNode &target) {//递归版本的插入
		if (!rt) {
			root = target;
			return;
		}
		if (rt->key > target->key) {
			if (rt->left == nullptr) {
				rt->left = target;
				target->p = rt;
				return;
			}
			recursion_tree_insert(rt->left, target);
		}
		else {
			if (rt->right == nullptr) {
				rt->right = target;
				target->p = rt;
				return;
			}
			recursion_tree_insert(rt->right, target);
		}
		
	}
	pt_treeNode tree_maximum(pt_treeNode tr) {
		while (tr->right)
			tr = tr->right;
		return tr;
	}
	pt_treeNode tree_minimum(pt_treeNode tr) {
		while (tr->left)
			tr = tr->left;
		return tr;
	}
	pt_treeNode& getRoot() {
		return root;
	}
	pt_treeNode tree_search(int k) {
		pt_treeNode rt = root;
		while (rt&&rt->key!=k) {
			rt = k > rt->key ? rt->right : rt->left;
		}
		return rt;
	}
	pt_treeNode tree_successor(pt_treeNode rt) {
		if (rt->right) 
			return tree_minimum(rt->right);
		while (rt->p&&rt->p->left != rt)
			rt = rt->p;
		return rt->p;
	}
	pt_treeNode tree_predecessor(pt_treeNode rt) {
		if (rt->left)
			return tree_maximum(rt->left);
		while (rt->p&&rt->p->right != rt)
			rt = rt->p;
		return rt->p;
	}
	void transplant(pt_treeNode &lhs, pt_treeNode &rhs) {
		if (lhs == root) {
			root = rhs;
		}
		else if (lhs == lhs->p->left) {
			lhs->p->left = rhs;
		}
		else {
			lhs->p->right = rhs;
		}
		if(rhs)
			rhs->p = lhs->p;
	}
	void tree_delete(pt_treeNode &target) {
		if (!target)
			return;
		if (!target->left) {
			transplant(target, target->right);
		}
		else if (!target->right) {
			transplant(target, target->left);
		}
		else {
			auto successor = tree_successor(target->right);
			if (successor != target->right) {
				transplant(successor, successor->right);
				successor->right = target->right;
				target->right->p = successor;
			}
			transplant(target, successor);
			successor->left = target->left;
			target->left->p = successor;
		}
	}
	void tree_delete_succ_pre(pt_treeNode &target) {
		if (!target)
			return;
		if (!target->left) {
			transplant(target, target->right);
		}
		else if (!target->right) {
			transplant(target, target->left);
		}
		else {
			if (flag) {
				flag = false;
				auto successor = tree_successor(target->right);
				if (successor != target->right) {
					transplant(successor, successor->right);
					successor->right = target->right;
					target->right->p = successor;
				}
				transplant(target, successor);
				successor->left = target->left;
				target->left->p = successor;
			}
			else {
				flag = true;
				auto predecessor = tree_predecessor(target->left);
				if (predecessor != target->left) {
					transplant(predecessor, predecessor->left);
					predecessor->left= target->left;
					target->left->p = predecessor;
				}
				transplant(target, predecessor);
				predecessor->right = target->right;
				target->right->p = predecessor;
			}
		}
	}

	void inorder_tree_walk(pt_treeNode rt,size_t counter_hight=0) {//中序遍历交换right和left的位置是因为打印出来的左右子树是反的
		if (rt) {
			++counter_hight;
			inorder_tree_walk(rt->right, counter_hight);
			for (size_t i = counter_hight; i != 0; --i)
				cout << "\t";
			cout << rt->key << endl;
			inorder_tree_walk(rt->left, counter_hight);
		}
	}

private:
	pt_treeNode root;
	bool flag = true;
};
/////////////////////////////////
class solution12_3_1 {
public:
	void operator()() {
		for (auto i : vect)
			bintree.recursion_tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
	}
private:
	vector<int>vect{ 12,5,18,2,9,15,19,13,17 };
	binary_tree bintree;
};

class solution12_3_2 {
public:
	void operator()() {
		cout << "查找这个关键字需要比对该关键字所在节点的关键字，而插入不需要"
			<< endl;
	}
};

class solution12_3_3 {
public:
	void operator()() {
		cout << "tree_insert 所进行的比较其实和快速排序相同，当序列是有序时会形成一棵单孩子数，花费cn^2,最好情况完全二叉树为cnlgn"
			<< endl;
	}
};

class solution12_3_4 {
public:
	void operator()() {
		cout << "不可交换，考虑一个有左右孩子的节点A,有一个左孩子B,而且B没有左右孩子 \n"
			<< "A的后继D不是A的右孩子，那么删除A,B和删除B,A后的树是不一样的"
			<< endl;
		
	}
};
class solution12_3_5 {
public:
	void operator()() {
		cout << "如果一个节点只含有这两个指针，那这个树就变成双向链表了，高度为链表长度满足题意"
			<< endl;
	}
};

class solution12_3_6 {
public:
	void operator()() {
		cout << "原树" << endl;
		for (auto i : vect)
			bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "----------------------------------------------" << endl;

		cout << "删除....." << endl;
		for (auto iter = vect.crbegin(); iter != vect.crend(); ++iter) {
			bintree.tree_delete(bintree.tree_search(*iter));
			bintree.inorder_tree_walk(bintree.getRoot());
			cout << "----------------------------------------------" << endl;
		}
		cout << "重新插入" << endl;
		for (auto i : vect)
			bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "----------------------------------------------" << endl;
		cout << "删除....." << endl;
		for (auto iter = vect.crbegin(); iter != vect.crend(); ++iter) {
			bintree.tree_delete_succ_pre(bintree.tree_search(*iter));
			bintree.inorder_tree_walk(bintree.getRoot());
			cout << "----------------------------------------------" << endl;
		}
	}
private:
	vector<int>vect{ 11,16,13,21,5,8,2,7,9,3,6,1 };
	binary_tree bintree;
};

class solution12_4_1 {
public:
	void operator()() {
		cout << "使用数学归纳法， 首先证明基本情况，当n=1时等式成立，然后假设当n=n-1 时等式成立，则有等式 ∑（i=0,n-1-1) C(i+3,3)=C(n+2,4) \n"
			<< "当n=n 时有等式 ∑（i=0,n-1) C(i+3,3)=∑（i=0,n-1-1) C(i+3,3)+C(n+2,3)=C(n+2,4)+C(n+2,3)=C(n+3,4)"
			<< endl;
	}
};

class solution12_4_2 {
public:
	void operator()() {
		cout << "参考公开课中教授的讲解 ，首先建立一棵有x个节点的满二叉树，树的高度为lgx,然后将一棵有n^(1/2)-lgx个节点的单边树连在之前满二叉树的 \n"
			<< "一个叶节点上，整个树的高度n^(1/2)-lgx+lgx=n^(1/2)显然是w(lgn),平均下来<=(n*lg(n-n^(1/2))+n^(1/2)*n^(1/2))/n=Θ(lgn)"
			<< endl;
	}
};

class solution12_4_3 {
public:
	void operator()() {
		cout << "翻译的不太好，不太了解题目的意思，直接看答案了 例如n=3。排列213和231是同一棵BST。"
			<< endl;
	}
};

class solution12_4_4 {
public:
	void operator()() {
		cout << "f''(x)>0"
			<< endl;
	}
};

class solution12_4_5 {
public:
	void operator()() {
		cout << ""/////////////////////
			<< endl;
	}
};

//思考题

class solution12_1 {
public:
	void operator()() {
		cout << "a.当具有相同关键字的序列越多，整个序列趋近有序，所以渐进性能趋近n^2 \n"
			<< "b.当整个序列都是相同关键字，可以构建一个完整二叉树，每次运行时不会偏向一边，O(nlgn) \n"
			<< "c.O(lgn) 如果少于一半的相同，树的高度期望是lg(n/2)=lgn,如果有只有常数个不同，树的高度为O(1),插入为O(1) \n"
			<< "d.最坏情况是总是选择left或right，此时为O(n^2),期望为O(nlgn)"
			<< endl;
	}
};

class solution12_2 {
	typedef shared_ptr<treeNode> pt_bool;
public:
	void operator()() {
		cout << "虽然节点中不用存储原关键字，当是要先区别深浅阴影节点还是需要有一个标记，我的程序为了方便就直接用int标记了，存在书籍为1，否则为0 \n"
			<< "建立一棵radix_tree树花费Θ（n)，注意n所代表的意义，然后先序输出所有标记为1的节点，此时花费Θ(n)"
			<< endl;
		for (auto &i : vect)
			insert(i);
		preorder_radix_tree_sort_walk(root, "");
	}
private:
	vector<string>vect{ "0","1011","011","100","10" };
	pt_bool root=shared_ptr<treeNode>(new treeNode(0));
	void insert(string &key) {
		if (key.empty())
			return;
		auto rt = root;
		for (auto iter = key.begin(); iter != key.end() - 1;++iter) {
			if (*iter == '0') {
				if (!rt->left)
					rt->left = shared_ptr<treeNode>(new treeNode(0));
				rt = rt->left;
			}
			else {
				if (!rt->right)
					rt->right = shared_ptr<treeNode>(new treeNode(0));
				rt = rt->right;
			}
		}
		if (key.back() == '0') {
			if (!rt->left)
				rt->left = shared_ptr<treeNode>(new treeNode(1));
			else
				rt->left->key = 1;
		}
		else {
			if (!rt->right)
				rt->right = shared_ptr<treeNode>(new treeNode(1));
			else
				rt->right->key = 1;
		}
	}
	void preorder_radix_tree_sort_walk(pt_bool rt,string k) {
		if (rt) {
			if (rt->key)
				cout << k << endl;
			preorder_radix_tree_sort_walk(rt->left, k + '0');
			preorder_radix_tree_sort_walk(rt->right, k + '1');
		}
	}
};

class solution12_3 {
public:
	void operator()() {
		cout << "a.定义如此 \n"
			<< "b.这个我在之前一个类似的题目上已经证明了 \n"
			<< "c.同上 \n"
			<< "d.同上 \n"
			<< "e.我在7-3已经证明，此题类似 \n"
			<< "f.程序如下，每次选择beg作为划分的主元"
			<< endl;
			for(auto i:vect)
				bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "\n" << "排序过程中的比较数对" << endl;
		quick_sort(0, vect.size() - 1);
		cout << "\n" << "排序完成后" << endl;
		for (auto i : vect)
			cout << i << endl;
	}
private:
	vector<int>vect{ 5,3,7,1,9,2,8,4,6 };
	binary_tree bintree;
	void quick_sort(size_t beg, size_t end) {
			swap(vect[beg], vect[end]);
			auto key = vect[end];
			size_t i = beg-1;
			for (size_t j = beg; j != end; ++j) {
				cout << key <<"\t"<< vect[j] << endl;
				if (vect[j] < key) {
					++i;
					swap(vect[i], vect[j]);
				}
			}
			swap(vect[end], vect[++i]);
			if(i!=beg)
				quick_sort(beg, i - 1);
			if(i!=end)
				quick_sort(i + 1, end);
		}
	
};

class solution12_4 {
public:
	void operator()() {
		cout << "a.可以解释为含有k个节点的左子树不同二叉树和含有n-k-1个节点的右子树不同二叉树的组合 \n"
			<< "b.xB(x)^2=x*(∑[n=0,∞] bnx^n)*(∑[n=0,∞] bnx^n)={(∑[n=0,∞] bnx^（n+1）)}*(∑[n=0,∞] bnx^n) \n"
			<< "取大括号{}括起来的每一个项与后面的相乘，下面只写出三项 ，分别是b0x^1,b1x^2,b2x^3 与后面每一项的乘积 \n"
			<< "b0^2*x^1+b0b1*x^2+b0b2*x^3...."
			<< "b2b0x^2+b2b1x^3+b2b2x^4...."
			<< "b3b0x^3+b3b1x^4+b3b2x^5..."
			<< "可以得到原式的前三项的系数为 \n"
			<< "b0^2*x^1+(b0b1+b0b2)*x^2+(b0b2+b2b1+b3b0)x^3..... \n"
			<< "根据a所证明的等式可以得到该等式成立 \n"
			<< "c.我看了答案，非常复杂，没有比较好的数学基础的人很难看出其中规律，直接放弃 \n"
			<< "d.用斯特林公式对c中证明出来的等式求解"
			<< endl;
	}
};
#endif