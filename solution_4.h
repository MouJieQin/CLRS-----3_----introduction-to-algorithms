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
		cout << "��������������һ��Ԫ��" << endl;
	}
};

struct maxSubarray {
	maxSubarray(size_t low = 0, size_t high = 0,int max=INT_MAX) :low(low), high(high), maxSum(max) {}
	size_t low;//�洢��������鿪ʼ���±�
	size_t high;//�洢���������������±�
	int maxSum;//�洢���������ĺ�
	bool operator>(const maxSubarray&rhs) {
		return maxSum > rhs.maxSum;
	}
};

class solution4_1_2 {
public:
	 maxSubarray operator()(vector<int>&vect) {
		 int tempMaxSum = INT_MIN;//��ʱ�洢ÿһ�����������ĺ�
		 int high = 0;//��ʱ�洢�������������±�
		 for (auto beg = vect.begin(); beg != vect.end(); ++beg) {//���ÿһ����*beg��ͷ��������
			 int tempSum = 0;//�洢��*beg��ͷ��*iter��β�ĺ�
			 for (auto iter = beg; iter != vect.end(); ++iter) {
				 tempSum += *iter;
				 if (tempSum > tempMaxSum) {
					 high = iter - vect.begin();
					 tempMaxSum = tempSum;
				 }
			 }
			 if (tempMaxSum > result.maxSum) {//�������������
				 result.maxSum = tempMaxSum;
				 result.low = beg - vect.begin();
				 result.high = high;
			 }
		 }
		 return result;
	}
private:
	maxSubarray result;//�洢���
};

class solution4_1_3 {
public:
	maxSubarray operator()(vector<int>&vect) {//���صĽṹ�嶨��������
		cout << "n0=lgnʱ�����ܽ����,�޸ĺ����ܽ���㲻��ı�" << endl;
		return divideMaxSubarray(vect, 0, vect.size() - 1);
	}
private:
	maxSubarray maxCrossArray(vector<int>&vect, size_t beg, size_t mid, size_t end) {//���η�����������к�
		int leftMaxSum = INT_MIN;//�洢�������±���mid������
		int rightMaxSum = INT_MIN;//�洢�ұ�����±���mid������
		int leftSum = 0;
		int rightSum = 0;
		size_t low=0;
		size_t high=0;
		for (auto i = mid; i != beg-1; --i) {
			leftSum += vect[i];//vect[i...mid]�ĺ�
			if (leftSum > leftMaxSum) {
				leftMaxSum = leftSum;
				low = i;
			}
		}
		for (auto i = mid+1; i <= end; ++i) {
			rightSum += vect[i];//vect[mid+1...i]�ĺ�
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
		else {//�Ľ��ݹ�����㷨
			if (high - low + 1 >= log(vect.size()) / log(2)) {//����ģ����lgnʱ�÷����㷨
				size_t mid = (low + high) / 2;
			//�ݹ齫�����Ϊmax(max��vect[low,mid],max��vect[mid+1...high],max��vect[low...mid...high])
				maxSubarray leftSum(divideMaxSubarray(vect, low, mid));
				maxSubarray rightSum(divideMaxSubarray(vect, mid + 1, high));
				maxSubarray crossMidSum(maxCrossArray(vect, low, mid, high));
				auto tempMax = leftSum > rightSum ? leftSum : rightSum;
				return tempMax > crossMidSum ? tempMax : crossMidSum;//������������һ��
			}
			else {//����㷨
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
		cout << "��ԭ���ķ���ֵ��0�ȽϺ󷵻�ԭֵ��0" << endl;
	}
};

class solution4_1_5 {
public:
	maxSubarray operator()(vector<int>&vect){
		prove();//��ӡ֤��
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
		cout << "tempSum=��vect[i...j]>0,maxSubSum=��vect[i...k],k<=j;�ʼi=0	\n"
			<< "maxSubSumΪ��v[i]��ͷ��vect[i...k]������������к�,ǰ����tempSum>0,\n"
			<< "һ��tempSum<0,Ҳ����tempSum=��vect[i...j+1]<0,tempSum�����㣬��i��Ϊj+2������������\n"
			<< "ԭ��vect[i...j+1]�����Ტ������Ŀ�����������м��㲽�裬maxSubSum��ֵ�����������´εıȽ�\n"
			<< "֤������:\n"
			<< "���赱tempSum=��vect[i...j+1]<0ʱ���в����´������еļ�ֵ����[i...j+1]�бش���x,ʹ��:\n"
			<< "��vect[x,j+1]>0;��tempSum=��vect[i...x-1]+��vect[x...j+1]<0;����vect[x,j+1]>0�����У�\n"
			<< "��vect[i...x-1]<0;����ǰ�����j+1�ǵ�һ�����vect[i...j+1]=0�������������ʼ��費������"
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
	//����m*n ����� n*x ����ĳ˷�����һ���㷨ʵ�֣���checking
	shared_ptr<vector<vector<int>>> matrix_multiply(vector<vector<int>>&lhs, vector<vector<int>>&rhs) {
		shared_ptr < vector<vector<int>> >ptr(new vector<vector<int>>);
		for(auto i=0;i!=lhs.size();++i)//�����i��
			for (auto j = 0; j != rhs[0].size(); ++j) {//�����j��
				int tempMult = 0;//�洢result(i,j)
				for (auto k = 0; k != rhs.size(); ++k) //����result(i,j)
					tempMult += lhs[i][k] * rhs[k][j];
				j == 0 ? (*ptr).push_back(vector<int>{tempMult}) : (*ptr)[i].push_back(tempMult);
			}
		return ptr;
	}
};

class solution4_3_1 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=cn^2;\n"
			<< "1.����T(n-1)<=c(n-1)^2����	\n"
			<< "T(n)<=c(n-1)^2+n=cn^2-cn<=cn^2,��c>=1ʱ����"
			<< endl;
	}
};

class solution4_3_2 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=clgn	\n"
			<< "T(n)<=clg��n/2��+1==clgn-clg2+1=clgn-c<=clgn ,c>=1ʱ����"
			<< endl;
	}
};

