#pragma once
#ifndef _SOLUTION_8_H_
#define _SOLUTION_8_H_
#include<iostream>
#include<vector>
#include<cmath>
#include<list>
using namespace std;

class solution8_1_1 {
public:
	void operator()() {
		cout << "a.n-1  \n"
			<< endl;
	}
};

class solution8_1_2 {
public:
	void operator()() {
		cout << "���ݹ�˾(C.11),lgn���ֺ�Ϊnlgn-x/ln2,�����½���������æ�(nlgn) \n"
			<< endl;
	}
};

class solution8_1_3 {
public:
	void operator()() {
		cout << "lg(n!/2)=��(nlgn),lg(n!/n)=����nlgn),lg(n!/2^n)=lg(n!)-n=����nlgn)"
			<< endl;
	}
};

class solution8_1_4 {
public:
	void operator()() {
		cout << "ÿ�������ж���k�������У�һ����n/k�������У�����һ����(k!)^(n/k)�����У� \n"
			<< "�߶�Ϊh��Ҷ�ڵ㲻����2^h,2^h>=(k!)^(n/k),h>=n/klgk!=nlgk "
			<< endl;
	}
};

void print_vector(vector<int>&vect) {
	for (size_t i = 1; i != vect.size(); ++i)
		cout << vect[i] << "\t";
	cout << "\n" << endl;
}

class solution8_2_1 {
public:
	void operator()() {
		counting_sort();
	}
private:
	vector<int>A{ 0,6,0,2,0,1,3,4,6,1 };
	void print_v(vector<int>&v) {
		for (size_t i = 1; i != v.size(); ++i)
			cout << i << "\t";
		cout << endl;
		print_vector(v);
	}
	void print_vc(vector<int>&v) {
		for (size_t i = 0; i < v.size(); ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : v)
			cout << i << '\t';
		cout << "\n" << endl;
	}
	void counting_sort() {
		vector<int>C(7, 0);
		cout << "ԭʼC�е�Ԫ��Ϊ:" << endl;
		print_vc(C);
		vector<int>B(A.size() , 0);
		cout << "ԭʼB�е�Ԫ��Ϊ:" << endl;
		print_v(B);
		for (size_t i = 1; i != A.size(); ++i)
			++C[A[i]];
		cout << "��ɼ������C��Ԫ��Ϊ:" << endl;
		print_vc(C);
		for (size_t i = 1; i != C.size(); ++i)
			C[i] += C[i - 1];
		cout << "���ͳ�Ƽ������C�е�Ԫ��Ϊ:" << endl;
		print_vc(C);
		for (size_t i = A.size() - 1; i != 0; --i) {//�ݼ�ѭ����ά�ּ��������ȶ��Ĺؼ�
			B[C[A[i]]] = A[i];
			--C[A[i]];
			cout << "�����B�еĹ���..." << endl;
			print_v(B);
		}
	}
};
////////////////////////////////////////////////
class countingSort {//����������һ�㻯�����Դ������ⷶΧ�ڵ���ֵ��������ֵ����Ȼ�������
public:
	countingSort(vector<int>&target):target_vect(target){}
	void operator()(bool flag=true);//�����Ҫ��Ҫ�ı�ԭ�����ֵ��Ĭ�ϸı�
private:
	pair<int, int>find_min_max();//�ҵ����ֵ����Сֵ
	void init();//��ʼ������vector
	vector<int>&target_vect;//Ŀ��vector����
	vector<int>counter;//����
	vector<int>temp_order;//��������ʱ����
	int differ_zero;//differ_zero+min=0,ʹ��������һ�㻯�Ĺؼ���
};
inline
pair<int, int>countingSort::find_min_max() {
	int max = target_vect[0];
	int min = target_vect[0];
	for (size_t i = 0; i != target_vect.size(); ++i)
		if (min > target_vect[i])
			min = target_vect[i];
		else if (max < target_vect[i])
			max = target_vect[i];
	return{ min,max };
}
inline
void countingSort::init() {
	pair<int, int>temp_pair{ find_min_max() };
	size_t differ = temp_pair.second - temp_pair.first + 1;
	if (differ > target_vect.size()*log(target_vect.size()) / log(2))
		cerr << "���棬����̫ϡ�裬��������ʱ�临�Ӷȿ��ܳ�����(nlgn)���ռ��˷Ѿ޴�" << endl;
	differ_zero = -temp_pair.first;
	counter.assign(temp_pair.second+differ_zero+1, 0);
	temp_order.assign(target_vect.size(), 0);
}
inline 
void countingSort::operator()(bool flag) {
	find_min_max();
	init();
	for (size_t i = 0; i != target_vect.size(); ++i)
		++counter[target_vect[i] + differ_zero];
	for (size_t i = 1; i != counter.size(); ++i)
		counter[i] += counter[i - 1];
	for (size_t i = target_vect.size() - 1; i != -1; --counter[target_vect[i] + differ_zero],--i)
		temp_order[counter[target_vect[i] + differ_zero]-1]= target_vect[i];
	if (flag)
		for (size_t i = 0; i != temp_order.size(); ++i)
			target_vect[i] = temp_order[i];
	temp_order.~vector<int>();//�ͷ��ڴ棬��ͬ
	counter.~vector<int>();
}
/////////////////////////////////////////

