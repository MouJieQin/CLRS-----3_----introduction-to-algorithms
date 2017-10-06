#pragma once
#ifndef _SOLUTION_2
#define _SOLUTION_2
#include<vector>
#include<iostream>
#include<string>
#include<utility>
#include<climits>
using namespace std;
class solution2_1_1 {
public:
	solution2_1_1():vect{31,41,59,26,41,58}{}
	void operator()() {
		for (auto i = 1; i != vect.size(); ++i) {
			auto key = vect[i];
			int j = i - 1;
			for (; j >= 0 && key < vect[j]; --j)
				vect[j + 1] = vect[j];
			vect[j + 1] = key;
			for (auto i : vect)
				cout << i << "\t";
			cout <<"\t("<<i<<")" <<endl;
		}
	}
private:
	vector<int>vect;
};

class solution2_1_2{
public:
	void operator()(vector<int>&refv) {//�ǽ�������
		for (auto i = 1; i != refv.size(); ++i) {
			auto key = refv[i];
			auto j =i - 1;
			for (; j >= 0 && key > refv[j]; --j)
				refv[j + 1] = refv[j];
			refv[j + 1] = key;
		}
	}
};

class solution2_1_3 {//���ҹؼ���
public:
	int operator()(vector<int>&refv, size_t n,int v) {
		auto i = 0;
		for (; i != n&&refv[i] != v; ++i)
			;
		return i == n ? -1:i;
	}
};

class solution2_1_4 {//��������string��ʽ�����Ƶĺͣ�λ���ɲ���ͬ
public:
	string operator()( string &lhs, string &rhs) {
		auto lhsSize = lhs.size();
		auto rhsSize = rhs.size();//��0���϶̵Ķ�����������
		lhsSize > rhsSize ? rhs = string(lhsSize - rhsSize, '0') + rhs : lhs = string(rhsSize - lhsSize, '0') + lhs;
		auto pre= adder('0', lhs.back(), rhs.back());//���λ�ӷ��������޽�λ����������
		string result = string()+pre.first;//�洢���
		char carry = pre.second;//��¼��λ
		int n = lhs.size()-2;//�ӵͶ�λ��ʼ����
		while (n >=0) {//��������
			pre=adder(carry, lhs[n], rhs[n]);
			result = pre.first + result;
			carry= pre.second;
			--n;
		}		
		return pre.second+result;//�������λ�Ľ�λ
	}
private:
	pair<char,char>half_adder(const char lhs, const char rhs) {//���������λ���룬���firstΪ������secondΪ��λ��
		return
			lhs == '1' ? rhs == '1' ? make_pair('0', '1') : make_pair('1', '0') : rhs == '1' ? make_pair('1', '0') : make_pair('0', '0');
	}
	char orer(const char lhs, const char rhs) { if (lhs == '1' || rhs == '1')return '1'; return '0'; }//���߼�
	pair<char, char>adder(const char carry, const char lhs, const char rhs) {//ȫ��������һ����λ���룬firstΪ������secondΪ��λ����
		auto sumbit_carry_one = half_adder(lhs, rhs);
		auto sumbit_carry_two = half_adder(carry, sumbit_carry_one.first);
		return
			make_pair(sumbit_carry_two.first, orer(sumbit_carry_one.second, sumbit_carry_two.second));
	}
};

class solution2_2_2 {
public:
	void operator()(vector<int>&rv) {//ѡ������
		for (auto i = 0; i != rv.size() - 1; ++i) {//ѭ���彫����n-1��
			auto n = findMin(rv, i, rv.size());//i=1 (n-1)��(Ti)=n*(n-1)/2=��(n^2)
			auto min = rv[n];//����ʱ��
			int temp = rv[i];//����ʱ��
			rv[i] = min;//����ʱ��
			rv[n] = temp;//����ʱ��
		}
	}//��д�����ѡ��������ú������ʱ�䶼ΪT(n)=n*(n-1)/2=��(n^2) �㷨������
	//��ʼ������1�ν������1λΪ��1С��ֵ
	//���֣���k�ν������kλΪ��kС��ֵ��1��kλ������;
	//��ֹ����n-1�ν������n-1λΪ��n-1С��ֵ����nλֻ���ǲ�����n-1λ��ֵ
	//������ȻӦ��n-1λ�����������ì�ܣ����Բ���Ҫ��n��Ԫ������
private:
	int findMin(vector<int>&rv,size_t beg, size_t end) {
		size_t n(beg);
		int min = rv[n];
		while (++beg != end)
			if (min > rv[beg]) {
				min = rv[beg]; 
				n = beg;
			}
		return n; 
	}
};

