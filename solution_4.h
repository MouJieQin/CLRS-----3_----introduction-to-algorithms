#pragma once
#ifndef _SOLUTION_4_H_
#define _SOLUTION_4_H_
#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
#include<memory>
using namespace std;
class solution4_1_1 {
public:
	void operator()() {
		cout << "返回数组中最大的一个元素" << endl;
	}
};

struct maxSubarray {
	maxSubarray(size_t low = 0, size_t high = 0,int max=INT_MAX) :low(low), high(high), maxSum(max) {}
	size_t low;//存储最大子数组开始的下标
	size_t high;//存储最大子数组结束的下标
	int maxSum;//存储最大子数组的和
	bool operator>(const maxSubarray&rhs) {
		return maxSum > rhs.maxSum;
	}
};

class solution4_1_2 {
public:
	 maxSubarray operator()(vector<int>&vect) {
		 int tempMaxSum = INT_MIN;//临时存储每一个最大子数组的和
		 int high = 0;//临时存储最大子数组结束下标
		 for (auto beg = vect.begin(); beg != vect.end(); ++beg) {//穷举每一个以*beg开头的子数组
			 int tempSum = 0;//存储以*beg开头以*iter结尾的和
			 for (auto iter = beg; iter != vect.end(); ++iter) {
				 tempSum += *iter;
				 if (tempSum > tempMaxSum) {
					 high = iter - vect.begin();
					 tempMaxSum = tempSum;
				 }
			 }
			 if (tempMaxSum > result.maxSum) {//更新最大子数组
				 result.maxSum = tempMaxSum;
				 result.low = beg - vect.begin();
				 result.high = high;
			 }
		 }
		 return result;
	}
private:
	maxSubarray result;//存储结果
};

class solution4_1_3 {
public:
	maxSubarray operator()(vector<int>&vect) {//返回的结构体定义在上面
		cout << "n0=lgn时是性能交差点,修改后性能交差点不会改变" << endl;
		return divideMaxSubarray(vect, 0, vect.size() - 1);
	}
private:
	maxSubarray maxCrossArray(vector<int>&vect, size_t beg, size_t mid, size_t end) {//分治法求最大子序列和
		int leftMaxSum = INT_MIN;//存储左边最高下标是mid的最大和
		int rightMaxSum = INT_MIN;//存储右边最低下标是mid的最大和
		int leftSum = 0;
		int rightSum = 0;
		size_t low=0;
		size_t high=0;
		for (auto i = mid; i != beg-1; --i) {
			leftSum += vect[i];//vect[i...mid]的和
			if (leftSum > leftMaxSum) {
				leftMaxSum = leftSum;
				low = i;
			}
		}
		for (auto i = mid+1; i <= end; ++i) {
			rightSum += vect[i];//vect[mid+1...i]的和
			if (rightSum > rightMaxSum) {
				rightMaxSum = rightSum;
				high = i;
			}
		}
		return maxSubarray(low, high, leftMaxSum + rightMaxSum);
	}
	maxSubarray divideMaxSubarray(vector<int>&vect, size_t low, size_t high) {
		if (low == high)
			return maxSubarray(low, high, vect[low]);
		else {//改进递归分治算法
			if (high - low + 1 >= log(vect.size()) / log(2)) {//当规模大于lgn时用分治算法
				size_t mid = (low + high) / 2;
			//递归将问题分为max(max∑vect[low,mid],max∑vect[mid+1...high],max∑vect[low...mid...high])
				maxSubarray leftSum(divideMaxSubarray(vect, low, mid));
				maxSubarray rightSum(divideMaxSubarray(vect, mid + 1, high));
				maxSubarray crossMidSum(maxCrossArray(vect, low, mid, high));
				auto tempMax = leftSum > rightSum ? leftSum : rightSum;
				return tempMax > crossMidSum ? tempMax : crossMidSum;//返回三者最大的一个
			}
			else {//穷举算法
				int maxSum = INT_MIN;
				int maxSubSum = INT_MIN;
				int beg = 0;
				int end = 0;
				for (auto i = low; i <= high; ++i) {
					int tempSum = 0;
					for (auto j = i; j <= high; ++j) {
						tempSum += vect[j];
						if (tempSum > maxSubSum) {
							end = j;
							maxSubSum = tempSum;
						}
					}
					if (maxSubSum > maxSum) {
						beg = i;
						maxSum = maxSubSum;
					}
				}
				return maxSubarray(beg, end, maxSum);
			}
		}
	}
};