class solution8_2_2 {
public:
	void operator()() {
		cout << "��10�еݼ�ѭ��������ʹ��ԭ������ͬԪ�غ����Ԫ���ȳ��֣���C[A[j]]�洢������ͬԪ�������δ��� \n"
			<< "�±�����ֵ�����Ը���ԭ����˳����ͬԪ�����һ��Ԫ�������������������һ��Ԫ�ص���ͬλ�� \n"
			<< "�ǰ��Ԫ������������ȷλ��"
			<< endl;
	}
};

class solution8_2_3 {
public:
	void operator()() {
		cout << "���������ԣ���ͬԪ�ص���ǰ���һ��Ԫ�ر����ڵı�Ӧ�����һ��Ԫ�ص�λ�ã���Ϊ����ͬԪ�أ����������� \n"
			<< "��ȷ�ģ�����û���ȶ���"
			<< endl;
	}
};
class solution8_2_4 {
public:
	void operator()() {
		cout << "�ڵ�9�в���counter_a_to_b=C[b]-C[a-1]"
			<< endl;
	}
};

class solution8_3_1 {
public:
	void operator()() {
		radix_sort();
		for (auto &i : vect) {
			for (auto &j : i)
				cout << j << "\t";
			cout << endl;
		}
	}
private:
	vector<vector<string>>vect{ {"COW"},{"DOG"},{"SEA"},{"RUG"},{"ROW"},{"MOB"},{"BOX"},{"TAB"},{"BAR"},{"EAR"},
	{"TAR"},{ "DIG" },{ "BIG"},{ "TEA"},{ "NOW"},{ "FOX"} };
	void countingSort(size_t n) {
		vector<size_t>counter('Z' + 1, 0);
		vector<string>temp(vect.size());
		for (size_t i = 0; i != vect.size(); ++i)
			++counter[vect[i].back()[n]];
		for (size_t i = 1; i != counter.size(); ++i)
			counter[i] += counter[i - 1];
		for (size_t i = vect.size() - 1; i != -1; --i) {
			temp[counter[vect[i].back()[n]]-1] = vect[i].back();
			--counter[vect[i].back()[n]];
		}
		for (size_t i = 0; i != temp.size(); ++i)
			vect[i].push_back(temp[i]);
	}
	void radix_sort() {
		for (size_t i = 2; i != -1; --i)
			countingSort(i);
	}
};

class solution8_3_2 {
public:
	void operator()() {
		cout << "��������͹鲢�������ȶ��ģ��鲢��������Ԫ�����ʱ����ߵ�Ԫ��������� \n"
			<<"����ʼʱ����ͬԪ�صĺ�������±�ɨ��һ�����pair��Ȼ���Ԫ������ \n"
			<<"������ɺ���ɨ��һ�����飬����ͬԪ���������У�ʱ��Ϳռ䶼���Ѧ�(n)"
			<< endl;
	}
};

