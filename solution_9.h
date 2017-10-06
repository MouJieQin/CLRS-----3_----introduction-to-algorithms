#pragma once
#ifndef	_SOLUTION_9_H_
#define _SOLUTION_9_H_
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<memory>
using namespace std;

class solution9_1_1 {
public:
	void operator()() {
		cout << "每两个一起比较，将较小的元素挑出来作为下次循环迭代的输入，在下一次迭代之前的输出都是树的一层 \n"
			<< "且节点数量减少约两倍，直到最后为1达到根节点，也就是最小值，容易验证一共进行了n-1次比较 \n"
			<< "而最小值一定与第二小的值进行了比较，所以可以迭代查看，具体做法如下 : \n"
			<< "1.将要排序元素制成数节点，有左右指针和元素并存入容器vector，最开始的左右指针都是空指针 \n"
			<< "2.将容器中的元素分成[0,1],[2,3],[4,5]...两两一组，将较小的元素创造一个节点，左指针指向较小元素的 \n"
			<< "的节点，右指针指向较大元素，如对于节点9和3，以3为元素制造一个节点，该节点左指针指向之前的3节点 \n"
			<< "右指针指向9节点，每扫描一小组都将新产生的节点存入另一个容器，直到扫描完所有小组 \n"
			<< "3，将新容器作为步骤2的输入，迭代直到容器size()为1，我的程序并没有使用迭代 \n"
			<< "详细见下面注释"
			<< endl;
		find_second();
	}
private:
	struct node {//树节点，其中key=left_min
		node(int part, const shared_ptr<node>&left = nullptr, const shared_ptr<node>&right = nullptr) :key(part), left_min(left), right_max(right) {}
		int key;
		shared_ptr<node>left_min;
		shared_ptr<node>right_max;
	};
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,
		72,73,174,76,77,81,82,83,272,90,91,95,101,105,140,111,112,204,124,189,271,132,245,74,
		7,123,139,231,136,144,172,153,293,116,141,164,275,39,135,177,127,186,165,296,197,157,163,59,
		138,211,213,65,248,279,192,255,108,252,147,223,285,286,214,222,200,268,199,297,159,276,224,270,
		137,288,249,184,292,254 };//测试数组

	shared_ptr<node>root_min_ptr;//最后根节点的指针，存放了最小值
	unsigned int counter_compare=0;//用来计数一共比较了多少次
	void find_second() {
		vector<shared_ptr<node>>tmp;
		for (size_t i = 0; i != vect.size(); ++i)
			tmp.push_back(shared_ptr<node>(new node(vect[i])));//构造最开始的树节点，此时左右指针为空指针		
		subFind(tmp);//见定义注释

		cout << "最小元素是 " << root_min_ptr->key << endl;
		cout << "第二小的元素是 " << second_min(root_min_ptr) << endl;
		cout << "一共进行了 " << counter_compare << " 次比较" << endl;
		//下面用来计算理论比较次数
		cout << " n= " << vect.size() << "\n n+lgn-2= " << vect.size() + log(vect.size()) / log(2) - 2 << endl;
	}
	void subFind(vector < shared_ptr<node>>&temp) {	
		
		while (true) {
			vector<shared_ptr<node>>tmp;//为下次输入构造的新容器
			for (auto &i : temp)
				cout << i->key << "\t";
			cout << endl;
			if (temp.size() & 1) {//如果输入数据大小为奇数则1，2...n-1分组，最后一个元素最后push进去
				for (size_t i = 0; i != temp.size() - 1;++counter_compare, i += 2)//counter_compare计数
					if (temp[i]->key < temp[i + 1]->key)
						tmp.push_back(shared_ptr<node>(new node(temp[i]->key, temp[i], temp[i + 1])));
					else
						tmp.push_back(shared_ptr<node>(new node(temp[i+1]->key, temp[i + 1], temp[i])));
				tmp.push_back(temp.back());
			}
			else {//偶数处理
				for (size_t i = 0; i != temp.size(); ++counter_compare, i += 2)
					if (temp[i]->key < temp[i + 1]->key)
						tmp.push_back(shared_ptr<node>(new node(temp[i]->key, temp[i], temp[i + 1])));
					else
						tmp.push_back(shared_ptr<node>(new node(temp[i + 1]->key, temp[i + 1], temp[i])));
			}		
			if (tmp.size() == 1) {//如果到达根节点记录根节点的指针并退出
				root_min_ptr = tmp.front();
				break;
			}
			temp.swap(tmp);//交换新数组作为下次输入，迭代改循环的关键
		} 
	}
	int second_min(shared_ptr<node>&ptr) {//找第二小的值
		auto left = ptr->left_min;
		auto right = ptr->right_max;
		int sec_min =right->key;//记录第二小的值
		while (left->right_max) {
			int temp = left->right_max->key;
			if (temp < sec_min)
				sec_min = temp;
			++counter_compare;
			left = left->left_min;
		}
		return sec_min;
	}
};
class solution9_1_2 {
public:
	void operator()() {
		cout << "当n为偶数时,两两一组比较一共进行了n/2次比较，产生了n/2对元素，其中较小的数组存入数组A,较大的存入 \n"
			<< "数组B,取min等于A[1],一共进行n/2-1次比较得到最小值，B数组同理，所以一共进行了n/2+(n/2-1)*2=3n/2-2 次"
			<< "比较,当n为奇数时同理"
			<< endl;
	}
};
class solution9_2_1 {
public:
	void operator()() {
		cout << "书上第120面的程序和后面的解释对不起来，程序第3行randomized_partition函数返回的是绝对下标 \n"
			<< "如果它使用的是快排里面的那个，也就是q所对应的元素在原数组中真正对应的第q个顺序统计量，而不是 \n"
			<< "相对子数组A[p,r]的顺序统计量，如下是我自己写的程序. \n"
			<<"当然书中的程序也是正确的，对这题也是按书上的程序来分析 \n"
			<<"程序最开始必定有1<=p<=i<=r，如果p=r,第2行会返回，如果继续执行，p<r,第3行p<=q<=r,1<=k<=r-p+1, \n"
			<<"可能产生对0长度的数组递归的为第8行和第9行，如果第8行产生0长度数组，也就是q-1<p,则q=p,此时k=1 \n"
			<<"而if条件却是i<k=1,是不可能发生的，对第9行，q+1>r,q=r,k=r-p+1，i>k也是不可能的,因为这里的q是相对 \n"
			<<"子数组的坐标"
			<< endl;
		const size_t i = 3;
		cout <<"第 "<<i<<" 个顺序统计量为 "
			<<randomized_select(1, vect.size() - 1, i) << endl;
	}
private:
	vector<int>vect{ 0,3,2,9,7,5,4,8,6,1 };//vect[0]不在顺序统计量的范围内,即有效数字为1,2,3,4,5,6,7,8,9
	size_t partition(size_t p, size_t r) {
		int key = vect[r];
		size_t i = p - 1;
		for (size_t j = p; j != r; ++j)
			if (vect[j] <= key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[r], vect[i + 1]);
		return i + 1;
	}
	size_t randomized_partition(size_t p,size_t r) {
		srand(static_cast<unsigned int>(time(0)));
		size_t i = p+rand()%(r-p+1);
		swap(vect[i], vect[r]);
		return
			partition(p, r);
	}
	int randomized_select(size_t p, size_t r, size_t i) {
		if (p == r)
			return vect[i];
		size_t q = randomized_partition(p, r);
		if (i == q)
			return vect[q];
		else if (i < q)
			return
			randomized_select(p, q - 1, i);
		else
			return
			randomized_select(q + 1, r, i);
	}
};

