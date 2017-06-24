#pragma once
#ifndef _SOLUTION_16_H_
#define _SOLUTION_16_H_
#include<iostream>
#include<vector>
#include<deque>
#include<ctime>
using namespace std;

class solution16_1_1 {
public:
	void operator()() {
		cout << "动态规划花费O(n^3)，注释掉的两行可以计算另一个最优解"
			<< endl;
		dynamic_activity();


	}
private:
	vector<pair<int, int>>activity{ {0,0},{1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{8,11},{8,12},{2,14},{12,16},{INT_MAX,INT_MAX} };
	void dynamic_activity() {
		int n = activity.size() - 1;
		vector<vector<int>>c(n + 1, vector<int>(n + 1, 0));
		deque<deque<int>>r(n + 1, deque<int>(n + 1, 0));
		//sort(activity.begin(), activity.end(), [](pair<int, int>&lhs, pair<int, int>&rhs) {return lhs.first < rhs.first; });
		//	cout << activity[6].first << "\t" << activity[6].second << endl;//第6个活动就是之前的第二个活动
		for (int len = 1; len <= n + 1; ++len) {
			for (int i = 0; i <= n - len + 1; ++i) {
				int j = i + len - 1;
				for (int k = i + 1; k < j; ++k) {
					int temp = 0;
					//确认i,j之间是否有不冲突活动
					if (activity[k].first >= activity[i].second&&activity[k].second <= activity[j].first)
						temp = c[i][k] + c[k][j] + 1;
					if (temp > c[i][j]) {//c[i][j]只能记录最早使得其值变大的一个，所以不能计算所有可能的最优解
						c[i][j] = temp;
						r[i][j] = k;
					}
				}
			}
		}
		print_selector(r, 0, n);
		cout << "\n" << endl;
	}
	
	void print_selector(deque<deque<int>>&r, int i, int j) {
		if (r[i][j]) {
			print_selector(r, i, r[i][j]);
			cout << r[i][j] << "\t";
			print_selector(r, r[i][j], j);
		}
	}

};

class solution16_1_2 {
public:
	void operator()() {
		cout << "和书中的算法说明类似，假设最大兼容活动的最后一个活动不是所有活动中最晚开始的，则可以用最晚的活动代替这个活动得到最优解，以此类推 \n"
			<< endl;
		greedy_activity_selector();
	}
private:
	vector<pair<int, int>>activity{ { 0,0 },{ 1,4 },{ 3,5 },{ 0,6 },{ 5,7 },{ 3,9 },{ 5,9 },{ 6,10 },{ 8,11 },{ 8,12 },{ 2,14 },{ 12,16 }};
	void greedy_activity_selector() {
		//根据说动开始的时间排序
		sort(activity.begin(), activity.end(), [](pair<int, int>&lhs, pair<int, int>&rhs) {return lhs.first < rhs.first; });
		deque<int>s;//存储最优结果
		int k = activity.size() - 1;
		s.insert(s.begin(), k);
		int n =k-1 ;
		for (int i = n; i != 0; --i) {
			if (activity[i].second <= activity[k].first) {
				s.insert(s.begin(),i);
				k = i;
			}
		}
		for (auto i : s)
			cout << activity[i].first << "\t" << activity[i].second << "\t" << i << endl;	
	}
};

class soltuion16_1_3 {
public:
	void operator()() {
		cout << "如果最短时间的活动最后结束，则选择最短者不能找到最大兼容集 \n"
			<< "假设唯一不重叠的活动在最后结束，其它的两两重叠，但隔一个不重叠，则不能找到最优解 \n"
			<<"如果最早开始者最晚结束不能找到最优解"
			<< endl;
	}
};

class solution16_1_4 {
public:
	void operator()() {
		cout << "按时间顺序使用贪心算法，按活动的开始时间排序，活动开始时看是否有之前的活动结束后留下的已经使用过的教室，如果有就进入该教室，如果没有\n"
			<< "就分配一个新教室\n"
			<<"可以看到插入程序的每一个循环都不会超过活动个数n,所以时间为cn,而要插入n次，所以最坏情况为cn^2 "
			<< endl;
		least_greedy();
	}
private:
	vector<pair<int, int>>activity{ { 0,0 },{ 1,4 },{ 3,5 },{ 0,6 },{ 5,7 },{ 3,9 },{ 5,9 },{ 6,10 },{ 8,11 },{ 8,12 },{ 2,14 },{ 12,16 } };