class solution4_3_3 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)>=cnlgn;	\n"
			<< "T(n)>=2(c*n/2*lg(n/2)+d)+n=cnlgn-cn+n>=cnlgn,��c=1����"
			<< endl;
	}
};

class solution4_3_4 {
public:
	void operator()() {
		cout << "��һ������ⶼ��������һ�������֤��" << endl;
	}
};

class solution4_3_6 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=cnlgn	\n"
			<< "T(n)<=2(c*(n/2)*lg(n/2)+17)+n=cnlgn-cn+34=cnlgn-cn<=cnlgn"
			<< endl;
	}
};

class solution4_3_7 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=cn^log(3,4)	\n"
			<< "T(n)<=4*c(n/3)^log(3,4)+n=cn^log(3,4)+n,������ֱ��֤��T(n)<=cn^log(3,4)	\n"
			<< "������֤�� T(n)=��(cn^log(3,4))	\n"
			<< "Ҫ֤��T(n)<=cn^log(3,4)-6n	\n"
			<< "T(n)<=4*(c*(n/3)^log(3,4)-6*n/3)+n=cn^log(3,4)-7*n<=cn^log(3,4)-6n,c>=1ʱ����"
			<< endl;
	}
};

class solution4_3_8 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=cn^2	\n"
			<< "T(n)<=4*c*(n^2)/4+n=cn^2+n,������ֱ��֤��T(n)<=cn^2	\n"
			<< "������֤�� T(n)=��(n^2)	\n"
			<< "Ҫ֤��T(n)<=cn^2-2n	\n"
			<< "T(n)=4*(c*(n^2)/4-n)+n=cn^2-3n<=cn^2-2n,c>=1ʱ����"
			<< endl;
	}
};

class solution4_3_9 {
public:
	void operator()() {
		cout << "��n=2^m,T(n)=3T(n/2)+n,T(2^m)=3T(2^(m/2))+m;	\n"
			<< "S(m)=3T(m/2)+m;	S(m)=��(m^(lg3)),��֤�������õݹ����õ���������������������õ�	\n"
			<<"T(n)=(lgn)^(lg3)"
			<< endl;
	}
};

