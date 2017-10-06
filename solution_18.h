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
		cout << "������Ϊ1�������"
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
		cout << "ÿ����ɫ�ڵ������1,2����ɫ�ڵ㣬��������ÿ���ڵ������\n"
			<< "2,3���ؼ��֣�������2-3��"
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
	pt_b maxiumn(pt_b rt) {//���ؽ��ܸ��ڵ����Сֵ����
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
	void b_tree_merge(pt_b rt, int i) {//�ϲ�rt[i]��rt[i+1]
		auto pre = rt->c[i];//����������ƣ������ڵ�Ĺؼ��ִ�С��Ϊt-1
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
			if (rt->c.empty())//�����ѿ�
				return;
			root = rt->c[0];
			rt = root;
		}
		int i = rt->n-1;
		while (i >= 0 && rt->key[i] > k)//�ҵ�������k���±�
			--i;

		if (rt->leaf && (i < 0 || rt->key[i] != k))//�ؼ��ֲ�������
			return;

		if (i>=0&&rt->key[i] == k) {//�ýڵ㺬�йؼ���
			if (rt->leaf) {//Ҷ�ڵ�ֱ��ɾ������Ϊ�ݹ�Ĺ�ϵ��Ҷ�ڵ��nһ������t-1
				for (int j = i; j < rt->n - 1; ++j)
					rt->key[j] = rt->key[j + 1];
				rt->n -= 1;
				rt->key.resize(rt->n);
			}
			else {//�ؼ������ڲ��ڵ�		
		
				if (rt->c[i]->n > t - 1) {//ǰһ���ڵ��n����t-1���ҵ��ùؼ��ֵ�ǰ�������ݹ�ɾ����ǰ��һ����Ҷ�ڵ���
					auto pre = maxiumn(rt->c[i]);//��ǰ������ؼ��֣����ͬ��
					int pre_key = pre->key.back();
					b_tree_delete(root, pre_key);
					rt->key[i] = pre_key;
				}
				else if (rt->c[i + 1]->n > t - 1) {//��һ���ڵ��n����t-1
					auto suc = miniumn(rt->c[i + 1]);
					int suc_key = suc->key.front();
					b_tree_delete(root, suc_key);
					rt->key[i] = suc_key;
				}
				else {//�ϲ�ǰ��ڵ㣬��ʱ�ؼ��ֽ���ǰһ���ڵ㣬�ݹ�ɾ��
					b_tree_merge(rt, i);
					b_tree_delete(rt->c[i], k);
				}
			}
		}
		else {//��ǰ�ڵ㲻�����ؼ���
			i += 1;
			auto tar = rt->c[i];//�ؼ������������ĸ��ڵ㣬����ؼ��������еĻ�
			
			if (tar->n > t - 1)//���ڵ��n����t-1
				b_tree_delete(tar, k);
			else {//���ڵ��nС�ڵ���t-1
				if (!i) {//i=0,û��ǰ���ڵ㣬�����ǰ���ǽ��������ǹؼ���
					auto suc = rt->c[i + 1];
					if (suc->n > t - 1) {//ǰ�ڵ�n����t-1
						left_replace(rt, i);//Ϊ���е�3a���֮һ
						b_tree_delete(rt->c[i], k);
					}
					else {//ǰ��n<=t-1,�ϲ�
						b_tree_merge(rt, i);
						b_tree_delete(rt->c[i], k);
					}
				}
				else if (i == rt->n) {//û�к�̽ڵ㣬
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
				else {//��ǰ���ͺ�̽ڵ�
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
			cout << rt->key.size() << "|" << rt->c.size() << "|" << rt->n << endl;
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
		cout << str << "����д�����....." << endl;
	}
	void disk_read(string str) {
		cout << "���ڴӴ��̶�ȡ" << str << "......" << endl;
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
		cout << "û��"
			<< endl;
	}
};

class solution18_2_3 {
public:
	void operator()() {
		cout << "1.�Ӹ��ڵ�r��ʼ�������ǰ�ڵ���Ҷ�ڵ㣬���ص�ǰ�ڵ�ĵ�һ���ؼ���\n"
			<< "2.����r->c[0]�����һ��\n"
			<< "����Ѱ�ҵ��ùؼ������ڽڵ�n��ͬʱ��¼Ѱ�ҹ����б���С�Ĺؼ���k \n"
			<< "������ڽڵ�nΪҶ�ڵ㣬����k,ע��k�����������Ƚڵ�Ĺؼ���Ҳ������\n"
			<< "ͬһ��Ҷ�ڵ�Ĺؼ��֣�\n"
			<< "����ؼ������ڽڵ�n��ΪҶ�ڵ㣬���ùؼ���ǰһ������ָ�����max()\n"
			<< "�ú������ؽ���ָ����Ϊ���ڵ�����ֵ��Ѱ�����ֵ����Сֵ����\n"
			<< endl;
	}
};

class solution18_2_4 {
public:
	void operator()() {
		cout << "����n)" << endl;//���������̫����ճ��
	}
};

class solution18_2_5 {
public:
	void operator()() {
		cout << "����������жϸýڵ��ǲ���Ҷ�ڵ㣬ʹ���µ�tֵ�ж��Ƿ�Ϊ��"
			<< endl;
	}
};

class solution18_2_6 {
public:
	void operator()() {
		cout << "��������ѰҶ�ڵ�Ϊ��׼����Ѱʱ��Ϊ��a+bt)log[t,(n+1)/2] \n"
			<< "��ʽ���󵼺�t=3����Сֵ"
			<< endl;
	}
};

class solution18_3_2 {
public:
	void operator()() {
		//string str = "LKJHGFDSAZXCVBNMPOIUYTREWQ";
		string str = "mnbvcxzasdfghjklpoiuytrewq";
		for (auto i : str) 
			bt.b_tree_insert(i);
		print(bt.getRoot());
		cout << "\n-----------------------------\n";
		cout << "ɾ����...\n";
		//string s = "QAZXSWEDCRFVTGBYHNUJMIKOLP";
		for (auto i : str) {
			cout << "ɾ���ؼ���" << i << endl;
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
			cout << rt->key.size() << "|" << rt->c.size() << "|" << rt->n;
			//	<<"|"<<rt->leaf<< endl;

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

//˼����
	
class solution18_1 {
public:
	void operator()() {
		cout << "����̫��"
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
		cout << "���������2-3-4��\n"
			<< "a.���ĸ߶ȵ����Ӻͼ��ٶ����ڸ��ڵ��λ�øı�ģ� ���Բ���ı佥������ʱ��\n"
			<< "b.�ͺ�������������ݽṹ���ƣ������Ʋ�������ڽϸߵ�һ�������ҵ�\n"
			<< "x�ĺ��ʽڵ㣬�ýڵ�ĸ߶ȱ���һ����С���ĸ߶ȴ�1��ע����ҹ�����\n"
			<< "�����ڵ���ѣ������x�ϲ��ϸ������ҵ��ڵ����������һ������Ȼ�����ýڵ�\n"
			<< "��Ϊ��Ŀ�������ƣ�x�ĺ��ʽڵ㲻��������߾������ұ�\n"
			<< "c.��һ���ڵ��в������һ��С��k�Ĺؼ��ֵ��±�ֱ���ҵ�k,\n"
			<< "��Щ�ؼ�����ɵľ��ǹؼ����ϣ��ؼ�����ߵļ��Ͼ������ļ���\n"
			<< "�߶�֮�����1"
			<< "d.�ؼ����������"
			<< endl;
	}
private:
	b_tree bt;
};
#endif
