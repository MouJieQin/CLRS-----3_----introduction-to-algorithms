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
	void operator()(vector<int>&refv) {//非降序排序
		for (auto i = 1; i != refv.size(); ++i) {
			auto key = refv[i];
			auto j =i - 1;
			for (; j >= 0 && key > refv[j]; --j)
				refv[j + 1] = refv[j];
			refv[j + 1] = key;
		}
	}
};

class solution2_1_3 {//查找关键字
public:
	int operator()(vector<int>&refv, size_t n,int v) {
		auto i = 0;
		for (; i != n&&refv[i] != v; ++i)
			;
		return i == n ? -1:i;
	}
};

class solution2_1_4 {//计算两个string形式二进制的和，位数可不相同
public:
	string operator()( string &lhs, string &rhs) {
		auto lhsSize = lhs.size();
		auto rhsSize = rhs.size();//用0将较短的二进制数补齐
		lhsSize > rhsSize ? rhs = string(lhsSize - rhsSize, '0') + rhs : lhs = string(rhsSize - lhsSize, '0') + lhs;
		auto pre= adder('0', lhs.back(), rhs.back());//最低位加法较特殊无进位，单独处理
		string result = string()+pre.first;//存储结果
		char carry = pre.second;//记录进位
		int n = lhs.size()-2;//从低二位开始计算
		while (n >=0) {//迭代计算
			pre=adder(carry, lhs[n], rhs[n]);
			result = pre.first + result;
			carry= pre.second;
			--n;
		}		
		return pre.second+result;//加上最高位的进位
	}
private:
	pair<char,char>half_adder(const char lhs, const char rhs) {//半加器，两位输入，输出first为和数，second为进位数
		return
			lhs == '1' ? rhs == '1' ? make_pair('0', '1') : make_pair('1', '0') : rhs == '1' ? make_pair('1', '0') : make_pair('0', '0');
	}
	char orer(const char lhs, const char rhs) { if (lhs == '1' || rhs == '1')return '1'; return '0'; }//或逻辑
	pair<char, char>adder(const char carry, const char lhs, const char rhs) {//全加器，多一个进位输入，first为和数，second为进位数；
		auto sumbit_carry_one = half_adder(lhs, rhs);
		auto sumbit_carry_two = half_adder(carry, sumbit_carry_one.first);
		return
			make_pair(sumbit_carry_two.first, orer(sumbit_carry_one.second, sumbit_carry_two.second));
	}
};

class solution2_2_2 {
public:
	void operator()(vector<int>&rv) {//选择排序
		for (auto i = 0; i != rv.size() - 1; ++i) {//循环体将进行n-1次
			auto n = findMin(rv, i, rv.size());//i=1 (n-1)∑(Ti)=n*(n-1)/2=Θ(n^2)
			auto min = rv[n];//常数时间
			int temp = rv[i];//常数时间
			rv[i] = min;//常数时间
			rv[n] = temp;//常数时间
		}
	}//我写的这个选择排序法最好和最坏的总时间都为T(n)=(n-1)*n*(n-1)/2=Θ(n^3) 算法分析：
	//初始化：第1次交换后第1位为第1小的值
	//保持：第k次交换后第k位为第k小的值，1到k位已排序;
	//终止：第n-1次交换后第n-1位为第n-1小的值，第n位只能是不大于n-1位的值
	//如若不然应与n-1位交换，与假设矛盾，所以不需要对n个元素运行
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
		cout << "平均需要检查总元素数量的一半\n T(n)=n/2=Θ(n)\
			\n最坏情况为总是在最后一个找到所需元素\n T(n)=n=Θ(n)" << endl;
	}
};

