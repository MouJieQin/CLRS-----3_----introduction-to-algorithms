#pragma once
#ifndef _SOLUTION_8_H_
#define _SOLUTION_8_H_
#include<iostream>
#include<vector>
#include<cmath>
#include<list>
using namespace std;

class solution8_1_1 {
public:
	void operator()() {
		cout << "a.n-1  \n"
			<< endl;
	}
};

class solution8_1_2 {
public:
	void operator()() {
		cout << "根据公司(C.11),lgn积分后为nlgn-x/ln2,将上下界条件带入得Θ(nlgn) \n"
			<< endl;
	}
};

class solution8_1_3 {
public:
	void operator()() {
		cout << "lg(n!/2)=Ω(nlgn),lg(n!/n)=Ω（nlgn),lg(n!/2^n)=lg(n!)-n=Ω（nlgn)"
			<< endl;
	}
};

class solution8_1_4 {
public:
	void operator()() {
		cout << "每个子序列都有k！种排列，一共有n/k个子序列，所以一共有(k!)^(n/k)种排列， \n"
			<< "高度为h的叶节点不多于2^h,2^h>=(k!)^(n/k),h>=n/klgk!=nlgk "
			<< endl;
	}
};

void print_vector(vector<int>&vect) {
	for (size_t i = 1; i != vect.size(); ++i)
		cout << vect[i] << "\t";
	cout << "\n" << endl;
}

class solution8_2_1 {
public:
	void operator()() {
		counting_sort();
	}
private:
	vector<int>A{ 0,6,0,2,0,1,3,4,6,1 };
	void print_v(vector<int>&v) {
		for (size_t i = 1; i != v.size(); ++i)
			cout << i << "\t";
		cout << endl;
		print_vector(v);
	}
	void print_vc(vector<int>&v) {
		for (size_t i = 0; i < v.size(); ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : v)
			cout << i << '\t';
		cout << "\n" << endl;
	}
	void counting_sort() {
		vector<int>C(7, 0);
		cout << "原始C中的元素为:" << endl;
		print_vc(C);
		vector<int>B(A.size() , 0);
		cout << "原始B中的元素为:" << endl;
		print_v(B);
		for (size_t i = 1; i != A.size(); ++i)
			++C[A[i]];
		cout << "完成计数后的C中元素为:" << endl;
		print_vc(C);
		for (size_t i = 1; i != C.size(); ++i)
			C[i] += C[i - 1];
		cout << "完成统计计数后的C中的元素为:" << endl;
		print_vc(C);
		for (size_t i = A.size() - 1; i != 0; --i) {//递减循环是维持计数排序稳定的关键
			B[C[A[i]]] = A[i];
			--C[A[i]];
			cout << "输出到B中的过程..." << endl;
			print_v(B);
		}
	}
};
////////////////////////////////////////////////
class countingSort {//将计数排序一般化，可以处理任意范围内的数值，包括负值，当然不能溢出
public:
	countingSort(vector<int>&target):target_vect(target){}
	void operator()(bool flag=true);//排序后要不要改变原数组的值，默认改变
private:
	pair<int, int>find_min_max();//找到最大值和最小值
	void init();//初始化处理vector
	vector<int>&target_vect;//目标vector引用
	vector<int>counter;//计数
	vector<int>temp_order;//排序后的临时数组
	int differ_zero;//differ_zero+min=0,使计数排序一般化的关键点
};
inline
pair<int, int>countingSort::find_min_max() {
	int max = target_vect[0];
	int min = target_vect[0];
	for (size_t i = 0; i != target_vect.size(); ++i)
		if (min > target_vect[i])
			min = target_vect[i];
		else if (max < target_vect[i])
			max = target_vect[i];
	return{ min,max };
}
inline
void countingSort::init() {
	pair<int, int>temp_pair{ find_min_max() };
	size_t differ = temp_pair.second - temp_pair.first + 1;
	if (differ > target_vect.size()*log(target_vect.size()) / log(2))
		cerr << "警告，数组太稀疏，计数排序时间复杂度可能超过Θ(nlgn)，空间浪费巨大" << endl;
	differ_zero = -temp_pair.first;
	counter.assign(temp_pair.second+differ_zero+1, 0);
	temp_order.assign(target_vect.size(), 0);
}
inline 
void countingSort::operator()(bool flag) {
	find_min_max();
	init();
	for (size_t i = 0; i != target_vect.size(); ++i)
		++counter[target_vect[i] + differ_zero];
	for (size_t i = 1; i != counter.size(); ++i)
		counter[i] += counter[i - 1];
	for (size_t i = target_vect.size() - 1; i != -1; --counter[target_vect[i] + differ_zero],--i)
		temp_order[counter[target_vect[i] + differ_zero]-1]= target_vect[i];
	if (flag)
		for (size_t i = 0; i != temp_order.size(); ++i)
			target_vect[i] = temp_order[i];
	temp_order.~vector<int>();//释放内存，下同
	counter.~vector<int>();
}
/////////////////////////////////////////