class solution9_2_2 {
public:
	void operator()() {
		cout << "无论k为何值，总存在一个T(max(k-1,n-k))"
			<< endl;
	}
};

class solution9_2_3 {
public:
	void operator()() {
		const size_t i = 5;
		cout << endl;
		cout << "第 " << i << " 个顺序统计量为 "
			<< randomized_select(1, vect.size() - 1, i) << endl;
	}
private:
	vector<int>vect{ 0,3,2,9,7,5,4,8,6,1 };
	size_t partition(size_t p, size_t r) {
		int key = vect[r];
		size_t i = p - 1;
		for (size_t j = p; j != r; ++j)
			if (vect[j] <= key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[r], vect[i + 1]);
		return i + 1;
	}
	size_t randomized_partition(size_t p, size_t r) {
		srand(static_cast<unsigned int>(time(0)));
		size_t i = p + rand() % (r - p + 1);
		swap(vect[i], vect[r]);
		return
			partition(p, r);
	}
	int randomized_select(size_t p, size_t r, size_t i) {
		while (p < r) {
			size_t q = randomized_partition(p, r);
			if (q == i)
				return vect[q];
			else if (i < q)
				r = q - 1;
			else
				p = q - 1;
		}	
		return vect[p];
	}
};
class solution9_2_4 {
public:
	void operator()() {
		cout << "q依次等于9,8,7,6,5,4,3,2,1,0"
			<< endl;
	}
};