class solution8_3_3 {
public:
	void operator()() {
		cout << "����n��bλr��������˵ \n"
			<< "��ʼ���Ե�һλ�Ѿ����� \n"
			<< "���Ѿ��źõ�kλ����˵��Ҫ�źù�k+1λ����ֻ��Ҫ��ԭ���Ļ������ȶ��������е�k+1λ��֤������ \n"
			<< "�����źõ�kλ���(kλ��)����Ϊa1��a2.....an,��������i<j,ai<=aj,��k+1λ��������ɵ�����Ϊ c1,c2...cn \n"
			<< "����ai��aj��Ӧ�ĵ�k+1λΪcm��cn��1.��m<n,Ҳ����˵ai��Ӧ�Ĺ�k+1λ��С��aj��, \n"
			<< "���׿��� cm*b^k+ai<=cn*b^k+aj,�����10������321,432��ai=21,aj=32,cm=3,cn=4,��Ȼ321<432 \n"
			<< "2.��m>n,Ҳ����˵ai��Ӧ�Ĺ�k+1λ��������aj�ģ�cm*b^k+ai>=cn*b^k+aj \n"
			<< "521,432,ai=21,aj=32,cm=5,cn=4,��Ȼ521>432,��Ȼ21<32 \n"
			<< "3.m=n,������������һ������֮ͬ�����ڶ��ȶ��Ե�����������m=n,���ڲ��ȶ�������˵�����ܻ�� \n"
			<< "m��Ӧ��Ԫ�ط��ڷ���n�ĺ�ߣ���ʱ�����������521,532��m=n=5,����Ȼ532��С��521"
			<< endl;
	}
};
class solution8_3_4 {
public:
	void operator()(){
		radix_sort();
		for (auto i : vect)
			cout << i << "\t";
		cout << endl;
	}
private:
	vector<int>vect{ 32,121,0,332,64,887,876,779,12,9 };
	size_t pow(size_t e, size_t n) {
		if (!n)
			return 1;
		while (n-1) {
			e *= e;
			--n;
		}
		return e;
	}
	size_t get(size_t value,size_t n) {
		size_t k=pow(10, n);
		value %= k;
		k = pow(10, n - 1);
		return value / k;
	}
	void countingSort(vector<pair<size_t,int>>&v) {
		vector<int>counter(10, 0);
		vector<int>temp(v.size());
		for (size_t i = 0; i != v.size(); ++i)
			++counter[v[i].first];
		for (size_t i = 1; i != 10; ++i)
			counter[i] += counter[i - 1];
		for (size_t i = 9; i != -1; --i) {
			temp[counter[v[i].first]-1] = v[i].second;
			--counter[v[i].first];
		}
		for (size_t i = 0; i != v.size(); ++i)
			v[i].second = temp[i];
	}
	void radix_sort() {
		vector<pair<size_t, int>>v(vect.size());
		for (size_t i = 0; i != vect.size(); ++i) //��ֵװ���ض�������
			v[i].second = vect[i];
		for (size_t i = 1; i != 4; ++i) {//�Ը�ʮ��λ�ֱ��������
			for (size_t j = 0; j != vect.size(); ++j)
				v[j].first = get(v[j].second, i);//��ȡ��ʮ��λ��ֵ
			countingSort(v);
		}
		for (size_t i = 0; i != vect.size(); ++i)//��������ֵ����ԭ����
			vect[i] = v[i].second;
	}
};

class solution8_3_5 {
public:
	void operator()() {
		cout << "��Ҫ9*10^(d-1)�����򣬼�¼�Ķ���Ҳ����ô�࣬����3λ����˵����λ��9�����֣�ʮλ�͸�λ����10�� "
			<< endl;
	}
};