class solution8_2_2 {
public:
	void operator()() {
		cout << "第10行递减循环变量，使得原数组相同元素后面的元素先出现，而C[A[j]]存储的是相同元素排序后未输出 \n"
			<< "下标的最大值，所以根据原来的顺序，相同元素最后一个元素首先输出到排序后最后一个元素的相同位置 \n"
			<< "最靠前的元素最后被输出到正确位置"
			<< endl;
	}
};

class solution8_2_3 {
public:
	void operator()() {
		cout << "如上题所言，相同元素的最前面的一个元素被放在的本应是最后一个元素的位置，因为是相同元素，所以排序是 \n"
			<< "正确的，但是没有稳定性"
			<< endl;
	}
};
class solution8_2_4 {
public:
	void operator()() {
		cout << "在第9行插入counter_a_to_b=C[b]-C[a-1]"
			<< endl;
	}
};

class solution8_3_1 {
public:
	void operator()() {
		radix_sort();
		for (auto &i : vect) {
			for (auto &j : i)
				cout << j << "\t";
			cout << endl;
		}
	}
private:
	vector<vector<string>>vect{ {"COW"},{"DOG"},{"SEA"},{"RUG"},{"ROW"},{"MOB"},{"BOX"},{"TAB"},{"BAR"},{"EAR"},
	{"TAR"},{ "DIG" },{ "BIG"},{ "TEA"},{ "NOW"},{ "FOX"} };
	void countingSort(size_t n) {
		vector<size_t>counter('Z' + 1, 0);
		vector<string>temp(vect.size());
		for (size_t i = 0; i != vect.size(); ++i)
			++counter[vect[i].back()[n]];
		for (size_t i = 1; i != counter.size(); ++i)
			counter[i] += counter[i - 1];
		for (size_t i = vect.size() - 1; i != -1; --i) {
			temp[counter[vect[i].back()[n]]-1] = vect[i].back();
			--counter[vect[i].back()[n]];
		}
		for (size_t i = 0; i != temp.size(); ++i)
			vect[i].push_back(temp[i]);
	}
	void radix_sort() {
		for (size_t i = 2; i != -1; --i)
			countingSort(i);
	}
};

class solution8_3_2 {
public:
	void operator()() {
		cout << "插入排序和归并排序是稳定的，归并排序当两个元素相等时让左边的元素输出即可 \n"
			<<"排序开始时将相同元素的和其相对下标扫描一遍存入pair，然后对元素排序 \n"
			<<"排序完成后，再扫描一遍数组，对相同元素重新排列，时间和空间都花费Θ(n)"
			<< endl;
	}
};