class solution9_3_1 {
public:
	void operator()() {
		cout << "1,2,4要O(n)的时间，3对n/7个元素递归调用要T(n/7),至少有4*(1/2(n/7)-2)=2n/7-8个元素大于x，有 \n"
			<< "2n/7-8个元素小于x，第5步至多需要T(5n/7+8),T(n)=T(n/7)+T(5n/7+8)+an, \n"
			<< "要证明T(n)<=cn,T(n)<=cn/7+5cn/7+8c+an=cn+(-cn/7+8c+an),-cn/7+8c+an<=0,当n>2*56,c>14成立 \n"
			<< "若每组3个元素，T(n)=T(n/3)+T(2n/3+4)+an=T(n/3)+T(2n/3)+an,递归树求解，最少有log(3,n)层， \n"
			<< "注意到n/3+2n/3等于n，所以每层耗费an，T(n)>=cnlgn,所以不是线性的"
			<< endl;
	}
};

class solution9_3_2 {
public:
	void operator()() {
		cout << "一共被划分成n/5组，所以有n/5个中位数，除去x所在的小组和成员少于5的一个小组，\n"
			<< "其中有一半1/2*n/5再减去2个中位数是小于中位数的中位数x的， \n"
			<< "而对于这些1/2*n/5-2个中位数假设其中一个为y所在的5个一组中，\n"
			<< "有2位假设其中一个为z是小于其中位数的，所有z<y<x,所以小于中位数的一共有(1+2)*(1/2*n/5-2) \n"
			<< "=3n/10-6>n/4,大于中位数的中位数的个数同理有3n/10-6>n/4，至于剩下的4n/10+12个数是无法 \n"
			<< "通过不等式的传递性得到其与x的大小关系的，如果第5步检测到i<k,则递归检测小于x的3n/10-6加上 \n"
			<< "不能确定关系的4n/10+12共7n/10+6个数，大于同理也是这么多"
			<< endl;
	}
};