	void least_greedy() {
		sort(activity.begin(), activity.end(), [](pair<int, int>&lhs, pair<int, int>&rhs) {return lhs.first < rhs.first; });
		list<int>time_list;//记录某一时刻正在进行的活动，按活动结束时间的增序排序，
		vector<int>room(activity.size(), INT_MIN);//记录每一个活动所用的教室
		vector<bool>classRoom;//记录使用过的教室，
		size_t counter = time_list.size();//记录使用教室的最大值
		for (int i = 0; i != activity.size(); ++i) {
			selector_insert(time_list,room,classRoom, i);
			if (time_list.size() > counter)
				counter = time_list.size();
		}
		cout << "需要用到 " << counter << "个教室\n" << endl;
		for (int i = 0; i != activity.size(); ++i)
			cout << "[" << activity[i].first << "\t" << activity[i].second << ")\t" << room[i] << endl;
	}


	void selector_insert(list<int>&time_list, vector<int>&room, vector<bool>&classRoom, int k) {
		auto iter = time_list.begin();
		for (; iter != time_list.end() && activity[*iter].second <= activity[k].first; iter = time_list.begin()) {
			classRoom[room[*iter]] = false;//k活动开始时剔除所有此时已经结束的活动并将占用的教室置为空闲
			time_list.erase(iter);
		}

		auto it = 0;
		for (; it != classRoom.size() &&classRoom[it]; ++it)
			;
		if (it == classRoom.size()) {//如果已经使用过的所有教室都有活动正在进行则开辟一间新教室,否则进入空闲教室
			classRoom.push_back(true);
			room[k] = classRoom.size()-1;
		}
		else {
			room[k] = it;
			classRoom[it] = true;
		}

		int c = 0;
		for (iter = time_list.begin(); iter != time_list.end() && activity[k].second > activity[*iter].second;++c, ++iter)
			;//将活动k按结束时间插入适当位置便于下次活动的删除
		time_list.insert(iter, k);
		
	}

};

class solution16_1_5 {
public:
	void operator()() {

	}
private:

};

class solution16_2_1 {
public:
	void operator()() {
		cout << "因为背包总是能够装满，假设在还有x美元每磅的商品g磅，选择了g磅的y,且x>y,则用x替代y能得到更好的解 "
			<< endl;
	}
};

class solution16_2_2 {
public:
	void operator()() {
		cout << "profit[i][j]代表剩余重量为j来装1...i件商品的最大收益 \n"
			<< "profit[n][w]为所求，代表背包容量w在1...n件商品中的最大收益 \n"
			<< "如果第i件商品的质量大于剩余质量j,则收益profit[i][j]=profit[i-1][j]，因为显然在剩余质量装不下超重的商品 \n"
			<<"如果第i件商品的质量小于等于剩余质量j,则收益profit[i][j]=max{profit[i-1][j],i.price+profit[i-1][j-i.weight] \n"
			<<"因为可以选择不装第i将商品或是装第i件商品，用剩余质量再去装1...i-1件商品，选取其中较大的值，基本情况收益为0"
			<< endl;
		knapsack_problem_01();
	}
private:
	vector<pair<int, int>>goods{ {60,10},{100,20},{120,30} };
	void knapsack_problem_01(int w=50) {
		int n = goods.size();
		vector<vector<int>>profit(n+1, vector<int>(w+1, 0));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= w; ++j) {
				if (j < goods[i - 1].second)
					profit[i][j] = profit[i-1][j];
				else {
					int temp = goods[i - 1].first + profit[i - 1][j - goods[i - 1].second];
					profit[i][j] = temp > profit[i - 1][j] ? temp : profit[i - 1][j];
				}
			}
		}
		cout << profit[n][w] << endl;
	}
};

