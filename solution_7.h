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
		cout << "����r,����޸Ľ������һ�������أ������ظ�Ԫ�أ����Կ����޸ĺ�ĳ��������Լ���ִ�в���"
			<< endl;
	}
};

class solution7_1_3 {
public:
	void operator()() {
		cout << "���Կ�����ѭ���⣬���д��۾�Ϊ����ʱ�䣬��ѭ����Ҫִ��n����ÿ�����ѳ���ʱ�䣬��Ϊ��(n)"
			<< endl;
	}
};

class solution7_1_4 {
public:
	void operator()() {
		cout << "��partition��4�е�<=��Ϊ>="
			<< endl;
	}
};

class solution7_2_1 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)<=cn^2,T(n)<=c(n-1)^2+cn=cn^2-cn+c<=cn^2,,c>=1ʱ����,T(n)=O(n^2) \n"
			<< "Ҫ֤��T(n)>=c1*n^2,T(n)>=c1*(n-2)^2+c2*n=c1*n^2+(c2-2*c1)+c1>=c1*n^2����c2>=2c1ʱ���� \n"
			<< "T(n)=��(n^2) \n"//���֤���н��
			<<"����T(n)=��(n^2)"
			<< endl;
	}
};

class solution7_2_2 {
public:
	void operator()() {
		cout << "��(n^2),������һ��ĵݹ�ʽ"
			<< endl;
	}
};

class solution7_2_3 {
public:
	void operator()() {
		cout << "������Ԫ��ѡȡ�����ұߵ�Ԫ�أ���ÿ�����ұߵ�Ԫ�ض�������������С�ģ�����ÿ�ζ���������Ȼ��� \n"
			<< "����ʽΪ�����⣬Ϊ��(n^2)"
			<< endl;
	}
};

class solution7_2_4 {
public:
	void operator()() {
		cout << "���ڼ��������������˵��������������Ǧ�(n),��Ϊ�ڲ�ѭ��ֻ���ѳ���ʱ�䣬��quicksort����Ϊ��(n^2) \n"
			<< endl;
	}
};

class solution7_2_5 {
public:
	void operator()() {		
		cout << "T(n) = T(na) + T(n(1 - a)) + cn,��С���Ϊ����ߵģ�log(1/a,n)=-log(a,n)=-lgn/lga \n"
			<< "�����������ұߣ�log(1/(1-a),n)=-log(1-a,n)=-lgn/lg(1-a)"
			<< endl;
	}
};
class solution7_2_6 {
public:
	void operator()() {
		cout << "0<a<=1/2,��a<b<=1/2ʱ��b���ָ�ƽ�⣬����0,1/2]���ֳ��߶Σ�a�����߶λ��ֳ�������(0,a],(a,1/2) \n"
			<< "Pr{X=b>a}=(1/2-a)/(1/2-0)=1-2a"
			<< endl;
	}
};
class solution7_3_1 {
public:
	void operator()(){
		cout << "��������㷨������£�n����ʱ���������ֵĸ���Ϊ0"
			<< endl;
	}
};
class solution7_3_2 {
public:
	void operator()() {
		cout << "�����£������������������������γɵĻ���������������С������Ԫ�أ�ÿ�λ��ֳ�n-1��0�� \n"
			<< "��Ҫ���æ�(n)�Σ���õ������(lgn)��"
			<< endl;
	}
};
class solution7_4_1 {
public:
	void operator()() {
		cout << "Ҫ֤��T(n)>=cn^2,T(n)>=(cq^2+c(n-q-1)^2)+��(n)<=cn^2-c(2n-1)+��(n),����һ���㹻С��c \n"
			<< "ʹ��c(2n-1)С�ڦ�(n)��"
			<< endl;
	}
};