class solution2_2_3 {
public:
	void operator()() {
		cout << "ƽ����Ҫ�����Ԫ��������һ��\n T(n)=n/2=��(n)\
			\n����Ϊ���������һ���ҵ�����Ԫ��\n T(n)=n=��(n)" << endl;
	}
};

class solution2_3_1 {
public:
	void operator()() {
		merge_sort(vect, 0, vect.size() - 1);
	}
private:
	void merge_sort(vector<int>&vect, size_t beg, size_t end) {
		if (beg < end) {//ֻ�������е�������1��ʱ�ſ�ʼ�ϲ�
			auto mid = (beg + end) / 2;//ȡ�м�ֵ
			merge_sort(vect, beg, mid);//�ݹ���Σ���ͬ
			merge_sort(vect, mid + 1, end);
			merge(vect, beg, mid, end);//�ϲ�
		}
	}
	void merge(vector<int>&vect,size_t beg, size_t mid, size_t end) {
		vector<int>larr(&vect[beg], &vect[mid+1]);//��ʼ������������ͬ
		vector<int>rarr(&vect[mid+1], &vect[end] + 1);
		larr.push_back(INT_MAX);//�����ڱ�����ͬ
		rarr.push_back(INT_MAX);
		auto lbeg = larr.begin();
		auto rbeg = rarr.begin();
		for (auto n=beg; n != end+1; ++n)//ȡ���������н�С��������ԭ����
			vect[n] = *lbeg < *rbeg ? *lbeg++ : *rbeg++;
		for (auto n = beg; n != end + 1; ++n)//��ӡ�������
			cout << vect[n] << "\t";
		cout << endl;
	}
	vector<int>vect{ 3,41,52,26,38,57,9,49 };
};

class solution2_3_2 {
public:
	void operator()(vector<int>&vect) {
		merge_sort(vect, 0, vect.size() - 1);
	}
private:
	void merge_sort(vector<int>&vect, size_t beg, size_t end) {
			if (beg < end) {//ֻ�������е�������1��ʱ�ſ�ʼ�ϲ�
				auto mid = (beg + end) / 2;//ȡ�м�ֵ
				merge_sort(vect, beg, mid);//�ݹ���Σ���ͬ
				merge_sort(vect, mid + 1, end);
				merge(vect, beg, mid, end);//�ϲ�
		}
	}
	void merge(vector<int>&vect, size_t beg, size_t mid, size_t end) {
		vector<int>larr(&vect[beg], &vect[mid + 1]);//��ʼ������������ͬ
		vector<int>rarr(&vect[mid + 1], &vect[end] + 1);
		auto lbeg = larr.begin();
		auto rbeg = rarr.begin();
		for (; lbeg != larr.end() && rbeg != rarr.end(); ++beg)//ȡ���������н�С��������ԭ����
			vect[beg] = *lbeg < *rbeg ? *lbeg++ : *rbeg++;
		while (lbeg != larr.end())//��δ�յ������е��������Ž�ԭ��������ͬ
			vect[beg++] = *lbeg++;
		while (rbeg != rarr.end())
			vect[beg++] = *rbeg++;
	}
};
class solution2_3_3 {
public:
	void operator()() {
		cout << "1.��k=1ʱ��T(n)=2=(2)lg(2)����ʽ����\n"
			<< "2.��k>1ʱ������T(n)=nlgn��������T(2^(k))=2*T(2^(k-1))+2^(k)=k*2^(k)\n"
			<< "3.T(2^(k+1))=2T(2^(k))+2^(k+1),����ʽ�е�T(2^(k))����ʽ�е�k*2^(k)�滻\n"
			<< "��T(2^(k+1))=(k+1)*2^(k+1)=ԭ�����nlgn��������Ĺ�ʽ,�ʵ�֤" << endl;
	}
};
class solution2_3_4 {
public:
	void operator()() {
		cout << "T(n)=1 (n=2) \n"
			<<"T(n)=T(n-1)+n-1 (n>2)" << endl;
	}
};

