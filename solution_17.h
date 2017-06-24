#pragma once
#ifndef _SOLUTION_17_H_
#define _SOLUTION_17_H_
#include<iostream>
#include<vector>
using namespace std;

class solution17_1_1 {
public:
	void operator()() {
		cout << "不是，因为理论上可以一直执行multipush，而花费kn \n"
			<< endl;
	}
};

class solution17_1_2 {
public:
	void operator()() {
		cout << "可以在an，a<1的时间内将k位计数器填满，然后交替进行decrement和increment操作，每次都耗费k,所以Θ(nk)"
			<< endl;
	}
};

class solution17_1_3 {
public:
	void operator()() {
		cout << "对于输入规模n,最多有lgn+1项2的幂，2^0+2^1+2^2+....+2^lgn=2n,剩余项最多n项花费n,所以摊还代价为1"
			<< endl;
	}
};

class solution17_2_1 {
public:
	void operator()() {
		cout << "push和pop支付2美元，每进行一次操作都会至少有1美元的剩余，因为要进行k次操作后才能进行复制操作，而栈的大小不会大于k,所以 \n"
			<< "k次操作后栈中肯定至少有k美元剩余"
			<< endl;
	}
};

class solution17_2_2 {
public:
	void operator()() {
		cout << "不论i是否为2的幂，每次操作是都支付3美元，如果第i次操作不是2的幂，那么剩余信用还有2，如果是2的幂，对于第2^k次操作，\n"
			<< "在与前一个不包括2^(k-1)之间包括2^k本身还有2^k-2^(k-1)个数，每个数还剩余2美元，所以一共有2*2^k-2^k=2^k美元，刚好够 \n"
			<< "这次花费使用"
			<< endl;
	}
};

class  solution17_2_3 {
public:
	void operator()() {
		cout << "给每一个被检测和翻转的位支付3,每次检测和翻转花费2，如果下一次是复位，每一位可以用信用支付复位的费用，如果不是复位 \n"
			<< "可以推断每一次每一位会有更多信用\n"
			<< endl;
	}
};

class solution17_3_1 {
public:
	void operator()() {
		cout << "φ'(Di)=φ(Di)-φ(D0),φ'(0)=0,φ'(Di)的摊还代价为φ'(Dn)-φ'(D0)=φ(Dn)-φ(D0)与φ(Di)的摊还代价相同"
			<< endl;
	}
};

class solution17_3_2 {
public:
	void operator()() {
		cout << "φ=2*i-2^(1+┕lgi┙）"//借鉴
			<< endl;
	}
};

class solution17_3_3 {
public:
	void operator()() {
		cout << "φ=∑[i=1,n] lgi,其中n为进行操作后元素个数，当进行insert操作时，φ(Di)-φ(Di-1)=lgn,ci=lgn+lgn=2lgn, \n"
			<< "当进行extract_min操作时，φ(Di)-φ(Di-1)=-lgn，ci=lgn-lgn=O(1)"
			<< endl;
	}
};

class solution17_3_4 {
public:
	void operator()() {
		cout << "φ(Di)为栈中元素个数，对于push操作ci'=c1+1=2,对于pop操作，ci'=c1-1=0,对于mulitpop，ci'=k'-k'=0 \n"
			<< "对于实际操作∑ci<=∑2+sn-s0=2n+sn-s0"
			<< endl;
	}
};

class solution17_3_5 {
public:
	void operator()() {
		cout << "n=Ω(b),表示b<=n，根据上面的公式就能看出来"
			<< endl;
	}
};

class solution17_3_6 {
public:
	void operator()() {
		cout << "入队时直接push进s1，出队时如果s2不为空则直接将s2 pop出去，为空则将s1的所有元素pop进s2,然后pop出去 \n"
			<< "入队支付3美元，入队操作支付一美元，进入s2栈1美元，将来被弹出1美元"
			<< endl;
	}
};

class solution17_3_7 {
public:
	void operator()() {
		cout << "首先分配一个足够大的数组队列，插入直接在尾端插入，支付5美元，操作本身耗费1美元，剩下4美元，线性时间找到中位数，并用中位数 \n"
			<< "作为划分元素partition,这两个操作每个加起来不会超过2n美元，n是元素的大小，每个元素还剩2美元 \n"
			<< "删除只需要移动tail，自行花费1美元，将删除的一大半元素的钱均分到未删除元素，这时每个元素就拥有4美元，可以进行下次删除 \n"
			<< endl;
	}
};

class solution17_4_1 {
public:
	void operator()() {
		cout << "当转载因子接近1时，插入操作花费的时间开始升高到线性时间，第11章已经讲过3种开放地址的插入算法。因为对于不是O(1)的操作可以平摊到O(1)的操作上，从而使得每个操作都是O(1)"
			<< endl;
	}
};
class solution17_4_2{
public:
	void operator()() {
		cout << "ci'=ci+φi-φ(i-1)=1+2*(num-1)-size-(2*num-size)=-1"
			<< endl;
	}
};

class solution17_4_3 {
public:
	void operator()() {
		cout << "假设删除操作并没有引起表的收缩 \n"
			<< "ci'=1+|2*（num-1)-size|-|2*num-size| \n"
			<< "如果转载因子大于1/2，ci'=-1 \n"
			<< "如果转载因子小于等于1/2，ci'=3 \n"
			<< "如果引起了表的收缩 \n"
			<< "ci'=1+1/3*s+|2*(num-1)-2/3*size|-|2*num-size| \n"
			<< "其中num=1/3*size,ci'=3 \n"
			<< endl;
	}
};

//思考题
class solution17_1 {
public:


};

#endif