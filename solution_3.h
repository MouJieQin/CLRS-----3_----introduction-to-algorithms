#pragma once
#ifndef _SOLUTION_3_H_
#define _SOLUTION_3_H_
#include<iostream>
using namespace std;

class solution3_1_1 {
public:
	void operator()() {
		cout << " f(n)=Θ(f_(n)),g(n)=Θ(g_(n));max(f(n),g(n))=max(Θ(f_(n)),Θ(g_(n)));\n"
			<< "Θ(f(n)+g(n))=max(Θ(f_(n)),Θ(g_(n)))" << endl;
	}
};

class solution3_1_2 {
public:
	void operator()() {
		cout << "(n+a)^b=(max(Θ(n),Θ(a))^b=Θ(n^b)" << endl;
	}
};

class solution3_1_3 {
public:
	void operator()() {
		cout << "O包含了至多的意思" << endl;
	}
};
 
class solution3_1_4 {
public:
	void operator()(){
		cout << "1. 2^(n+1)=2*2^(n)=Θ(2^n) 成立\n"
			<< "当n→∞时(2^(2n)/2^n)=(2^n)→∞,不成立"
			<< endl;
	}
};

class solution3_1_5 {
public:
	void operator()() {
		cout << "如果f(n)和g(n)都是多项式，则g(n)的最高阶级数要高于f(n)\n"
			<< "多次使用洛必达法则可令分子为常数，分母带n，等式成立，其它情况要具体问题具体分析\n"
			<< "从一般来说o的定义类似于无穷小的定义" << endl;
	}
};
//3.1-6,3.1-7答案是书上的定义
class solution3_1_8 {
public:
	void operator()() {
		cout << "Ω(g(n,m))={f(n,m):存在正常量c,n0，m0，使得对所有n>=n0或m>=m0,有0<=cg(m,n)<=f(n,m)}"
			<< "O(g(n,m))={f(n,m):存在正常量c1,c2,n0，m0，使得对所有n>=n0或m>=m0,有0<=c1g(m,n)<=f(n,m)<=c2g(m,n)}"
			<< endl;
	}
};

class solution3_2_1 {
public:
	void operator()() {
		cout << "取n1<n2,则f(n1)<f(n2),g(n1)<g(n2),f(n1)+g(n1)<f(n2)+g(n2),故f(n)+g(n)是增函数\n"
			<< "取n1<n2,m1<m2则f(m1)<f(m2),g(n1)<g(n2),令m1=g(n1),m2=g(n2),有f(g(n1))<f(g(n2)),故f(g(n))是增函数\n"
			<< "取n1<n2,则f(n1)<f(n2),g(n1)<g(n2),f(n1)*g(n1)<f(n2)*g(n2),故f(n)*g(n)是增函数" << endl;
	}
};

class solution3_2_2 {
public:
	void operator()() {
		cout << "对等式两边分别取以自然对数为底的对数函数可化为："
			<< "log(c,b)*ln(a)=log(b,a)*ln(c) \n"
			<< "等式左边展开后得：(lga*lgb)/(lgb*lge)=等式右边展开" << endl;
	}
};

class solution3_2_3 {
public:
	void operator()() {
		cout << "1.根据斯特林公式的提示，n→∞时e^(an)→1,常量系数根号下2π可以忽略，等式变成n!=n^(1/2)*(n/e)^n \n"
			<< "对等式两边分别取2的对数，等式右边等于1/2lgn+(1/lge)*nlgn\n"
			<< "故log(n!)=Θ(nlgn) \n"
			<< "2.存在n0,对任意n>=n0的数,对任意正常量c,0<=n!<c*2^n;"
			<< "3.存在n0,对任意n>=n0的数,对任意正常量c,0<=n!<c*n^n;" << endl;
	}
};

class solution3_2_4 {
public:
	void operator()() {
		cout << "两个函数都是非严格递增，无摆动。当n1<n2时，f(n1)<=f(n2),应该有界" << endl;
	}//无把握，即使结论对了，理由也可能是错的
};

class solution3_2_5 {
public:
	void operator()() {
		cout << "	n	4	16	16^2		65536	65536^2		2^65536		\n"
			<< "lg(*)lgn	1	2	3		3	    4			4		\n"
			<< "lglg(*)n	1	lg3	lg3		2	    2			lg5		\n"
			<< "lg(*)lgn 渐进更大一些"
			<< endl;
	}
};

class solution3_2_7 {
public:
	void operator()() {
		cout << "本以为式(3.25)是对该题的提示，所以我花了一段时间去想这个式子怎么得来的……\n"//abs为绝对值
			<< "虽然和本题无关也还是写出来：用x>0，y来代替共轭数，当i为偶数时，Fi=x^i/5^(1/2)+abs(x^i/5^(1/2)) \n"
			<< "Fi<x^i/5^(1/2)+1/2 然后对这个式子向下取整比较好理解\n"
			<< "当n为奇数时可这样思考，Fi-1(1)(2)Fi(3)(4)Fi+1,其中括号内的数字为相邻整数的四个位置\n"
			<< "(1)为(Fi-1,Fi-1/2),(2)为(Fi-1/2,Fi),(3)(Fi,Fi+1/2),(4)(Fi+1/2,Fi+1) \n"
			<< "Fi=x^i/5^(1/2)-abs(x^i/5^(1/2)),此时等式右边的值在(2)区域，因为abs()<1/2 \n"
			<< "等式右边同时加上1得:Fi<x^i/5^(1/2)+1/2 ，此时不等式右边的值应该在(3)区，向下取整后得Fi,故可合并成 \n"
			<< "式(3.25) \n"
			<< "证明:1.F1=0,F2=1 \n"
			<< "2.假设Fn，F(n+1)成立\n"
			<< "3.Fn+F(n+1)变形后得((3+5^1/2)x^n-(3+5^1/2)y^n)/5^1/2=F(n+2)变形后，得证" << endl;
	}
};