class solution2_3_5 {
public:
	int operator()(int key) {
		auto beg = 0;//��ʼ��Χ����
		auto end = vect.size() - 1;//������Χ����
		int mid;//�м�ֵ
		cout << prove << endl;
		while (mid=(beg+end)/2,beg != end&&key != vect[mid]) //���ֲ��ң�vect������
			key < vect[mid] ? end = mid : beg = mid + 1;//�������ҷ�Χ
		return  key == vect[mid] ? mid : -1;//����ҵ������±꣬���û�ҵ�����-1
	}
private:
	vector<int>vect{ 1,2,3,4,5,6,7,8 };
	string prove = "���ֲ���ѭ����������������lgn�α��˳�ѭ����\
		\n��Ϊ������lgn��2��beg=end,���Ĳ��ҷ�Χֻ��һ��ԭ��Χ����ӽ�����ڹؼ��ֵ�ֵ";
};

class solution2_3_6 {
public:
	int operator()(vector<int>&vect) {
		cout << "���ܸ��ƣ���Ϊ�����¼�ʹ���ֲ����ҵ��ؼ��ֵ���ȷλ�ã�Ҳ������Ҫ���������i����ȫ�����һλ"
			<< endl;
	}
};

class solution2_3_7 {
public://���ԸĽ�����(nlgn),����һ����(nlgn)���򷨽�vect����
	pair<int, int>operator()(vector<int>&vect,int sum) {//����vect����һ����(nlgn)������鲢����
		solution2_3_2 merge_sort;// ���ù鲢����
		merge_sort(vect);
		for (auto i = 0; i != vect.size()-1; ++i) {//����ѭ��n��
			auto key = sum - vect[i];//
			int beg = i+1;//����ʹ����ͬԪ�أ���֮ǰ���ҹ���Ԫ�ز��ÿ�������
			int end = vect.size() - 1;
			int mid=0;
			if (key<vect[beg]|| key>vect.back())continue;//�Ż�
			while (mid = (beg + end) / 2, beg != end&&key != vect[mid])//���ֲ��Ҧ�(lgn)
				key < vect[mid] ? end = mid : beg = mid + 1;
			return key == vect[mid] ? make_pair(i, mid) : make_pair(-1, -1);//�����������±꣬û�з���(-1,-1)
		}//��ѭ�������ʱ��n*��(lgn)=��(nlgn)
		return{ -1, -1};
	}//�ú�������ʱ��Ϊ��(nlgn)+��(nlgn)=��(nlgn)
};

//˼����
class solution2_1 {
public:
	void operator()(vector<int>&vect, size_t k) {
		cout << prove_a << endl;
		cout << prove_b << endl;
		cout << prove_c << endl;
		cout << prove_d << endl;
	}
private:
	string prove_a="a.��������Ϊk�ĵ��ӱ�����Ϊ��(k^2),һ����n/k���ӱ���ʱ��T(n)=n/k*��(k^2)=��(nk)";
	string prove_b = "b.��ͼ2-5��֪ÿһ��ϲ�����ʱ�䶼Ϊcn��cΪ�������ӣ�������ײ�ֻ����n/k���ӱ���ǲ㣬\
		\n���ĸ߶�lg(n/k)+1,ÿ��鲢�Ĵ��۶�Ϊn��T(n)=cn*(lg(n/k)+1)=��(nlg(n/k))";
	string prove_c = "c.��(nk+nlg(n/k))=��(nk+nlgn-nlgk),���Կ���nlgk����������û��nk�ߣ���ԭʽ=��(nk+nlgn)\
				\nҲ����Ҫ�æ�(nk+nlgn)=��(nlgn),nkҪС�ڵ���nlgn����������k=��(lgn)";
	string prove_d = "d.�����ģΪkʱ����������͹鲢�����ʱ��һ������ʱ��";
};