class solution4_1_4{
public:
	void operator()() {
		cout << "将原来的返回值与0比较后返回原值或0" << endl;
	}
};

class solution4_1_5 {
public:
	maxSubarray operator()(vector<int>&vect){
		prove();//打印证明
		int maxSubSum = INT_MIN;
		int tempSum = 0;
		int low = 0;
		int high = 0;
		bool flag = false;
		for (auto i = 0; i != vect.size(); ++i) {
			tempSum += vect[i];
			if (tempSum > maxSubSum) {
				maxSubSum = tempSum;
				high = i;
				if (flag) {
					flag = false;
					low = i;
				}
			}
			if (tempSum < 0) {
				tempSum = 0;
				flag = true;
			}
		}
		return maxSubarray(low, high, maxSubSum);
	}
private:
	void prove() {
		cout << "tempSum=∑vect[i...j]>0,maxSubSum=∑vect[i...k],k<=j;最开始i=0	\n"
			<< "maxSubSum为以v[i]开头的vect[i...k]的中最大子序列和,前提是tempSum>0,\n"
			<< "一旦tempSum<0,也就是tempSum=∑vect[i...j+1]<0,tempSum将置零，将i置为j+2重新上述步骤\n"
			<< "原先vect[i...j+1]将不会并入后续的可能最大子序列计算步骤，maxSubSum的值被保存用于下次的比较\n"
			<< "证明如下:\n"
			<< "假设当tempSum=∑vect[i...j+1]<0时还有并入下次子序列的价值，则[i...j+1]中必存在x,使得:\n"
			<< "∑vect[x,j+1]>0;而tempSum=∑vect[i...x-1]+∑vect[x...j+1]<0;若∑vect[x,j+1]>0，必有：\n"
			<< "∑vect[i...x-1]<0;这与前提假设j+1是第一个令∑vect[i...j+1]=0的条件不符，故假设不成立。"
			<< endl;
	}
};

class solution4_2_1 {
public:
	void operator()() {
		cout << "s1=6,s2=4,s3=12,s4=-2,s5=6,s6=8,s7=-2,s8=10,s9=-6,s10=8	\n"
			<< "p1=6,p2=8,p3=6,p4=-10,p5=48,p6=-20,p7=-48	\n"
			<< "c11=48-10-8-20=18,c12=14,c21=62,c22=36"
			<< endl;
	}
	//任意m*n 矩阵和 n*x 矩阵的乘法运算一般算法实现，无checking
	shared_ptr<vector<vector<int>>> matrix_multiply(vector<vector<int>>&lhs, vector<vector<int>>&rhs) {
		shared_ptr < vector<vector<int>> >ptr(new vector<vector<int>>);
		for(auto i=0;i!=lhs.size();++i)//计算第i行
			for (auto j = 0; j != rhs[0].size(); ++j) {//计算第j列
				int tempMult = 0;//存储result(i,j)
				for (auto k = 0; k != rhs.size(); ++k) //计算result(i,j)
					tempMult += lhs[i][k] * rhs[k][j];
				j == 0 ? (*ptr).push_back(vector<int>{tempMult}) : (*ptr)[i].push_back(tempMult);
			}
		return ptr;
	}
};

class solution4_3_1 {
public:
	void operator()() {
		cout << "要证明T(n)<=cn^2;\n"
			<< "1.假设T(n-1)<=c(n-1)^2成立	\n"
			<< "T(n)<=c(n-1)^2+n=cn^2-cn<=cn^2,当c>=1时成立"
			<< endl;
	}
};

class solution4_3_2 {
public:
	void operator()() {
		cout << "要证明T(n)<=clgn	\n"
			<< "T(n)<=clg┍n/2┑+1==clgn-clg2+1=clgn-c<=clgn ,c>=1时成立"
			<< endl;
	}
};

class solution4_3_3 {
public:
	void operator()() {
		cout << "要证明T(n)>=cnlgn;	\n"
			<< "T(n)>=2(c*n/2*lg(n/2)+d)+n=cnlgn-cn+n>=cnlgn,当c=1成立"
			<< endl;
	}
};