class solution2_3_1 {
public:
	void operator()() {
		merge_sort(vect, 0, vect.size() - 1);
	}
private:
	void merge_sort(vector<int>&vect, size_t beg, size_t end) {
		if (beg < end) {//只有容器中的数大于1个时才开始合并
			auto mid = (beg + end) / 2;//取中间值
			merge_sort(vect, beg, mid);//递归分治，下同
			merge_sort(vect, mid + 1, end);
			merge(vect, beg, mid, end);//合并
		}
	}
	void merge(vector<int>&vect,size_t beg, size_t mid, size_t end) {
		vector<int>larr(&vect[beg], &vect[mid+1]);//初始化左容器，下同
		vector<int>rarr(&vect[mid+1], &vect[end] + 1);
		larr.push_back(INT_MAX);//设置哨兵，下同
		rarr.push_back(INT_MAX);
		auto lbeg = larr.begin();
		auto rbeg = rarr.begin();
		for (auto n=beg; n != end+1; ++n)//取左右容器中较小的数存入原容器
			vect[n] = *lbeg < *rbeg ? *lbeg++ : *rbeg++;
		for (auto n = beg; n != end + 1; ++n)//打印排序过程
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
			if (beg < end) {//只有容器中的数大于1个时才开始合并
				auto mid = (beg + end) / 2;//取中间值
				merge_sort(vect, beg, mid);//递归分治，下同
				merge_sort(vect, mid + 1, end);
				merge(vect, beg, mid, end);//合并
		}
	}
	void merge(vector<int>&vect, size_t beg, size_t mid, size_t end) {
		vector<int>larr(&vect[beg], &vect[mid + 1]);//初始化左容器，下同
		vector<int>rarr(&vect[mid + 1], &vect[end] + 1);
		auto lbeg = larr.begin();
		auto rbeg = rarr.begin();
		for (; lbeg != larr.end() && rbeg != rarr.end(); ++beg)//取左右容器中较小的数存入原容器
			vect[beg] = *lbeg < *rbeg ? *lbeg++ : *rbeg++;
		while (lbeg != larr.end())//将未空的容器中的所有数放进原容器，下同
			vect[beg++] = *lbeg++;
		while (rbeg != rarr.end())
			vect[beg++] = *rbeg++;
	}
};
class solution2_3_3 {
public:
	void operator()() {
		cout << "1.当k=1时，T(n)=2=(2)lg(2)，等式成立\n"
			<< "2.当k>1时，假设T(n)=nlgn成立，则T(2^(k))=2*T(2^(k-1))+2^(k)=k*2^(k)\n"
			<< "3.T(2^(k+1))=2T(2^(k))+2^(k+1),将此式中的T(2^(k))用上式中的k*2^(k)替换\n"
			<< "得T(2^(k+1))=(k+1)*2^(k+1)=原假设解nlgn计算出来的公式,故得证" << endl;
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
		auto beg = 0;//开始范围坐标
		auto end = vect.size() - 1;//结束范围坐标
		int mid;//中间值
		cout << prove << endl;
		while (mid=(beg+end)/2,beg != end&&key != vect[mid]) //二分查找，vect已排序
			key < vect[mid] ? end = mid : beg = mid + 1;//调整查找范围
		return  key == vect[mid] ? mid : -1;//如果找到返回下标，如果没找到返回-1
	}
private:
	vector<int>vect{ 1,2,3,4,5,6,7,8 };
	string prove = "二分查找循环或迭代中最多运行lgn次便退出循环，\
		\n因为最多除以lgn次2后beg=end,最后的查找范围只有一个原范围中最接近或等于关键字的值";
};

class solution2_3_6 {
public:
	int operator()(vector<int>&vect) {
		cout << "不能改善，因为最坏情况下即使二分查找找到关键字的正确位置，也还是需要将已排序的i个数全体后移一位"
			<< endl;
	}
};