class solution4_4_1 {
public:
	void operator()() {
		cout << "�ݹ������Ͻ�Ϊ��(n^lg(3/2)),Ҫ֤��T(n)<=cn^lg(3/2)-cn		\n"
			<< "T(n)<=3*(c(n/2)^lg(3/2)-cn/2)+n=cn^lg(3/2)-cn,c>=1ʱ��������֤"
			<< endl;
	}
};

class solution4_4_2 {
public:
	void operator()() {
		cout << "T(n)=��(n^2),Ҫ֤��T(n)<=cn^2	\n"
			<< "T(n)<=c*n^2/4+n^2<=cn^2,��c>=1ʱ��������֤"
			<< endl;
	}
};

class solution4_4_3 {
public:
	void operator()() {
		cout << "Ҫ֤T(n)<=cn^2-dn;d>0Ϊ����	\n"
			<< "T(n)<=4(c(n/2+2)^2-d(n/2+2))+n=cn^2+(8c-2d+1)n+16c-8d<=cn^2-dn,c>=1,b>=8c+1ʱ����"
			<< endl;
	}
};
class solution4_4_4 {
public:
	void operator()() {
		cout << "T(n)<=cn^2;\n"
			<< "T(n)<=c(n-1)^2+1=cn^2-cn+c<=cn^2,��c>=1ʱ����"
			<< endl;
	}
};

class solution4_4_5 {
public:
	void operator()() {
		cout << "�ݹ������Ϊn-1�㣬������������ȫ��������ƽ��ÿ��С��2^i���ڵ㣻\n"
			<< "T(n)<=c2^(n+1)-2n,T(n)=c*2^n+2*c*2^(n/2)-2n+1<=c2^(n+1)-2n,c>=1ʱ����"
			<< endl;
	}
};

class solution4_4_6 {
public:
	void operator()() {//�н��
		cout << "������̲�Ϊ����ߵ���������log(3,n)�㣬ÿһ�㻨��cn,���Ի������ĸ��ڵ���ǲ�\n"
			<< "cn/3^2,2cn/3^2,2cn/3^2,4cn/3^2������Ϊcn��������cnlog(3,n),�༴cnlgn���ʦ�(cnlgn);"
			<< "ע:��ͬ�����������ʶ�����ͬ�ģ�lim n����log(a,n)/lg(b,n)=lim n����(lgn/lga)*(lgb/lgn)=lga/lgbΪ������"
			<< endl;
	}
};

class solution4_4_7 {
public:
	void operator()() {
		cout << "T(n)=��(n^2);\n"
			<< "Ҫ֤��T(n)>=cn^2;T(n)>=4*c(n^2/4)+cn=cn^2+cn>cn^2,n>=1ʱ������T(n)=��(n^2)\n"
			<< "Ҫ֤��T(n)<=cn^2-cn-n;T(n)<=4*(c(n^2/4)-cn/2-n/2)+cn=cn^2-cn-2n<=cn^2-cn-n,c>=1ʱ����	\n"
			<< "T(n)=O(n^2),���ϣ�T(n)=��(n^2)"
			<< endl;
	}
};

class solution4_4_8 {
public:
	void operator()() {
		cout << "T(n)=��(n^2),��֤��T(n)=O(n^2),Ҫ֤��T(n)>=cn^2;	\n"
			<< "T(n)<=c*(n-a)^2+ca^2+cn=cn^2-2acn+2ca^2+cn=cn^2-cn(2a-1)+2ca^2<=cn^2,c>=1,n>2a^2/(2a-1)ʱ����	\n"
			<< "T(n)=��(n^2)��ô�ô��뷨û���������ĿҲ��û��Ҫ��,���ϣ�T(n)=��(n^2);"
			<< endl;
	}
};

class solution4_4_9 {
public:
	void operator()() {
		cout << "����0<a<1/2,�ݹ���������ֻһ����log(1/a,n)�㣬ÿ��ķ�cn���ܺķ�cnlgn(1/a,n)=clgn,(4_4_6 ��˵��)	\n"
			<< "Ҫ֤��T(n)>=cnlgn,T(n)<=c*a*n*lg(a*n)+cn(1-a)lg(n(1-a))+cn=cnlgn+cn>=cnlgn,c>=1ʱ����	\n"
			<< "Ҫ֤��T(n)<=cnlgn+cn;T(n)>=c*a*n*lg(a*n)+cn(1-a)lg(n(1-a))+cn+cna+c(1-a)n=cnlgn+cn,c>=1ʱ����"
			<< endl;
	}
};

