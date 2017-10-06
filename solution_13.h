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
		cout << "��ȫ������������������Ϊ������ĺͱ���С��һ���࣬���Ը�ֵΪ8��Ȼ����ɷ�������Ϊ��ȫ���������Կ�������������õ���� \n"
			<< "������Ԫ�ǻ������е���λ����Ҳ����˵����ֻ��Ҫ��[1..15]ȡ��λ��8�����ֳ�������[1..7]��[8...15],Ȼ��ֱ�������������� \n"
			<< "ȡ��λ��4,12���������������ϵ��´����ҵ�����Ϊ8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 \n"
			<< "bk=2,������ڵ�һ�㣬��2,4��Ⱦɫ�ɺ�ɫ������Ϊ��ɫ \n"
			<< "bk=3,��2��3,4����һ��Ⱦ�ɺ�ɫ��������ɫ \n"
			<< "bk=4,ȫȾ�ɺ�ɫ"
			<< endl;
	}
};

class solution13_1_2 {
public:
	void operator()() {
		cout << "��������4��ֻ�к�ɫʱ�Ǻ������������"
			<< endl;
	}
};

class solution13_1_3 {
public:
	void operator()() {
		cout << "�ǣ���Ϊ֮ǰ����4�����������ڵ��ɺ�ɫ������������� "
			<< endl;
	}
};

class solution13_1_4 {
public:
	void operator()() {
		cout << "û̫�����Ŀ��˼"
			<< endl;
	}
};

class solution13_1_5 {
public:
	void operator()() {
		cout << "���ݵ�4�����ʿ�֪�����ں���y����ɫ�ڵ��·����������x=y-1����ɫ�ڵ㣬����������Ժ�ɫ�ڵ���ͷ��ÿ���ڵ�ֻ��һ���ӽڵ� \n"
			<< "��ɫ����ı䣬���һ��ɫ�ڵ���������ɫ�ڵ������ \n"
			<< "Ҫ��������5������ڸ�Ϊbk,���·��Ϊbk+1,�·��ֻ��Ϊbk+1+bk,��֤"
			<< endl;
	}
};

