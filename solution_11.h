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
		cout << "相当于无序数组求最大值，需要O(n)"
			<< endl;
	}
};
class solution11_1_2 {
public:
	void operator()() {
		cout << "用0和1来代表有数据和无数据，借鉴，没看懂"
			<< endl;
	}
};

class solution11_1_3 {
public:
	void operator()() {
		cout << "将相同关键字的元素存储在一个链表中，这种方法后面会讲到，前提是具有相同关键字的元素不是太多"
			<< endl;
	}
};

class solution11_1_4 {
public:
	void operator()() {
		cout << "没太理解题目意思，就直接看答案了\n"
			<< "字典中每个元素带有一个索引，表示关于该元 素的的key存储在辅助栈中的位置。\n"
			<< "而辅助栈用数组实现，因此可以随机访问。辅助栈中存储 所有存在于字典中的元素的key ，\n"
			<< "于是形成了一个所谓validating cycle。要判断从字典中 直接读取到的元素是不是需要的数据，\n"
			<< "只需要取出该元素中的索引，判断这个索引是否有效 （大于栈底而小于栈顶），\n"
			<< "然后通过索引获取栈中的key ,与自己需要的元素的key比较看是 否相等即可以。\n"
			<< "相等表示该数据是要找的数据，否则不是。显而易见，通过这个数据结构模 型来进行SEARCH, \n"
			<< "INSERT都为O(1)。至于DELETE 操作，需要将被删除的数据在栈中的key 与栈顶存储的key交换后再删除，\n"
			<< "同样可以达到O(1)，要注意的是删除过程中，需要更新与 原栈顶中key相关元素的索引。"
			<< endl;
	}
};

class solution11_2_1 {
public:
	void operator()() {
		cout << "E(∑(i=1,n)∑(j=i+1,n) Xij)=(n-1)n/(2m),计算过程是本面公式推导的一部分，所以不写出 \n"
			<< "Pr{h(ki)=h(kj)}=1/m,是因为一共有m个曹，对于任意一个键i，和不同于i的j \n"
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
		cout << "对成功查找影响不大，因为链表不能随机存取，所以不能使用二分查找法\n"
			<< "可减少失败查找的时间，当节点的值大于要查找的关键字时就不用继续查找 \n"
			<< "会提高插入的时间，因为需要维持有序，删除操作与是否有序无关 \n"
			<< endl;
	}
};

class solution11_2_4 {
public:
	void operator()() {
		cout << "具有删除，插入，和判断元素是否属于元素属于字典操作，但根据题目用途，只需要删除插入就可以 \n"
			<< "判断一个元素是否属于单双链表都需要cn的时间，只需要单链表就可以实现O(1)的时间，每次插入和删除 \n"
			<< "都在表头操作就可以"
			<< endl;
	}
};

class solution11_2_5 {
public:
	void operator()() {
		cout << "没太看懂题目意思，直接借鉴了，它所谓的全域和我想的全域不是一个意思 \n"
			<< "鸽笼原理：Hash U中所有元素，则必有一个slot的元素数量大于n。\n"
			<< "若不然，m个slots共有小于等于nm个元素，矛盾"
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
		cout << "用散列值到达关键值的槽"
			<< endl;
	}
};

class solution11_3_2 {
public:
	void operator()() {
		cout << "这个可能需要用到后面数论的姿势，下面的答案有借鉴 \n"
			<< "h(k)=(a0*128^0+a1*128^1+a2*128^3....)mod(m)=(a0*128^0mod(m)+a1*128^1mod(m)....)mod(m)"
			<<"这样就可以不用存储一个很大的数"
			<< endl;
	}
};
class solution11_3_3 {
public:
	void operator()() {
		cout << "((2^p)^(n))mod(2^p-1)=1,利用上一题的公式可知最后的散列值只与各位的数字之和有关，将x的各字符置换后的和显然不变,应用可自己举例"
			<< endl;
	}
};

class solution11_3_4 {
public:
	void operator()() {
		for (auto i : vect) {
			cout << i << "\t→ " << hash(i) << endl;
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