class solution4_5_1 {
public:
	void operator()() {
		cout << "a.a=2,b=4,f(n)=1,n^(log(4,2))=n^(1/2),f(n)=O(n^(1/2-��))����=1/2��T(n)=��(n^(1/2))	\n"
			<< "b.a=2,b=4,f(n)=n^(1/2),f(n)=��(n^1/2),T(n)=n^(1/2)	lgn	\n"
			<< "c.a=2,b=4,f(n)=n,f(n)=��(n^(1/2+��))����=1/2������c=1/2,af(n/b)=2*n/4=n/2<=cf(n),T(n)=��(n)	\n"
			<< "a=2,b=4,f(n)=n^2,f(n)=��(n^(1/2+��)),��=3/2,����c=1/8��af(n/b)=2*(n/4)^2=n^2/8=cf(n),T(n)=��(n^2)	\n"
			<< endl;
	}
};

class solution4_5_2 {
public:
	void operator()() {
		cout << "�������㷨�ӽ�Strassen�㷨ʱΪ��(n^lg7),n^lg7=n^(log(4,a)),Ӧ�����1��a=49,"
			<<"Ҫ����Strassen���������a=48"
			<< endl;
	}
};

class solution4_5_3 {
public:
	void operator()() {
		cout << "a=1,b=2,f(n)=��(1),n^(log(b,a))=1,f(n)=��(n^(log(b,a)),T(n)=��(lgn)"
			<< endl;
	}
};

class solution4_5_4 {
public:
	void operator()() {
		cout << "�����ԣ�a=4,b=2,f(n)=n^2lgn,n^(b,a)=n^2,��������ҪӦ�����3	\n"
			<< "��f(n)/n^(b,a)=lgn������С��n^��,���Ƕ���ʽ�����ϵĴ���	\n"
			<< "T(n)=��(n^2*(lgn)^2),Ҫ֤��T(n)<=cn^2*(lgn)^2		\n"
			<< "T(n)<=cn^2((lgn)^2-2lgn+1)+n^2*lgn=cn^2*(lgn)^2-2cn^2lgn+cn<=cn^2((lgn)^2-2lgn+1),c>=1ʱ����"
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
		cout << "n[j]=��n/b^j��	\n"
			<< "֮����b������������ʵ��������ͬ������ͨ�����ֻ�ܱ���С��λ��һ��λ���ľ�ȷֵ��	\n"
			<< "����aΪ�����Ե�С����lim n���ޣ�(1+a)^n/(1^n)=��"
			<< endl;
	}
};

class solution4_6_2 {
public:
	void operator()() {
		cout << "n=b^m,T(n)=acb^(mlog(b,a))*(lgb)^(k+1)+b^(mlog(b,a))*(lg(b^m))^k	\n"
			<< "=(a^m)*(m^(k+1))*(ac(lgb)^(k+1)+(lgb)^k/m),��n���ޣ�m���ޣ�(lgb)^k/m��0��ac(lgb)^(k+1)+(lgb)^k/mΪ����	\n"
			<< "T(n)=c(a^m)m^(k+1)=��(n^(log(b,a))*(lgn)^(k+1)"
			<< endl;
	}
};

class solution4_6_3 {
public:
	void operator()() {
		cout << "f(n)=��(n^(log(b,a)+��),�༴f(n)=n^�ˣ���-log(b,a)=�ţ�֤�����£�\n"
			<< "af(n/b)<=cf(n),a(n/b)^��<=cn^��,��>=log(b,a/c),0<c<1,a/c>a,log(b,a/c)>log(b,a),�ʦ�-log(b,a)=�ţ���>0"
			<< endl;
	}
};