class solution16_2_3 {
public:
	void operator()() {
		cout << "按商品重量的递增序给商品排序A，从第一个商品开始直到背包不能装下下一个商品为止为最优解，证明， \n"
			<< "假设最优解里包含Aj而不包含Ai，其中j>i，则可以用Ai代替Aj形成一个更优解 \n"
			<< endl;
	}
};
class solution16_2_4 {
public:
	void operator()() {
		cout << "以起点i为圆心m为半径画圆，连接起点和在圆内的补水点标上方向形成有向图，然后在找到的补水点为圆心重复以上步骤直至到达目的地j \n"
			<< "找到该图的无权最短路径，该问题具有最优子结构，15-3节已经讲了，不打算写程序，学到图时应该会有类似问题 \n"
			<< endl;
	}
};

class solution16_2_5 {
public:
	void operator()() {
		cout << "首先对点集按增序排序，以最开始的点x1为单位长度的左区间起点，找到第一个大于x1+1的点xk,然后以xk为起点重复以上步骤 \n"
			<< "证明，只需证明第一步找到的集合f[d]是最优解中的某个集合s[d],f[d]不可能是s[d]的真子集，因为没有比x1更小的元素，而xk不能被包含 \n"
			<< "假设s[1]...s[d]包含f[d]的部分元素，那么必然至少有一个包含x1集合s[k]是f[d]的真子集,因为不可能存在除f[d]内元素以外的任何任何 \n"
			<< "元素能与x1在一个长度为1的集合里面，这时可以把s[1]...s[d]中的f[d]中的元素抽出来放在s[k]中组成f[d]，此时集合的个数没有改变 \n"
			<< "所以f[d]必然是最优解集合中的一个,对于剩下来的元素以xk作为x1重复上述推论，得证 \n"
			<< endl;
	}
};

class solution16_2_6 {
public:
	void operator()() {
		cout << "总是装包外的价值密度最高的商品，直到包满,前提是背包的容量W为某一范围内常数，建一个最大堆花费cn,每次取最大值最多取W次\n"
			<<"每次维护最大堆最多花费lgn,cn+cwlgn=O(n) \n"
			<< endl;
	}
};

class solution16_2_7 {
public:
	void operator()() {
		cout << "A,B按降序排序，只需证明a1^b1是最优解的某一项，假设不是，则必然有a1^by,ax^b1,其中a1>ax,b1>by,\n"
			<< "易证a1^b1*ax^by>=a1^by*ax^by,化简后得（a1/ax)^(b1-by)>=1，显然成立 \n"
			<< "所以可以用a1^b1*ax^by代替原来的最优解，所以a1^b1必然是最优解的某一项，对于剩下的数以此类推,得证 \n"
			<<"排序花费cnlgn,相乘花费cn，所以总花费cnlgn"
			<< endl;
	}
};

class solution16_3_1 {
public:
	void operator()() {
		cout << "x.freq<=a.freq<=b.freq,x.freq<=y.freq<=b.freq"
			<< endl;
	}
};

class solution16_3_2 {
public:
	void operator()() {//中国的满二叉树定义和国外不同，我之前使用到的都是中国满二叉树到的定义
		cout << "对于任何一个只有一个子树的节点，都可以去掉该节点将其子树移植到该节点位置降低搜索深度"
			<< endl;
	}
};

class solution16_3_3 {
public:
	void operator()() {
		cout << "是一个单偏树，当然没有这个名词，是我编的，就是树的高度等于内部节点的数量，而每个内部节点除最底层的一个外都有且仅有一个叶节点 \n"
			<< "看起来完全偏向左边或是右边\n"
			<< "0,10,110,1110,11110....."
			<< endl;
	}
};

class solution16_3_4 {
public:
	void operator()() {
		cout << "对于任一深度为d的叶节点c，其代价为c.freq*d,有d个c.fred相加，而该节点的所有祖先节点的和必然包含了它的代价，且只包含了每一个叶节点的\n"
			<< "点的代价"
			<< endl;
	}
};

class solution16_3_5 {
public:
	void operator()() {
		cout << "没太明白题目意思"
			<< endl;
	}
};

class solution16_3_6 {
public:
	void operator()() {
		/////////////////
	}
};