class solution8_4_1 {
public:
	void operator()(){
		bucket_sort();
		cout << "\n" << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << endl;
	}
private:
	vector<double>vect{ 0.79,0.13,0.16,0.64,0.39,0.20,0.89,0.53,0.71,0.42 };
	void insert_sort(list<double>&lt) {
		for (auto iter1 = ++lt.begin(); iter1 != lt.end(); ++iter1) {
			double key = *iter1;
			auto temp = iter1;
			auto iter2 = --temp;
			for (; iter2 !=lt.begin() && *iter2 > key; --iter2) {
				auto temp_iter = iter2;
				++temp_iter;
				*temp_iter = *iter2;
			}
			if (iter2 == lt.begin() && *iter2 > key) {
				auto temp_iter = iter2;
				++temp_iter;
				*temp_iter = *iter2;
			}
			else
				*(++iter2) = key;
		}
	}
	void bucket_sort() {
		vector<list<double>>vtr(vect.size());
		for (size_t i = 0; i != vect.size(); ++i)
			vtr[static_cast<size_t>(vect.size()*vect[i])].push_back(vect[i]);
		size_t n = 0;
		for (auto &i : vtr) {
			cout << n++;
			for (auto j : i)
				cout << "��" << j ;
			cout << endl;
		}
		for (auto &i : vtr)
			if (i.size() >= 2)
				insert_sort(i);
		n = 0;
		for (auto &i : vtr)
			if (!i.empty())
				for (auto j : i)
					vect[n++] = j;
	}	
};

class solution8_4_2 {
public:
	void operator()() {
		cout << "������Ԫ�ض�����һ��ͰʱΪ���������������滻��������(nlgn)�������㷨������ź͹鲢"
			<< endl;
	}
};

class solution8_4_3 {
public:
	void operator()() {
		cout << "E[X^2]=0^2*1/4+1^2*1/4*2+2^2*1/4=3/2,E^2[X]=1^2=1"
			<< endl;
	}
};

class solution8_4_4 {
public:
	void operator()() {
		bucket_sort();
	}
private:
	typedef double point;
	typedef double distance;
	vector<pair<point, point>>vect{ {0.21,0.33},{-0.31,0.21} ,{0.19,0.96},{0.98,0.10},
	{-0.11,0.99}, {0.56,0.77},{0.31,0.42},{0.8,0.4},{-0.78,-0.44},{0.77,-0.34},{0.22,-0.23},
	{0.21,0.11},{-0.5,-0.76} };
	distance getDistance(point x, point y) {//�����ĵ�ԭ��ľ���
		return
			sqrt(x*x + y*y);
	}
	void insert_sort(vector<pair<distance,size_t>>&v) {
		for (size_t i = 1; i != v.size(); ++i) {
			distance key = v[i].first;
			size_t j = i;
			for (; j != 0 && key < v[j-1].first; --j)
				v[j] = v[j-1];
			v[j].first = key;
		}
	}
	void bucket_sort() {
		vector<vector<pair<distance,size_t>>>v_distance(vect.size());	//����pair.firstΪ���룬pair.secondΪ�����Ӧ��	
		for (size_t i = 0; i != vect.size(); ++i) {//���±�
			distance dis = getDistance(vect[i].first, vect[i].second);
			v_distance[static_cast<size_t>(dis*vect.size())].push_back(make_pair(dis, i));
		}
		for (size_t i = 0; i != v_distance.size() && v_distance[i].size() >= 2; ++i)
			insert_sort(v_distance[i]);
		size_t n = 0;
		vector<pair<point, point>>temp(vect.size());
		for (auto &i : v_distance)
			if (!i.empty()) {//��Ȼ����������ѭ����������ʱ����Ȼ�Ǧ�(n)
				for (size_t m = 0; m != i.size(); ++m) {
					temp[n++] = vect[i[m].second];
					cout << "(" << vect[i[m].second].first << "," << vect[i[m].second].second << ")"
						<< "\t" << i[m].first << endl;
				}
			}
		n = 0;
		for (auto &i : temp)
			vect[n++] = i;
	}
};

class solution8_4_5 {
public:
	void operator()() {
		cout << "��������������ĸ����ܶȺ���f(x),���ʷֲ�����F(X)=P(X<=x)=��f(x)dx,��������Ϊ(-�ޣ�x) \n"
			<< "��f(x)dx=1,���л�������Ϊ(-�ޣ���),��Ȼ����Ͱ�����Ҫ��"
			<< endl;
	}
};

//˼����

class solution8_1 {
public:
	void operator()() {
		cout << "a.Ҷ�ڵ���Ԫ���±��һ��˳�򣬶�����һ�����룬ֻ��һ��Ҷ�ڵ�Ԥ�ƶ�Ӧ��������Ҷ�ڵ��ⲻ�ᵽ�� \n"
			<< "����Ϊ0����Ϊ������������ҹ���n���ֿ������룬���Ը���Ϊ1/(n!) \n"
			<< "b.D(T)��������������������Ҷ�ڵ㵽���ڵ��·���ܳ��� \n"
			<< "D(LT)����������Ҷ�ڵ㵽���������ڵ�ĵ�·���ܳ�,����ÿһ�ڵ㵽���������ڵ�ľ����ܳ��ȵ�ԭ�ȸ��ڵ� \n"
			<< "��1��D(RT)ͬ��һ����k���ڵ㣬����D(T)=D(LT)+D(RT)+k \n"
			<< "c.d(k)=min{D(T)}=min{D(i)+D(k-i)+k},����T������k��Ҷ�ڵ�ľ�����������Ȼ \n"
			<< "min{D(i)+D(k-i)+k}=min{d(i)+d(k-i)+k} \n"
			<< "d.������i=k/2+x,-k/2<=x<=k/2,��ȡ�����ֵ�����뻯���k/2lg(k^2/4-x^2)+xlg((1+4/(k/x-2))) \n"
			<< "��x<0ʱ��ֵ��x>0ʱ��ֵ��С��x=0ʱ��ֵ���������̫�಻д \n"
			<< "������k��Ҷ�ڵ��������Щ�lgk�����lgk��<=lgk+1����d(i)+d(k-i)<=i(lgi+1)+(k-i)(lg(k-i)+1) \n"
			<< "=ilgi+(k-i)lg(k-i)+k<=klgk+k,d(k)=��(klgk) \n"
			<< "e.���ڹ�ģΪn��������n!��Ҷ�ڵ㣬������ʽ��֤��D(T)ΪҶ�ڵ�·���ܳ���һ����n!��Ҷ�ڵ㣬���� \n"
			<< "ƽ��Ϊ��(n!lgn!)/n!=��(lgn!)=��(nlgn) \n"
			<< "f.û̫�����Ŀ��������һλ���С��Ĵ�,����֤��ȷ \n"
			<< "A deterministic algorithm A corresponding to B would be one that has made its 'random' choices \n"
			<< "in advance. To construct it we just remove the randomized nodes by replacing them  \n"
			<< "by a child we pick. The new result is a subtree (in respect to the non-randomized nodes) and \n"
			<< "its number of choices is less than or equal to the one of the randomized algorithm.\n"
			<< "Since any subtree we pick is ��(nlgn), this implies that B is ��(nlgn)."
			<< endl;
	}
};

class solution8_2 {
public:
	void operator()() {
		cout << "a.b.c.��������˷���abc������Ŀ������㷨 \n"
			<< "d.������һ�ⷢ��abc����ͬʱ��������������ֻ��С��a���㷨���У���Ϊradix_sort �����㷨�������ȶ��� \n"
			<<"������㷨��ʱ�䳬��ΪO(n),����������O(bn) \n"
			<<"e.���ȶ�����ע��"
			<< endl;
		partition_sort();
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;

		countingSort_();
		for (auto i : vt)
			cout << i << "\t";
		cout << "\n" << endl;		
	}
private:
	vector<int>vect{ 0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1 };
	vector<int>vt{ 32,12,5,2,23,11,35,32,5,11,12 };
	void partition_sort() {
		size_t i = -1;
		for(size_t j=0;j!=vect.size();++j)
			if (!vect[j]) {
				++i;
				swap(vect[i], vect[j]);
			}
	}
	void countingSort_() {
		vector<size_t>counter(36, 0);//�����ֵΪ35
		for (auto i : vt)
			++counter[i];
		size_t n = 0;
		for (size_t i = 0; i != 36; ++i)//counter[i]��Ӧi��vt�еĸ���
			for (size_t j = 1; j <= counter[i]; ++j)
				vt[n++] = i;//���Կ������ĸ�ֵ��ȫ����ʵ��i����ԭ����vt��ֵ�޹أ�����̸�����ȶ�
	}//����㷨ֻ�����ڴ���������ϣ����������������������ݵĶ���
};