//˼����
class solution4_1 {
public:
	void operator()() {
		cout << "a.T(n)=��(n^4)��Ӧ����������ã�����֤����ͬ	\n"
			<< "b.T(n)=��(n)	\n"
			<< "c.T(n)=��(n^2)	\n"
			<< "d.T(n)=��(n^2)	\n"
			<< "e.T(n)=��(n^lg7)	\n"
			<< "f.T(n)=��(n^(1/2)lgn)	\n"
			<< "g.T(n)=��(n-2*i)^2=��(n^3),����i=0...n/2 ���뿴����֤����   \n"
			<< "T(n)<=cn^2��T(n)<=c(n-2)^2+n^2=(c+1)^2-4cn+4c=cn^2-cn+c<=cn^2     \n"
			<< "���������ҵĽ��۲���,�������(c+1)^2-4cn+4c=cn^2-cn+c��һ��    \n"
			<< "������ʽ�ұ�����ͬ���������Ĵ�����cn^2,����óȻ����ߵ�ϵ���򻯳�c����Ȼ�������ߵ�c����ͬһ��c\n"
			<< "(c+1)^2-4cn+4c=(c+1)^2-cn+c>=cn^2, \n"
			<< "��Ϊ������һ��ŷ���������⣬����ǰ���֤��������д���,�������ø���"
			<< endl;
	}
};

class solution4_2 {
public:
	void operator()() {
		cout << "a.1.T(n)=T(n/2)+c,T(n)= ��(lgn)	\n"
			<< "2.T(n)=T(n/2)+cN,T(n)=��(nlgn)		\n"
<< "3.T(n)=T(n/2)+cn/2,T(n)=��(n)		\n"
<< "b.1.T(n)=2T(n/2)+cn��T(n)=��(n)		\n"
<< "2.T(n)=2T(n/2)+cN,T(n)=��(n^2)		\n"
<< "3.T(n)=2T(n/2)+cn,T(n)=��(nlgn)		\n"
<< "b��1��3��ͬ���ڲ��۲�����ô���ݣ�ÿ�㻹����Ҫn�αȽϣ�����cn������1�в������ݲ���Ҫ��ֵ����	\n"
<< "ֻ��Ҫ����һ����ʼָ�룬��������Ҫn�αȽϣ�ÿ�αȽϻ���c��cn+c��д��cn"
<< endl;
	}
};
class solution4_3 {
public:
	void operator()() {
		cout << "a.����(4.21),T(n)=��(n^log(3,4)+��(4/3)^i*(lgn-ilg3),i=0...lg(3,n)-1,�ȱ���Ȳ���ĺͣ��ô�λ��������	\n"
			<< "T(n)=lg(n)*n^log(3,4)"//����֤������׼ȷ��
			<< "b.T(n)=��(nlglgn)"//�������֤��ȷ��Ҳûд���̣����ƿ��º��ô��뷨��֤�ģ���д���ͬ��
			<< "c.����(4.21)��ͺ��T(n)=n^2+n^(3/2)��2^(j/2),T(n)=��(n^2)	\n"
			<< "d.T(n)=3T(n/3)+n/2,�����������T(n)=nlg	\n"
			<< "e.����(4.21)��ͺ��T(n)=n+n��(1/(lgn-j),j=0...lgn-1,n��(1/(lgn-j)<=n��1/lgn=n,T(n)=��(n)		\n"
			<< "f.T(n)=��(n),T(n)<=cn,T(n)<=c7n/8+n<=cn,c>=8ʱ����,T(n)>=cn,c<=8ʱ����	\n"
			<< "g.T(n)=��(lnn)	\n"
			<< "h.T(n)=lg(n!)<=lg(n^n)=nlgn,T(n)=O(nlgn)��T(n)<=cnlgn,T(n)<=cnlg(n-1)-clg(n-1)+lgn<=clgn,��c=1ʱ������	\n"
			<< "n���ޣ�lgn/lg(n-1)=lgn(n-1,n)=1	\n"
			<< "i.T(n)=��1/lg(2i),i=1...n/2,T(n)=O(n),T(n)=��(n/lgn)	\n"
			<< "j.��������ݹ�������i����n^(0)*n^(1/2)*n^(1/4)*n^(1/8)*...*n^(1/(2^i)=n^(1-1/(2^i),��i��ڵ�Ĵ�С\n"
			<< "Ϊn^(1/(2^i),Ȼ�����һ���ж��ٲ㣬��n^(1/(2^i)=һ��������ȡ2�ȽϺ��ʣ�n^(1/(2^i)=2��i=lglgn	\n"
			<< "һ����lglgn�㣬T(n)=��n^(1-1/(2^i)*n^(1/(2^i)=��n=nlglgn,����i=0...lglgn,	\n"
			<< "T(n)=��(nlglgn)"
			<< endl;
	}
};