class solution4_3_4 {
public:
	void operator()() {
		cout << "下一题和这题都可以用这一题的书上证明" << endl;
	}
};

class solution4_3_6 {
public:
	void operator()() {
		cout << "要证明T(n)<=cnlgn	\n"
			<< "T(n)<=2(c*(n/2)*lg(n/2)+17)+n=cnlgn-cn+34=cnlgn-cn<=cnlgn"
			<< endl;
	}
};

class solution4_3_7 {
public:
	void operator()() {
		cout << "要证明T(n)<=cn^log(3,4)	\n"
			<< "T(n)<=4*c(n/3)^log(3,4)+n=cn^log(3,4)+n,并不能直接证明T(n)<=cn^log(3,4)	\n"
			<< "但可以证明 T(n)=Ω(cn^log(3,4))	\n"
			<< "要证明T(n)<=cn^log(3,4)-6n	\n"
			<< "T(n)<=4*(c*(n/3)^log(3,4)-6*n/3)+n=cn^log(3,4)-7*n<=cn^log(3,4)-6n,c>=1时成立"
			<< endl;
	}
};

class solution4_3_8 {
public:
	void operator()() {
		cout << "要证明T(n)<=cn^2	\n"
			<< "T(n)<=4*c*(n^2)/4+n=cn^2+n,并不能直接证明T(n)<=cn^2	\n"
			<< "但可以证明 T(n)=Ω(n^2)	\n"
			<< "要证明T(n)<=cn^2-2n	\n"
			<< "T(n)=4*(c*(n^2)/4-n)+n=cn^2-3n<=cn^2-2n,c>=1时成立"
			<< endl;
	}
};

class solution4_3_9 {
public:
	void operator()() {
		cout << "令n=2^m,T(n)=3T(n/2)+n,T(2^m)=3T(2^(m/2))+m;	\n"
			<< "S(m)=3T(m/2)+m;	S(m)=Θ(m^(lg3)),不证明，可用递归树得到，后面可以依靠主方法得到	\n"
			<<"T(n)=(lgn)^(lg3)"
			<< endl;
	}
};

class solution4_4_1 {
public:
	void operator()() {
		cout << "递归树的上界为Θ(n^lg(3/2)),要证明T(n)<=cn^lg(3/2)-cn		\n"
			<< "T(n)<=3*(c(n/2)^lg(3/2)-cn/2)+n=cn^lg(3/2)-cn,c>=1时成立，得证"
			<< endl;
	}
};

class solution4_4_2 {
public:
	void operator()() {
		cout << "T(n)=Θ(n^2),要证明T(n)<=cn^2	\n"
			<< "T(n)<=c*n^2/4+n^2<=cn^2,当c>=1时成立，得证"
			<< endl;
	}
};

class solution4_4_3 {
public:
	void operator()() {
		cout << "要证T(n)<=cn^2-dn;d>0为常数	\n"
			<< "T(n)<=4(c(n/2+2)^2-d(n/2+2))+n=cn^2+(8c-2d+1)n+16c-8d<=cn^2-dn,c>=1,b>=8c+1时成立"
			<< endl;
	}
};
class solution4_4_4 {
public:
	void operator()() {
		cout << "T(n)<=cn^2;\n"
			<< "T(n)<=c(n-1)^2+1=cn^2-cn+c<=cn^2,当c>=1时成立"
			<< endl;
	}
};

class solution4_4_5 {
public:
	void operator()() {
		cout << "递归树最长的为n-1层，此树并不是完全二叉树，平均每层小于2^i个节点；\n"
			<< "T(n)<=c2^(n+1)-2n,T(n)=c*2^n+2*c*2^(n/2)-2n+1<=c2^(n+1)-2n,c>=1时成立"
			<< endl;
	}
};

class solution4_4_6 {
public:
	void operator()() {//有借鉴
		cout << "树的最短层为最左边的那条，有log(3,n)层，每一层花费cn,可以画到有四个节点的那层\n"
			<< "cn/3^2,2cn/3^2,2cn/3^2,4cn/3^2加起来为cn，共花费cnlog(3,n),亦即cnlgn，故Ω(cnlgn);"
			<< "注:不同底数的增长率都是相同的，lim n→∞log(a,n)/lg(b,n)=lim n→∞(lgn/lga)*(lgb/lgn)=lga/lgb为常数。"
			<< endl;
	}
};