class solution16_3_8 {
public:
	void operator()() {
		cout << "abcdefgh,a<f<2*a,构造编码树的时候，每次构造的子树都会被插入最小堆的末尾，所以基本每次都能构造两个都是叶子的子树，当每个叶子节点 \n"
			<< "的父节点都构造完成后会形成(ab)(cd)(ef)(gh)的最小堆，同样(ab)<(gh)<2*(ab)，因为256是2的幂，所以最后的编码树为完全二叉树 \n"
			<< "每一个叶节点都具有相同的高度lg(256)=8,每一位都是8位码字"
			<< endl;
	}
};

class solution16_3_9 {
public:
	void operator()() {
		cout << "根据上一题可以证明这个结论"
			<< endl;
	}
};

class solution16_4_1 {
public:
	void operator()() {
		cout << "根据3条性质逐条证明"
			<< endl;
	}
};

class solution16_4_2 {
public:
	void operator()() {
		cout << "同上"
			<< endl;//并不懂矩阵列的线性无关
	}
};

class solution16_4_3 {
public:
	void operator()() {
		cout << "假设不是补集，那么必然存在一个x使得其既不是前者的最大独立子集也不是后者的最大的独立子集但x∈s,但根据I’的定义， \n"
			<< "如果想不属于后者的最大独立子集则必然属于前者，反之同理，所以假设不成立 \n"
			<< endl;
	}
};

class solution16_4_4 {
public:
	void operator()() {
		cout << "因为A来自于S的划分，所以具有独立性"
			<< endl;//不会证
	}
};

class solution16_4_5{
public:
	void operator()() {
		cout << "本小节最小树生成问题中给出了描述"
			<< endl;//这小节没太看懂
	}
};

class solution16_5_1 {
public:
	void operator()() {
		task_scheduling();
	}
private:
	vector<pair<size_t, size_t>>a{ {4,10},{2,20},{4,30},{3,40},{1,50},{4,60},{6,70} };
	void task_scheduling() {
		//根据惩罚度排序
		sort(a.begin(), a.end(), [](pair<size_t, size_t>&lhs, pair<size_t, size_t>&rhs) {return lhs.second > rhs.second; });
		vector<size_t>task;
		size_t punishment = 0;
		for (size_t i = 0; i < a.size(); ++i)
			if (a[i].first > task.size())//贪心选择，如果排序后的第i个任务的截止时间不超过提前优先任务task则加入否则放弃
				task.push_back(i);
			else
				punishment += a[i].second;
		sort( task.begin(),task.end(), [](size_t lhs, size_t rhs) {return lhs > rhs; });
		cout << "最优调度为" << endl;
		for (auto i : task)
			cout << "a" << 7-i << "\t";//根据题目特征判断的排序后的对应的原任务序号
		
		cout << "\n总惩罚为 " << endl;
		cout << punishment;
		cout << "\n" << endl;
	}
};

class solution16_5_2 {
public:
	void operator()() {
		cout << "k=Ai∪k,i=1...|A|,顺序扫描元素" << endl;
	}
};
//思考题
class solution16_1 {
public:
	void operator()() {
		cout << "a/b,面额按降序排序，总是找需要第一个小于要找零钱的面额，证明，当k=1时，对于零钱a1c+a2>=c的情况,a1>=1,如果使用贪心算法，得到a1+a2 \n"
			<< "否则如果在零钱大于c的情况下不使用面额c，则得到a1c+a2个硬币，显然贪心算法能得到最优解，\n"
			<< "假设贪心耍法在c^(k-1)上成立，当面额有c^k时，用g(k,x)表示用贪心算法在面额最大面额c^(k)上求得零钱x的最优解，当零钱为akc^k+x>c^k，\n"
			<< "不使用面额c^k，那么最优解为g(k-1,akc^k+x)=ak*c+g(k-1,x),而如果使用贪心算法为g(k,akc^k+x)=ak+g(k-1,x)<ak*c+g(k-1,x),得证 \n"
			<< "c.12,9,1来找零27 \n"
			<< "d.使用动态规划，具体看注释，两个循环代价显然是cnk"
			<< endl;
		get_min();
	}
private:
	vector<int>notes{ 1,2,5,10,20 };
	void get_min(int dollar = 99) {
		vector<int>m(dollar + 1, INT_MAX);// m[i]表示要找零钱i的最小数
		vector<int>r(m);//r[i]表示零钱i第一次找的面额
		m[0] = 0;
		//循环之前需要先对面额升序排序，这里省略
		for(int i=1;i<=dollar;++i)
			for (size_t j = 0; j < notes.size() && i >= notes[j]; ++j) {
				int temp = 1 + m[i - notes[j]];
				if (temp < m[i]) {//对比第一次找哪个面额的值能得到最小值
					m[i] = temp;
					r[i] = notes[j];
				}
			}
		cout << "最少找 " << m[dollar] << " 个硬币" << endl;
		cout << "面额为" << endl;
		while (dollar) {
			cout << r[dollar] << "\t";
			dollar -= r[dollar];
		}
		cout << "\n" << endl;
	}
};
///////////////////////////
struct task {
	friend::ostream &operator<<(ostream&cout, const task&t);
	task(int k,int r,int p):index(k),r(r),p(p){}
	int index;
	int r;
	int p;
};
ostream &operator<<(ostream&cout, const task&t) {
	cout << t.index << "\t" << t.r << "\t" << t.p;
	return cout;
}

