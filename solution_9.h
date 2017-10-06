#pragma once
#ifndef	_SOLUTION_9_H_
#define _SOLUTION_9_H_
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<memory>
using namespace std;

class solution9_1_1 {
public:
	void operator()() {
		cout << "ÿ����һ��Ƚϣ�����С��Ԫ����������Ϊ�´�ѭ�����������룬����һ�ε���֮ǰ�������������һ�� \n"
			<< "�ҽڵ���������Լ������ֱ�����Ϊ1�ﵽ���ڵ㣬Ҳ������Сֵ��������֤һ��������n-1�αȽ� \n"
			<< "����Сֵһ����ڶ�С��ֵ�����˱Ƚϣ����Կ��Ե����鿴�������������� : \n"
			<< "1.��Ҫ����Ԫ���Ƴ����ڵ㣬������ָ���Ԫ�ز���������vector���ʼ������ָ�붼�ǿ�ָ�� \n"
			<< "2.�������е�Ԫ�طֳ�[0,1],[2,3],[4,5]...����һ�飬����С��Ԫ�ش���һ���ڵ㣬��ָ��ָ���СԪ�ص� \n"
			<< "�Ľڵ㣬��ָ��ָ��ϴ�Ԫ�أ�����ڽڵ�9��3����3ΪԪ������һ���ڵ㣬�ýڵ���ָ��ָ��֮ǰ��3�ڵ� \n"
			<< "��ָ��ָ��9�ڵ㣬ÿɨ��һС�鶼���²����Ľڵ������һ��������ֱ��ɨ��������С�� \n"
			<< "3������������Ϊ����2�����룬����ֱ������size()Ϊ1���ҵĳ���û��ʹ�õ��� \n"
			<< "��ϸ������ע��"
			<< endl;
		find_second();
	}
private:
	struct node {//���ڵ㣬����key=left_min
		node(int part, const shared_ptr<node>&left = nullptr, const shared_ptr<node>&right = nullptr) :key(part), left_min(left), right_max(right) {}
		int key;
		shared_ptr<node>left_min;
		shared_ptr<node>right_max;
	};
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,
		72,73,174,76,77,81,82,83,272,90,91,95,101,105,140,111,112,204,124,189,271,132,245,74,
		7,123,139,231,136,144,172,153,293,116,141,164,275,39,135,177,127,186,165,296,197,157,163,59,
		138,211,213,65,248,279,192,255,108,252,147,223,285,286,214,222,200,268,199,297,159,276,224,270,
		137,288,249,184,292,254 };//��������

	shared_ptr<node>root_min_ptr;//�����ڵ��ָ�룬�������Сֵ
	unsigned int counter_compare=0;//��������һ���Ƚ��˶��ٴ�
	void find_second() {
		vector<shared_ptr<node>>tmp;
		for (size_t i = 0; i != vect.size(); ++i)
			tmp.push_back(shared_ptr<node>(new node(vect[i])));//�����ʼ�����ڵ㣬��ʱ����ָ��Ϊ��ָ��		
		subFind(tmp);//������ע��

		cout << "��СԪ���� " << root_min_ptr->key << endl;
		cout << "�ڶ�С��Ԫ���� " << second_min(root_min_ptr) << endl;
		cout << "һ�������� " << counter_compare << " �αȽ�" << endl;
		//���������������۱Ƚϴ���
		cout << " n= " << vect.size() << "\n n+lgn-2= " << vect.size() + log(vect.size()) / log(2) - 2 << endl;
	}
	void subFind(vector < shared_ptr<node>>&temp) {	
		
		while (true) {
			vector<shared_ptr<node>>tmp;//Ϊ�´����빹���������
			for (auto &i : temp)
				cout << i->key << "\t";
			cout << endl;
			if (temp.size() & 1) {//����������ݴ�СΪ������1��2...n-1���飬���һ��Ԫ�����push��ȥ
				for (size_t i = 0; i != temp.size() - 1;++counter_compare, i += 2)//counter_compare����
					if (temp[i]->key < temp[i + 1]->key)
						tmp.push_back(shared_ptr<node>(new node(temp[i]->key, temp[i], temp[i + 1])));
					else
						tmp.push_back(shared_ptr<node>(new node(temp[i+1]->key, temp[i + 1], temp[i])));
				tmp.push_back(temp.back());
			}
			else {//ż������
				for (size_t i = 0; i != temp.size(); ++counter_compare, i += 2)
					if (temp[i]->key < temp[i + 1]->key)
						tmp.push_back(shared_ptr<node>(new node(temp[i]->key, temp[i], temp[i + 1])));
					else
						tmp.push_back(shared_ptr<node>(new node(temp[i + 1]->key, temp[i + 1], temp[i])));
			}		
			if (tmp.size() == 1) {//���������ڵ��¼���ڵ��ָ�벢�˳�
				root_min_ptr = tmp.front();
				break;
			}
			temp.swap(tmp);//������������Ϊ�´����룬������ѭ���Ĺؼ�
		} 
	}
	int second_min(shared_ptr<node>&ptr) {//�ҵڶ�С��ֵ
		auto left = ptr->left_min;
		auto right = ptr->right_max;
		int sec_min =right->key;//��¼�ڶ�С��ֵ
		while (left->right_max) {
			int temp = left->right_max->key;
			if (temp < sec_min)
				sec_min = temp;
			++counter_compare;
			left = left->left_min;
		}
		return sec_min;
	}
};
class solution9_1_2 {
public:
	void operator()() {
		cout << "��nΪż��ʱ,����һ��Ƚ�һ��������n/2�αȽϣ�������n/2��Ԫ�أ����н�С�������������A,�ϴ�Ĵ��� \n"
			<< "����B,ȡmin����A[1],һ������n/2-1�αȽϵõ���Сֵ��B����ͬ������һ��������n/2+(n/2-1)*2=3n/2-2 ��"
			<< "�Ƚ�,��nΪ����ʱͬ��"
			<< endl;
	}
};
class solution9_2_1 {
public:
	void operator()() {
		cout << "���ϵ�120��ĳ���ͺ���Ľ��ͶԲ������������3��randomized_partition�������ص��Ǿ����±� \n"
			<< "�����ʹ�õ��ǿ���������Ǹ���Ҳ����q����Ӧ��Ԫ����ԭ������������Ӧ�ĵ�q��˳��ͳ������������ \n"
			<< "���������A[p,r]��˳��ͳ���������������Լ�д�ĳ���. \n"
			<<"��Ȼ���еĳ���Ҳ����ȷ�ģ�������Ҳ�ǰ����ϵĳ��������� \n"
			<<"�����ʼ�ض���1<=p<=i<=r�����p=r,��2�л᷵�أ��������ִ�У�p<r,��3��p<=q<=r,1<=k<=r-p+1, \n"
			<<"���ܲ�����0���ȵ�����ݹ��Ϊ��8�к͵�9�У������8�в���0�������飬Ҳ����q-1<p,��q=p,��ʱk=1 \n"
			<<"��if����ȴ��i<k=1,�ǲ����ܷ����ģ��Ե�9�У�q+1>r,q=r,k=r-p+1��i>kҲ�ǲ����ܵ�,��Ϊ�����q����� \n"
			<<"�����������"
			<< endl;
		const size_t i = 3;
		cout <<"�� "<<i<<" ��˳��ͳ����Ϊ "
			<<randomized_select(1, vect.size() - 1, i) << endl;
	}
private:
	vector<int>vect{ 0,3,2,9,7,5,4,8,6,1 };//vect[0]����˳��ͳ�����ķ�Χ��,����Ч����Ϊ1,2,3,4,5,6,7,8,9
	size_t partition(size_t p, size_t r) {
		int key = vect[r];
		size_t i = p - 1;
		for (size_t j = p; j != r; ++j)
			if (vect[j] <= key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[r], vect[i + 1]);
		return i + 1;
	}
	size_t randomized_partition(size_t p,size_t r) {
		srand(static_cast<unsigned int>(time(0)));
		size_t i = p+rand()%(r-p+1);
		swap(vect[i], vect[r]);
		return
			partition(p, r);
	}
	int randomized_select(size_t p, size_t r, size_t i) {
		if (p == r)
			return vect[i];
		size_t q = randomized_partition(p, r);
		if (i == q)
			return vect[q];
		else if (i < q)
			return
			randomized_select(p, q - 1, i);
		else
			return
			randomized_select(q + 1, r, i);
	}
};