class solution9_3_3 {
public:
	void operator()() {
		cout << "可以利用这一节的线性查找方法花费Θ(n)查找n个规模的中位数,这样就能保证最好的划分花费 \n "
			<< "Θ(n)+Θ(nlgn)=Θ(nlgn)"
			<< endl;
	}
};
//////////////////////////////////////////////////////
class select {//按照书中的select递归找到的中位数，经测试找到的中位数并不是中位数的中位数
public:
	void operator()() {
		cout <<"select()测试的值为"<<getMid(vect) << endl;
		
	}
private:
	bool flag = true;
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71,
		72,73,174,76,77,81,82,83,272,90,91,95,101,105,140,111,112,204,124,189,271,132,245,74,
		7,123,139,231,136,144,172,153,293,116,141,164,275,39,135,177,127,186,165,296,197,157,163,59,
		138,211,213,65,248,279,192,255,108,252,147,223,285,286,214,222,200,268,199,297,159,276,224,270,
		137,288,249,184,292,254 };
	void bubble_sort(vector<int>&v) {
		if (v.empty())
			return;
		for (size_t i = v.size() - 1; i != 0; --i) {
			for (size_t j = 0; j != i; ++j)
				if (v[j + 1] < v[j])
					swap(v[j + 1], v[j]);
		}
	}
	int getMid(vector<int>&vc) {
	/*	for (auto i : vc)
			cout << i << "\t";
		cout << endl;
		cout << endl;*/
		if (vc.size() == 1)
			return vc[0];
		vector<vector<int>>vv(vc.size()/5+1);
		vector<int>temp;
		for (size_t i = 0; i != vc.size(); ++i) 
			vv[i / 5].push_back(vc[i]);
		for (size_t i = 0; i != vv.size(); ++i) {
			bubble_sort(vv[i]);
			for (auto j : vv[i])
				cout << j<< "\t";
			cout << endl;
		}
		
		cout<<"\n----------------------------------"<< endl;
		for (size_t i = 0; i != vv.size(); ++i)
			if(!vv[i].empty())
				temp.push_back(vv[i][(vv[i].size()-1) / 2]);
		if (flag) {
			flag = false;
		    vector<int>real(temp);
			sort(real.begin(), real.end());
			for (auto i : real)
				cout << i << "\t";
			cout << "\n" << endl;
			cout << "真正的中位数的中位数为 " << real[(real.size() - 1) / 2] << endl;
		}
		return getMid(temp);
	}
};
///////////////////////////////////////////////////////////////////////
class solution9_3_4 {
public:
	void operator()() {

	}
};
class solution9_3_5 {
public:
	void operator()() {
		cout << "将9.2节程序的第3行的q值赋予线性时间查找出来的中位数的下标，这样就能保证T(n)=T(n/2)+Θ(n)，T(n)=Θ(n)"
			<< endl;
	}
};