class solution13_1_6 {
public:
	void operator()() {
		cout << "�����������������������������ڵ���ɫ�������У�2^(2^k)-1,���ٵ������ȫ�Ǻ�ɫ�ĵ�������k+1"
			<< endl;
	}
};
class solution13_1_7 {
public:
	void operator()() {
		cout << "���ݵ�4�����ʿ�֪�����ں���y����ɫ�ڵ��·����������x=y-1����ɫ�ڵ㣬����������Ժ�ɫ�ڵ���ͷ��ÿ���ڵ�ֻ��һ���ӽڵ� \n"
			<< "��ɫ����ı䣬���һ��ɫ�ڵ���������ɫ�ڵ���������Ա�ֵΪy/(y-1),��y=2ʱȡ�����ֵ2����С��ֵΪ0���ڵ�ȫΪ��ɫ "
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
	bool color;//true �����ɫ
	pt_rbt p;
	pt_rbt left;
	pt_rbt right;
};
///////////////////////
class read_black_tree {
public://�ں����������nullptr����nil���棬nil���Լ����õ�һ�����������ݵĺ�ɫ�ڵ�
	void left_rotate(pt_rbt target) {//����
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
	void right_rotate(pt_rbt target) {//����
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
	void rb_insert(pt_rbt target) {//����ڵ�
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
		rb_insert_fixup(target);//����ڵ���޸����������
		print(root);/////////////////////////////////
		cout << "------------------------------------------------------------------"<<endl;/////////////////////////////////
	}
	void rb_insert_fixup(pt_rbt target) {//Ҫ�뽫�޸������������д�ԣ�����Լ���������������λ�����
		while (!target->p->color) {//�������ڵ�ĸ��ڵ����ɫ�Ǻ�ɫ������Ҫѭ���޸�
			auto grandpar = target->p->p;//��¼үү�ڵ�
			if (target->p == grandpar->left) {//���Ŀ��ڵ���үү�������Ľڵ��Ӧ���1,2,3
				if (!grandpar->right->color) {//�����ڵ��Ǻ�ɫ��Ӧ���1
					grandpar->left->color = true;
					grandpar->right->color = true;
					grandpar->color = false;
					target = grandpar;
				}
				else {//��ڵ��Ǻ�ɫ��Ӧ���2,3������������������ִ�����Ϳ���ֱ���˳�
					if (target ==target->p->right) {//���Ŀ��ڵ��Ǹ��ڵ���ҽڵ��Ӧ���2����ʱĿ��ڵ��븸�ڵ��үү�ڵ㲻��һ������
						left_rotate(target->p);//��Ҫ�������ڵ�ʹ����һ������
						target = target->left;
					}
					grandpar->color = false;//���3��Ӧ����һ�����ϣ���ʱֻ��Ҫ�ı���ɫ��ת
					grandpar->left->color = true;
					right_rotate(grandpar);
				}
			}
			else {//���Ŀ��ڵ���үү�������Ľڵ��Ӧ���4,5,6
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
	void rb_delete(pt_rbt target) {//ɾ���ڵ�
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
				x->p = y;//��x���ڱ�ʱΪɾ����׼��
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
				if (!w->color) {//���1������ֵܽڵ��Ǻ�ɫ
					x->p->color = false;
					w->color = true;
					left_rotate(x->p);
					w = x->p->right;
				}
				
				if (w->right->color&&w->left->color) {//��������ֵܽڵ�������ӽڵ㶼�Ǻ�ɫ
					w->color = false;
					x = x->p;
				}
				else if (w->right->color) {//�ֵܽڵ����ڵ�Ϊ��ɫ
					w->color = false;
					w->left->color = true;
					right_rotate(w);
					w = x->p->right;
				}
				if (!w->right->color) {//�ֵܽڵ���ҽڵ�Ϊ��ɫ
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
			rt->color ? cout << "��" << endl : cout << "��" << endl;
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
		cout << "��������д��"<<endl;
	}
};

class solution13_2_2 {
public:
	void operator()() {
		cout << "��Ҷ�ڵ㿪ʼ�������ڵ���ÿһ���ڵ㶼��һ�����ϵ���˫�׽ڵ��Ӧ��·����ÿһ��·������Ӧһ����ת��������n-1�ֿ��ܵ���ת"
			<< endl;
	}
};

class solution13_2_3 {
public:
	void operator()() {
		cout << "a�ĸ߶ȼ�1��b�ĸ߶Ȳ��䣬c�ĸ߶ȼ�1"
			<< endl;
	}
};
class solution13_2_4 {
public:
	void operator()() {
		cout << "ͼ13-2������ͼ�е�һ����������ұߵ���ʽ��Ȼ��Խڵ�x�������ٶ�y�ڵ����� \n"
			<<"�κη��Ҳ���չ��������һ����ʽ�����Ի����⼸����ʽ��һ�� \n"
			<< "�������ڽڵ��������ȿ��Խ����������Ҳ���չ������Ϊ�������ǶԳƵģ���Ȼ������״����a,b��������cn����ת����Ҳ���չ�� \n"
			<< "����aҪת����bֻ��Ҫ��ת�����Ҳ���չ����Ȼ����bת�����Ҳ���չ���ķ�����ת��"
			<< endl;
	}
};

class solution13_2_5 {
public:
	void operator()() {
		cout << "�Ҳ���չ���Ѿ����������������Ҳ���չ��T1����������������Ҳ���չ��T2 \n"
			<< "T1������ĸ��ڵ㲻����������������������Ҫ���������Ľڵ�ת���T2�ĸ��ڵ���Ҫ����O(n)���ݹ�õ�T2 \n"//���
			<< "ʱ�临�Ӷ�T(n)=T(nL)+T(nR)+O(n)=O(n^2)������nL+nR=n-1��"
			<< endl;
	}
};

class solution13_3_1 {
public:
	void operator()() {
		cout << "���ƻ�����5�����������5���ƻ���򵥵ķ������Ǹı���ɫ"
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
		cout << "�鷳��д"
			<< endl;
	}
};
class solution13_3_4 {
public:
	void operator()() {
		cout << "�㷨�иı���ɫ����������֣����ڵ����ɫ�����ڵ����ɫ��үү�ڵ����ɫ����ڵ�͸��ڵ����ƽ�еģ���֮�����ܽ���ѭ���������� \n"
			<< "���ڵ����ɫ�Ǻ�ɫ�ģ�Ҳ����˵���ڵ����ڵ㲻����Ϊnil,������ڵ����ɫ�Ǻ�ɫ����˵�����ڵ㲻�Ǹ��ڵ㣬��ʱүү�ڵ�Ҳ�Ͳ�����\n"
			<< "��nil"
			<< endl;
	}
};

class solution13_3_5 {
public:
	void operator()() {
		cout << "�������n-1���ڵ��û�к�ڵ㣬��ô�����n���ڵ��һ�������Ǻ�ڵ�������޸� "
			<< endl;
	}
};

class solution13_3_6 {
public:
	void operator()() {
		cout << " We need to remove line 8 from RB - INSERT and modify RB - INSERT - FIXUP."
			<< "At any point in RB - INSERT - FIXUP we need only keep track of at most 2 ancestors:"
			<< "z.p and z.p.p.We can find and store each of these nodes in log n time"
			<< "and use them for the duration of the call to RB - INSERT - FIXUP.This won��t"
			<< "change the running time of RB - INSERT"
			<< endl;
	}
};


class solution13_4_1 {
public:
	void operator()() {
		cout << "����Ҫɾ�����Ǹ��ڵ� �� \n"
			<< "������ڵ����������ӣ����20�лὫ�¸��ڵ����ɫ��Ϊ��ɫ \n"
			<< "������ڵ�ֻ��һ�����ӣ�x�����Ϊ�µĸ��ڵ㣬�����޸������\n"
			<< "�������ѭ������23�б���Ϊ��ɫ \n"
			<< "�����ɾ���Ľڵ㲻�Ǹ��ڵ㣬���û�н����޸�����\n"
			<< "��ô���ڵ����ɫ����ı䣬��������޸����� \n"
			<< "ֻ���������ṩ�������������Ϊ������������ǶԳƵģ�\n"
			<< "�������1����������ѭ��2��ֱ���˳�������������ĸ��ڵ� \n"
			<< "�Ǻ�ɫ�ģ�������2�󲻻�ı�֮ǰ���ڵ����ɫ�������ܱ�֤\n"
			<< "�������ڵ����ɫ�Ǻ�ɫ�ġ�����֮��������������������4\n"
			<< "�Ż���ֹ�������4��ֹ��x�����µĸ��ڵ㲢��23�б�Ϊ��ɫ \n"
			<<"���Ը��ڵ�ʼ��Ϊ��ɫ"
			<< endl;
	}
};

class solution13_4_2 {
public:
	void operator()() {
		cout << "�������ѭ��x��ֱ����Ϊ��ɫ"
			<< endl;
	}
};

class solution13_4_3 {
public:
	void operator()(){
		cout << "������......" << endl;
		for (auto i : ins)
			rbt.rb_insert(shared_ptr<rbtNode>(new rbtNode(i,false,rbt.get_nil(), rbt.get_nil(), rbt.get_nil() )));
		cout << "ɾ����...." << endl;
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
		cout << "x�п������ڱ������Գ���������x��Ա�ڸ�ֵ����ߣ� \n"
			<< "x����x�ĳ�Ա�ڲ��������ұߵĶ����ܻ�����޸��ڱ� \n"
			<< endl;
	}
};

class solution13_4_6 {
public:
	void operator()() {
		cout << "��Ϊw�Ǻ�ɫ�ģ�����x.pһ���Ǻ�ɫ��"
			<< endl;
	}
};

class solution13_4_7 {
public:
	void operator()() {
		cout << "���Կ�������ǰ��һ��" << endl;
		cout << "������......" << endl;
		for (auto i : ins)
			rbt.rb_insert(shared_ptr<rbtNode>(new rbtNode(i, false, rbt.get_nil(), rbt.get_nil(), rbt.get_nil())));
		cout << "ɾ����...." << endl;
		rbt.rb_delete(rbt.search(1));
	}
private:
	vector<int>ins{ 3,2,1 };
	read_black_tree rbt;

};

//˼����

class solution13_1 {
public:
	void operator()() {
		cout << "a.�����Ƚڵ�\n"
			<< "b.����Ͳ�д�ˣ��Զ����²���ʱ�½�ÿһ�������Ľڵ㣬\n"
			<< "ÿ����һ���ڵ㣬�͸��Ƹýڵ��ȫ�����ԣ�ֱ�������½ڵ�\n"
			<< "c.h  \n"
			<< "d.��Ϊÿһ���ڵ��p���Զ�ֻ��ָ��һ�����ڵ㣬����ÿһ��\n"
			<< "�ڵ㶼Ҫ����һ��\n"
			<< "e.��Ϊ��������Ա�֤����ΪO(lgn) \n"
			<< endl;
	}
};
class solution13_2 {
public:
	void operator()() {
		cout << "a.�����������Ľ�������ʱ��Ϊ��(lgn),ÿ�β�����ɺ��root����\n"
			<< "��nil�ĺ�ɫ�ڵ����Ҳֻ��Ҫclgn,���Բ������Ӷ���Ľ�������ʱ��\n"
			<< "�Ͷ���ռ䣬������ɫ�ڵ��Լ�����\n"
			<< "b.ά��һ��ָ�룬��ʼʱָ��T1.root,ֻҪ��ǰ�ڵ���right!=nil \n"
			<< "curr��ָ���ҽڵ㣬����ָ����ڵ㣬����¼�ڵ�ĺڸ�ֱ������T2.bh \n"
			<< "c.�½���xΪ�ؼ��ֵĽڵ㣬left=Ty,right=T2....\n"
			<< "d.��ɫ����x����rb_insert_fixup()�У���Ϊ��������������޸�����2,4��\n"
			<< "e.��T2�кڸ�ΪT1.bh�ľ�����С�ؼ��ֵĺ�ɫ�ڵ�y \n"
			<< "f.���ң��޸�����O(lgn)"
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
		cout << "a.������ֻ֤��Ҷ�ڵ����һ�㲻�����ģ���Ȼ�߶Ȳ��Ϊ1 \n"
			<< "����Ҷ�ڵ����һ�㣬������2^h-1���ڵ㣬��������O(lgn) \n"
			<< "b.��4�������ֻ�����������֣����������ǶԳƵģ����ڵ�\n"
			<<"�սڵ�ĸ߶�Ϊ-1�����ڵ���������߶ȼ��������߶�Ϊ2,������ӽڵ�������ӵ�������\n"
			<<"ͨ����������ӵõ���2�����������������������ڵ㣬���������\n"
			<<"����ƽ����\n"
			<<"c.������,\n"
			<<"d.��Ϊ����ΪO(lgn)�����Ǵ��ϵ����ҵ�����ڵ��λ�ò���Ȼ��ݹ��������ά��avl���ĸ߶�\n"
			<<"��ת�Ͳ���ֻ���ѳ���ʱ�䣬����ΪO(lgn),��Ҫ��תλ�õ��½ڵ�ĸ߶Ⱥ�֮ǰ�߶���ͬ�����������Ƚڵ㲻��Ҫ��ת\n"
			<<"������תO(1)"
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
		if (!target)//�սڵ�ĸ߶�Ϊ-1
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
	void avl_insert(pt_avl rt,pt_avl target) {//avl������
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
				if (target->key > rt->left->key)//���1ת��Ϊ���2
					left_rotate(rt->left);
				right_rotate(rt);//�������2
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
		}//�ڵ�߶�Ϊ���������߶�����߼�1
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