class solution9_2_2 {
public:
	void operator()() {
		cout << "����kΪ��ֵ���ܴ���һ��T(max(k-1,n-k))"
			<< endl;
	}
};

class solution9_2_3 {
public:
	void operator()() {
		const size_t i = 5;
		cout << endl;
		cout << "�� " << i << " ��˳��ͳ����Ϊ "
			<< randomized_select(1, vect.size() - 1, i) << endl;
	}
private:
	vector<int>vect{ 0,3,2,9,7,5,4,8,6,1 };
	size_t partition(size_t p, size_t r) {
		int key = vect[r];
		size_t i = p - 1;
		for (size_t j = p; j != r; ++j)
			if (vect[j] <= key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[r], vect[i + 1]);
		return i + 1;
	}
	size_t randomized_partition(size_t p, size_t r) {
		srand(static_cast<unsigned int>(time(0)));
		size_t i = p + rand() % (r - p + 1);
		swap(vect[i], vect[r]);
		return
			partition(p, r);
	}
	int randomized_select(size_t p, size_t r, size_t i) {
		while (p < r) {
			size_t q = randomized_partition(p, r);
			if (q == i)
				return vect[q];
			else if (i < q)
				r = q - 1;
			else
				p = q - 1;
		}	
		return vect[p];
	}
};
class solution9_2_4 {
public:
	void operator()() {
		cout << "q���ε���9,8,7,6,5,4,3,2,1,0"
			<< endl;
	}
};