class solution9_3_6 {
public:
	void operator()() {
		cout << "这一题翻译浪费了我很多时间，通过我在网络上的查询，我对k分位数的理解是，把n个数分成k个等大小集合，除去最后一个集合\n"
			<< "每个集合的最大值，因为最后一个集合的最大值必定是原集合的最大值，不具备划分作用。例如： \n"
			<< "4,11,9,13,14,6,1,7,8,15,2,5,10,3,12 ,排序后是1,2,3,|4,5,6,|7,8,9,|10,11,12,|13,14,15 \n"
			<< "分成5份，5-1=4个k分位数为3,6,9,12 \n"
			<< "算法思路是要找到(beg,end,k)beg到end范围内的k分位数，可以先找到第k/2分位数，这个数有一个下标index,\n"
			<< "然后递归查找(beg,index-1,k/2)和（index+1,end,k/2)，当然这并不完全准确，还要看k的奇偶性,详情见程序\n"
			<< "T(n,k)表示在n个数里找到k个分位数，算法的递归式是 \n"
			<< "T(n,k)=T(n/2,k/2)+T(n/2,k/2)+cn,可以用递归树求解，每一层花费cn,直到k=1,所以有lgk层，所以O(nlgk) \n"
			<< "比如要找1...15的5分位数，先找到分位数6花费15，然后在1...5里找4花费5，在7...15里找9,12花费9,9+4=14约为15 \n"
			<<"但是其中的常数非常大，如果你运行这个程序会发现，排序都比它快，我的笔记本要十几秒才能得到结果\n"
			<<"并不是所有的序列都有k分位数，比如这个程序测试的序列有98个，对于k=16,如果每个集合6个元素，会多出2个元素就有17个序列 \n"
			<<"如果每个集合7个元素，前15个集合就需要105个元素，\n"
			<< endl;

		const size_t k = 17;//设置k值
		factory_find_k(0, vect.size() - 1, k);//查找k分位数并将k-1个顺序统计量存入vect_k
		cout << "这个是按程序查找顺序找到的k分位数" << endl;
		for (auto i : vect_k)
			cout << i << "\t";
		cout << endl;
		sort(vect_k.begin(), vect_k.end());
		cout << "下面是为了方便测试程序是否正确而排序后的k分位数" << endl;
		for (auto i : vect_k)
			cout << i << "\t";
		cout <<endl;

		auto n = vect.size();
		size_t dif = n%k ? (n + k - n%k) / k : n / k;//在这个函数里是为了分段
		cout << "下面是k分位数查找程序运行完后的序列，可以看到可能并不是完全有序" << endl;
		size_t rows = 0;//记录行数
		for (auto i = 0; i != vect.size(); ++i) {
			cout << vect[i] << "\t";
			if (!((i + 1) % dif)) {
				cout << "\t\t" << ++rows << "行" << endl;
				cout << "\n";
			}
		}
		cout << "\n" << "-------------------------------" << endl;
		for (int i = 1; i != vect.size(); ++i) {//插入排序
			int key = vect[i];
			int j = i;
			for (; i != 0 && key < vect[j - 1]; --j)
				vect[j] = vect[j - 1];
			vect[j] = key;
		}
		cout << "下面是排序完成后的序列" << endl;
		
		for (auto i = 0,rows = 0; i != vect.size(); ++i) {
			cout << vect[i] << "\t";
			if (!((i + 1) % dif)) {
				cout << "\t\t" << ++rows << "行" << endl;
				cout << "\n";
			}
		}
		cout << endl;
	}	
private:
	vector<int>vect{ 71,248,279,192,255,108,252,147,223,//测试序列
		72,73,91,95,101,105,140,111,112,204,124,189,271,132,245,74,138,211,213,65,285,286,214,222,200,
		7,123,139,231,136,144,172,156,206,11,14,15,19,26,27,31,34,89,44,293,116,186,165,296,197,157,163,59,
		268,199,297,159,276,224,270,174,76,77,81,82,83,272,90,53,56,57,228,61,64,253,70,
		137,288,249,184,292,254,141,164,275,39,135,177,127, };
//	vector<int>vect{ 4,11,9,13,14,6,1,7,8,15,2,5,10,3,12 };
	vector<int>vect_k;
	size_t partition(size_t beg, size_t end) {
		size_t i = beg - 1;
		int key = vect[end];
		for(size_t j=beg;j!=end;++j)
			if (vect[j] < key) {
				++i;
				swap(vect[i], vect[j]);
			}
		swap(vect[end], vect[++i]);
		return i;
	}
	size_t randomized_partition(size_t beg, size_t end) {
	
		srand(static_cast<unsigned int>(time(nullptr)));
		size_t rd = rand() % (end - beg + 1) + beg;
		swap(vect[rd], vect[end]);
		return partition(beg, end);
	}
	void randomized_select(size_t beg, size_t end, size_t k) {//随机查找
		size_t index = randomized_partition(beg, end);
		while (k != index) {
			if (k < index) {
				index = randomized_partition(beg, index - 1);
			}
			else {
				index = randomized_partition(index + 1, end);
			}
		}
	}
	void find_k(size_t beg, size_t end, size_t k,size_t dif) {		
		if (k>0) {
			auto index = beg + dif*((k+1)/ 2) - 1;
			if (index >= vect.size())return;
			randomized_select(beg, end, index);
			vect_k.push_back(vect[index]);
			if (k & 1) {
				find_k(beg,index-1,k/2,dif);
				find_k(index+1,end,k/2,dif);
			}
			else {
				find_k(beg, index - 1, k / 2 - 1, dif);
				find_k(index + 1, end, k / 2, dif);
			}
		}
	}
	void factory_find_k(size_t beg, size_t end, size_t k) {
		size_t n = end - beg + 1;
		size_t dif = n%k ? (n + k - n%k) / k : n / k;
		k = k - 1;
		find_k(beg, end, k, dif);
	}
};

