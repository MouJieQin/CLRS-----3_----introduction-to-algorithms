#pragma once
#ifndef	_SOLUTION_5_H
#define _SOLUTION_5_H
#include<iostream>
#include<cmath>
using namespace std;

class solution5_1_1 {
public:
	void operator()() {
		cout << "看不太懂题目意思"
			<< endl;
	}
};

class solution5_1_2 {
public:
	void operator()() {
		cout << "random(0,1)*(b-a)+a"////////////////////
			<< endl;
	}
};

class solution5_1_3 {
public:
	void operator()() {
		cout << ""/////////////////////////////
			<< endl;
	}
};

class solution5_2_1 {
public:
	void operator()() {
		cout << "雇用一次水平最高的人第一个面试，其他人随意排列,Pr{X=1}=(n-1)!/n!=1/n    \n"
			<<"雇佣n次水平呈递增排列，Pr(X=n)=1/n!"
			<< endl;
	}
};

class solution5_2_2 {
public:
	void operator()() {
		cout << "第一个人不管水平如何一定会被雇用，如果第一个人的水平最高为1，则不可能雇用两次 \n"
			<< "第一个人水平为2,1可以在后续随便排列有(n-1)!种可能 \n"
			<< "第一个人水平为3，2必须在1的后面，有C(n-1,2)(n-3)! \n"
			<< "第一个人水平为4，2,3必须在1的后面且可随意排列，有C(n-1,3)(n-4)!2! ...... \n"
			<< "第一个人水平为n,1必须排在第2位，有(n-2)!,以此得到规律有∑(n-1,k)*(n-k-1)!(k-1)!,k=1...n-1  \n"
			<< "化简得(n-1)!∑(1/k)=(n-1)!*ln(n-1)+O(1),因为一共有n!种可能，Pr{X=2)=((n-1)!*ln(n-1)+O(1))/n! \n"
			<< "=(1/n)*(ln(n-1)+O(1)) \n"
			<< "以上是我自己的做法，下面陈述别人的：\n"
			<< "第一个水平为i的被雇佣的概率为1/n,比它水平高的还有i-1位，水平最高的1必定在i-1位之中且必须排在首位 \n"
			<< "概率为1/(i-1),Pr{X=2}=∑(1/n)*1/(i-1),i=2....n,=1/n∑1/k,k=1...n-1,=(1/n)(ln(n-1)+O(1))"
			<< endl;
	}
};

class solution5_2_3 {
public:
	void operator()() {
		cout << "指示器随机变量X(i)对应1个骰子出现点数i的事件，1个骰子之和的期望E(X)=∑X(i)*Pr{i}=21/6,i=1...6"
			<< "n个骰子的期望之和E(∑X";
	}///////////////////////////////////////
};

class solution5_2_4 {
public:
	void operator()() {
		cout << "指示器随机变量X(i)对应第i个顾客拿到自己帽子的 \n"
			<< "随机变量X表示拿到自己帽子的总人数		\n"
			<< "E(X)=E∑(X(i))=∑E(X(i))=n*1/n=1,其中i=1...n"
			<< endl;
	}
};

class solution5_2_5 {
public:
	void operator()() {
		cout << "";////////////////////////
	}
};

class solution5_3_3 {
public:
	void operator()() {
		cout << "不能，";///////////////////////
	}
};

class solution5_4_1 {
public:
	void operator()() {
		cout << "1.k个人中没有人和你的生日相同的概率((n-1)/n)^k,1-((n-1)/n)^k>=1/2,其中n=356，解得k>=253 \n"
			<< "2.没有人的生日为7.4的概率为((n-1)/n)^k,只有一个人的生日为7.4的概率为k/n*((n-1)/n)^(k-1) \n"
			<< "1-(((n-1)/n)^k+k/n*((n-1)/n)^(k-1))>=1/2 ,k>=613 "
			<< endl;
	}
};

class solution5_4_2 {
public:
	void operator()() {
		cout << "类似于生日悖论"
			<< endl;
	}
};

class solution5_4_3 {
public:
	void operator()() {//有借鉴
		cout << "1.独立是必须的，书中两种分析都有依赖独立性，两两独立足够，书中只依赖两两独立"
			<< endl;
	}
};

class solution5_4_4 {
public:
	void operator()() {
		cout << "三个人为特定某天的生日的概率为1/n^3,天一共有n种，E({Xi>=3))=C(k,3)*1/n^3*n>=1,当期望大于1时表明期望有 \n"
			<< "三人的生日相同，解得k=94"
			<< endl;
	}
};

class solution5_4_5 {
public:
	void operator()() {
		cout << "每个字符串有n种可能，k个字符串有n^k种可能，其中包含重复，k排列不能有重复，可能的排列有A(n,k)种 \n"
			<< "Pr{X(k)}=(n!)/((n-k)!*n^k),与生日悖论问题互补"
			<< endl;
	}
};

class solution5_4_6 {
public:
	void operator()() {
		cout << "1.投中一个箱子的概率是1/n,投不中的概率为1-1/n,n次都没投中的概率为(1-1/n)^n, \n"
			<< "一共有n个箱子，E=n*(1-1/n)^n=n/e  \n"
			<< "2.一个箱子只有一个球的期望是n次只有一次投中，n*1/n*(1-1/n)^(n-1)=1/e,  \n"
			<< "一共有n个箱子，E=n/e"
			<< endl;
	}
};

class solution5_4_7 {
public:
	void operator()() {
		cout << ""//////////////////////////////////
			<< endl;
	}
};

//思考题


#endif //_SOLUTION_5_H