class solution9_3_1 {
public:
	void operator()() {
		cout << "1,2,4ҪO(n)��ʱ�䣬3��n/7��Ԫ�صݹ����ҪT(n/7),������4*(1/2(n/7)-2)=2n/7-8��Ԫ�ش���x���� \n"
			<< "2n/7-8��Ԫ��С��x����5��������ҪT(5n/7+8),T(n)=T(n/7)+T(5n/7+8)+an, \n"
			<< "Ҫ֤��T(n)<=cn,T(n)<=cn/7+5cn/7+8c+an=cn+(-cn/7+8c+an),-cn/7+8c+an<=0,��n>2*56,c>14���� \n"
			<< "��ÿ��3��Ԫ�أ�T(n)=T(n/3)+T(2n/3+4)+an=T(n/3)+T(2n/3)+an,�ݹ�����⣬������log(3,n)�㣬 \n"
			<< "ע�⵽n/3+2n/3����n������ÿ��ķ�an��T(n)>=cnlgn,���Բ������Ե�"
			<< endl;
	}
};

class solution9_3_2 {
public:
	void operator()() {
		cout << "һ�������ֳ�n/5�飬������n/5����λ������ȥx���ڵ�С��ͳ�Ա����5��һ��С�飬\n"
			<< "������һ��1/2*n/5�ټ�ȥ2����λ����С����λ������λ��x�ģ� \n"
			<< "��������Щ1/2*n/5-2����λ����������һ��Ϊy���ڵ�5��һ���У�\n"
			<< "��2λ��������һ��Ϊz��С������λ���ģ�����z<y<x,����С����λ����һ����(1+2)*(1/2*n/5-2) \n"
			<< "=3n/10-6>n/4,������λ������λ���ĸ���ͬ����3n/10-6>n/4������ʣ�µ�4n/10+12�������޷� \n"
			<< "ͨ������ʽ�Ĵ����Եõ�����x�Ĵ�С��ϵ�ģ������5����⵽i<k,��ݹ���С��x��3n/10-6���� \n"
			<< "����ȷ����ϵ��4n/10+12��7n/10+6����������ͬ��Ҳ����ô��"
			<< endl;
	}
};