class solution8_3_3 {
public:
	void operator()() {
		cout << "对于n个b位r进制数来说 \n"
			<< "初始：对第一位已经排序 \n"
			<< "对已经排好第k位数来说，要排好共k+1位数，只需要在原来的基础上稳定重新排列第k+1位，证明如下 \n"
			<< "假设排好第k位后的(k位数)序列为a1，a2.....an,对于任意i<j,ai<=aj,若k+1位排序后生成的序列为 c1,c2...cn \n"
			<< "假设ai与aj对应的第k+1位为cm，cn，1.若m<n,也就是说ai对应的共k+1位数小于aj的, \n"
			<< "容易看出 cm*b^k+ai<=cn*b^k+aj,如对于10进制数321,432，ai=21,aj=32,cm=3,cn=4,显然321<432 \n"
			<< "2.若m>n,也就是说ai对应的共k+1位数大于于aj的，cm*b^k+ai>=cn*b^k+aj \n"
			<< "521,432,ai=21,aj=32,cm=5,cn=4,显然521>432,虽然21<32 \n"
			<< "3.m=n,情况分析与第种一样，不同之处在于对稳定性的依赖，由于m=n,对于不稳定排序来说，可能会把 \n"
			<< "m对应的元素放在放在n的后边，此时会产生错误，如521,532，m=n=5,很显然532不小于521"
			<< endl;
	}
};
class solution8_3_4 {
public:
	void operator()(){
		radix_sort();
		for (auto i : vect)
			cout << i << "\t";
		cout << endl;
	}
private:
	vector<int>vect{ 32,121,0,332,64,887,876,779,12,9 };
	size_t pow(size_t e, size_t n) {
		if (!n)
			return 1;
		while (n-1) {
			e *= e;
			--n;
		}
		return e;
	}
	size_t get(size_t value,size_t n) {
		size_t k=pow(10, n);
		value %= k;
		k = pow(10, n - 1);
		return value / k;
	}
	void countingSort(vector<pair<size_t,int>>&v) {
		vector<int>counter(10, 0);
		vector<int>temp(v.size());
		for (size_t i = 0; i != v.size(); ++i)
			++counter[v[i].first];
		for (size_t i = 1; i != 10; ++i)
			counter[i] += counter[i - 1];
		for (size_t i = 9; i != -1; --i) {
			temp[counter[v[i].first]-1] = v[i].second;
			--counter[v[i].first];
		}
		for (size_t i = 0; i != v.size(); ++i)
			v[i].second = temp[i];
	}
	void radix_sort() {
		vector<pair<size_t, int>>v(vect.size());
		for (size_t i = 0; i != vect.size(); ++i) //将值装进特定容器中
			v[i].second = vect[i];
		for (size_t i = 1; i != 4; ++i) {//对个十百位分别计数排序
			for (size_t j = 0; j != vect.size(); ++j)
				v[j].first = get(v[j].second, i);//获取个十百位的值
			countingSort(v);
		}
		for (size_t i = 0; i != vect.size(); ++i)//将排序后的值存入原数组
			vect[i] = v[i].second;
	}
};

class solution8_3_5 {
public:
	void operator()() {
		cout << "需要9*10^(d-1)轮排序，记录的堆数也是这么多，对于3位数来说，百位有9种数字，十位和个位都有10种 "
			<< endl;
	}
};