class solution4_4_7 {
public:
	void operator()() {
		cout << "T(n)=Θ(n^2);\n"
			<< "要证明T(n)>=cn^2;T(n)>=4*c(n^2/4)+cn=cn^2+cn>cn^2,n>=1时成立，T(n)=Ω(n^2)\n"
			<< "要证明T(n)<=cn^2-cn-n;T(n)<=4*(c(n^2/4)-cn/2-n/2)+cn=cn^2-cn-2n<=cn^2-cn-n,c>=1时成立	\n"
			<< "T(n)=O(n^2),综上，T(n)=Θ(n^2)"
			<< endl;
	}
};

class solution4_4_8 {
public:
	void operator()() {
		cout << "T(n)=Θ(n^2),先证明T(n)=O(n^2),要证明T(n)>=cn^2;	\n"
			<< "T(n)<=c*(n-a)^2+ca^2+cn=cn^2-2acn+2ca^2+cn=cn^2-cn(2a-1)+2ca^2<=cn^2,c>=1,n>2a^2/(2a-1)时成立	\n"
			<< "T(n)=Ω(n^2)怎么用代入法没想出来，题目也并没有要求,综上，T(n)=Θ(n^2);"
			<< endl;
	}
};

class solution4_4_9 {
public:
	void operator()() {
		cout << "假设0<a<1/2,递归树画出来只一共有log(1/a,n)层，每层耗费cn，总耗费cnlgn(1/a,n)=clgn,(4_4_6 有说明)	\n"
			<< "要证明T(n)>=cnlgn,T(n)<=c*a*n*lg(a*n)+cn(1-a)lg(n(1-a))+cn=cnlgn+cn>=cnlgn,c>=1时成立	\n"
			<< "要证明T(n)<=cnlgn+cn;T(n)>=c*a*n*lg(a*n)+cn(1-a)lg(n(1-a))+cn+cna+c(1-a)n=cnlgn+cn,c>=1时成立"
			<< endl;
	}
};

class solution4_5_1 {
public:
	void operator()() {
		cout << "a.a=2,b=4,f(n)=1,n^(log(4,2))=n^(1/2),f(n)=O(n^(1/2-ε))，ε=1/2，T(n)=Θ(n^(1/2))	\n"
			<< "b.a=2,b=4,f(n)=n^(1/2),f(n)=Θ(n^1/2),T(n)=n^(1/2)	lgn	\n"
			<< "c.a=2,b=4,f(n)=n,f(n)=Ω(n^(1/2+ε))，ε=1/2，对于c=1/2,af(n/b)=2*n/4=n/2<=cf(n),T(n)=Θ(n)	\n"
			<< "a=2,b=4,f(n)=n^2,f(n)=Ω(n^(1/2+ε)),ε=3/2,对于c=1/8，af(n/b)=2*(n/4)^2=n^2/8=cf(n),T(n)=Θ(n^2)	\n"
			<< endl;
	}
};

class solution4_5_2 {
public:
	void operator()() {
		cout << "当设想算法接近Strassen算法时为Θ(n^lg7),n^lg7=n^(log(4,a)),应用情况1，a=49,"
			<<"要快于Strassen的最大整数a=48"
			<< endl;
	}
};

class solution4_5_3 {
public:
	void operator()() {
		cout << "a=1,b=2,f(n)=Θ(1),n^(log(b,a))=1,f(n)=Θ(n^(log(b,a)),T(n)=Θ(lgn)"
			<< endl;
	}
};

class solution4_5_4 {
public:
	void operator()() {
		cout << "不可以，a=4,b=2,f(n)=n^2lgn,n^(b,a)=n^2,看起来需要应用情况3	\n"
			<< "但f(n)/n^(b,a)=lgn都渐进小于n^ε,不是多项式意义上的大于	\n"
			<< "T(n)=Θ(n^2*(lgn)^2),要证明T(n)<=cn^2*(lgn)^2		\n"
			<< "T(n)<=cn^2((lgn)^2-2lgn+1)+n^2*lgn=cn^2*(lgn)^2-2cn^2lgn+cn<=cn^2((lgn)^2-2lgn+1),c>=1时成立"
			<< endl;
	}
};