class solution9_3_3 {
public:
	void operator()() {
		cout << "����������һ�ڵ����Բ��ҷ������Ѧ�(n)����n����ģ����λ��,�������ܱ�֤��õĻ��ֻ��� \n "
			<< "��(n)+��(nlgn)=��(nlgn)"
			<< endl;
	}
};
//////////////////////////////////////////////////////
class select {//�������е�select�ݹ��ҵ�����λ�����������ҵ�����λ����������λ������λ��
public:
	void operator()() {
		cout <<"select()���Ե�ֵΪ"<<getMid(vect) << endl;
		
	}
private:
	bool flag = true;
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,
		72,73,174,76,77,81,82,83,272,90,91,95,101,105,140,111,112,204,124,189,271,132,245,74,
		7,123,139,231,136,144,172,153,293,116,141,164,275,39,135,177,127,186,165,296,197,157,163,59,
		138,211,213,65,248,279,192,255,108,252,147,223,285,286,214,222,200,268,199,297,159,276,224,270,
		137,288,249,184,292,254 };
	void bubble_sort(vector<int>&v) {
		if (v.empty())
			return;
		for (size_t i = v.size() - 1; i != 0; --i) {
			for (size_t j = 0; j != i; ++j)
				if (v[j + 1] < v[j])
					swap(v[j + 1], v[j]);
		}
	}
	int getMid(vector<int>&vc) {
	/*	for (auto i : vc)
			cout << i << "\t";
		cout << endl;
		cout << endl;*/
		if (vc.size() == 1)
			return vc[0];
		vector<vector<int>>vv(vc.size()/5+1);
		vector<int>temp;
		for (size_t i = 0; i != vc.size(); ++i) 
			vv[i / 5].push_back(vc[i]);
		for (size_t i = 0; i != vv.size(); ++i) {
			bubble_sort(vv[i]);
			for (auto j : vv[i])
				cout << j<< "\t";
			cout << endl;
		}
		
		cout<<"\n----------------------------------"<< endl;
		for (size_t i = 0; i != vv.size(); ++i)
			if(!vv[i].empty())
				temp.push_back(vv[i][(vv[i].size()-1) / 2]);
		if (flag) {
			flag = false;
		    vector<int>real(temp);
			sort(real.begin(), real.end());
			for (auto i : real)
				cout << i << "\t";
			cout << "\n" << endl;
			cout << "��������λ������λ��Ϊ " << real[(real.size() - 1) / 2] << endl;
		}
		return getMid(temp);
	}
};
///////////////////////////////////////////////////////////////////////
class solution9_3_4 {
public:
	void operator()() {

	}
};
class solution9_3_5 {
public:
	void operator()() {
		cout << "��9.2�ڳ���ĵ�3�е�qֵ��������ʱ����ҳ�������λ�����±꣬�������ܱ�֤T(n)=T(n/2)+��(n)��T(n)=��(n)"
			<< endl;
	}
};