class solution8_4_1 {
public:
	void operator()(){
		bucket_sort();
		cout << "\n" << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << endl;
	}
private:
	vector<double>vect{ 0.79,0.13,0.16,0.64,0.39,0.20,0.89,0.53,0.71,0.42 };
	void insert_sort(list<double>&lt) {
		for (auto iter1 = ++lt.begin(); iter1 != lt.end(); ++iter1) {
			double key = *iter1;
			auto temp = iter1;
			auto iter2 = --temp;
			for (; iter2 !=lt.begin() && *iter2 > key; --iter2) {
				auto temp_iter = iter2;
				++temp_iter;
				*temp_iter = *iter2;
			}
			if (iter2 == lt.begin() && *iter2 > key) {
				auto temp_iter = iter2;
				++temp_iter;
				*temp_iter = *iter2;
			}
			else
				*(++iter2) = key;
		}
	}
	void bucket_sort() {
		vector<list<double>>vtr(vect.size());
		for (size_t i = 0; i != vect.size(); ++i)
			vtr[static_cast<size_t>(vect.size()*vect[i])].push_back(vect[i]);
		size_t n = 0;
		for (auto &i : vtr) {
			cout << n++;
			for (auto j : i)
				cout << "→" << j ;
			cout << endl;
		}
		for (auto &i : vtr)
			if (i.size() >= 2)
				insert_sort(i);
		n = 0;
		for (auto &i : vtr)
			if (!i.empty())
				for (auto j : i)
					vect[n++] = j;
	}	
};

class solution8_4_2 {
public:
	void operator()() {
		cout << "当所有元素都进入一个桶时为最坏情况，插入排序替换成其它Θ(nlgn)的排序算法，如快排和归并"
			<< endl;
	}
};

class solution8_4_3 {
public:
	void operator()() {
		cout << "E[X^2]=0^2*1/4+1^2*1/4*2+2^2*1/4=3/2,E^2[X]=1^2=1"
			<< endl;
	}
};

class solution8_4_4 {
public:
	void operator()() {
		bucket_sort();
	}
private:
	typedef double point;
	typedef double distance;
	vector<pair<point, point>>vect{ {0.21,0.33},{-0.31,0.21} ,{0.19,0.96},{0.98,0.10},
	{-0.11,0.99}, {0.56,0.77},{0.31,0.42},{0.8,0.4},{-0.78,-0.44},{0.77,-0.34},{0.22,-0.23},
	{0.21,0.11},{-0.5,-0.76} };
	distance getDistance(point x, point y) {//计算点的到原点的距离
		return
			sqrt(x*x + y*y);
	}
	void insert_sort(vector<pair<distance,size_t>>&v) {
		for (size_t i = 1; i != v.size(); ++i) {
			distance key = v[i].first;
			size_t j = i;
			for (; j != 0 && key < v[j-1].first; --j)
				v[j] = v[j-1];
			v[j].first = key;
		}
	}
	void bucket_sort() {
		vector<vector<pair<distance,size_t>>>v_distance(vect.size());	//轻重pair.first为距离，pair.second为距离对应点	
		for (size_t i = 0; i != vect.size(); ++i) {//的下标
			distance dis = getDistance(vect[i].first, vect[i].second);
			v_distance[static_cast<size_t>(dis*vect.size())].push_back(make_pair(dis, i));
		}
		for (size_t i = 0; i != v_distance.size() && v_distance[i].size() >= 2; ++i)
			insert_sort(v_distance[i]);
		size_t n = 0;
		vector<pair<point, point>>temp(vect.size());
		for (auto &i : v_distance)
			if (!i.empty()) {//虽然这里有两个循环，但运行时间仍然是Θ(n)
				for (size_t m = 0; m != i.size(); ++m) {
					temp[n++] = vect[i[m].second];
					cout << "(" << vect[i[m].second].first << "," << vect[i[m].second].second << ")"
						<< "\t" << i[m].first << endl;
				}
			}
		n = 0;
		for (auto &i : temp)
			vect[n++] = i;
	}
};

class solution8_4_5 {
public:
	void operator()() {
		cout << "连续性随机变量的概率密度函数f(x),概率分布函数F(X)=P(X<=x)=∫f(x)dx,积分区间为(-∞，x) \n"
			<< "∫f(x)dx=1,其中积分区间为(-∞，∞),显然满足桶排序的要求"
			<< endl;
	}
};

//思考题