class solution2_3_7 {
public://可以改进到Θ(nlgn),先用一个Θ(nlgn)排序法将vect排序
	pair<int, int>operator()(vector<int>&vect,int sum) {//假设vect已用一个Θ(nlgn)排序法如归并排序
		solution2_3_2 merge_sort;// 调用归并排序
		merge_sort(vect);
		for (auto i = 0; i != vect.size()-1; ++i) {//最坏情况循环n次
			auto key = sum - vect[i];//
			int beg = i+1;//不能使用相同元素，且之前查找过得元素不用考虑在内
			int end = vect.size() - 1;
			int mid=0;
			if (key<vect[beg]|| key>vect.back())continue;//优化
			while (mid = (beg + end) / 2, beg != end&&key != vect[mid])//二分查找Θ(lgn)
				key < vect[mid] ? end = mid : beg = mid + 1;
			return key == vect[mid] ? make_pair(i, mid) : make_pair(-1, -1);//返回排序后的下标，没有返回(-1,-1)
		}//该循环体的总时间n*Θ(lgn)=Θ(nlgn)
		return{ -1, -1};
	}//该函数的总时间为Θ(nlgn)+Θ(nlgn)=Θ(nlgn)
};

//思考题
class solution2_1 {
public:
	void operator()(vector<int>&vect, size_t k) {
		cout << prove_a << endl;
		cout << prove_b << endl;
		cout << prove_c << endl;
		cout << prove_d << endl;
	}
private:
	string prove_a="a.单个长度为k的的子表最坏情况为Θ(k^2),一共有n/k个子表，总时间T(n)=n/k*Θ(k^2)=Θ(nk)";
	string prove_b = "b.从图2-5可知每一层合并的总时间都为cn，c为常量因子，此题最底层只到有n/k个子表的那层，\
		\n树的高度lg(n/k)+1,每层归并的代价都为n，T(n)=cn*(lg(n/k)+1)=Θ(nlg(n/k))";
	string prove_c = "c.Θ(nk+nlg(n/k))=Θ(nk+nlgn-nlgk),可以看出nlgk的增长量级没有nk高，故原式=Θ(nk+nlgn)\
				\n也就是要让Θ(nk+nlgn)=Θ(nlgn),nk要小于等于nlgn得量级，故k=Θ(lgn)";
	string prove_d = "d.输入规模为k时，插入排序和归并排序的时间一样长的时候";
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
	string prove_a = "a.我们需要证明 A′ 是 A 的一个排列";//借鉴，注意元素起始坐标是0，结构并不完整
	string prove_b = "b.循环不变式：A[j-1]是A[i...n-1]个元素的最小元素，保持:每次交换都将已比较的最小元素前移";
	string prove_c = "c.起始时A[0...i-1]的元素为空，循环不变式显然成立，\
		\n保持：第2到4行for循环每次迭代前，子数组A[0...i-1]按从小到大的顺序包含原数组中i个最小元素\
		\n终止时i=n,子数组A[0...i-1]就是按从小到大顺序的原数组A[0...n-1]";
	string prove_d = "d.上界和下界都为T(n)=Θ(n^2),和插入排序一样";
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
	string prove_a = "a.Θ(n^2)";
	string prove_b = "b. y=0\
		\n	for i=0 to n\
		\n		y+=a(i)*pow(x,i)\
		\nT(n)=Θ(n^2),性能不如霍纳规则";
	string prove_c = "c.终止时i=-1带入公式可得";//结构并不完整
	string prove_d = "d. c已经证明出来了！";
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
	string prove_b = "b. 集合按降序排列具有最多的逆序对n*(n-1)/2对";
	string prove_c = "c. 成正比,插入排序的外层循环i标记的是逆序对中j，内存循环j为查找逆序对j对应的逆序对i\
	\n而移动对应的逆序对个数的位数";
};
void solution2_4::merge(vector<int>&vect, size_t beg, size_t mid, size_t end,size_t &count) {
	vector<int>lvec(&vect[beg], &vect[mid + 1]);
	vector<int>rvec(&vect[mid + 1], &vect[end] + 1);	
	lvec.push_back(INT_MAX);
	rvec.push_back(INT_MAX);
	size_t n1 = mid - beg + 1;
	size_t n2 = end - mid;
	for (size_t n = beg, i = 0, j = 0; n <= end; ++n)//因为lvec和rvec都已排序，若lvec[i]>rvec[j],则与rvec[j]对应的
		vect[n] = lvec[i] < rvec[j] ?lvec[i++]:( count+=n1-i ,rvec[j++]);//逆序对一共有n1-i个
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