class solution16_2 {
public:
	void operator()() {
		cout << "a,使用贪心算法,每次都选取没有完成任务中耗时pi中最小的任务 \n"
			<< "证明最小耗时的任务a1要首先完成，假设某个最优解的第一个任务不是a1而是ak,根据si=s(i-1)+pi,s和c表示相公意义，但其中i表示 \n"
			<< "任务安排完成后的顺序而不是原始a1,a2,的顺序，a1前面的任务序号为g,此时c(1)=s(g+1)=sg+p1,ck=s1=pk, \n"
			<< "ak和a1之间的累计代价和为x,所以前g+1项的代价和为pk+x+sg+p1,交换任务a1，ak,此时s1=p1,因为p1<pk，根据si=s(i-1)+pi的累加性 \n"
			<< "ak和a1之间的累计代价和x'<=x,sg'<=sg,所以前g+1项的代价和pk+x'+sg'+p1<=pk+x+sg+p1,所以某个最优解的第一个任务必然为a1,后面的子问题 \n"
			<< "后面的子问题以此类推\n"
			<< "b.首先按运行时间的升序排序，然后按释放时间的升序稳定排序，当释放时间到达时运行第一个任务直到下一个任务的释放时间到达，此时比较\n"
			<< "正在运行任务的剩下时间和下一个任务的运行时间，如果大于则被抢占，将剩余运行时间的任务插入优先队列，否则继续运行这个任务，并把 \n"
			<< "未运行的任务插入优先队列，直到进行下一次比较，这样可以保证能够最先完成的任务最先完成，证明上一小问已证明 \n"
			<< "下面的程序因为要模拟时间的发展过程中任务的执行，所以要复杂一些"
			<< endl;
		get_preemption();
	}
private:
	vector<task>tk{ task(1,3,5), task(2,4,2), task(3,2,7), task(4,3,6), task(5,11,6), task(6,6,3), task(7,12,5), task(8,9,1) };
	void get_preemption() {
		sort(tk.begin(), tk.end(), [](task lhs, task rhs) {return lhs.p < rhs.p; });
		stable_sort(tk.begin(), tk.end(), [](task lhs, task rhs) {return lhs.r < rhs.r; });
		for (auto &k : tk)
			cout << k << endl;
		list<task>priority;
		int sum = 0;//每次运行完成的时间和
		int t = tk[0].r;//正在运行任务开始运行的时间，注意被挂起过的任务正在运行时开始运行时的时间不等于第一次运行的时间
		for (size_t i = 0; i < tk.size(); ++i) {
			if (priority.empty()) {
				priority.insert(priority.begin(),tk[i]);//运行第一个可以运行任务
				cout << "任务 " << tk[i].index << " 在" << "时刻 " << t << " 开始运行" << endl;
			}
			else {
				while (!priority.empty() && tk[i].r - t >= priority.front().p) {//在某个任务的释放时间到之前一直运行可运行任务
					sum += t + priority.front().p;//记录完成时刻
					t += priority.front().p;
					cout << "任务 " << priority.front().index << " 在时刻 " << t << "运行完毕" << endl;
					priority.erase(priority.begin());//删除已经运行完成的任务
					cout << "，同时任务 " << priority.front().index << "开始运行 " << endl;
				}
				int surplus = priority.front().p - (tk[i].r - t);//正在运行任务的剩余时间
				if (surplus > tk[i].p) {//如果正在运行的任务的剩余时间比可以开始运行任务的释放时间大
					priority.front().p = surplus;
					t = tk[i].r;
					cout << "任务 " << priority.front().index << "在时刻 " << t << " 被挂起" << ",剩余运行时间 " << priority.front().p << endl;
					cout << "，同时任务 " << tk[i].index << "开始运行 " << endl;
					priority.insert(priority.begin(), tk[i]);
				}
				else {//正在运行的任务的剩余时间比释放时间小,继续执行原任务，将可执行任务插入合适位置
					auto iter = priority.begin();
					for (; iter != priority.end() && (*iter).p <= tk[i].p; ++iter)
						;
					priority.insert(iter, tk[i]);
				}
			}

		}
		while (!priority.empty()) {
			t += priority.front().p;
			sum += t;
			cout << "任务 " << priority.front().index << "在时刻 " << t << " 完成";
			priority.erase(priority.begin());
			if(!priority.empty())
				cout<< "，同时任务 " << priority.front().index << "开始运行 " << endl;
		}
		cout << "\n\n平均运行时间为 " << static_cast<double>(sum) / tk.size() << endl;
	}
};