class solution8_1 {
public:
	void operator()() {
		cout << "a.叶节点是元素下标的一个顺序，对于任一种输入，只有一个叶节点预制对应，其它的叶节点这不会到达 \n"
			<< "概率为0，因为输入是随机的且共有n！种可能输入，所以概率为1/(n!) \n"
			<< "b.D(T)等于左子树和右子树的叶节点到根节点的路径总长度 \n"
			<< "D(LT)等于左子树叶节点到左子树根节点的的路径总长,对于每一节点到左子树根节点的距离总长比到原先根节点 \n"
			<< "少1，D(RT)同理，一共有k个节点，所以D(T)=D(LT)+D(RT)+k \n"
			<< "c.d(k)=min{D(T)}=min{D(i)+D(k-i)+k},其中T代表有k个叶节点的决策树。而显然 \n"
			<< "min{D(i)+D(k-i)+k}=min{d(i)+d(k-i)+k} \n"
			<< "d.假设在i=k/2+x,-k/2<=x<=k/2,处取得最大值，代入化简得k/2lg(k^2/4-x^2)+xlg((1+4/(k/x-2))) \n"
			<< "当x<0时的值和x>0时的值都小于x=0时的值，具体分析太多不写 \n"
			<< "对于有k个叶节点的数最多有┍lgk┑深，┍lgk┑<=lgk+1所以d(i)+d(k-i)<=i(lgi+1)+(k-i)(lg(k-i)+1) \n"
			<< "=ilgi+(k-i)lg(k-i)+k<=klgk+k,d(k)=Ω(klgk) \n"
			<< "e.对于规模为n的输入有n!个叶节点，代入上式得证，D(T)为叶节点路径总长，一共有n!个叶节点，所以 \n"
			<< "平均为Ω(n!lgn!)/n!=Ω(lgn!)=Ω(nlgn) \n"
			<< "f.没太理解题目，下面是一位外国小哥的答案,不保证正确 \n"
			<< "A deterministic algorithm A corresponding to B would be one that has made its 'random' choices \n"
			<< "in advance. To construct it we just remove the randomized nodes by replacing them  \n"
			<< "by a child we pick. The new result is a subtree (in respect to the non-randomized nodes) and \n"
			<< "its number of choices is less than or equal to the one of the randomized algorithm.\n"
			<< "Since any subtree we pick is Ω(nlgn), this implies that B is Ω(nlgn)."
			<< endl;
	}
};

class solution8_2 {
public:
	void operator()() {
		cout << "a.b.c.下面给出了符合abc三个题目提议的算法 \n"
			<< "d.看了这一题发现abc不能同时满足三个条件，只有小题a的算法可行，因为radix_sort 的子算法必须是稳定的 \n"
			<<"如果子算法的时间超不为O(n),则不满足条件O(bn) \n"
			<<"e.不稳定，见注释"
			<< endl;
		partition_sort();
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;

		countingSort_();
		for (auto i : vt)
			cout << i << "\t";
		cout << "\n" << endl;		
	}
private:
	vector<int>vect{ 0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1 };
	vector<int>vt{ 32,12,5,2,23,11,35,32,5,11,12 };
	void partition_sort() {
		size_t i = -1;
		for(size_t j=0;j!=vect.size();++j)
			if (!vect[j]) {
				++i;
				swap(vect[i], vect[j]);
			}
	}
	void countingSort_() {
		vector<size_t>counter(36, 0);//最大数值为35
		for (auto i : vt)
			++counter[i];
		size_t n = 0;
		for (size_t i = 0; i != 36; ++i)//counter[i]对应i在vt中的个数
			for (size_t j = 1; j <= counter[i]; ++j)
				vt[n++] = i;//可以看到最后的赋值完全来自实数i，与原数组vt的值无关，所以谈不上稳定
	}//这个算法只能用在纯粹的排序上，不能用来排序含有卫星数据的对象
};