class solution4_4 {
public:
	void operator()() {
		cout << "a.zf(z)+z^2f(z)=��z^2+2z^3+3z^4+....����Ȼf(z)=z+zf(z)+z^2f(z)	\n"
			<< "b.��a�ʽ�һԪ���η��̵�F(z)=z/(1-z-z^2),����������ʽ�������մ���չ����֪�����	\n"
			<< "c.ֻ��Ҫ֤����1/(5^(1/2))(x^i-y^i)��쳲��������еĹ�ʽ���ɣ�����solution3_2_7�ù��ɷ����֤����	\n"
			<< "d.ͬ����Ҳ��ϸ˵����"
			<< endl;
	}
};

class solution4_5 {
public: 
	void operator()() {
		cout << "a.��������һ��оƬ������г��Լ���n-1�ݼ����������е��ڻ򳬹�n/2���Ǻõģ���ô��ͬ������������n/2 \n"
			<< "����֪�����оƬ����ʵ�û�����������������г���n/2���ǻ��ģ����޷�ͨ��ͳ��ȷ���û� \n"
			<< endl;
	}/////////////////////////////////////////////

};

class solution4_6 {
public:
	void operator()() {
		cout << "a.i<k,k=i+n,����A[i,j]+A[k,j+1]<=A[i,j+1]+A[k,j]����	\n"
			<< "������֪����ʽ��A[k,j]+A[k+1,j+1]<=A[k,j+1]+A[k+1,j] \n"
			<< "����������ӻ����A[i,j]+A[k+1,j+1]<=A[i,j+1]+A[k+1,j]  \n"
			<< "��Ϊ���������k=i+1ʱ���������Զ���1<=i<k<=nʱ����ʽ��������ͬ���֤  \n"
			<< "b.�ѵڶ��е�7��Ϊ5		\n"
			<< "c.�������1<=i<k<=m,f(i)>f(k),����Monge���е����ʣ�A[i,f(k)]+A[k,f(i)]<=A[i,f(i)]+A[k,f(k)]  \n"
			<< "A[i,f(i)]<A[i,f(k)],A[k,f(k)]<A[i,f(k),��A[i,f(k)]+A[k,f(i)]>A[i,f(i)]+A[k,f(k)],�ʼ��費����   \n"
			<< "d.1<=f(2)<=f(4)<=f(6)<=...<=f(m-2)<=f(m)<=n,����mΪż��������ͬ��Ѱ��������������СԪ��ʱ  \n"
			<< "ֻ��Ƚ�����ż����֮�������f(1)��1...f(2),f(3)��f(4)...f(2),...,f(m-1)��n..f(m)  \n"
			<< "T'(n)=f(2)-f(1)+1+f(4)-f(2)+1+f(6)-f(4)+1+...+f(m)-f(m-2)+1,+n-f(m)+1=n+m/2=O(n+m)	\n"
			<< "e.T(m)=T(m/2)+c(m+n),����Ϊ��m����С����Ԫ�ص�����һ���ż����С����Ԫ������O(m+n)��������СԪ�� \n"
			<< "T(m)=��c(m/(2^i)+n),i=0...lgm,T(m)=cnlgm+cm��(1/(2^i)=cnlgm+cm-c=O(m+nlgn)"
			<< endl;
		print_min_index(vect);
		check(vect);
	}
private:
	void print_min_index(vector<vector<int>>&vect) {//��ӡÿ��������СԪ�أ�ֻ�����ڽϴ��ģ����ע�͵������оͲ���
		vector<size_t>index_vect(vect.size(),0);//û��ע������Ϊ������򲢲����������������٣�������bug
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
	void  check(vector < vector<int>>&vect) {//��ӡ���������ʵ����Ͻ�����
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