class solution9_3_6 {
public:
	void operator()() {
		cout << "��һ�ⷭ���˷����Һܶ�ʱ�䣬ͨ�����������ϵĲ�ѯ���Ҷ�k��λ��������ǣ���n�����ֳ�k���ȴ�С���ϣ���ȥ���һ������\n"
			<< "ÿ�����ϵ����ֵ����Ϊ���һ�����ϵ����ֵ�ض���ԭ���ϵ����ֵ�����߱��������á����磺 \n"
			<< "4,11,9,13,14,6,1,7,8,15,2,5,10,3,12 ,�������1,2,3,|4,5,6,|7,8,9,|10,11,12,|13,14,15 \n"
			<< "�ֳ�5�ݣ�5-1=4��k��λ��Ϊ3,6,9,12 \n"
			<< "�㷨˼·��Ҫ�ҵ�(beg,end,k)beg��end��Χ�ڵ�k��λ�����������ҵ���k/2��λ�����������һ���±�index,\n"
			<< "Ȼ��ݹ����(beg,index-1,k/2)�ͣ�index+1,end,k/2)����Ȼ�Ⲣ����ȫ׼ȷ����Ҫ��k����ż��,���������\n"
			<< "T(n,k)��ʾ��n�������ҵ�k����λ�����㷨�ĵݹ�ʽ�� \n"
			<< "T(n,k)=T(n/2,k/2)+T(n/2,k/2)+cn,�����õݹ�����⣬ÿһ�㻨��cn,ֱ��k=1,������lgk�㣬����O(nlgk) \n"
			<< "����Ҫ��1...15��5��λ�������ҵ���λ��6����15��Ȼ����1...5����4����5����7...15����9,12����9,9+4=14ԼΪ15 \n"
			<<"�������еĳ����ǳ�������������������ᷢ�֣����򶼱����죬�ҵıʼǱ�Ҫʮ������ܵõ����\n"
			<<"���������е����ж���k��λ�����������������Ե�������98��������k=16,���ÿ������6��Ԫ�أ�����2��Ԫ�ؾ���17������ \n"
			<<"���ÿ������7��Ԫ�أ�ǰ15�����Ͼ���Ҫ105��Ԫ�أ�\n"
			<< endl;

		const size_t k = 17;//����kֵ
		factory_find_k(0, vect.size() - 1, k);//����k��λ������k-1��˳��ͳ��������vect_k
		cout << "����ǰ��������˳���ҵ���k��λ��" << endl;
		for (auto i : vect_k)
			cout << i << "\t";
		cout << endl;
		sort(vect_k.begin(), vect_k.end());
		cout << "������Ϊ�˷�����Գ����Ƿ���ȷ��������k��λ��" << endl;
		for (auto i : vect_k)
			cout << i << "\t";
		cout <<endl;

		auto n = vect.size();
		size_t dif = n%k ? (n + k - n%k) / k : n / k;//�������������Ϊ�˷ֶ�
		cout << "������k��λ�����ҳ��������������У����Կ������ܲ�������ȫ����" << endl;
		size_t rows = 0;//��¼����
		for (auto i = 0; i != vect.size(); ++i) {
			cout << vect[i] << "\t";
			if (!((i + 1) % dif)) {
				cout << "\t\t" << ++rows << "��" << endl;
				cout << "\n";
			}
		}
		cout << "\n" << "-------------------------------" << endl;
		for (int i = 1; i != vect.size(); ++i) {//��������
			int key = vect[i];
			int j = i;
			for (; i != 0 && key < vect[j - 1]; --j)
				vect[j] = vect[j - 1];
			vect[j] = key;
		}
		cout << "������������ɺ������" << endl;
		
		for (auto i = 0,rows = 0; i != vect.size(); ++i) {
			cout << vect[i] << "\t";
			if (!((i + 1) % dif)) {
				cout << "\t\t" << ++rows << "��" << endl;
				cout << "\n";
			}
		}
		cout << endl;
	}	
private:
	vector<int>vect{ 71,248,279,192,255,108,252,147,223,//��������
		72,73,91,95,101,105,140,111,112,204,124,189,271,132,245,74,138,211,213,65,285,286,214,222,200,
		7,123,139,231,136,144,172,156,206,11,14,15,19,26,27,31,34,89,44,293,116,186,165,296,197,157,163,59,
		268,199,297,159,276,224,270,174,76,77,81,82,83,272,90,53,56,57,228,61,64,253,70,
		137,288,249,184,292,254,141,164,275,39,135,177,127, };
//	vector<int>vect{ 4,11,9,13,14,6,1,7,8,15,2,5,10,3,12 };
	vector<int>vect_k;
	size_t partition(size_t beg, size_t end) {
		size_t i = beg - 1;
		int key = vect[end];
		for(size_t j=beg;j!=end;++j)
			if (vect[j] < key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[end], vect[++i]);
		return i;
	}
	size_t randomized_partition(size_t beg, size_t end) {
	
		srand(static_cast<unsigned int>(time(nullptr)));
		size_t rd = rand() % (end - beg + 1) + beg;
		swap(vect[rd], vect[end]);
		return partition(beg, end);
	}
	void randomized_select(size_t beg, size_t end, size_t k) {//�������
		size_t index = randomized_partition(beg, end);
		while (k != index) {
			if (k < index) {
				index = randomized_partition(beg, index - 1);
			}
			else {
				index = randomized_partition(index + 1, end);
			}
		}
	}
	void find_k(size_t beg, size_t end, size_t k,size_t dif) {		
		if (k>0) {
			auto index = beg + dif*((k+1)/ 2) - 1;
			if (index >= vect.size())return;
			randomized_select(beg, end, index);
			vect_k.push_back(vect[index]);
			if (k & 1) {
				find_k(beg,index-1,k/2,dif);
				find_k(index+1,end,k/2,dif);
			}
			else {
				find_k(beg, index - 1, k / 2 - 1, dif);
				find_k(index + 1, end, k / 2, dif);
			}
		}
	}
	void factory_find_k(size_t beg, size_t end, size_t k) {
		size_t n = end - beg + 1;
		size_t dif = n%k ? (n + k - n%k) / k : n / k;
		k = k - 1;
		find_k(beg, end, k, dif);
	}
};