class solution8_3 {
public:
	void operator()() {
		cout << "a.这个算法在前面我已经写过，就是对缺位补0的计数排序 \n"
			<< "b.同理可以对缺位补0，字母的比较也是转换成ASCLL码也就是大于0的数字的计数排序"
			<< endl;
		radix_sort();
		for (auto i : vect)
			cout << i << endl;
		cout << "\n" << endl;
	}
private:
	vector<string>vect{ "VB","MOU","WC","VC","B","JIE","A","BC","QIN","NIGHT","C","PYTHON","MATLAB" };
	void counting_sort(vector<pair<size_t,string>>&vp) {	//计数排序
		vector<size_t>counter('Z' + 1, 0);
		for (auto i : vp)
			++counter[i.first];
		for (size_t i = 1; i != counter.size(); ++i)
			counter[i] += counter[i - 1];
		vector<string>order(vp.size());//用来存放计数排序后字符串
		for (size_t i = vp.size() - 1; i != -1; --i) {
			order[counter[vp[i].first] - 1] = vp[i].second;
			--counter[vp[i].first];
		}
		for (size_t i = 0; i != vp.size(); ++i)//将vp中的字符串重新排序
			vp[i].second = order[i];
	}
	void radix_sort() {
		vector<pair<size_t, string>>vp(vect.size());//first存放某个字符串的某位字符，缺少则补0
		for (size_t i = 0; i != vect.size(); ++i)//初始化vp内容
			vp[i].second = vect[i];
	
		for (size_t i = 5; i != -1; --i) {
			for (auto &j : vp)
				if (j.second.size() < i+1)
					j.first = 0;
				else
					j.first = j.second[i];
			counting_sort(vp);
		}
		for (size_t i = 0; i != vp.size(); ++i)//改变原目标位置的字符串顺序
			vect[i] = vp[i].second;
	}
};

class solution8_4 {
public:
	void operator()() {
		cout << "a.选择一个红水壶在蓝水壶中查找，知道找到一个匹配的为止，重复这一过程直到完成所有匹配 \n"
			<< "b.如果用比较算法，最后的红水壶和蓝水壶必然都有序，n个有序问题的下界为Ω(nlgn),2Ω(nlgn)=Ω(nlgn) \n"
			<< "c.用类似于快排的方法，选取一个红水壶，将容量小于这个水壶的放在左边，否则放着右边，用和这个水壶 \n"
			<< "相同容量的蓝色水壶用同样的方法去划分红水壶，依次递归，递归式为T(n)=T(an)+T(n(1-a)+cn \n"
			<< "根据课本前面的分析可知递归式的期望趋向于好的情况为O(nlgn),最好情况为Θ(n^2)"
			<< endl;
	}
};
 
class solution8_5 {
public:
	void operator()() {
		cout << "a.k=1代入公式得A[i]<=A[i+1],即非递减排序 \n"
			<< "b.2,1,3,5,4,7,6,8,10,9 \n"
			<< "c.原不等式左边=A[i]+∑A[j](j=i+1...i+k-1),右边=∑A[j](j=i+1...i+k-1)+A[i+k] \n"
			<< "所以A[i]<=A[i+k] \n"
			<< "d.将i=1...k起头共k个，数列B[j]=i+k*j,j=1,2,3...r,且B[j]max<=A[n],分成k组，例如b中的二分列数 \n"
			<< "分为2,3,5,7,8,9和1,5,7,8,10两组。每组有n/k个数，运用nlgn的排序算法排序时间为n/k(nlg(n/k)) \n"
			<< "因为一共有k组，所以总的运行时间为Θ(nlg(n/k)) \n"
			<< "e.参看solution6_5_9 \n"
			<< "f.对于d中的Θ(nlg(n/k))=Θ(nlgn-nlgk),因为k为常数，所以原式Ω(nlgn)"
			<< endl;
	}
};

class solution8_6 {
public:
	void operator()() {
		cout << "a.C(2n,n) \n"
			<< "b."
			<< endl;/////////
	}
};
#endif //_SOLUTION_8_H_