class solution8_3 {
public:
	void operator()() {
		cout << "a.����㷨��ǰ�����Ѿ�д�������Ƕ�ȱλ��0�ļ������� \n"
			<< "b.ͬ����Զ�ȱλ��0����ĸ�ıȽ�Ҳ��ת����ASCLL��Ҳ���Ǵ���0�����ֵļ�������"
			<< endl;
		radix_sort();
		for (auto i : vect)
			cout << i << endl;
		cout << "\n" << endl;
	}
private:
	vector<string>vect{ "VB","MOU","WC","VC","B","JIE","A","BC","QIN","NIGHT","C","PYTHON","MATLAB" };
	void counting_sort(vector<pair<size_t,string>>&vp) {	//��������
		vector<size_t>counter('Z' + 1, 0);
		for (auto i : vp)
			++counter[i.first];
		for (size_t i = 1; i != counter.size(); ++i)
			counter[i] += counter[i - 1];
		vector<string>order(vp.size());//������ż���������ַ���
		for (size_t i = vp.size() - 1; i != -1; --i) {
			order[counter[vp[i].first] - 1] = vp[i].second;
			--counter[vp[i].first];
		}
		for (size_t i = 0; i != vp.size(); ++i)//��vp�е��ַ�����������
			vp[i].second = order[i];
	}
	void radix_sort() {
		vector<pair<size_t, string>>vp(vect.size());//first���ĳ���ַ�����ĳλ�ַ���ȱ����0
		for (size_t i = 0; i != vect.size(); ++i)//��ʼ��vp����
			vp[i].second = vect[i];
	
		for (size_t i = 5; i != -1; --i) {
			for (auto &j : vp)
				if (j.second.size() < i+1)
					j.first = 0;
				else
					j.first = j.second[i];
			counting_sort(vp);
		}
		for (size_t i = 0; i != vp.size(); ++i)//�ı�ԭĿ��λ�õ��ַ���˳��
			vect[i] = vp[i].second;
	}
};

class solution8_4 {
public:
	void operator()() {
		cout << "a.ѡ��һ����ˮ������ˮ���в��ң�֪���ҵ�һ��ƥ���Ϊֹ���ظ���һ����ֱ���������ƥ�� \n"
			<< "b.����ñȽ��㷨�����ĺ�ˮ������ˮ����Ȼ������n������������½�Ϊ��(nlgn),2��(nlgn)=��(nlgn) \n"
			<< "c.�������ڿ��ŵķ�����ѡȡһ����ˮ����������С�����ˮ���ķ�����ߣ���������ұߣ��ú����ˮ�� \n"
			<< "��ͬ��������ɫˮ����ͬ���ķ���ȥ���ֺ�ˮ�������εݹ飬�ݹ�ʽΪT(n)=T(an)+T(n(1-a)+cn \n"
			<< "���ݿα�ǰ��ķ�����֪�ݹ�ʽ�����������ںõ����ΪO(nlgn),������Ϊ��(n^2)"
			<< endl;
	}
};
 
class solution8_5 {
public:
	void operator()() {
		cout << "a.k=1���빫ʽ��A[i]<=A[i+1],���ǵݼ����� \n"
			<< "b.2,1,3,5,4,7,6,8,10,9 \n"
			<< "c.ԭ����ʽ���=A[i]+��A[j](j=i+1...i+k-1),�ұ�=��A[j](j=i+1...i+k-1)+A[i+k] \n"
			<< "����A[i]<=A[i+k] \n"
			<< "d.��i=1...k��ͷ��k��������B[j]=i+k*j,j=1,2,3...r,��B[j]max<=A[n],�ֳ�k�飬����b�еĶ������� \n"
			<< "��Ϊ2,3,5,7,8,9��1,5,7,8,10���顣ÿ����n/k����������nlgn�������㷨����ʱ��Ϊn/k(nlg(n/k)) \n"
			<< "��Ϊһ����k�飬�����ܵ�����ʱ��Ϊ��(nlg(n/k)) \n"
			<< "e.�ο�solution6_5_9 \n"
			<< "f.����d�еĦ�(nlg(n/k))=��(nlgn-nlgk),��ΪkΪ����������ԭʽ��(nlgn)"
			<< endl;
	}
};

class solution8_6 {
public:
	void operator()() {
		cout << "a.C(2n,n) \n"
			<< "b."
			<< endl;/////////
	}
};
#endif //_SOLUTION_8_H_