class solution9_3_7 {
public:
	void operator()() {
		cout << "1.����select�ҵ��ü��ϵ���λ������cn \n"
			<< "2.Ūһ��pair��second�洢����Ԫ�أ�first�洢��ӦԪ�غ���λ���Ĳ�ľ���ֵ������cn \n"
			<< "3.��select�ҵ�first�ĵ�k��˳��ͳ����x����cn����x��Ϊ��Ԫ��pair���л��ֻ���cn������ǰK��Ԫ�ػ��� \n"
			<< "��ʱ��ΪO(n),��Ȼ�ҵķ���������select�����ҵĳ����л����õ�randomized_select \n"
			<< "ԭ��������д�������֮ǰ�һ��Ƕ�select�������ҳ���λ������λ�������ɻ�������Ҳд��һ�����Գ��� \n"
			<< "��������������󡣵����岢����������ķ���"
			<< endl;
		const size_t k = 5;
		find(k);
		cout << "��ӽ���λ���� " << k << "  ������" << endl;
		for (auto i : anw)//��ӡ��
			cout << i << "\t";
		cout << "\n" << endl;

		for (size_t j = vect.size() - 1; j != 0; --j)//ð������
			for (size_t i = 0; i != j; ++i)
				if (vect[i] > vect[i+1])
					swap(vect[i], vect[i+1]);
		cout << "��������Ϊ" << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71 };
	vector<int>anw;
	size_t partition(vector<int>&vp, size_t beg, size_t end) {
		size_t i = beg - 1;
		int key = vp[end];
		for(size_t j=beg;j!=end;++j)
			if (vp[j] <= key) {
				++i;
				swap(vp[i], vp[j]);
			}
		swap(vp[i+1], vp[end]);
		return i+1;
	}
	int randomized_select(vector<int>&vp,size_t beg,size_t end,size_t k) {
		if (beg == end)
			return vp[beg];
		srand(static_cast<unsigned int>(time(nullptr)));
		size_t rd = beg + (rand() % (end - beg + 1));
		swap(vp[rd], vp[end]);
		size_t n = partition(vp, beg, end);
		if (k == n)
			return vp[n];
		else if (k < n)
			return randomized_select(vp, beg, n - 1,k);
		else
			return randomized_select(vp, n + 1, end,k);
	}
	void find(size_t k) {
		vector<pair<int, int>>vp;
		for (size_t i = 0; i != vect.size(); ++i)
			vp.push_back({0,vect[i]});
		int midian = randomized_select(vect, 0,vect.size()-1,(vect.size() - 1) / 2);
		cout << "��λ���� " << midian << endl;
		for (size_t i = 0; i != vp.size(); ++i) {
			int differ=vp[i].second - midian;
			vp[i].first = differ > 0 ? differ : -differ;
		}
		vector<int>temp;
		for (auto &i : vp)
			temp.push_back(i.first);
		int key_k = randomized_select(temp,0,temp.size()-1, k-1);
		cout << "key_k=    " << key_k << endl;
		size_t i = -1;
		for (size_t j =0; j != vp.size(); ++j)
			if (vp[j].first <= key_k) {
				++i;
				swap(vp[i], vp[j]);
			}
		for (auto &i : vp)
			cout << i.first << "   " << i.second << endl;
		for (size_t j = 0; j != i+1; ++j)
			anw.push_back(vp[j].second);
	}
};

