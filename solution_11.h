#pragma once
#ifndef _SOLUTION_11_H
#define _SOLUTION_11_H
#include<iostream>
#include<vector>
#include<memory>
using namespace std;
class solution11_1_1 {
public:
	void operator()() {
		cout << "�൱���������������ֵ����ҪO(n)"
			<< endl;
	}
};
class solution11_1_2 {
public:
	void operator()() {
		cout << "��0��1�����������ݺ������ݣ������û����"
			<< endl;
	}
};

class solution11_1_3 {
public:
	void operator()() {
		cout << "����ͬ�ؼ��ֵ�Ԫ�ش洢��һ�������У����ַ�������ὲ����ǰ���Ǿ�����ͬ�ؼ��ֵ�Ԫ�ز���̫��"
			<< endl;
	}
};

class solution11_1_4 {
public:
	void operator()() {
		cout << "û̫�����Ŀ��˼����ֱ�ӿ�����\n"
			<< "�ֵ���ÿ��Ԫ�ش���һ����������ʾ���ڸ�Ԫ �صĵ�key�洢�ڸ���ջ�е�λ�á�\n"
			<< "������ջ������ʵ�֣���˿���������ʡ�����ջ�д洢 ���д������ֵ��е�Ԫ�ص�key ��\n"
			<< "�����γ���һ����νvalidating cycle��Ҫ�жϴ��ֵ��� ֱ�Ӷ�ȡ����Ԫ���ǲ�����Ҫ�����ݣ�\n"
			<< "ֻ��Ҫȡ����Ԫ���е��������ж���������Ƿ���Ч ������ջ�׶�С��ջ������\n"
			<< "Ȼ��ͨ��������ȡջ�е�key ,���Լ���Ҫ��Ԫ�ص�key�ȽϿ��� ����ȼ����ԡ�\n"
			<< "��ȱ�ʾ��������Ҫ�ҵ����ݣ������ǡ��Զ��׼���ͨ��������ݽṹģ ��������SEARCH, \n"
			<< "INSERT��ΪO(1)������DELETE ��������Ҫ����ɾ����������ջ�е�key ��ջ���洢��key��������ɾ����\n"
			<< "ͬ�����ԴﵽO(1)��Ҫע�����ɾ�������У���Ҫ������ ԭջ����key���Ԫ�ص�������"
			<< endl;
	}
};

class solution11_2_1 {
public:
	void operator()() {
		cout << "E(��(i=1,n)��(j=i+1,n) Xij)=(n-1)n/(2m),��������Ǳ��湫ʽ�Ƶ���һ���֣����Բ�д�� \n"
			<< "Pr{h(ki)=h(kj)}=1/m,����Ϊһ����m���ܣ���������һ����i���Ͳ�ͬ��i��j \n"
			<< "Pr{h(ki)=h(kj)}=1/m*1/m*m=1/m"
			<< endl;
	}
};

class solution11_2_2 {
public:
	solution11_2_2():hash_table(10){}
	void operator()() {
		hash();
	}
private:
	vector<int>vect{ 5,28,19,15,20,33,12,17,10 };
	struct singlely_link{
		singlely_link(int k,const shared_ptr<singlely_link>&ptr=nullptr):key(k),next(ptr){}
		int  key;
		shared_ptr<singlely_link>next;
	};
	vector<shared_ptr<singlely_link>>hash_table;
	void hash() {
		for (auto i : vect) {
			auto temp = shared_ptr<singlely_link>(new singlely_link(i, hash_table[i % 9]));
			hash_table[i % 9] = temp;
			size_t n = 0;
			for (auto &i : hash_table) {
				cout << n++ << " : ";
				auto tmp = i;
				while (tmp) {
					cout << tmp->key<<"\t";
					tmp = tmp->next;
				}	
				cout << endl;
			}
			cout << "\n" << endl;
		}
	}
};

class solution11_2_3 {
public:
	void operator()() {
		cout << "�Գɹ�����Ӱ�첻����Ϊ�����������ȡ�����Բ���ʹ�ö��ֲ��ҷ�\n"
			<< "�ɼ���ʧ�ܲ��ҵ�ʱ�䣬���ڵ��ֵ����Ҫ���ҵĹؼ���ʱ�Ͳ��ü������� \n"
			<< "����߲����ʱ�䣬��Ϊ��Ҫά������ɾ���������Ƿ������޹� \n"
			<< endl;
	}
};

class solution11_2_4 {
public:
	void operator()() {
		cout << "����ɾ�������룬���ж�Ԫ���Ƿ�����Ԫ�������ֵ��������������Ŀ��;��ֻ��Ҫɾ������Ϳ��� \n"
			<< "�ж�һ��Ԫ���Ƿ����ڵ�˫������Ҫcn��ʱ�䣬ֻ��Ҫ������Ϳ���ʵ��O(1)��ʱ�䣬ÿ�β����ɾ�� \n"
			<< "���ڱ�ͷ�����Ϳ���"
			<< endl;
	}
};

class solution11_2_5 {
public:
	void operator()() {
		cout << "û̫������Ŀ��˼��ֱ�ӽ���ˣ�����ν��ȫ��������ȫ����һ����˼ \n"
			<< "����ԭ��Hash U������Ԫ�أ������һ��slot��Ԫ����������n��\n"
			<< "����Ȼ��m��slots����С�ڵ���nm��Ԫ�أ�ì��"
			<< endl;
	}
};

class solution11_2_6 {
public:
	void operator()() {

	}
};

class solution11_3_1 {
public:
	void operator()() {
		cout << "��ɢ��ֵ����ؼ�ֵ�Ĳ�"
			<< endl;
	}
};

class solution11_3_2 {
public:
	void operator()() {
		cout << "���������Ҫ�õ��������۵����ƣ�����Ĵ��н�� \n"
			<< "h(k)=(a0*128^0+a1*128^1+a2*128^3....)mod(m)=(a0*128^0mod(m)+a1*128^1mod(m)....)mod(m)"
			<<"�����Ϳ��Բ��ô洢һ���ܴ����"
			<< endl;
	}
};
class solution11_3_3 {
public:
	void operator()() {
		cout << "((2^p)^(n))mod(2^p-1)=1,������һ��Ĺ�ʽ��֪����ɢ��ֵֻ���λ������֮���йأ���x�ĸ��ַ��û���ĺ���Ȼ����,Ӧ�ÿ��Լ�����"
			<< endl;
	}
};

class solution11_3_4 {
public:
	void operator()() {
		for (auto i : vect) {
			cout << i << "\t�� " << hash(i) << endl;
		}
	}
private:
	vector<int>vect{ 61,62,63,64,65 };
	size_t hash(size_t n) {
		const double A = (sqrt(5.0) - 1) / 2;
		const double value = n*A;
		return static_cast<size_t>((value - static_cast<size_t>(value)) *1000);
	}
};

class solution11_3_5 {
public:
	void operator()() {
	}
};
#endif//_SOLUTION_11_H