class solution9_3_7 {
public:
	void operator()() {
		cout << "1.先用select找到该集合的中位数花费cn \n"
			<< "2.弄一个pair，second存储集合元素，first存储对应元素和中位数的差的绝对值，花费cn \n"
			<< "3.用select找到first的第k个顺序统计量x花费cn，以x作为主元对pair进行划分花费cn，返回前K个元素花费 \n"
			<< "总时间为O(n),虽然我的分析中用了select，当我的程序中还是用的randomized_select \n"
			<< "原因在于在写这个程序之前我还是对select迭代能找出中位数的中位数存在疑惑，我上面也写了一个测试程序 \n"
			<< "可能是我理解有误。但总体并不妨碍问题的分析"
			<< endl;
		const size_t k = 5;
		find(k);
		cout << "最接近中位数的 " << k << "  个数是" << endl;
		for (auto i : anw)//打印答案
			cout << i << "\t";
		cout << "\n" << endl;

		for (size_t j = vect.size() - 1; j != 0; --j)//冒泡排序
			for (size_t i = 0; i != j; ++i)
				if (vect[i] > vect[i+1])
					swap(vect[i], vect[i+1]);
		cout << "有序排列为" << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	vector<int>vect{ 6,206,11,14,15,19,26,27,31,34,89,44,53,56,57,228,61,64,253,70,71 };
	vector<int>anw;
	size_t partition(vector<int>&vp, size_t beg, size_t end) {
		size_t i = beg - 1;
		int key = vp[end];
		for(size_t j=beg;j!=end;++j)
			if (vp[j] <= key) {
				++i;
				swap(vp[i], vp[j]);
			}
		swap(vp[i+1], vp[end]);
		return i+1;
	}
	int randomized_select(vector<int>&vp,size_t beg,size_t end,size_t k) {
		if (beg == end)
			return vp[beg];
		srand(static_cast<unsigned int>(time(nullptr)));
		size_t rd = beg + (rand() % (end - beg + 1));
		swap(vp[rd], vp[end]);
		size_t n = partition(vp, beg, end);
		if (k == n)
			return vp[n];
		else if (k < n)
			return randomized_select(vp, beg, n - 1,k);
		else
			return randomized_select(vp, n + 1, end,k);
	}
	void find(size_t k) {
		vector<pair<int, int>>vp;
		for (size_t i = 0; i != vect.size(); ++i)
			vp.push_back({0,vect[i]});
		int midian = randomized_select(vect, 0,vect.size()-1,(vect.size() - 1) / 2);
		cout << "中位数是 " << midian << endl;
		for (size_t i = 0; i != vp.size(); ++i) {
			int differ=vp[i].second - midian;
			vp[i].first = differ > 0 ? differ : -differ;
		}
		vector<int>temp;
		for (auto &i : vp)
			temp.push_back(i.first);
		int key_k = randomized_select(temp,0,temp.size()-1, k-1);
		cout << "key_k=    " << key_k << endl;
		size_t i = -1;
		for (size_t j =0; j != vp.size(); ++j)
			if (vp[j].first <= key_k) {
				++i;
				swap(vp[i], vp[j]);
			}
		for (auto &i : vp)
			cout << i.first << "   " << i.second << endl;
		for (size_t j = 0; j != i+1; ++j)
			anw.push_back(vp[j].second);
	}
};

class solution9_3_8 {
public:
	void  operator()() {
		cout << "因为2n个元素必然是偶数，所以中位数要大于等于n-1个元素，小于等于n个元素，用二分法来寻找中位数以 \n"
			<< "充分利用序列已排序的条件。可以先假设中位数在X中，每次看情况对半查找，假设选取的元素下标为mid \n"
			<< "则在X中此元素element大于等于mid个元素，小于n-mid-1个元素注意下标从0开始，所以在Y中， \n"
			<< "element大于等于n-1-mid个元素，也即是element>=Y[Y.size()-1-mid-1],小于n-(n-mid-1)个元素，也即是 \n"
			<< "element<=Y[Y.size()-1-mid-1+1],然后查找中位数是否在Y中"
			<< endl;
		cout <<"clgn的花费的计算的中位数为 "<< factory_find() << endl;
		for (auto i : X)
			Y.push_back(i);
		sort(Y.begin(),Y.end());
		for (auto i : Y)
			cout << i << "\t";
		cout << "\n" << endl;
		cout << "排序计算后的中位数是 " << Y[X.size() - 1] << endl;
	}
private:
//	vector<int>X{ 2,6,8,17,19,29,33,42,45,50,56,59,62,62,68,71,76,80,81,84};
//	vector<int>Y{ 5,12,13,25,32,34,35,41,50,53,63,64,68,71,75,79,85,85,88,89 };
	vector<int>X{ 2,8,20,32,33,35,38,39,63,73,74,86,116,124,127,150,152,155,164,171,174,181,181,187,196,229,
		246,259,266,273,284,297,304,310,313,324,328,337,339,353,360,377,379,383,387,389,392,392,395,399,414,
		414,434,467,485,501,549,560,562,574,575,577,578,587,595,616,617,619,630,638,641,657,667,669,672,674,
		687,720,722,733,755,758,775,788,800,818,834,848,848,848,880,883,897,913,930,944,951,962,973,975 };