class solution9_3_8 {
public:
	void  operator()() {
		cout << "��Ϊ2n��Ԫ�ر�Ȼ��ż����������λ��Ҫ���ڵ���n-1��Ԫ�أ�С�ڵ���n��Ԫ�أ��ö��ַ���Ѱ����λ���� \n"
			<< "�����������������������������ȼ�����λ����X�У�ÿ�ο�����԰���ң�����ѡȡ��Ԫ���±�Ϊmid \n"
			<< "����X�д�Ԫ��element���ڵ���mid��Ԫ�أ�С��n-mid-1��Ԫ��ע���±��0��ʼ��������Y�У� \n"
			<< "element���ڵ���n-1-mid��Ԫ�أ�Ҳ����element>=Y[Y.size()-1-mid-1],С��n-(n-mid-1)��Ԫ�أ�Ҳ���� \n"
			<< "element<=Y[Y.size()-1-mid-1+1],Ȼ�������λ���Ƿ���Y��"
			<< endl;
		cout <<"clgn�Ļ��ѵļ������λ��Ϊ "<< factory_find() << endl;
		for (auto i : X)
			Y.push_back(i);
		sort(Y.begin(),Y.end());
		for (auto i : Y)
			cout << i << "\t";
		cout << "\n" << endl;
		cout << "�����������λ���� " << Y[X.size() - 1] << endl;
	}
private:
//	vector<int>X{ 2,6,8,17,19,29,33,42,45,50,56,59,62,62,68,71,76,80,81,84};
//	vector<int>Y{ 5,12,13,25,32,34,35,41,50,53,63,64,68,71,75,79,85,85,88,89 };
	vector<int>X{ 2,8,20,32,33,35,38,39,63,73,74,86,116,124,127,150,152,155,164,171,174,181,181,187,196,229,
		246,259,266,273,284,297,304,310,313,324,328,337,339,353,360,377,379,383,387,389,392,392,395,399,414,
		414,434,467,485,501,549,560,562,574,575,577,578,587,595,616,617,619,630,638,641,657,667,669,672,674,
		687,720,722,733,755,758,775,788,800,818,834,848,848,848,880,883,897,913,930,944,951,962,973,975 };

	vector<int>Y{ 12,16,28,41,42,42,42,68,69,79,89,90,100,134,144,152,154,154,155,157,177,183,190,191,196,215,
		219,240,245,253,255,269,282,300,325,339,342,352,358,370,382,404,415,416,419,420,449,459,473,486,490,
		531,554,559,570,574,598,608,610,611,620,625,668,677,681,710,718,723,746,751,759,775,787,790,791,806,
		814,816,823,825,830,842,849,850,851,855,860,891,900,906,947,953,962,963,972,977,979,987,988,988 };
	int find_median(vector<int>&X,vector<int>&Y, size_t p, size_t r) {
		size_t mid = (p + r) / 2;
		cout << X[mid] << endl;
		if (p <= r) {
			if (X[mid] >= Y[Y.size() - 1 - mid - 1])
				if (X[mid] <= Y[Y.size() - 1 - mid - 1 + 1])
					return X[mid];
				else
					return find_median(X, Y, p, mid - 1);
			else
				return find_median(X, Y, mid + 1, r);
		}
		else
			return	INT_MAX;//��λ������Z��
	}
	int factory_find() {
		int temp = find_median(X, Y, 0, X.size() - 1);
		if (temp != INT_MAX)
			return temp;
		else
			return find_median(Y,X ,0, X.size() - 1);
	}
};

class solution9_3_9 {
public:
	void operator()() {
		cout << "���Լ������еĵ�����궼�ڵ�һ���ޣ���ô���ܵ���λ�þ���y=midan,midanΪ���е��y�������λ�� \n"
			<< "��������ʱ�����ҳ�һ���������е���λ����С���Ѿ������㷨����׸�ԡ��������֤���� \n"
			<< "�������ܵ���y=k,��ô�ܳ��ȵ��ڡ�|y(i)-k|,�����׵ó����ܵ�Ӧ��������;������� \n"
			<< "����������;��ı��棬���;������������Ϊa,b,c,d,e,f,g,������ܵ����м䣬�� \n"
			<< "a,b,c,d,k,e,f,g,���㵽k�ľ������e-d+f-c+g-b+k-a=k+e+f+g-a-b-c,������ܵ������м� \n"
			<< "��a,b,c,d,e,k,f,g,���㵽k�ľ������f-e+g-d+3k-a-b-c=k+k+f+g-a-b-c+(k-e)>k+e+f+g-a-b-c \n"
			<< "k����λ�����ͬ���֤�����Ե�nΪż��ʱ���ܵ�����������λ������֮������λ�ö����ԣ� \n"
			<< "��nΪ����ʱ������λ������"
			<< endl;
	}
};
//˼����
class solution9_1 {
public:
	void operator()() {
		cout << "a.cnlgn \n"
			<< "b.cn+i*lgn \n"
			<< "c.cn+i*lg(i)"
			<< endl;
	}
};

class solution9_2 {
public:
	void operator()() {
		cout << ""
			<< endl;
	}
};
#endif //_SOLUTION_9_H_
