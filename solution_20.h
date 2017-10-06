#pragma once
#ifndef _SOLUTION_20_H_
#define _SOLUTION_20_H_
#include<iostream>
#include<vector>
#include<memory>
#include<cmath>
using namespace std;

class solution20_1_1 {
public:
	void operator()() {
		cout << "������A��Ϊ��ά���飬����һά���������Ԫ�ص��߼���\n"
			<< "��Ϊԭʼ���ݽṹ���߼���\n"
			<< endl;
	}
};

class solution20_1_2 {
public:
	void operator()() {
		cout << "������Ԫ���е�λ������Ϊָ�룬ָ��Ҳ������Ϊλ����ʹ��\n"
			<< endl;
	}
};

class solution20_1_3 {
public:
	void operator()() {
		cout  << "�����Ʋ��������ע�⵽����������ڵ�ᱻ��ΪҶ�ڵ�\n"
			<< "�������У�����ǰ���ͺ��һ���������Ƚڵ��У����Լ�¼���\n"
			<< "һ������x�����Ƚڵ�\n"
			<< endl;
	}
};


class solution20_1_4 {
public:
	void operator()() {
		cout << "�߶�Ϊk��ʱ��O��U^(1/k))"
			<< endl;
	}
}; 

/////////////////////////////
struct vebNode;
typedef shared_ptr<vebNode> pt_veb;
const size_t nil = SIZE_MAX;
//�����ֵ
struct vebNode {
	vebNode(size_t u=0,size_t min=nil,size_t max=nil,pt_veb sum=nullptr):
		u(u), min(min), max(max), summary(sum) {}

	size_t u;
	size_t min;
	size_t max;
	pt_veb summary;
	vector<pt_veb>cluster;
};

class veb_tree {
public://maxΪ��С�����������ֵ��ֵ
	 veb_tree(size_t max):vrt(shared_ptr<vebNode>(new vebNode )){
		 new_space(vrt, get_power(max));//��Ϊ�������ڴ�
	 }

	size_t veb_tree_minimum(pt_veb v) {
		return v->min;
	}
	size_t veb_tree_maximum(pt_veb v) {
		return v->max;
	}

	void veb_tree_insert(pt_veb v,size_t k) {
		if (v->min == nil) {
			veb_empty_tree_insert(v, k);
		}
		else {
			if (k < v->min)
				swap(k, v->min);
			if (v->u > 2) {
				if (veb_tree_minimum(v->cluster[high(k,v->u)]) == nil) {
					veb_tree_insert(v->summary, high(k, v->u));
					veb_empty_tree_insert(v->cluster[high(k, v->u)], low(k, v->u));
				}
				else
					veb_tree_insert(v->cluster[high(k, v->u)], low(k,v->u));

			}
			if (k > v->max)
				v->max = k;
		}
	}

	size_t veb_tree_successor(pt_veb v, size_t k) {
		if (v->u == 2) {
			if (k == 0 && v->max == 1)
				return 1;
			return nil;
		}
		else if (v->min != nil&&v->min > k)
			return v->min;
		else {
			auto maxlow = veb_tree_maximum(v->cluster[high(k, v->u)]);
			if (maxlow != nil&&low(k, v->u) < maxlow) {
				auto offset = veb_tree_successor(v->cluster[high(k, v->u)], low(k, v->u));
				return index(high(k, v->u), offset,v->u);
			}
			else {
				auto succ_cluster = veb_tree_successor(v->summary, high(k, v->u));
				if (succ_cluster == nil)
					return nil;
				else {
					auto offset = veb_tree_minimum(v->cluster[succ_cluster]);
					return
						index(succ_cluster, offset,v->u);
				}
			}
		}
	}