class solution16_3 {
public:
	void operator()() {
		cout << "a.缺少相关知识 \n"
			<< "b.c.d.e略"
			<< endl;
	}
};

class solution16_5{
public:
	void operator()() {
		cout << "a.算法时间分析见注释\n"
			<<"b.r1...rn的最大命中率等于r1...rk的最大命中率加上rk+1...rn大最大命中率 \n"
		//	<<"c.r1...rk的最大命中率应为"
			<< endl;
		cache_hit();
	}
private:
	void cache_hit(int k = 5) {
		vector<int>request;
		list<int>cache;
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 1; i != 71; ++i) {//随机生成一定范围内序列
			request.push_back(rand() % 10 + 0);
			cout << request.back() << "\t";
		}
		cout << endl;
		int sum = 0;
		vector<list<int>>future(11, list<int>());
		for (size_t i = 0; i < request.size(); ++i) //扫描一遍序列，cn,所以离线缓存适用于多次读取同一数据
			future[request[i]].push_back(i);//记录序列中相同元素出现大的下标,实际应用中应使用哈希表

		for (size_t i = 0; i < request.size(); ++i) {//模拟访问每个元素
			future[request[i]].erase(future[request[i]].begin());//删除已经出现过的元素的下标
			if (!cache.empty()&&request[i] == cache.front()) {//如果命中，因为插入缓存的方式，模拟缓存的链表cache总是将最先出现的元素放在首位
				cout << "hit " << request[i] << endl;
				++sum;
				if (!future[cache.front()].empty()) {//如果命中的元素下次还会出现
					auto iter = ++cache.begin();
					for (; iter != cache.end() && future[*iter].front() < future[cache.front()].front(); ++iter)
						;//ck
					if (iter != ++cache.begin()) {
						cache.insert(iter, request[i]);
						cache.erase(cache.begin());
					}
				}
				else {//命中元素下次不会出现则在缓存中删除元素
					cache.erase(cache.begin());
				}
			}
			else {//如果不在缓存中则插入元素
				cache_insert(cache,k,future,request[i]);
			}
		}
		cout << "命中次数为 " << sum << endl;
	}
	void cache_insert(list<int>&cache, size_t k,vector<list<int>>&future, int key) {
		if (future[key].empty())//如果要插入的元素下次不会出现直接返回
			return;
		auto iter = cache.begin();
		for (; iter != cache.end() && !future[*iter].empty()&&future[*iter].front() < future[key].front(); ++iter)
			;//找到第一个元素下一次出现的距离不小于要插入的元素，ck

		if (cache.size() < k) {//如果缓存未满则插入元素
			cache.insert(iter, key);
		}
		else if (iter != cache.end()) {//如果缓存满了并且要插入元素下一次出现的距离不是最大的则替换
			cache.insert(iter, key);
			cache.erase(--cache.end());
		}

		for (auto i : cache)
			cout << i <<future[i].front()<< "\t";
		cout << "\n" << key << future[key].front() << "\n" << endl;
	}
};
#endif 