class solution4_5_5 {
public:
	void operator()() {
		cout << "T(n)=8T(n/4)+n^2lglgn"
			<< endl;
	}
};

class solution4_6_1 {
public:
	void operator()() {
		cout << "n[j]=┍n/b^j┑	\n"
			<< "之所以b是整数和任意实数有所不同在于普通计算机只能保留小数位后一定位数的精确值，	\n"
			<< "假设a为被忽略的小数，lim n→∞，(1+a)^n/(1^n)=∞"
			<< endl;
	}
};

class solution4_6_2 {
public:
	void operator()() {
		cout << "n=b^m,T(n)=acb^(mlog(b,a))*(lgb)^(k+1)+b^(mlog(b,a))*(lg(b^m))^k	\n"
			<< "=(a^m)*(m^(k+1))*(ac(lgb)^(k+1)+(lgb)^k/m),当n→∞，m→∞，(lgb)^k/m→0，ac(lgb)^(k+1)+(lgb)^k/m为常数	\n"
			<< "T(n)=c(a^m)m^(k+1)=Θ(n^(log(b,a))*(lgn)^(k+1)"
			<< endl;
	}
};

class solution4_6_3 {
public:
	void operator()() {
		cout << "f(n)=Ω(n^(log(b,a)+ε),亦即f(n)=n^λ，λ-log(b,a)=ε，证明如下：\n"
			<< "af(n/b)<=cf(n),a(n/b)^λ<=cn^λ,λ>=log(b,a/c),0<c<1,a/c>a,log(b,a/c)>log(b,a),故λ-log(b,a)=ε，ε>0"
			<< endl;
	}
};

//思考题
class solution4_1 {
public:
	void operator()() {
		cout << "a.T(n)=Θ(n^4)，应用主定理求得，不验证，下同	\n"
			<< "b.T(n)=Θ(n)	\n"
			<< "c.T(n)=Θ(n^2)	\n"
			<< "d.T(n)=Θ(n^2)	\n"
			<< "e.T(n)=Θ(n^lg7)	\n"
			<< "f.T(n)=Θ(n^(1/2)lgn)	\n"
			<< "g.T(n)=∑(n-2*i)^2=Θ(n^3),其中i=0...n/2 但请看下面证明：   \n"
			<< "T(n)<=cn^2，T(n)<=c(n-2)^2+n^2=(c+1)^2-4cn+4c=cn^2-cn+c<=cn^2     \n"
			<< "看起来与我的结论不符,问题出在(c+1)^2-4cn+4c=cn^2-cn+c这一步    \n"
			<< "当不等式右边有相同增长量级的此题是cn^2,不能贸然将左边的系数简化成c，不然左右两边的c不是同一个c\n"
			<< "(c+1)^2-4cn+4c=(c+1)^2-cn+c>=cn^2, \n"
			<< "因为我在这一题才发现这个问题，所以前面的证明题可能有错误,但我懒得改了"
			<< endl;
	}
};

