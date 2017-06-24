#pragma once
#ifndef _SOLUTION_7_H_
#define _SOLUTION_7_H_
#include<iostream>
#include<vector>
using namespace std;
void print_vector(vector<int>&vect) {
	for (auto beg=vect.begin()+1;beg!=vect.end();++beg)
		cout << *beg<< "\t";
	cout << "\t" << endl;
}

class solution7_1_1 {
public:
	void operator()() {
		QuickSort(1, vect.size() - 1);
	}
private:
	vector<int>vect{ INT_MIN,13,19,9,5,12,8,7,4,21,2,6,11};
	//vector<int>vect{ 9,9,9,9,9,9,9,9,9,9,9,9,9 };
	void QuickSort(size_t beg,size_t end) {
		if (beg < end) {
			size_t mid = partition(beg, end);
		//	size_t mid = partition(beg, end,true);
			QuickSort(beg, mid - 1);
			QuickSort(mid + 1, end);
		}
	}
	size_t partition(size_t beg, size_t end) {
		size_t i = beg - 1;
		for (size_t j = beg; j < end; ++j) 
			if (vect[j] <= vect[end]) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[i+1], vect[end]);
		print_vector(vect);
		return i + 1;
	}
	size_t partition(size_t beg, size_t end,bool) {
		size_t i = beg - 1;
		for (size_t j = beg; j < end; ++j)
			if (vect[j] <= vect[end]) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[i + 1], vect[end]);
		print_vector(vect);
		return
			i + 1 == end ? (beg + end) / 2 : i + 1;
	}
};

class solution7_1_2 {
public:
	void operator()() {
		cout << "返回r,检测修改结果在上一题中重载，对于重复元素，可以看出修改后的程序能明显减少执行步数"
			<< endl;
	}
};

class solution7_1_3 {
public:
	void operator()() {
		cout << "可以看出除循环外，所有代价均为常数时间，而循环需要执行n步，每步花费常数时间，故为Θ(n)"
			<< endl;
	}
};

class solution7_1_4 {
public:
	void operator()() {
		cout << "把partition第4行的<=改为>="
			<< endl;
	}
};

class solution7_2_1 {
public:
	void operator()() {
		cout << "要证明T(n)<=cn^2,T(n)<=c(n-1)^2+cn=cn^2-cn+c<=cn^2,,c>=1时成立,T(n)=O(n^2) \n"
			<< "要证明T(n)>=c1*n^2,T(n)>=c1*(n-2)^2+c2*n=c1*n^2+(c2-2*c1)+c1>=c1*n^2，当c2>=2c1时成立 \n"
			<< "T(n)=Ω(n^2) \n"//这个证明有借鉴
			<<"综上T(n)=Θ(n^2)"
			<< endl;
	}
};

class solution7_2_2 {
public:
	void operator()() {
		cout << "Θ(n^2),就是上一题的递归式"
			<< endl;
	}
};

class solution7_2_3 {
public:
	void operator()() {
		cout << "由于主元是选取的最右边的元素，而每个最右边的元素都是子数组中最小的，所以每次都是最坏不均匀划分 \n"
			<< "迭代式为上上题，为Θ(n^2)"
			<< endl;
	}
};

class solution7_2_4 {
public:
	void operator()() {
		cout << "对于几乎有序的序列来说，插入插入排序是Θ(n),因为内层循坏只花费常数时间，而quicksort代价为Θ(n^2) \n"
			<< endl;
	}
};

class solution7_2_5 {
public:
	void operator()() {		
		cout << "T(n) = T(na) + T(n(1 - a)) + cn,最小深度为最左边的，log(1/a,n)=-log(a,n)=-lgn/lga \n"
			<< "最大深度在最右边，log(1/(1-a),n)=-log(1-a,n)=-lgn/lg(1-a)"
			<< endl;
	}
};
class solution7_2_6 {
public:
	void operator()() {
		cout << "0<a<=1/2,当a<b<=1/2时，b划分更平衡，将（0,1/2]划分成线段，a将该线段划分成两部分(0,a],(a,1/2) \n"
			<< "Pr{X=b>a}=(1/2-a)/(1/2-0)=1-2a"
			<< endl;
	}
};
class solution7_3_1 {
public:
	void operator()(){
		cout << "在随机化算法的情况下，n→∞时，最坏情况出现的概率为0"
			<< endl;
	}
};
class solution7_3_2 {
public:
	void operator()() {
		cout << "最坏情况下，随机数生成器产生的随机数形成的划分是子数组中最小或最大的元素，每次划分成n-1和0， \n"
			<< "需要调用Θ(n)次，最好的情况Θ(lgn)次"
			<< endl;
	}
};
class solution7_4_1 {
public:
	void operator()() {
		cout << "要证明T(n)>=cn^2,T(n)>=(cq^2+c(n-q-1)^2)+Θ(n)<=cn^2-c(2n-1)+Θ(n),存在一个足够小的c \n"
			<< "使得c(2n-1)小于Θ(n)项"
			<< endl;
	}
};