	vector<int>Y{ 12,16,28,41,42,42,42,68,69,79,89,90,100,134,144,152,154,154,155,157,177,183,190,191,196,215,
		219,240,245,253,255,269,282,300,325,339,342,352,358,370,382,404,415,416,419,420,449,459,473,486,490,
		531,554,559,570,574,598,608,610,611,620,625,668,677,681,710,718,723,746,751,759,775,787,790,791,806,
		814,816,823,825,830,842,849,850,851,855,860,891,900,906,947,953,962,963,972,977,979,987,988,988 };
	int find_median(vector<int>&X,vector<int>&Y, size_t p, size_t r) {
		size_t mid = (p + r) / 2;
		cout << X[mid] << endl;
		if (p <= r) {
			if (X[mid] >= Y[Y.size() - 1 - mid - 1])
				if (X[mid] <= Y[Y.size() - 1 - mid - 1 + 1])
					return X[mid];
				else
					return find_median(X, Y, p, mid - 1);
			else
				return find_median(X, Y, mid + 1, r);
		}
		else
			return	INT_MAX;//中位数不在Z中
	}
	int factory_find() {
		int temp = find_median(X, Y, 0, X.size() - 1);
		if (temp != INT_MAX)
			return temp;
		else
			return find_median(Y,X ,0, X.size() - 1);
	}
};

class solution9_3_9 {
public:
	void operator()() {
		cout << "可以假设所有的点的坐标都在第一象限，那么主管道的位置就是y=midan,midan为所有点的y坐标的中位数 \n"
			<< "而在线性时间内找出一个无序序列的中位数本小结已经给出算法，不赘言。下面给出证明： \n"
			<< "假设主管道在y=k,那么总长度等于∑|y(i)-k|,很容易得出主管道应该在最北面油井的南面 \n"
			<< "和最南面的油井的北面，各油井纵坐标排序后为a,b,c,d,e,f,g,如果主管道在中间，有 \n"
			<< "a,b,c,d,k,e,f,g,各点到k的距离等于e-d+f-c+g-b+k-a=k+e+f+g-a-b-c,如果主管道不在中间 \n"
			<< "有a,b,c,d,e,k,f,g,各点到k的距离等于f-e+g-d+3k-a-b-c=k+k+f+g-a-b-c+(k-e)>k+e+f+g-a-b-c \n"
			<< "k在中位数左边同理可证，所以当n为偶数时，管道修在两个中位数或其之间任意位置都可以， \n"
			<< "当n为奇数时修在中位数上面"
			<< endl;
	}
};
//思考题
class solution9_1 {
public:
	void operator()() {
		cout << "a.cnlgn \n"
			<< "b.cn+i*lgn \n"
			<< "c.cn+i*lg(i)"
			<< endl;
	}
};

class solution9_2 {
public:
	void operator()() {
		cout << ""
			<< endl;
	}
};
#endif //_SOLUTION_9_H_