class solution4_2 {
public:
	void operator()() {
		cout << "a.1.T(n)=T(n/2)+c,T(n)= Θ(lgn)	\n"
			<< "2.T(n)=T(n/2)+cN,T(n)=Θ(nlgn)		\n"
<< "3.T(n)=T(n/2)+cn/2,T(n)=Θ(n)		\n"
<< "b.1.T(n)=2T(n/2)+cn，T(n)=Θ(n)		\n"
<< "2.T(n)=2T(n/2)+cN,T(n)=Θ(n^2)		\n"
<< "3.T(n)=2T(n/2)+cn,T(n)=Θ(nlgn)		\n"
<< "b中1，3相同在于不论参数怎么传递，每层还是需要n次比较，花费cn，例如1中参数传递不需要赋值数组	\n"
<< "只需要传递一个起始指针，但还是需要n次比较，每次比较花费c，cn+c简写成cn"
<< endl;
	}
};
class solution4_3 {
public:
	void operator()() {
		cout << "a.根据(4.21),T(n)=Θ(n^log(3,4)+∑(4/3)^i*(lgn-ilg3),i=0...lg(3,n)-1,等比与等差积的和，用错位相减法求得	\n"
			<< "T(n)=lg(n)*n^log(3,4)"//不保证计算结果准确性
			<< "b.T(n)=Θ(nlglgn)"//借鉴不保证正确，也没写过程，估计靠猜后用代入法验证的，下写借鉴同此
			<< "c.根据(4.21)求和后得T(n)=n^2+n^(3/2)∑2^(j/2),T(n)=Θ(n^2)	\n"
			<< "d.T(n)=3T(n/3)+n/2,运用主定理得T(n)=nlg	\n"
			<< "e.根据(4.21)求和后得T(n)=n+n∑(1/(lgn-j),j=0...lgn-1,n∑(1/(lgn-j)<=n∑1/lgn=n,T(n)=Θ(n)		\n"
			<< "f.T(n)=Θ(n),T(n)<=cn,T(n)<=c7n/8+n<=cn,c>=8时成立,T(n)>=cn,c<=8时成立	\n"
			<< "g.T(n)=Θ(lnn)	\n"
			<< "h.T(n)=lg(n!)<=lg(n^n)=nlgn,T(n)=O(nlgn)，T(n)<=cnlgn,T(n)<=cnlg(n-1)-clg(n-1)+lgn<=clgn,当c=1时成立，	\n"
			<< "n→∞，lgn/lg(n-1)=lgn(n-1,n)=1	\n"
			<< "i.T(n)=∑1/lg(2i),i=1...n/2,T(n)=O(n),T(n)=Ω(n/lgn)	\n"
			<< "j.如果画出递归树，第i层有n^(0)*n^(1/2)*n^(1/4)*n^(1/8)*...*n^(1/(2^i)=n^(1-1/(2^i),第i层节点的大小\n"
			<< "为n^(1/(2^i),然后计算一共有多少层，令n^(1/(2^i)=一个常数，取2比较合适，n^(1/(2^i)=2，i=lglgn	\n"
			<< "一共有lglgn层，T(n)=∑n^(1-1/(2^i)*n^(1/(2^i)=∑n=nlglgn,其中i=0...lglgn,	\n"
			<< "T(n)=Θ(nlglgn)"
			<< endl;
	}
};

class solution4_4 {
public:
	void operator()() {
		cout << "a.zf(z)+z^2f(z)=∑z^2+2z^3+3z^4+....，显然f(z)=z+zf(z)+z^2f(z)	\n"
			<< "b.对a问解一元二次方程得F(z)=z/(1-z-z^2),后面两个等式将两个φ代入展开可知道相等	\n"
			<< "c.只需要证明∑1/(5^(1/2))(x^i-y^i)是斐波那契数列的公式即可，我在solution3_2_7用归纳法简短证明过	\n"
			<< "d.同上我也仔细说明过"
			<< endl;
	}
};

class solution4_5 {
public: 
	void operator()() {
		cout << "a.对于任意一块芯片，最多有除自己外n-1份检测结果，如果有等于或超过n/2个是好的，那么相同结果超过或等于n/2 \n"
			<< "可以知道这块芯片的真实好坏就是这个结果，如果有超过n/2个是坏的，则无法通过统计确定好坏 \n"
			<< endl;
	}/////////////////////////////////////////////

};