class solution2_2 {
public:
	void operator()() {
		cout << prove_a << endl;
		cout << prove_b << endl;
		cout << prove_c << endl;
		cout << prove_d << endl;
	}
private:
	string prove_a = "a.������Ҫ֤�� A�� �� A ��һ������";//�����ע��Ԫ����ʼ������0���ṹ��������
	string prove_b = "b.ѭ������ʽ��A[j-1]��A[i...n-1]��Ԫ�ص���СԪ�أ�����:ÿ�ν��������ѱȽϵ���СԪ��ǰ��";
	string prove_c = "c.��ʼʱA[0...i-1]��Ԫ��Ϊ�գ�ѭ������ʽ��Ȼ������\
		\n���֣���2��4��forѭ��ÿ�ε���ǰ��������A[0...i-1]����С�����˳�����ԭ������i����СԪ��\
		\n��ֹʱi=n,������A[0...i-1]���ǰ���С����˳���ԭ����A[0...n-1]";
	string prove_d = "d.�Ͻ���½綼ΪT(n)=��(n^2),�Ͳ�������һ��";
};

class solution2_3 {
public:
	void operator()() {
		cout << prove_a << endl;
		cout << prove_b << endl;
		cout << prove_c << endl;
		cout << prove_d << endl;
	}
private:
	string prove_a = "a.��(n^2)";
	string prove_b = "b. y=0\
		\n	for i=0 to n\
		\n		y+=a(i)*pow(x,i)\
		\nT(n)=��(n^2),���ܲ�����ɹ���";
	string prove_c = "c.��ֹʱi=-1���빫ʽ�ɵ�";//�ṹ��������
	string prove_d = "d. c�Ѿ�֤�������ˣ�";
};

class solution2_4 {
public:
	size_t operator()(vector<int>&vect) {
		cout << prove_a << endl;
		cout << prove_b << endl;
		cout << prove_c << endl;		
		size_t count=0;
		merge_inversion(vect, 0, vect.size() - 1,count);
	//	cout << count << endl;
		return count;
	}
private:
	void merge(vector<int>&vect, size_t beg, size_t mid, size_t end,size_t &count);
	void merge_inversion(vector<int>&vect, size_t beg, size_t end,size_t &count);
	string prove_a = "a. 0 4,1 4,2 3,2 4,3 4";
	string prove_b = "b. ���ϰ��������о������������n*(n-1)/2��";
	string prove_c = "c. ������,������������ѭ��i��ǵ����������j���ڴ�ѭ��jΪ���������j��Ӧ�������i\
	\n���ƶ���Ӧ������Ը�����λ��";
};
void solution2_4::merge(vector<int>&vect, size_t beg, size_t mid, size_t end,size_t &count) {
	vector<int>lvec(&vect[beg], &vect[mid + 1]);
	vector<int>rvec(&vect[mid + 1], &vect[end] + 1);	
	lvec.push_back(INT_MAX);
	rvec.push_back(INT_MAX);
	size_t n1 = mid - beg + 1;
	size_t n2 = end - mid;
	for (size_t n = beg, i = 0, j = 0; n <= end; ++n)//��Ϊlvec��rvec����������lvec[i]>rvec[j],����rvec[j]��Ӧ��
		vect[n] = lvec[i] < rvec[j] ?lvec[i++]:( count+=n1-i ,rvec[j++]);//�����һ����n1-i��
}
void solution2_4::merge_inversion(vector<int>&vect, size_t beg, size_t end, size_t &count) {
	if (beg < end) {
		auto mid = (beg + end) / 2;
		merge_inversion(vect, beg, mid,count);
		merge_inversion(vect, mid + 1, end,count);
		merge(vect, beg, mid, end, count);
	}
}
#endif //_SOLUTION_2