class solution7_4_2 {
public:
	void operator()() {
		cout << "最好情况下的递归式为T(n)=2T(n/2)+Θ(n),要证明T(n)>=cnlgn \n"
			<< "T(n)>=2*c/2*lg(n/2)+c1*n=cnlgn-cn+c1*n,当c<c1时成立"
			<< endl;
	}
};

class solution7_4_3 {
public:
	void operator()() {
		cout << "令x=q+1,则x=1...q,原式=（x-1)^2+(n-x)^2=2x^2-(2+2n)x+n^2+1,可知关于x的一元二次函数的函数图像顶点 \n"
			<< "x1=(1+n)/2对应的值是最小值，最大值为区间1或q对应的值"
			<< endl;
	}
};

class  solution7_4_4 {
public:
	void operator()() {
		cout << "式子（7.4)∑{i=1,n-1}∑{k=1,n-i} (2/(k+1))>=∑{i=1,n/2}∑{k=1,n-i} (2/(k+1)) \n"
			<< ">=∑{i=1,n/2}∑{k=1,n/2} (2/(k+1))=∑{i=1,n/2} ln(n)+c=Ω(nlgn)"
			<< endl;
	}
};

class solution7_4_5 {
public:
	void operator()() {
		cout << "因为快速排序总体期望接近于最好情况，所以每次都是常数划分，这里取1/2,方便计算 \n"
			<< "递归树叶为n/k时有lg(n/k)层，每层耗费c1*n，所以快排耗费c1*nlg(n/k) \n"
			<< "插入排序对于规模为k的，代价为c2*k^2,一共有n/k个，所以为c2*nk，综上 O(nk+nlg(n/k) \n"
			<< "理论上：c2*nlgn>=c1*nk+c2*nlg(n/k),k<=c2/c1*lgk \n"
			<< "实践中 k取对于几乎有序的插入排序的代价低于快排的的规模"
			<< endl;
	}
};

class solution7_4_6 {
public:
	void operator()() {
		cout << "三个元素可以重复，假设输入规模为n，取的中位数为na的概率为1/n,小于等于的概率为na/n,大于等于为n(1-a)/n \n"
			<< "一共有3！种排列，总体概率为 6*a(1-a)/n"
			<< endl;
	}
};
//思考题

class solution7_1 {
public:
	void operator()() {
		//a.
		quickSort(1, vect.size() - 1);
		cout << "排序之后:" << endl;
		print_vector(vect);
		cout << "b.数组j越界的可能是第一次进入repeat-until就越界，但是当j=p时必然不满足循环条件退出循环，此时i=j \n"
			<< "退出while循环。如果j在越界之前退出循环，进入i循环后，i第一次退出循环必然是当i=p时， \n"
			<<"此时A[i]=x,如果i<j,执行交换，这也就意味着，在j左边必然有一个元素不满足j的循环条件， \n"
			<<"因为不满足循环条件的被交换到j左边去了，而i右边也必然存在一个元素i不满足i的循环条件 \n"
			<<"因为不满足循环条件的被交换到i右边去了，重复这一过程直到i>=j退出while循环 \n"
			<<"c.当x=最数组中的最小值时返回p，不会返回r是要返回r的必要条件是j=r时j退出循环，而此时i必然也会退出循环 \n"
			<<"交换后必然满足i<j,此时i会再次递减一次，其它情况下则有返回值 \n"
			<<"d.A[p...j]<=x,A[i...r]>=x,所以A[p...j]]<=A[i...r] \n"
			<<"e.见a"
			<< endl;
	}
private: 
	vector<int>vect{0,13,19,9,5,12,8,7,4,11,2,6,21 };
	void quickSort(size_t beg,size_t end) {
		if (beg < end) {
			cout << "辅助变量的值是" << vect[beg] << ",排序后的结果为:" << endl;
			size_t mid = hore_partition(beg, end);
			print_vector(vect);
			quickSort(beg, mid);
			quickSort(mid + 1, end);
		}
	}
	size_t hore_partition(size_t p,size_t r) {
		int x = vect[p];
		size_t i = p - 1;
		size_t j = r + 1;
		while (true) {
			do {
				--j;
			} while (vect[j]>x);
			do {
				++i;
			} while (vect[i]<x);
			if (i < j)
				swap(vect[i], vect[j]);
			else
				return j;
		}
	}
};