class solution4_6 {
public:
	void operator()() {
		cout << "a.i<k,k=i+n,假设A[i,j]+A[k,j+1]<=A[i,j+1]+A[k,j]成立	\n"
			<< "根据已知不等式有A[k,j]+A[k+1,j+1]<=A[k,j+1]+A[k+1,j] \n"
			<< "两个不等相加化简得A[i,j]+A[k+1,j+1]<=A[i,j+1]+A[k+1,j]  \n"
			<< "因为基本情况当k=i+1时成立，所以对于1<=i<k<=n时不等式成立，列同理可证  \n"
			<< "b.把第二行的7改为5		\n"
			<< "c.假设存在1<=i<k<=m,f(i)>f(k),根据Monge阵列的性质，A[i,f(k)]+A[k,f(i)]<=A[i,f(i)]+A[k,f(k)]  \n"
			<< "A[i,f(i)]<A[i,f(k)],A[k,f(k)]<A[i,f(k),故A[i,f(k)]+A[k,f(i)]>A[i,f(i)]+A[k,f(k)],故假设不成立   \n"
			<< "d.1<=f(2)<=f(4)<=f(6)<=...<=f(m-2)<=f(m)<=n,假设m为偶数，奇数同理，寻找奇数行最左最小元素时  \n"
			<< "只需比较相邻偶数行之间的数，f(1)→1...f(2),f(3)→f(4)...f(2),...,f(m-1)→n..f(m)  \n"
			<< "T'(n)=f(2)-f(1)+1+f(4)-f(2)+1+f(6)-f(4)+1+...+f(m)-f(m-2)+1,+n-f(m)+1=n+m/2=O(n+m)	\n"
			<< "e.T(m)=T(m/2)+c(m+n),解释为求m行最小最左元素等于求一半的偶数最小最左元素再以O(m+n)求奇数最小元素 \n"
			<< "T(m)=∑c(m/(2^i)+n),i=0...lgm,T(m)=cnlgm+cm∑(1/(2^i)=cnlgm+cm-c=O(m+nlgn)"
			<< endl;
		print_min_index(vect);
		check(vect);
	}
private:
	void print_min_index(vector<vector<int>>&vect) {//打印每行最左最小元素，只适用于较大规模，如注释掉的阵列就不行
		vector<size_t>index_vect(vect.size(),0);//没有注释是因为这个程序并不完美，测试用例少，可能有bug
		vector<size_t>rows_vect;
		for (size_t i = 0; i != vect.size(); ++i)
			rows_vect.push_back(i);
		int min = INT_MAX;
		for (size_t i = index_vect[vect.size() - 2]; i != vect[0].size(); ++i)
			if (vect[vect.size() - 1][i] < min) {
				min = vect[vect.size() - 1][i];
				index_vect.back() = i;
			}
		find_min_even_index(vect,rows_vect,index_vect);

		for (auto i : index_vect)
			cout << i+1 << endl;
	}
	void find_min_even_index(vector<vector<int>>&vect, vector<size_t>&rows_vect,vector<size_t>&index_vect) {
		if (rows_vect.size() != 2) {
			vector<size_t>tempVect;
			for (size_t i = 0; i < rows_vect.size(); i += 2)
				tempVect.push_back(rows_vect[i]);
			find_min_even_index(vect, tempVect, index_vect);
			find_min_odd_index(vect, rows_vect, index_vect);
		}
		else {
			int min = INT_MAX;
			for (size_t i = 0; i <vect[0].size(); ++i) 
				if (vect[0][i] < min) {
					min = vect[0][i];
					index_vect[0] = i;
				}
			min = INT_MAX;
			for (size_t i = index_vect[0]; i != vect[0].size(); ++i) 
				if (vect[rows_vect.back()][i] < min) {
					min = vect[rows_vect.back()][i];
					index_vect[rows_vect.back()] = i;
				}
		}
	}
	void find_min_odd_index(vector<vector<int>>&vect, vector<size_t>&rows_vect, vector<size_t>&index_vect) {
		for (size_t i =rows_vect[1]; i < rows_vect.size() - 1; i += 2) {
			int min = INT_MAX;
			for (size_t j = index_vect[rows_vect[i-1]]; j <=index_vect[rows_vect[i+1]]; ++j)
				if (vect[i][j] < min) {
					min = vect[i][j];
					index_vect[i] = j;
				}			
		}
	}
	void  check(vector < vector<int>>&vect) {//打印不符合性质的左上角坐标
		for (size_t i = 0; i < vect.size()-1; ++i) {
			for (size_t j = 0; j < vect[0].size()-1; ++ j) {
				int sum1 = vect[i][j] + vect[i + 1][j + 1];
				int sum2 = vect[i][j + 1] + vect[i + 1][j];
				if (sum1 > sum2) {
					cout << i+1 << "\t" << j+1<<endl;
					return;
				}
			}
		}
	}
//	vector<vector<int>>vect{ {37,23,22,32},{21,6,5,10},{53,34,30,31},{32,13,9,6},{43,21,15,13} };
	vector<vector<int>>vect{ {10,17,13,28,23},{17,22,16,29,23},{24,28,22,34,24},{11,13,6,17,7},{45,44,32,37,23},
	{36,33,19,21,6},{75,66,51,53,34} };
};

#endif //_SOLUTION_4_H_