class solution7_4_2 {
public:
	void operator()() {
		cout << "�������µĵݹ�ʽΪT(n)=2T(n/2)+��(n),Ҫ֤��T(n)>=cnlgn \n"
			<< "T(n)>=2*c/2*lg(n/2)+c1*n=cnlgn-cn+c1*n,��c<c1ʱ����"
			<< endl;
	}
};

class solution7_4_3 {
public:
	void operator()() {
		cout << "��x=q+1,��x=1...q,ԭʽ=��x-1)^2+(n-x)^2=2x^2-(2+2n)x+n^2+1,��֪����x��һԪ���κ����ĺ���ͼ�񶥵� \n"
			<< "x1=(1+n)/2��Ӧ��ֵ����Сֵ�����ֵΪ����1��q��Ӧ��ֵ"
			<< endl;
	}
};

class  solution7_4_4 {
public:
	void operator()() {
		cout << "ʽ�ӣ�7.4)��{i=1,n-1}��{k=1,n-i} (2/(k+1))>=��{i=1,n/2}��{k=1,n-i} (2/(k+1)) \n"
			<< ">=��{i=1,n/2}��{k=1,n/2} (2/(k+1))=��{i=1,n/2} ln(n)+c=��(nlgn)"
			<< endl;
	}
};

class solution7_4_5 {
public:
	void operator()() {
		cout << "��Ϊ�����������������ӽ���������������ÿ�ζ��ǳ������֣�����ȡ1/2,������� \n"
			<< "�ݹ���ҶΪn/kʱ��lg(n/k)�㣬ÿ��ķ�c1*n�����Կ��źķ�c1*nlg(n/k) \n"
			<< "����������ڹ�ģΪk�ģ�����Ϊc2*k^2,һ����n/k��������Ϊc2*nk������ O(nk+nlg(n/k) \n"
			<< "�����ϣ�c2*nlgn>=c1*nk+c2*nlg(n/k),k<=c2/c1*lgk \n"
			<< "ʵ���� kȡ���ڼ�������Ĳ�������Ĵ��۵��ڿ��ŵĵĹ�ģ"
			<< endl;
	}
};

class solution7_4_6 {
public:
	void operator()() {
		cout << "����Ԫ�ؿ����ظ������������ģΪn��ȡ����λ��Ϊna�ĸ���Ϊ1/n,С�ڵ��ڵĸ���Ϊna/n,���ڵ���Ϊn(1-a)/n \n"
			<< "һ����3�������У��������Ϊ 6*a(1-a)/n"
			<< endl;
	}
};
//˼����

class solution7_1 {
public:
	void operator()() {
		//a.
		quickSort(1, vect.size() - 1);
		cout << "����֮��:" << endl;
		print_vector(vect);
		cout << "b.����jԽ��Ŀ����ǵ�һ�ν���repeat-until��Խ�磬���ǵ�j=pʱ��Ȼ������ѭ�������˳�ѭ������ʱi=j \n"
			<< "�˳�whileѭ�������j��Խ��֮ǰ�˳�ѭ��������iѭ����i��һ���˳�ѭ����Ȼ�ǵ�i=pʱ�� \n"
			<<"��ʱA[i]=x,���i<j,ִ�н�������Ҳ����ζ�ţ���j��߱�Ȼ��һ��Ԫ�ز�����j��ѭ�������� \n"
			<<"��Ϊ������ѭ�������ı�������j���ȥ�ˣ���i�ұ�Ҳ��Ȼ����һ��Ԫ��i������i��ѭ������ \n"
			<<"��Ϊ������ѭ�������ı�������i�ұ�ȥ�ˣ��ظ���һ����ֱ��i>=j�˳�whileѭ�� \n"
			<<"c.��x=�������е���Сֵʱ����p�����᷵��r��Ҫ����r�ı�Ҫ������j=rʱj�˳�ѭ��������ʱi��ȻҲ���˳�ѭ�� \n"
			<<"�������Ȼ����i<j,��ʱi���ٴεݼ�һ�Σ�������������з���ֵ \n"
			<<"d.A[p...j]<=x,A[i...r]>=x,����A[p...j]]<=A[i...r] \n"
			<<"e.��a"
			<< endl;
	}
private: 
	vector<int>vect{0,13,19,9,5,12,8,7,4,11,2,6,21 };
	void quickSort(size_t beg,size_t end) {
		if (beg < end) {
			cout << "����������ֵ��" << vect[beg] << ",�����Ľ��Ϊ:" << endl;
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
		cout << "a.����Ԫ�ض���ͬ������������������������ʱ��Ϊ��(n^2) \n"
			<< "b.���·� \n"
			<<"c.���·� \n"
			<<"d.��ΪQuicksort'�ıȽϴ���һ������Quicksort������ʱ����ȻΪO(n log n)"
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
		cout << "a.��֤������֤����ȥ��E(X(i))=1/n, \n"
			<< "b.��������ʱ�������qΪ���ֳ����������������������ʱ�� \n"
			<< "c.E��(X(q)(T(q-1)+T(n-q))),q=1....n,����T(q-1)��T(n-q)�����������ͬ�� \n"
			<< "��q=n-q+1ʱ��T(q-1)=T(n-q),T(n-q)=T(q-1),���Կ��Լ�дΪ2E��X(q)(T(q))=2��E(Xq)(T(q)) \n"
			<< "E(X(a))=1/n,��Ϊ2��E(Xq)(T(q))=2/n��(E(T(q))+��(n)��������ΪӦ����<����Ϊ���˵�һ�εݹ����Ϊ1/n�� \n"
			<< "E(X(i))=1/(r-q+1),����Ӱ���������н�� \n"
			<< "d.<=lg��n/2)��k+lgn��k ��Ȼ���õȲ����е���͹�ʽ\n"//���
			<< "e.ֱ�Ӱѵ�ʽд�����Ϳ��Գ���һ��n"
			<< endl;
	}
};

class solution7_4 {
public:
	void operator()() {
		cout << "a.ÿһ��ѭ���������н�����ֳ�������A[p...q-1]��A[q+1...r],�����еݹ������������A[p...q-1], \n"
			<< "�ұ�A[q+1...r]����Ϊ��һ��A[p...r]���룬�ʿ��Զ�����A���� \n"
			<< "b.���������� \n"
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
	void operator()() {//�ҿ��������𰸶���ѡ�˲�ͬԪ��������ģ������ǿ���ѡȡ��ͬԪ�أ����Ժ��ҵĴ𰸲�ͬ
		cout << "a.Pi=1/n * i/n *(n-i)/n *3!=6*i*(n-i+1)/n^3 ,����p1=pn=0���Եó���Ŀ����˼��ȷ��ѡȡ��������ͬԪ�� \n"
			<< "���ظ��� Pi=6(i-1)(n-i)/(n(n-1)(n-2))  \n"
			<< "b.��i=(n+1)/2������ʽ�� Pi=3/(2n),����3/(2n)/1/n=1/2*1/n,lim n���� 1/2*1/n  \n"
			<< "���ظ�����ͬ����һ����ֱ����ı���Ϊ3/2 \n"
			<< "c.6/n^3*��(n/3,2n/3,���ǻ������Ͻ磬��i����)i*(n-i+1)=13/27 \n "
			<< "����һ���㷨ʱ���û��֣���n/3��2n/3��ѡȡһ���ĸ���Ϊ1/3,��1��2n/3��ѡȡһ���ĸ���Ϊ2/3, \n"
			<< "��n/3��n��ѡȡһ���ĸ���Ϊ2/3,P(X)=3!*1/3*2/3*/2/3=24/27,����24/27-1/3=13/27 \n"
			<< "���ظ�����ͬ"
			<< "d.����ȡ�з������ı�Ƚϴ�����ֻ����ߺû��ֵĸ��� "
			<< endl;
	}
};
#endif //_SOLUTION_7_H_