class solution7_2 {
public:
	void operator()() {
		cout << "a.所有元素都相同属于已排序的情况，所以运行时间为Θ(n^2) \n"
			<< "b.见下方 \n"
			<<"c.见下方 \n"
			<<"d.因为Quicksort'的比较次数一定少于Quicksort，运行时间仍然为O(n log n)"
			<< endl;
		// b. c.
		sortQuick(1, vect.size() - 1);
		print_vector(vect);
	}
private:
	vector<int>vect{ 0,3,5,1,2,2,8,3,3,6,4,12,9 };
//	vector<int>vect{ 2,2,2,2,2,2,2,2,2,2 };
	pair<size_t, size_t>partition(size_t beg,size_t end) {
		size_t q = beg - 1;
		size_t t = beg - 1;
		int x = vect[end];
		for(size_t j=beg;j!=end;++j)
			if (vect[j] < x) {
				++q;
				++t;
				if (q != t&&t != j) {
					swap(vect[q], vect[t]);
					swap(vect[q], vect[j]);
				}
				else
					swap(vect[q], vect[j]);
			}
			else if(vect[j]==x){
				++t;
				swap(vect[t], vect[j]);
			}
			swap(vect[end], vect[t+1]);
			print_vector(vect);
			return
			{ q+1,t+1 };
	}
	void sortQuick(size_t beg, size_t end) {
		if (beg < end) {
			pair<size_t, size_t>temp{ partition(beg,end) };
			cout << "q is "<<temp.first << "   t is " << temp.second << endl;
			sortQuick(beg, temp.first-1);
			sortQuick(temp.second+1, end);
		}
	}
};

class solution7_3 {
public:
	void operator()() {
		cout << "a.不证自明，证明略去，E(X(i))=1/n, \n"
			<< "b.期望运行时间等于以q为划分出来两个子数组的期望运行时间 \n"
			<< "c.E∑(X(q)(T(q-1)+T(n-q))),q=1....n,其中T(q-1)和T(n-q)有两种情况相同， \n"
			<< "当q=n-q+1时，T(q-1)=T(n-q),T(n-q)=T(q-1),所以可以简写为2E∑X(q)(T(q))=2∑E(Xq)(T(q)) \n"
			<< "E(X(a))=1/n,因为2∑E(Xq)(T(q))=2/n∑(E(T(q))+Θ(n)，个人认为应该用<，以为除了第一次递归调用为1/n外 \n"
			<< "E(X(i))=1/(r-q+1),但不影响最后的运行结果 \n"
			<< "d.<=lg（n/2)∑k+lgn∑k ，然后用等差数列的求和公式\n"//借鉴
			<< "e.直接把等式写出来就可以除掉一个n"
			<< endl;
	}
};

class solution7_4 {
public:
	void operator()() {
		cout << "a.每一次循环，第三行将数组分成两部分A[p...q-1]和A[q+1...r],第四行递归调用重新排序A[p...q-1], \n"
			<< "右边A[q+1...r]则作为下一次A[p...r]输入，故可以对数组A排序 \n"
			<< "b.已排序数组 \n"
			<< "c.while p<r  \n"
			<<"     q=partition(A,p,r)  \n"
			<<"     if(q<(q+r)/2)  \n"
			<<"           tail_recursive_quicksort(A,p,q-1)  \n"
			<<"           p=q+1  \n"
			<<"     else  \n"
			<<"           tail_recursive_quicksort(A,q+1,r)  \n"
			<<"           r=q-1               \n"
			<< endl;
	}
};

class solution7_5 {
public:
	void operator()() {//我看了两个答案都是选了不同元素来计算的，而我是可以选取相同元素，所以和我的答案不同
		cout << "a.Pi=1/n * i/n *(n-i)/n *3!=6*i*(n-i+1)/n^3 ,看到p1=pn=0可以得出题目的意思的确是选取的三个不同元素 \n"
			<< "不重复答案 Pi=6(i-1)(n-i)/(n(n-1)(n-2))  \n"
			<< "b.将i=(n+1)/2带入上式得 Pi=3/(2n),增加3/(2n)/1/n=1/2*1/n,lim n→∞ 1/2*1/n  \n"
			<< "不重复答案相同，有一个是直接算的倍数为3/2 \n"
			<< "c.6/n^3*∫(n/3,2n/3,这是积分下上界，对i积分)i*(n-i+1)=13/27 \n "
			<< "还有一种算法时不用积分，从n/3和2n/3中选取一个的概率为1/3,从1和2n/3中选取一个的概率为2/3, \n"
			<< "从n/3和n中选取一个的概率为2/3,P(X)=3!*1/3*2/3*/2/3=24/27,增加24/27-1/3=13/27 \n"
			<< "不重复答案相同"
			<< "d.三数取中法并不改变比较次数，只是提高好划分的概率 "
			<< endl;
	}
};
#endif //_SOLUTION_7_H_