	size_t veb_tree_predecessor(pt_veb v, size_t k) {
		if (v->u == 2) {
			if (k == 1 && v->min == 0)
				return 0;
			return nil;
		}		 
		else if (v->max != nil&&v->max < k) {
			return v->max;
		}
		else {
			auto min_low = veb_tree_minimum(v->cluster[high(k, v->u)]);
			if (min_low != nil&&min_low < low(k,v->u)) {
				auto offset = veb_tree_predecessor(v->cluster[high(k, v->u)], low(k, v->u));
				return index(high(k,v->u),offset, v->u);
			}
			else {
				auto prece_cluster = veb_tree_predecessor(v->summary, high(k, v->u));
				if (prece_cluster == nil)
					if (v->min != nil&&k > v->min)
						return v->min;
					else
						return nil;
				else {
					auto offset = veb_tree_maximum(v->cluster[prece_cluster]);
					return
						index(prece_cluster, offset, v->u);
				}
			}
		}
	}
	bool veb_tree_member(pt_veb v, size_t k) {
		if (k == v->min || k == v->max)
			return true;
		else if (v->u == 2)
			return false;
		else
			return
			veb_tree_member(v->cluster[high(k, v->u)], low(k, v->u));
	}
	void veb_tree_delete(pt_veb v, size_t k) {
		if (v->min == v->max) {
			v->min = nil;
			v->max = nil;
		}
		else if (v->u == 2) {
			if (k == 0)
				v->min = 1;
			else
				v->min = 0;////////////////
			v->max = v->min;
		}
		else {
			if (k == v->min) {
				auto first_cluster = veb_tree_minimum(v->summary);
				k = index(first_cluster,
					veb_tree_minimum(v->cluster[first_cluster]),v->u);
				v->min = k;
			}
			veb_tree_delete(v->cluster[high(k, v->u)], low(k,v->u));
			if (veb_tree_minimum(v->cluster[high(k, v->u)]) == nil) {
				veb_tree_delete(v->summary, high(k, v->u));
				if (k == v->max) {
					auto summary_max = veb_tree_maximum(v->summary);
					if (summary_max == nil)
						v->max = v->min;
					else
						v->max = index(summary_max, veb_tree_maximum(v->cluster[summary_max]), v->u);
				}
			}
			else if (k == v->max)
				v->max = index(high(k, v->u), veb_tree_maximum(v->cluster[high(k, v->u)]),v->u);
		}
	}
	pt_veb get_rt() { return vrt; }
private:
	pt_veb vrt;
	size_t get_power(size_t k) {//���ش���k��2����
		size_t r = static_cast<size_t>(log(k) / log(2));
		r = static_cast<size_t>(pow(2, r+1));
		return r;
	}
	size_t under_log(size_t u) {//��ƽ����
		double t = log(u) / log(2);
		return
			static_cast<size_t>(pow(2, static_cast<size_t>(t / 2)));
	}
	size_t up_log(size_t u) {//��ƽ����
		double t = log(u) / log(2);
		return
			static_cast<size_t>(pow(2, ceil(t / 2)));
	}

	size_t high(size_t key,size_t u) {
		return key/under_log(u);
	}
	size_t low(size_t key,size_t u) {
		
		return key%under_log(u);
	}
	size_t index(size_t heigh, size_t low,size_t u) {
		return heigh* under_log(u) + low;
	}

	void veb_empty_tree_insert(pt_veb v, size_t k) {
		v->max = k;
		v->min = k;
	}
	void new_space(pt_veb v, size_t u) {//ʹ�õݹ����ռ�
		if (u > 2) {
			v->u = u;
			size_t s = up_log(u);
			v->cluster.resize(s);

			for (auto &i : v->cluster) {
				i= shared_ptr<vebNode>(new vebNode);
				new_space(i, under_log(u));
			}

			v->summary = shared_ptr<vebNode>(new vebNode);
			new_space(v->summary, up_log(u));
		}
		else
			v->u = 2;
	}
};
//////////////////////////////
class solution {
public:
	solution():vebt(1000){}
	void operator()() {
		vector<size_t>vect{ 0,1,2,3,4,5,6,7,55,32,98,19,100,8,9,10,11,12,13};
		for (auto i : vect) {
			vebt.veb_tree_insert(vebt.get_rt(), i);
		}
		vector<size_t>suc{ 0,4,7,9,20,41,89,120 };
		for (auto i : suc) {
			cout << "\n--------------------------\n";
			cout << i;
			vebt.veb_tree_member(vebt.get_rt(), i) ?
				cout << "��" : cout << "����" ;
			cout <<"������"<< endl;
			cout << "\n" << i << "�ĺ��Ϊ\n";
			cout << vebt.veb_tree_successor(vebt.get_rt(), i) << endl;
			cout << "\n" << i << "��ǰ��Ϊ\n";
			cout << vebt.veb_tree_predecessor(vebt.get_rt(), i) << endl;
		}
		for (auto i : vect) {
			cout << "\n--------------------------\n";
			vebt.veb_tree_delete(vebt.get_rt(), i);

			cout << i;
			vebt.veb_tree_member(vebt.get_rt(), i) ?
				cout << "��" : cout << "����";
			cout << "������" << endl;
		}
	}
private:
	veb_tree vebt;
};
#endif
