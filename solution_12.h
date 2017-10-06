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
		cout << "̫�鷳ʡ��"
			<< endl;
	}
};

class solution12_1_2 {
public:
	void operator()() {
		cout << "�����������Ƕ�����һ�ڵ�x,x.left->key<=x.key<=x.right->key,����С���Ƕ�����һ�ڵ㣬x.key<=x.right->key,x.key<=x.left->key \n"
			<< "���Կ������ϵ����ֱ�������ֻ�õ����������ʣ����Կ�����O(n)��ʱ���������С��"
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
	void recursion_inorder_walk( shared_ptr<treeNode>pt) {//�ݹ��������
		if (pt) {
			recursion_inorder_walk(pt->left);
			cout << pt->key << endl;
			recursion_inorder_walk(pt->right);
		}
	}
	void stack_inorder_walk(shared_ptr<treeNode>pt) {//ģ�µݹ�ķǵݹ���ջ�������������
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
	void inorder_walk(shared_ptr<treeNode>pt) {//�ǵݹ��Ҳ���ջ�ĵݹ��㷨���ҵ���Сֵ�󲻶�ȡ����
		shared_ptr<treeNode>succ= minimum(pt);
		while (succ) {
			cout << succ->key << endl;
			succ = successor(succ);
		}
	}
	void recursion_preorder_walk(shared_ptr<treeNode>pt) {//�ݹ��������
		if (pt) {
			cout << pt->key << endl;
			recursion_preorder_walk(pt->left);
			recursion_preorder_walk(pt->right);
		}
	}
	void stack_preorder_walk(shared_ptr<treeNode>pt) {//ģ�µݹ�ķǵݹ���ջ�������������
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
	void inordor_tree_walk(pt_bst curr) {//ʹ�ñ�ǵķǵݹ��������
		while (curr) {
			while (curr&&curr->left&&curr->left->flag)//ȷ��������ӡ�Ľڵ�û���������������������Ѿ���ӡ��
				curr = curr->left;
			if (curr->flag) {//�����ǰ�ڵ�û�д�ӡ�����ӡ��ǰ�ڵ㣬���ı���
				cout << curr->key << endl;
				curr->flag = false;
			}
			if (curr&&curr->right&&curr->right->flag)//����ڵ�������������������û�д�ӡ��
				curr = curr->right;
			else//û�������������������Ѿ���ӡ�����򽫵�ǰ�ڵ�����
				curr = curr->p;
		}//ÿ���ڵ㶼ֻ���ʳ����Σ����Ի��Ѧ�(n)
	}
	void preordor_walk(pt_bst rt) {
		if (rt) {
			cout << rt->key << endl;
			preordor_walk(rt->left);
			preordor_walk(rt->right);
		}
	}
	void preordor_tree_walk(pt_bst curr) {//ʹ�ñ�ǵķǵݹ��������
		while (curr) {
			while (curr&&curr->left&&curr->flag) {//�����ǰ�ڵ�������������δ��������������ǰ�ڵ�
				cout << curr->key << endl;
				curr->flag = false;
				curr = curr->left;
			}
			if (!curr->left&&curr->flag) {//�����ǰ�ڵ�û����������δ��������������ǰ�ڵ�
				cout << curr->key << endl;
				curr->flag = false;
			}
			if (curr&&curr->right&&curr->right->flag)//�����ǰ�ڵ��������û�б�������򽫿������ڵ�ָ���ҽڵ�
				curr=curr->right;
			else//�������Ƶ�ǰ�ڵ�
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
	void postordor_tree_walk(pt_bst curr) {//ʹ�ñ�ǵķǵݹ�������
		while (curr) {
			while (curr&&curr->left&&curr->left->flag)//�����ǰ�ڵ����ڵ�δ����򽫵�ǰ�ڵ�ָ����ڵ�
				curr = curr->left;
			if (curr&&curr->right&&curr->right->flag)//�����ǰ�ڵ���ҽڵ�δ����򽫵�ǰ�ڵ�ָ���ҽڵ�
				curr = curr->right;
			else {//���������������Ҫôû����ڵ������ڵ��Ѿ���� ���� û���ҽڵ�����ҽڵ��Ѿ����
				cout << curr->key << endl;
				curr->flag = false;//��ʱ����ýڵ�������������Ķ���
				curr = curr->p;//�����ǰ�ڵ��Ѿ������˵���Ըýڵ�������������Ѿ�������������ƽڵ�
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
		cout << "�����Ķ���������������ֻ���Һ��ӻ�ֻ�����ӵ������������Ľڵ����������У������ڱȽ�����ģ��"
			<< endl;
	}
};

class solution12_2_1 {
public:
	void operator()() {
		cout << "c,e,�����Լ�������·��ͼ��c��911������912��e��347������299С"
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
		cout << "��ͼ12-2��������ҵĹؼ�����2�����ұߵ�4��ȻС������·���ϵ�6"
			<< endl;
	}
};

class solution12_2_5 {
public:
	void operator()() {
		cout << "����ڵ�ĺ��һ���Ǹýڵ�����������Сֵ�Ľڵ㣬����ýڵ������ӣ���ýڵ㲻����Сֵ \n"
			<< "����ڵ��ǰ���Ǹýڵ�������������ֵ������ýڵ����Һ��ӣ���ýڵ㲻�����ֵ \n"
			<< endl;
	}
};
class solution12_2_6 {
public:
	void operator()(){
		cout << "��λ�����Ĳ��ã��ر�����ԭ���У����ǿ��˴���֮������ģ��������������һ���ڵ�xû������������ô����ڵ�ĺ�̽ڵ�y���㣬��һ�� \n"
			<< "������x���ȵĽڵ㣬����������������е㲻��֤��������Ҫ֤���Ķ����֪������x��y֮�仹��a1,a2...an���ڵ㣬x��a1���ҽڵ㣬a1��a2���ҽڵ�...��an��y����ڵ�"
			<< "��Щ�ڵ����ڵ㻹��������������������������֤����Щ�����ϵĽڵ㲻�ÿ��ǣ�����a1�����������Ľڵ�Ĺؼ���k�ض�С��a1->key,��a1->key<x->key |n"
			<< "y->key>x->key,�����̵ı�Ҫ�����������Ѿ�֤������x,a1,a2,a3....an��Ϊ���Ƚڵ�Ľڵ㶼���������������л����y������ֻ��y�����ȣ�������һ�����ȱ�y�ڵ���ʺϵ���� \n"
			<< "�����Ʋ�����ڵ�g��������x->key<=g->key<=y-<key,Ҫ����x->key<=g->key��y�ض���g����������ĳ���ڵ㣬Ȼ��Ҫ����key<=y-<key��y������g����������ĳ���ڵ� \n"
			<< "����Ȼ������g�ڵ㲻����"
			<< endl;
	}
};
class solution12_2_7 {
public:
	void operator()() {
		cout<<"��Ϊx��Ҷ�ڵ�����xû���ӽڵ㣬���x��ǰ������y����ôx�ض���y����ڵ㣬��ʱy��x�ĺ�̣���֮y��x��ǰ��"
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
	void recursion_tree_insert(pt_treeNode rt, pt_treeNode &target) {//�ݹ�汾�Ĳ���
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

	void inorder_tree_walk(pt_treeNode rt,size_t counter_hight=0) {//�����������right��left��λ������Ϊ��ӡ���������������Ƿ���
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
		cout << "��������ؼ�����Ҫ�ȶԸùؼ������ڽڵ�Ĺؼ��֣������벻��Ҫ"
			<< endl;
	}
};

class solution12_3_3 {
public:
	void operator()() {
		cout << "tree_insert �����еıȽ���ʵ�Ϳ���������ͬ��������������ʱ���γ�һ�õ�������������cn^2,��������ȫ������Ϊcnlgn"
			<< endl;
	}
};

class solution12_3_4 {
public:
	void operator()() {
		cout << "���ɽ���������һ�������Һ��ӵĽڵ�A,��һ������B,����Bû�����Һ��� \n"
			<< "A�ĺ��D����A���Һ��ӣ���ôɾ��A,B��ɾ��B,A������ǲ�һ����"
			<< endl;
		
	}
};
class solution12_3_5 {
public:
	void operator()() {
		cout << "���һ���ڵ�ֻ����������ָ�룬��������ͱ��˫�������ˣ��߶�Ϊ��������������"
			<< endl;
	}
};

class solution12_3_6 {
public:
	void operator()() {
		cout << "ԭ��" << endl;
		for (auto i : vect)
			bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "----------------------------------------------" << endl;

		cout << "ɾ��....." << endl;
		for (auto iter = vect.crbegin(); iter != vect.crend(); ++iter) {
			bintree.tree_delete(bintree.tree_search(*iter));
			bintree.inorder_tree_walk(bintree.getRoot());
			cout << "----------------------------------------------" << endl;
		}
		cout << "���²���" << endl;
		for (auto i : vect)
			bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "----------------------------------------------" << endl;
		cout << "ɾ��....." << endl;
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
		cout << "ʹ����ѧ���ɷ��� ����֤�������������n=1ʱ��ʽ������Ȼ����赱n=n-1 ʱ��ʽ���������е�ʽ �ƣ�i=0,n-1-1) C(i+3,3)=C(n+2,4) \n"
			<< "��n=n ʱ�е�ʽ �ƣ�i=0,n-1) C(i+3,3)=�ƣ�i=0,n-1-1) C(i+3,3)+C(n+2,3)=C(n+2,4)+C(n+2,3)=C(n+3,4)"
			<< endl;
	}
};

class solution12_4_2 {
public:
	void operator()() {
		cout << "�ο��������н��ڵĽ��� �����Ƚ���һ����x���ڵ���������������ĸ߶�Ϊlgx,Ȼ��һ����n^(1/2)-lgx���ڵ�ĵ���������֮ǰ���������� \n"
			<< "һ��Ҷ�ڵ��ϣ��������ĸ߶�n^(1/2)-lgx+lgx=n^(1/2)��Ȼ��w(lgn),ƽ������<=(n*lg(n-n^(1/2))+n^(1/2)*n^(1/2))/n=��(lgn)"
			<< endl;
	}
};

class solution12_4_3 {
public:
	void operator()() {
		cout << "����Ĳ�̫�ã���̫�˽���Ŀ����˼��ֱ�ӿ����� ����n=3������213��231��ͬһ��BST��"
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

//˼����

class solution12_1 {
public:
	void operator()() {
		cout << "a.��������ͬ�ؼ��ֵ�����Խ�࣬�������������������Խ�����������n^2 \n"
			<< "b.���������ж�����ͬ�ؼ��֣����Թ���һ��������������ÿ������ʱ����ƫ��һ�ߣ�O(nlgn) \n"
			<< "c.O(lgn) �������һ�����ͬ�����ĸ߶�������lg(n/2)=lgn,�����ֻ�г�������ͬ�����ĸ߶�ΪO(1),����ΪO(1) \n"
			<< "d.����������ѡ��left��right����ʱΪO(n^2),����ΪO(nlgn)"
			<< endl;
	}
};

class solution12_2 {
	typedef shared_ptr<treeNode> pt_bool;
public:
	void operator()() {
		cout << "��Ȼ�ڵ��в��ô洢ԭ�ؼ��֣�����Ҫ��������ǳ��Ӱ�ڵ㻹����Ҫ��һ����ǣ��ҵĳ���Ϊ�˷����ֱ����int����ˣ������鼮Ϊ1������Ϊ0 \n"
			<< "����һ��radix_tree�����Ѧ���n)��ע��n����������壬Ȼ������������б��Ϊ1�Ľڵ㣬��ʱ���Ѧ�(n)"
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
		cout << "a.������� \n"
			<< "b.�������֮ǰһ�����Ƶ���Ŀ���Ѿ�֤���� \n"
			<< "c.ͬ�� \n"
			<< "d.ͬ�� \n"
			<< "e.����7-3�Ѿ�֤������������ \n"
			<< "f.�������£�ÿ��ѡ��beg��Ϊ���ֵ���Ԫ"
			<< endl;
			for(auto i:vect)
				bintree.tree_insert(bintree.getRoot(), shared_ptr<treeNode>(new treeNode(i)));
		bintree.inorder_tree_walk(bintree.getRoot());
		cout << "\n" << "��������еıȽ�����" << endl;
		quick_sort(0, vect.size() - 1);
		cout << "\n" << "������ɺ�" << endl;
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
		cout << "a.���Խ���Ϊ����k���ڵ����������ͬ�������ͺ���n-k-1���ڵ����������ͬ����������� \n"
			<< "b.xB(x)^2=x*(��[n=0,��] bnx^n)*(��[n=0,��] bnx^n)={(��[n=0,��] bnx^��n+1��)}*(��[n=0,��] bnx^n) \n"
			<< "ȡ������{}��������ÿһ������������ˣ�����ֻд������ ���ֱ���b0x^1,b1x^2,b2x^3 �����ÿһ��ĳ˻� \n"
			<< "b0^2*x^1+b0b1*x^2+b0b2*x^3...."
			<< "b2b0x^2+b2b1x^3+b2b2x^4...."
			<< "b3b0x^3+b3b1x^4+b3b2x^5..."
			<< "���Եõ�ԭʽ��ǰ�����ϵ��Ϊ \n"
			<< "b0^2*x^1+(b0b1+b0b2)*x^2+(b0b2+b2b1+b3b0)x^3..... \n"
			<< "����a��֤���ĵ�ʽ���Եõ��õ�ʽ���� \n"
			<< "c.�ҿ��˴𰸣��ǳ����ӣ�û�бȽϺõ���ѧ�������˺��ѿ������й��ɣ�ֱ�ӷ��� \n"
			<< "d.��˹���ֹ�ʽ��c��֤�������ĵ�ʽ���"
			<< endl;
	}
};
#endif