class solution3_2_8 {
public:
	void operator()() {
		cout << "klnk=Θ(n)意味着lnk相当于常数系数，故Θ(n/lnn)=Θ(n),得证" << endl;
	}//无把握，不太理解题目的意思，为什么要分别用k和n
};

//思考题
class solution3_1 {
public:
	void operator()() {
		cout << "存在正常数c,n0,使得当n>=n0时，0<=p(n)<=c*n^k \n"
			<< "存在正常数c,n0,使得当n>=n0时，0<=c*n^k<=p(n) \n"
			<< "存在正常数c1,c2,n0,使得当n>=n0时，0<=c1*n^k<=p(n)<=c2*n^k \n"
			<< "存在正常数c,n0,使得当n>=n0时，对任意c>0,0<=p(n)<cn^k \n"
			<< "存在正常数c,n0,使得当n>=n0时，对任意c>0,0<=c*n^k<p(n) \n"
			<< endl;
	}
};

class solution3_2 {
public:
	void operator()() {
		cout << "a.是，是，否，否，否\n"
			<< "b.是，是，否，否，否\n"
			<< "c.否，否，否，否，否\n"
			<< "d.否，否，是，是，否\n"
			<< "e.是，否，是，否，是\n"
			<< "f.是，是，否，否，否\n"
			<< endl;
	}
};

class solution3_4 {
public:
	void operator()() {
		cout << "a.否，n=O(n^2),n^2!=O(n) \n"
			<< "b.否，n^2+n=Θ(n^2)!=(Θ(min(n^2,n))=Θ(n)) \n"
			<< "c.是，1.f(n)=O(g(n)),N→∞时，1<=f(n)<=cg(n),lg(f(n))<=lg(cg(n))\n"
			<< "d.错，f(n)=n,g(n)=2n,2^n!=O(2^(2n))\n"
			<< "e.错，f(n)=1	\n"
			<< "f.是，根据O和Ω的定义可证\n"
			<< "g.否，f(n)=2^n,f(n/2)=2^(n/2),n→∞,f(n)/f(n/2)=2^(n/2)→∞	\n"
			<< "h.否，f(n) + o(f(n)) = Θ(max(f(n), o(f(n)))) = Θ(f(n))	\n"
			<< endl;
	}
};

class solution3_5 {
public:
	void operator()() {
		cout << "a.如果只有有限多个 n 使得 f(n) ≥ cg(n) ≥ 0，那么当 n 趋进 ∞ 时，\n"
			<< "必有 0 ≤ f(n) ≤ cg(n)，即 f(n) = O(g(n))显然，用 Ω替换\n"
			<< "∞	\n"
			<< "Ω时不成\n"//借鉴，没太看懂题目意思，照这个答案来看单纯Ω代表有限个的意思而不是正文中定义的Ω
			<< "b.Advantage: 可以刻画所有函数之间的关系Disadvantage: 刻画得不精确\n"//借鉴，这个Ω可能代表正文中的Ω
			<< "c.For any two functions f(n) and g(n), we have if f(n) = Θ(g(n)) then \n"
			<< "f(n) = O′（g(n)) and f(n) = Ω(g(n))But the converse is not true \n"
			<< "借鉴，反向不成立是因为O'的定义的集合里含有单调递减的负函数 \n"
			<< "d.~Ω(g(n))={f(n):存在正常量c,n0,k,使得当n>=n0时，0<=c*g(n)*lg(n)^k<=f(n)}	\n"
			<< "~Θ(g(n))={f(n):存在正常量c1,c2,n0,k1,k2,使得当n>=n0时，0<=c1*g(n)*lg(n)^k1<=f(n)<=c2*g(n)*lg(n)^k2	\n"
			<< "若f(n)=~Θ(g(n))成立，当且仅当f(n)=~O(g(n))并且f(n)=~Ω(g(n))	\n"
			<< endl;
	}
};

class solution3_6 {
public:
	void operator()() {
		cout << "a.n	\n"
			<< "b.k,k>1为正常量并使得2^（k-1)<n<=2^(k)	\n"
			<< "c.┍lgn┑		\n"
			<< "d.┍lgn┑ -1	\n"
			<< "e.k,使得n<=2^(2^k)	\n"
			<< "f.∞		\n"
			<< "g.>=lglgn/lg3		\n"//借鉴
			<< "O(log n)"//借鉴
			<< endl;
	}
};

#endif //_SOLUTION_3_H_
