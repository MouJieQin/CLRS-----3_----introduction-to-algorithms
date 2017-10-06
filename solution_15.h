#pragma once
#ifndef _SOLUTION_15_H_
#define _SOLUTION_15_H_
#include<iostream>
#include<vector>
#include<map>
#include<memory>
#include<ctime>
using namespace std;
class solution15_1_1 {
public:
	void operator()() {
		cout << "T(n)=1+∑[j=0,j=n-1] T(j),T(n-1)=1+∑[j=0,j=n-2] T(j),两式相减得T(n)-T(n-1)=T(n-1) \n"
			<< "T(n)=2T(n-1),对于基础情形T(0)=2^0=1,T(n)=2^n=2*2^(n-1)"
			<< endl;
	}
};

class solution15_1_2 {
public:
	void operator()() {
		sort_Density();
		testGreedy();
		cout << "长度为4时划分并不是最优的" << endl;
	}
private:
	typedef int length;
	typedef double density;
	vector<int>vect{ 0,1,5,8,9,10,17,17,20,24,30 };
	vector<pair<density, length>>price_density;
	void sort_Density() {//根据密度由大到小排序
		for (size_t i = 1; i != vect.size(); ++i)
			price_density.push_back({ static_cast<double>(vect[i]) / i, i });
		price_density.push_back({ 0,0 });
		sort(price_density.begin(), price_density.end(), [](pair<density, length>&a, pair<density, length>&b) {return a.first > b.first; });
		for (auto i : price_density)
			cout << i.first << "   ->   " << i.second << endl;
	}
	int greedy(int len) {//贪心算法
		int price = 0;
		int index = -1;//大于等于len的排序后密度的长度的下标
		cout << "对于长度为 " << len << " 的钢条" << endl;
		while (len) {
			length num = 0;
			while (!num) {
				num = static_cast<int>(len / price_density[++index].second);
			}
			price += num*vect[price_density[index].second];
			len -= num*price_density[index].second;
			cout << "划分出 " << num << " 个长度为" << price_density[index].second << endl;
		}
			cout << "------------------------------------" << endl;
		return price;
	}
	void testGreedy() {
		vector<int>price;
		for (size_t i = 0; i != 11; ++i)
			price.push_back(greedy(i));
		cout << endl;
		for (size_t i = 0; i != 11; ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : price)
			cout << i << "\t";
		cout << endl;
	}
};
class solution15_1_3 {
public:
	void operator()() {
		const int n = 24;
		const int c = 1;
		for(size_t n=1;n!=11;++n)
			extended_bottom_up_cut_rod(n,c);
	}
private:
	vector<int>p{ 0,1,5,8,9,10,17,17,20,24,30 };
	void extended_bottom_up_cut_rod(int n,int c=0) {//自底向上的算法;
		vector<int>s(n+1, 0);
		vector<int>r(n+1, 0);
		for (int i = 1; i <= n; ++i) {
			int q = INT_MIN;
			for(int j=1;j<i&&j!=11;++j)//书上这一行写的并不好，他用的n容易让读者把输入规模n搞混
				if (r[i - j] + p[j]-c > q) {//此处处理需要切割的情况
					q = r[i - j]+p[j]-c;
					s[i] = j;
				}
			if (i <= 10 && p[i] > q) {//此处处理不需要切割的情况
				q = p[i];
				s[i] = i;
			}
			r[i] = q;
		}
		cout << "长度为 " << n << " 的钢条的最优收益为 " << r[n] << endl;
		cout << "将钢条分成 ";
		while (n > 0) {
			cout << s[n] <<"\t";
			n = n - s[n];
		}
		cout << "\n" << endl;
	}
};
class solution15_1_4 {
public:
	void operator()() {
		for(size_t n=0;n!=11;++n)
			extended_memoized_cut_rod(n);
	//	cout << cut_rod(8) << endl;
	}
private:
	vector<int>p{ 0,1,5,8,9,10,17,17,20,24,30 };
	void extended_memoized_cut_rod(int n) {
		vector<int>r(n + 1,	INT_MIN);
		vector<int>s(n + 1,0);
		auto max=memoized_cut_rod_aux(n, r,s);
		cout << "最优化价格为 " << max << endl;
		cout << "将长度为 " << n << " 的钢条分为 " << endl;
		while (n) {
			cout << s[n] << "\t";
			n -= s[n];
		}
		cout << endl;
	}
	int memoized_cut_rod_aux(int n, vector<int>&r,vector<int>&s) {
		if (r[n] >= 0)
			return r[n];
		int q = INT_MIN;
		if (!n)
			return 0;
		for (int i = 1; i <= n&&i != 11; ++i) {//递归式为 T(n)=max( ∑[i=1,10] p(i)+T(n-i) )
			auto temp = p[i] + memoized_cut_rod_aux(n - i, r, s);
			if (temp > q) {
				q = temp;
				s[n] = i;
			}
		}
		r[n] = q;
		return r[n];
	}
	int cut_rod(int n) {//自顶向下的一般递归实现算法
		if (n == 0)
			return 0;
		int q = INT_MIN;
		for (int i = 1; i<=n&&i<= 10; ++i) {
			int temp = p[i] + cut_rod(n - i);
			if (temp > q) {
				q = temp;
			}
		}
		return q;
	}
};

class solution15_1_5 {
public:
	void operator()() {
		cout << "从图15-4可以看出规律，对于问题规模n=1，1个顶点0条边，对于n>1,有2n-4条边\n"
			<< endl;
		const int n = 10;
		f(n);
		cout << "\n-------------------------" << endl;
		f_recursion(n);
		cout << "\n" << endl;
	}
private:
	int f(int n) {//O(n)
		if (n == 1)
			return 0;
		else if (n == 2)
			return 1;
		int f_1 = 0;
		int f_2 = 1;
		int result = 0;
		for (int i = 3; i <= n; ++i) {
			result = f_1 + f_2;
			cout << result <<"\t";
			f_1 = f_2;
			f_2 = result;
		}
		return result;
	}
	int f_recursion(int n) {//这种递归算法做了很多重复计算
		if (n == 1)
			return 0;
		else if (n == 2)
			return 1;

		int result = f_recursion(n-2) + f_recursion(n - 1);
		cout << result << "\t";
		return result;
	}
};

class solution15_2_1 {
public:
	void operator()() {
		print_matrix();
		matrix_chain_order();
	}
private:
	vector<int>p{ 5,10,3,12,5,50,6 };
	//vector<int>p{ 30,35,15,5,10,20,25 };
	void print_matrix() {
		cout << "矩阵规模为" << endl;
		for (size_t i = 0; i + 1 != p.size(); ++i) 
			cout << "A" << i + 1 << " = " << p[i] << " X " << p[i + 1] << endl;
	}
	void matrix_chain_order() {
		int n = p.size() - 1;//矩阵链实际的矩阵个数
		vector<vector<int>>m(n + 1, vector<int>(n + 1, 0));
		vector<vector<int>>s(m);
		for (int len = 2; len <= n; ++len) {
			for (int i = 1; i <= n - len + 1; ++i) {
				int j = i + len - 1;
				m[i][j] = INT_MAX;
				for (int k = i; k != j; ++k) {
					int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
					if (q < m[i][j]) {
						m[i][j] = q;
						s[i][j] = k;
					}
				}
			}
		}
		cout << "\n" << "最优化方案为" << endl;
		print_optimal_parens(s, 1, s.size() - 1);
		cout << "\n最优化方案的乘法次数为 " << m[1][n] << endl;
	}
	void print_optimal_parens(vector<vector<int>>&s,int i,int j) {
		if (i == j)
			cout << "A" << i;
		else {
			cout << "(";
			print_optimal_parens(s, i, s[i][j]);
			print_optimal_parens(s, s[i][j] + 1, j);
			cout << ")";
		}
	}
};

class solution15_2_2 {
public:
	void operator()() {
		cout << "下面是随机生成的一定范围的数字的一定个数的矩阵乘积测试 \n"
			<< "具体可以查看注释，注意所有元素都是从下标0开始 \n"
			<< endl;
		test_matrix_chain_multiply();
	}
private:
	void test_matrix_chain_multiply() {
		srand(static_cast<unsigned>(time(nullptr)));
		size_t n = rand() % 5 + 5;//矩阵链个数
		vector<vector<vector<int>>>matrix_chain;//存储矩阵链
		vector<int>p;//记录行列数
		size_t rows = rand() % 7 + 3;
		p.push_back(rows);
		size_t columns = rand() % 7 + 3;
		for (size_t i = 1; i <= n; ++i) {
			p.push_back(columns);
			vector<vector<int>>matrix(rows, vector<int>(columns, 0));//单个矩阵
			for (size_t row = 0; row < rows; ++row) {
				for (size_t column = 0; column < columns; ++column) {
					matrix[row][column] = rand() %5-2;//矩阵元素的数字比较小避免溢出，输出更清晰
				}
			}
			matrix_chain.push_back(matrix);
			rows = columns;
			columns = rand() % 7 + 3;
		}
		print_matrix_chain(matrix_chain);//打印矩阵链

		vector<vector<int>>s(n , vector<int>(n, 0));
	
		matrix_chain_order(p, s);//动态规划最佳括号化路径

		print_optimal_parens(s, 0, n-1);

		auto result=matrix_chain_multiply(matrix_chain, s, 0, n-1);//按照最佳括号化路径计算矩阵链

		cout << "= " << endl;//打印结果
		for (auto &i : result) {
			for (auto j : i)
				cout << j << "\t";
			cout << endl;
		}
		cout << "\n" << endl;
	}
	void matrix_chain_order(vector<int>&p,vector<vector<int>>&s) {
		int n = p.size()-1;//真实矩阵个数
		vector<vector<int>>m(n , vector<int>(n , 0));//m[i][j]为从下标i到j最少的乘法次数，i=j时不用计算为0
		for (int len = 2; len <= n; ++len) {//len表示不同的矩阵组合长度，从2到n
			int last = n - len ;//最后一个长度为len组合的起点下标
			for (int i = 0; i <= last; ++i) {//起点1...last
				int j = i + len - 1;//以i为起点，长度为len组合的最后一个矩阵下标j
				m[i][j] = INT_MAX;
				for (int k = i; k < j; ++k) {//q=以下标k为划分节点的乘法次数，第i位的行数等于p[i-1]
					int q = m[i][k] + m[k + 1][j] + p[i] * p[k+1] * p[j+1];//因为是从下标0开始，所以这里有修改
					if (q < m[i][j]) {//m[i][k]生成的矩阵为p[i-1]*p[k]
						m[i][j] = q;
						s[i][j] = k;//s[i][j]记录从下标i到j最少乘法从小标k开始划分
					}
				}
			}
		}
		cout << "\n此乘法次数为 " << m[0][n-1] << endl;
	}
	void print_matrix_chain(vector<vector<vector<int>>>&A) {
		int n = 0;
		for (auto &i : A) {
			cout << "A" << ++n << "=" << endl;
			for (auto &j : i) {
				for (auto k : j)
					cout << k << "\t";
				cout << endl;
			}
			cout << "\n" << endl;
		}
		
	}
	void print_optimal_parens(vector<vector<int>>&s, int i, int j) {
		if (i == j)
			cout << "A" << i+1;
		else {
			cout << "(";
			print_optimal_parens(s, i, s[i][j]);
			print_optimal_parens(s, s[i][j] + 1, j);
			cout << ")";
		}
	}
	vector<vector<int>> matrix_multiply(vector<vector<int>>&lhs, vector<vector<int>>&rhs) {//两个矩阵链的乘法
		vector<vector<int>>result(lhs.size(), vector<int>(rhs[0].size(),0));

		for (int i = 0; i != lhs.size(); ++i) 
			for (int j = 0; j != rhs[0].size(); ++j) 
				for (int k =0; k != rhs.size(); ++k) 
					result[i][j] += lhs[i][k] * rhs[k][j];	
		return result;		
	}
	vector<vector<int>> matrix_chain_multiply(vector<vector<vector<int>>>&A, vector<vector<int>>&s, int beg, int n) {
		if (beg == n)//如果是单个矩阵返回该矩阵
			return A[beg];
		if (beg + 1 == n) //如果是相邻矩阵则进行两个矩阵的乘法
			return matrix_multiply(A[beg], A[n]);
		//如果是非相邻矩阵，将原矩阵链划分成两个矩阵链递归迭代
		return matrix_multiply(matrix_chain_multiply(A, s, beg, s[beg][n]), matrix_chain_multiply(A, s, s[beg][n] + 1,n));
	}
};

class solution15_2_3 {
public:
	void operator()() {
		cout << "T(n)=∑[k=1,n-1] 2^(k)*2^(n-k)=∑[k=1,n-1] 2^n>=c2^n,所以Ω（2^n)"
			<< endl;
	}
};

class solution15_2_4 {
public:
	void operator()() {
		cout << "不同于图15-3的递归树，类似于图15-4，对相同子问题节点进行收缩，对于划分节点k有n-1个选项，所以构成了一个等差数列和 个边 \n"
			<< "有n个节点，(n*(n-1))/2条边，对于每个节点的边指向小于自己的节点"
			<< endl;
	}
};

class solution15_2_5 {
public:
	void operator()() {
		cout << "我算出来如果每次访问两次为(n+3)(n^2-1)/3"
			<< endl;
	}
};

class solution15_2_6 {
public:
	void operator()() {
		cout << "使用数学归纳法，对于基本情况n=1,2显然成立，假设当n=k时成立需要k-1对括号，当n=k+1时，对于多出来的一个元素显然只需要再加一对括号来把它\n"
			<< "与前k个完全括号化的矩阵合并起来"
			<< endl;
	}
}; 

class solution15_3_1 {
public:
	void operator()() {
		cout << "答案是递归比枚举更有效，计算过程太复杂，放弃"
			<< endl;
	}
};

class solution15_3_2 {
public:
	void operator()() {
		cout << "因为子问题并没重叠部分"
			<< endl;
	}
};

class solution15_3_3 {
public:
	void operator()() {
		cout << "可以，因为对于A[i...j]分为A[i...k]和A[k...j]的乘积，而这两个矩阵链之间是无关的 \n"
			<< endl;
	}
};

class solution15_3_4 {
public:
	void operator()() {
		cout << "对于3个矩阵的链，AXB,BXC,CXD,假设B>C,所以贪心算法会选择第二个矩阵作为划分位置，则贪心算法的运行时间为AXCXD+AXBXC, \n"
			<< "而取第一个矩阵作为划分位置的代价为AXBXD+BXCXD，注意到在贪心算法中A出现两次，另一个D出现两次，所以只需要增大A的值，减小D的值 \n"
			<< "并保证B>C即可，如100*5,5*2,2*3,贪心算法=1600，另一个=1530"
			<< endl;
	}
};

class solution15_3_5 {
public:
	void operator()() {
		cout << "对于长度为4的钢条，假设L(5)=1,则最优子结构不成立"
			<< endl;
	}
};
////////////////////////////////////////
class fraction {
public:
	friend fraction operator*(fraction &lhs, fraction &rhs);
	friend ostream&operator<<(ostream&cout, fraction&frac);
	fraction(int t, int b = 1) :top(t), bottom(b) {}
	fraction get_reciprocal() { return fraction(bottom, top); }
	double get_double() { return static_cast<double>(top) / bottom; }
private:
	int top;
	int bottom;
};
fraction operator*(fraction &lhs, fraction &rhs) { return fraction(lhs.top*rhs.top, lhs.bottom*rhs.bottom); }
ostream&operator<<(ostream&cout, fraction&frac) { cout << frac.top << "/" << frac.bottom; return cout; }

class solution15_3_6 {
public:
	void operator()() {
		cout << "将题意理解为任意两种货币都能进行兑换，要满足最优子结构还需要满足条件，对于有n>=3种货币，任意形成环的汇率积要小于等于1 \n"
			<< "如对于货币i,j,k,r_ij*r_jk*r_ji<=1，不然在这条路径上收益会越滚越大，有限时间内无法计算 \n"
			<< "最优子结构为从原始货币i经过一定路径到达某一货币k时的d_k最大值，兑换成目标货币的最大收益j等于max{d_k*r_kj} \n"
			<< "算法描述为首先将货币1兑换成2...n种货币存入m[k]，然后如果2货币兑换成3...n种货币大于m[k]则更新m[k]的值，依次类推，而不用回头 \n"
			<< "因为回头会形成环，最后m[n]就是最大值，中间可以用数组记录路径\n"
			<< "如果中间有手续费，则不一定具有最优子结构"
			<< endl;
		test_exchange_rate();
	}
private:
	void test_exchange_rate() {
		srand(static_cast<unsigned int>(time(nullptr)));
		vector<vector<fraction>>exchange_rate(11, vector<fraction>(11, 1));
		for (int i = 1; i != 11; ++i)
			for (int j = i + 1; j != 11; ++j) {
				exchange_rate[i][j] = fraction(rand() % 7 + 3, rand() % 4 + 3);
				exchange_rate[j][i] = exchange_rate[i][j].get_reciprocal();
			}
		print_exchange_rate(exchange_rate);
	}
	void print_exchange_rate(vector<vector<fraction>>&r) {
		cout << "\t";
		for (int i = 1; i != 11; ++i)
			cout << i << "\t";
		cout << endl;
		for (int i = 1; i != 11; ++i) {
			cout << i << "\t";
			for (int j = 1; j != 11; ++j) {
				cout << r[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "\n" << endl;
	}
	double get_max_exchange(vector<vector<int>>&r, double d = 100, double c = 0) {
		//排列、、、、、、、、、、、、、、、、、
	}

};

 
class solution15_4_1 {
public:
	void operator()() {
		lcs_length();
	}
private:
	vector<bool>x{ 0, 1,0,0,1,0,1,0,1 };//注意下标是从0开始，所以x[0],y[0]不是有效数据
	vector<bool>y{ 0, 0,1,0,1,1,0,1,1,0 };
	void lcs_length() {
		vector<vector<int>>c(x.size(), vector<int>(y.size(), 0));
		vector<vector<char>>b(x.size(), vector<char>(y.size(), 0));
		for (int i = 1; i != x.size(); ++i)
			for (int j = 1; j != y.size(); ++j) {
				if (x[i] == y[j]) {
					c[i][j] = c[i - 1][j - 1] + 1;
					b[i][j] = -1;
				}
				else if (c[i - 1][j] > c[i][j - 1]) {
					c[i][j] = c[i - 1][j];
					b[i][j] = 0;
				}
				else {
					c[i][j] = c[i][j - 1];
					b[i][j] = 1;
				}
			}
		print_lcs(b, x.size() - 1, y.size() - 1);
		cout << "\n" << endl;
	}
	void print_lcs(vector<vector<char>>&b, int i, int j) {
		if (!i || !j)
			return;
		if (b[i][j] == -1) {
			print_lcs(b, i - 1, j - 1);
			cout << x[i] << "\t";
		}
		else if (b[i][j] == 0)
			print_lcs(b, i - 1, j);
		else
			print_lcs(b, i, j - 1);
	}
};

class solution15_4_2 {
public:
	void operator()() {
		lcs_length();
		vector<vector<int>>c(x.size(), vector<int>(y.size(), -1));
		for (int i = 0; i != x.size(); ++i)
			c[i][0] = 0;
		for (int i = 0; i != y.size(); ++i)
			c[0][i] = 0;
		memoized_lcs_length(c, x.size() - 1, y.size() - 1);//备忘录法，可以看到并没有计算所有情况
		for (auto &i : c) {
			for (auto j : i)
				cout << j << "\t";
			cout << endl;
		}
		print_lcs(c, x.size() - 1, y.size() - 1);
		cout << "\n" << endl;
	}
private:
	string x = "0ABCBDAB";
	string y = "0BDCABA";
	void lcs_length() {
		vector<vector<int>>c(x.size(), vector<int>(y.size(), 0));
		for(int i=1;i!=x.size();++i)
			for (int j = 1; j != y.size(); ++j) {
				if (x[i] == y[j]) {
					c[i][j] = c[i - 1][j - 1] + 1;
				}
				else if (c[i - 1][j] > c[i][j - 1])
					c[i][j] = c[i - 1][j];
				else
					c[i][j] = c[i][j - 1];
			}

		for (auto &i : c) {
			for (auto j : i)
				cout << j << "\t";
			cout << endl;
		}
		cout << "\n" << endl;
		print_lcs(c, x.size() - 1, y.size() - 1);	
		cout << "\n" << endl;
	}
	int memoized_lcs_length(vector<vector<int>>&c,int i,int j) {
		if (c[i][j]>=0)
			return c[i][j];

		if (x[i] == y[j]) {
			c[i][j] = memoized_lcs_length(c, i - 1, j - 1) + 1;
			return c[i][j];
		}
		else {
			auto c1 = memoized_lcs_length(c, i - 1, j);
			auto c2 = memoized_lcs_length(c, i, j - 1);
			if (c1 > c2) {
				c[i][j] = c1;
				return c1;
			}
			else {
				c[i][j] = c2;
				return c2;
			}
		}
	}
	void print_lcs(vector<vector<int>>&c, int i, int j) {
		if (!i || !j)
			return;
		if (c[i][j] == c[i][j - 1])
			print_lcs(c, i , j- 1);
		else if (c[i][j] == c[i- 1][j ])
			print_lcs(c, i- 1, j );
		else {
			print_lcs(c, i - 1, j - 1);
			cout << x[i]<<"\t";
		}
	}
};

class solution15_4_3 {
public:
	void operator()() {
		vector<vector<int>>c(x.size(), vector<int>(y.size(),INT_MIN));
		for (int i = 0; i != x.size(); ++i)
			c[i][0] = 0;
		for (int i = 0; i != y.size(); ++i)
			c[0][i] = 0;
		lcs_length(c, x.size() - 1, y.size() - 1);
		cout << " lcs is" << c[x.size() - 1][ y.size() - 1] << endl;////////////////
		print_lcs(c, x.size() - 1, y.size() - 1);
		cout << "\n" << endl;
	}
private:
	string x = "0ACCGGTCGAGTGAGCGGAAGCCGGCCGAA";
	string y = "0GTCGTTCGGAATGCCGTTGCTCTGTAAA";
	int lcs_length(vector<vector<int>>&c,int i,int j) {
		if (c[i][j] >= 0)
			return c[i][j];
		if (x[i] == y[j]) {
			c[i][j] = lcs_length(c, i - 1, j - 1) + 1;
			return c[i][j];
		}
		else {
			auto c1 = lcs_length(c, i-1, j);
			auto c2 = lcs_length(c, i, j - 1);
			if (c1 > c2) {
				c[i][j] = c1;
				return c1;
			}
			else {
				c[i][j] = c2;
				return c2;
			}
		}
	}
	void print_lcs(vector<vector<int>>&c, int i, int j) {
		if (!i || !j)
			return;
		if (c[i][j] == c[i - 1][j])
			print_lcs(c, i - 1, j);
		else if (c[i][j] == c[i][j - 1])
			print_lcs(c, i, j - 1);
		else {
			print_lcs(c, i - 1, j - 1);
			cout << y[j];
		}
	}
};

class solution15_4_4 {
public:
	void operator()() {
		lcs_length_2_rows();//只需要两行
		lcs_lenght_1_row();//只需一行，需要画图理解
	}
private:
	/*string x = "0ACCGGTCGAGTGAGCGGAAGCCGGCCGAA";
	string y = "0GTCGTTCGGAATGCCGTTGCTCTGTAAA";*/
	string x = "0ABCBDAB";
	string y = "0BDCABA";
	void lcs_length_2_rows() {
		if (x.size() < y.size())//保证x的长度更长
			swap(x, y);
		vector<vector<int>>c(2, vector<int>(y.size(), 0));
		for (int i = 1; i != x.size(); ++i) {
			for (int j = 1; j != y.size(); ++j) {
				if (x[i] == y[j])
					c[1][j] = c[0][j - 1] + 1;
				else if (c[1][j - 1] > c[0][j])
					c[1][j] = c[1][j - 1];
				else
					c[1][j] = c[0][j];
			}
			for (int k = 1; k != y.size(); ++k)//更新上一行为下一行的值以进入下一次循环
				c[0][k] = c[1][k];
		}
		cout << "\n最长子序列为 " << c[1][y.size()-1] << endl;
	}
	void lcs_lenght_1_row() {
		if (x.size() < y.size())
			swap(x, y);
		vector<int>c(y.size(), 0);
		int curr = 0;//记录当前值
		int last = 0;//记录上一个值
		for (int i = 1; i != x.size(); ++i) {
			for (int j = 1; j != y.size(); ++j) {
				if (j == 1)//如果是首次进入内层循环，很显然last=c[i][0]=0,其中c是为简化算法的矩阵
					last = 0;
				else//否则last随curr向右移动
					last = curr;
				if (x[i] == y[j]) {
					curr = c[j - 1] + 1;//c[j-1]相当于m*n中m[i-1][j-1]的值
				}
				else if (last > c[j]) {//last相当于c[i][j-1],c[j]相当于c[i-1][j]
					curr = last;
				}
				else {
					curr = c[j];
				}
				cout << curr << "\t";//打印当前值
				c[j - 1] = last;//更新c[i-1][j-1]的值作为下一次外层循环的值
			}
			c.back() = curr;//更新最后一个
			cout << endl;
		}
		cout << "\n最长子序列为 " << curr << endl;
	}
};

class solution15_4_5 {
public:
	void operator()() {
		cout << "1先将序列s升序排序并删除重复元素得到序列s'，然后求两个序列的lcs \n"
			<< "首先lcs肯定是单调递增的，因为他是无重复元素单调递增序列的子序列 \n"
			<< "然后可以用剪切粘贴法证明lcs是最长的"
			<<"2.m[i]表示以s[i]结尾的最长单调递增子序列的长度,s为原始序列\n"
			<<"m[i]=max{1,m[j]+1}，其中j=1...i-1,并且s[j]<s[i] \n"
			<<"r[i]记录以s[i]为尾元素的最长子序列的倒数第二个元素"
			<< endl;
		get_increase_subsequence();
		get_increase_subsequence(0);
	}
private:
	vector<int>s{ INT_MIN,4,3,4,9,7,8,7,9,12,34,23,16,78,45,35,39,37,40,8 };
	void get_increase_subsequence() {//动态规划算法
		vector<int>t(s);
		sort(t.begin(), t.end());
		size_t m = s.size()-1;
		size_t n = unique(t.begin(), t.end())-t.begin()-1;
		vector<vector<int>>r(m+1, vector<int>(n+1, 0));
		for (size_t i = 1; i <= m; ++i) {
			for (size_t j = 1; j <= n; ++j) {
				if (s[i] == t[j]) {
					r[i][j] = r[i - 1][j - 1] + 1;
				}
				else {
					r[i][j] = r[i][j - 1] > r[i - 1][j] ? r[i][j - 1] : r[i - 1][j];
				}

			}
		}
		vector<int>result;
		get_subseque(r, m, n, result);
		cout << "最长单调递增子序列为\n";
		for (auto i : result)
			cout << i << "\t";
		cout << "\n" << endl;
	}
	void get_increase_subsequence(int) {
		size_t n = s.size() - 1;
		vector<int>m(n + 1, 1);
		vector<int>r(n+1,0);
		int max = 1;//存储最长子序列的长度
		size_t index = 1;//存储最长子序列的尾元素的下标
		for (size_t i = 1; i <= n; ++i) {
			r[i] = i;
			for (size_t j = 1; j < i; ++j) {
				if (s[j] < s[i] && m[j] + 1 > m[i]) {
					m[i] = m[j] + 1;
					r[i] = j;
					if (m[i] > max) {
						max = m[i];
						index = i;
					}
				}
			}
		}
		vector<int>result;
		get_subseque(r, index,result);
		cout << "最长单调递增子序列为\n";
		for (auto i : result)
			cout << i << "\t";
		cout << "\n" << endl; 

	}
	void get_subseque(vector<int>&r, int i, vector<int>&result) {
		if (r[i] == i) {
			result.push_back(s[i]);
			return;
		}
		get_subseque(r, r[i], result);
		result.push_back(s[i]);
	}
	void get_subseque(vector<vector<int>>&r, size_t i, size_t j, vector<int>&result) {
		if (!i || !j)
			return;
		if (r[i][j] == r[i][j - 1]) {
			get_subseque(r, i, j - 1, result);
		}
		else if (r[i][j] == r[i - 1][j]) {
			get_subseque(r, i-1, j , result);
		}
		else {
			get_subseque(r, i - 1, j - 1, result);
			result.push_back(s[i]);
		}
	}
};

class solution15_4_6 {
public:
	void operator()() {
		cout << "curr[i]存储当前长度为i子序列的最小尾元素，\n"
			<< "curr的大小是目前为止的最大大小，如果当前元素大于尾元素\n"
			<< "则可以加入这个元素，否则每次用二分查找找到序列中\n"
			<< "第一个大于当前元素的值并替换，如果当前序列中有该元素则什么都不做\n"
			<< "last[i]存储目标数列元素s[i]结尾的最长子序列的前一个元素\n"
			<< "也就是在它前面比它小的元素"
			<< "\n"
			<< endl;
		cout << "最长单调递增子序列为 "
			<< "\n" << endl;
		mis_length();
	}
private:
	vector<int>s{ INT_MAX,4,3,4,9,7,8,7,9,12,34,23,16,78,45,35,39,37,40,8 };
	void mis_length() {
		size_t n = s.size() - 1;
		vector<int>last(n + 1,INT_MIN);
		vector<pair<int, int>>curr;
		curr.push_back({ INT_MIN, INT_MIN });
		int max = 0;

		for (size_t i = 1; i <= n; ++i) {
			if(s[i]>curr.back().second){
				last[i] = curr.back().first;
				curr.push_back({ i,s[i] });
				max = i;
			}
			else {
				int end = curr.size() - 1;
				int beg = 1;
				int mid;
				while (beg <= end) {
				    mid = (beg + end) >> 1;
					if (curr[mid].second > s[i]) {
						if (curr[mid - 1].second < s[i])
							break;
						else if (curr[mid - 1].second == s[i]) {
							mid = mid - 1;
							break;
						}
						else
							end = mid - 1;
					}
					else {
						beg = mid + 1;
					}
				}
	
				if (curr[mid].second != s[i]) {
					last[i] = curr[mid - 1].first;
					curr[mid].first = i;
					curr[mid].second = s[i];
				}
			}
		}
		vector<int>result;
		get_longest(last, max, result);
		result.push_back(s[max]);
		for (auto i : result)
			cout << i << "\t";
		cout << "\n" << endl;
	}

	void get_longest(vector<int>&last, int n, vector<int>&result) {
		if (last[n] == INT_MIN)
			return;
		get_longest(last, last[n], result);
		result.push_back(s[last[n]]);
	}
};
////////////////////////////////////
struct bstNode;
typedef shared_ptr<bstNode> pt_bst;
struct bstNode {
	bstNode(string k,pt_bst pa=nullptr,pt_bst lef = nullptr,pt_bst righ = nullptr):
		key(k),p(pa),left(lef),right(righ){}
	string key;
	pt_bst p;
	pt_bst left;
	pt_bst right;
};

//////////////////////////////////////
class solution15_5_1 {
public:
	void operator()() {
		cout << "见下一题solution15_5_2"
			<< endl;
	}
};

class solution15_5_2 {
public:
	void operator()() {
		optimal_bst();
	}
private:
	vector<double>p{ 0,0.04,0.06,0.08,0.02,0.10,0.12,0.14 };
	vector<double>q{ 0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05 };
//	vector<double>p{ 0,0.15,0.10,0.05,0.10,0.20 };
//	vector<double>q{ 0.05,0.10,0.05,0.05,0.05,0.10 };
	pt_bst rt;
	void optimal_bst() {
		int n = p.size() - 1;
		vector<vector<double>>e(p.size() + 1, vector<double>(p.size(),INT_MAX ));
		vector<vector<double>>w(e);
		vector<vector<int>>root(p.size(), vector<int> (p.size(), 0));
		for (int i = 1; i <= n+1; ++i) {
			e[i][ i - 1] = q[i - 1];
			w[i][ i - 1] = q[i - 1];
		}
		for (int len = 1; len <=n; ++len) {
			for (int i = 1; i <= n - len + 1; ++i) {
				int j = i + len - 1;
				w[i][j] = w[i][j - 1] + p[j] + q[j];
				for (int r = i; r <= j; ++r) {
					double temp = e[i][r-1] + e[r + 1][j] + w[i][j];
					if (temp < e[i][j]) {
						e[i][j] = temp;
						root[i][j] = r;
					}
				}
			}
		}
		for (auto &i : root) {
			for (auto j : i) 
				cout << j << "\t";
			cout << endl;
		}
		string temp = "K0";
		temp.back() = '0' + root[1][root.size() - 1];
		rt = shared_ptr<bstNode>(new bstNode(temp));//先制造根节点
		optimal_bst_insert(root,rt, 1, root.size() - 1);
		print_optimal_bst(rt);
	}
	//以rt为子树根节点，递归写入左右子树
	void optimal_bst_insert(vector<vector<int>>&root,pt_bst rt, int i, int j) {
			int r = root[i][j];
			string temp = "K0";
			string tmp = "d0";

			if (i <= r - 1) {
				temp.back() = '0' + root[i][r - 1];
				auto lef = shared_ptr<bstNode>(new bstNode(temp, rt));
				rt->left = lef;
				optimal_bst_insert(root, lef, i, r - 1);
			}
			else {
				tmp.back() = '0' + r - 1;
				auto lef = shared_ptr<bstNode>(new bstNode(tmp, rt));
				rt->left = lef;
			}

			if (r + 1 <= j) {
				temp.back() = '0' + root[r + 1][j];
				auto righ = shared_ptr<bstNode>(new bstNode(temp, rt));
				rt->right = righ;
				optimal_bst_insert(root, righ, r + 1, j);
			}
			else {
				tmp.back() = '0' + r;
				auto righ = shared_ptr<bstNode>(new bstNode(tmp, rt));
				rt->right = righ;
			}

	}
	void print_optimal_bst(pt_bst pt,int counter=0) {
		if (pt) {
			print_optimal_bst(pt->right,counter+1);
			for (int i = counter; i != 0; --i)
				cout << "\t";
			cout << pt->key << endl;
			print_optimal_bst(pt->left,counter+1);
		}
	}
};
class solution15_5_3 {
public:
	void operator()() {
		cout << "对渐进运行时间没有影响，会增大常数系数"
			<< endl;
	}
};

class solution15_5_4 {
public:
	void operator()() {

	}
};

//思考题
class solution15_1 {
public:
	void operator()() {
		cout << "假设每个起点都有权重，其实是s的权重为0，子问题为从s的各个邻接顶点出发到终点t的最长加权+该邻接点的权重，权重为s到该邻接点\n"
			<< "的权重,效率为边的条数"
			<< endl;
	}
};
////////////////////
struct node {
	node(size_t b,size_t e,size_t i):beg(b),end(e),index(i){}
	size_t beg;
	size_t end;
	size_t index;
};
class solution15_2 {
public:
	void operator()() {
		cout << "longest[i,j]表示从下标i到j的最长回文的对数，如果i=j,longest[i,j]=longest[i+1,j-1]+1,否则\n"
			<< "longest[i,j]=max{longest[i+1,j],longest[i,j-1]},运行时间为O(n^2)"
			<< endl;
		for (auto &i : vs) 
			longest_palindrome(i);
	}
private:
	vector<string>vs{ "aibohphobia","character","civic","racecar","aoigfebviafeiabvaifenai","fgsrrgsf" };
	void longest_palindrome(string &s) {
		string str = '0' + s;//有效下标必须从1开始，不然由于数组的原因，一维下标做减法可能越界
		size_t n = str.size()-1;//有效字符长度
		vector<vector<int>>longest(n+1, vector<int>(n+1,0));//i，j之间最长回文的对数
		vector<vector<node>>c(n + 1, vector<node>(n + 1,node(0,0,0)));//i,j之间node.index表示最后一个的相等元素的下标
		string palindrome = "";//node.beg,node.end表示子问题的下标
		for (size_t len = 2; len <= n; ++len) {
			for (size_t i = 1; i <= n - len + 1; ++i) {
				size_t j = i + len - 1;
				if (str[i] == str[j]) {
					longest[i][j] = longest[i + 1][j - 1] + 1;
					c[i][j].beg = i+1;
					c[i][j].end = j-1;
					c[i][j].index = i;
				}
				else {
					if (longest[i][j - 1] > longest[i + 1][j]) {
						longest[i][j] = longest[i][j - 1] ;
						c[i][j] = c[i][j - 1];
					}
					else {
						longest[i][j] = longest[i + 1][j];
						c[i][j] = c[i + 1][j];
					}
				}
			}
		}
		
		get_palindrome(c, str, palindrome, 1, n);
		cout <<s<< "最长回文子序列的为 " << endl;
		cout << palindrome << endl;
	}
	void get_palindrome(vector<vector<node>>&c, string &str, string &palindrome,int i, int j) {
		if (!c[i][j].index) {//下一个相等元素为的下标为0表示没有相等元素
			if (i <= j) {//如果i，j之间还有元素表示还可以加上一个元素
				palindrome += str[i];
				for (size_t r = palindrome.size() - 2; r != -1; --r)//此时结果中只存储了回文的前半段
					palindrome += palindrome[r];
			}
			else {//如果i,j之间没有元素
				string temp = "";
				for (size_t r = palindrome.size() - 1; r != -1; --r)
					palindrome += palindrome[r];
			}
			return;
		}
		else {
			palindrome += str[c[i][j].index];
			get_palindrome(c, str, palindrome, c[i][j].beg, c[i][j].end);
		}
	}
};
class solution15_3 {
public:
	void operator()() {

	}
private:
	vector<pair<double, double>>point{ {0,6},{1,0},{2,3},{5,4},{6,1},{7,5},{8,2} };
	double get_distance(pair<double, double>&lhs, pair<double, double>&rhs) {
		return sqrt(pow(lhs.first - rhs.first, 2.0)*pow(lhs.second - rhs.second, 2.0));
	}
	void bitionic_tours_min_distan() {
		vector<bool>flag(point.size(), true);

	}

};


class solution15_4 {
public:
	void operator()() {
		cout << "我的算法兼顾了最后一行的最后空格，rows[i,j]表示将下标为i到j放到一行时的\n"
			<< "额外空格的立方数之和，optimal[i]表示从1...i的最小立方数之和\n"
			<< "optimal[i]=min{optimal[j]+rows[j+1,i]}，j<=i,要求的为optimal[n] \n"
			<<"时间和空间都为O(n^2)"
			<< endl;
		regular_print();
	}
private:
	vector<int>len{ 0,3,6,5,3,2,4,5,6,7,3,2,5,1,4,6,5,3,5,2,11,7,3,7,6,2 };
	void regular_print(size_t M=20) {
		size_t n = len.size() - 1;
		vector<vector<int>>rows(n + 1, vector<int>(n + 1, INT_MAX));
		for (size_t i = 1; i <= n; ++i) {
			int sum = M - len[i];
			rows[i][i] = sum*sum*sum;

			for (size_t j = i+1;  j <= n; ++j) {
				sum = sum - 1 - len[j];
				if (sum >= 0)
					rows[i][j] = sum*sum*sum;
				else
					break;
			}
		}
		vector<int>optimal(n + 1, INT_MAX);
		optimal[0] = 0;
	
		vector<int>k(optimal);
		for (size_t i = 1; i <= n; ++i) {
			for (size_t j = 1; j < i; ++j) {
				if (optimal[j] != INT_MAX&&rows[j + 1][i]!=INT_MAX) {
					int temp = optimal[j] + rows[j + 1][i];
					if (temp < optimal[i]) {
						optimal[i] = temp;
						k[i] = j;
					}
				}
			}
			if (rows[1][i] < optimal[i]) {
				optimal[i] = rows[1][i];
				k[i] = i;
			}
		}

		cout << "额外空格的立方之和为" << endl;
		cout << optimal[n] << endl;
		cout << "排版为" << endl;
		print(k, n);
	}
	void print(vector<int>&k,size_t i) {
		if (i != k[i]) {
			print(k, k[i]);
			for (size_t n = k[i]+1; n <= i; ++n)
				cout << len[n] << "\t";
			cout << endl;
		}
		else {
			for (size_t n = 1; n <= i; ++n) 
				cout << len[n] << "\t";
			cout << endl;
		}
	}
};
class solution15_8 {
public:
	void operator()() {
		cout << "a.首先选择第一行有n种可能性，T(x)表示第x行一共有多少种\n"
			<< "可能性，有递归式T(x)>=2T(x-1)，因为选定第一行像素点\n"
			<< "后，下一行的像素点可选点最少有两个，形成等比数列\n"
			<< "T(m)>n*2^m \n"
			<< endl;
		cout << "s[i][j],表示经过原矩阵m[i][j]点的最小损坏，有递归式\n"
			<< "s[i][j]=min{s[i-1][j],s[i-1][j-1],s[i-1][j+1]\n"
			<< "s[m][k]为所求，其中，m为原矩阵的行数，k为使最后一行\n"
			<< "最小的值\n"
			<< endl;
		const int m = 7;
		const int n = 6;
		srand(static_cast<unsigned int>(time(nullptr)));
		vector<vector<int>>d(m + 1, vector<int>(n + 1, 0));

		cout << "原矩阵为" << endl;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				d[i][j] = rand() % 10+1;
				cout << d[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "\n" << endl;

		min_disruption(d);
	}
	void min_disruption(vector<vector<int>>&d) {
		vector<vector<int>>s(d.size(), vector<int>(d.front().size(), INT_MAX));
		vector<vector<int>>r(s);
		for (size_t i = 1; i < d.size(); ++i)//初始化
			s[i][0] = 0;
		for (size_t i = 1; i < d.front().size(); ++i)
			s[0][i] = 0;

		size_t m = d.size() - 1;
		size_t n = d.front().size() - 1;

		for (size_t i = 1; i < d.size(); ++i) {
			for (size_t j = 1; j < d.front().size(); ++j) {

				int dis = 0;
				if (j == 1) {
					dis = s[i - 1][j] < s[i - 1][j + 1] ? s[i - 1][j] : s[i - 1][j + 1];
				}
				else if (j == m) {
					dis = s[i - 1][j] < s[i - 1][j - 1] ? s[i - 1][j] : s[i - 1][j - 1];
				}
				else {

					dis = s[i - 1][j - 1] < s[i - 1][j] ? s[i - 1][j - 1] : s[i - 1][j];
					if (s[i-1][j - 1] < dis)
						dis = s[i-1][j - 1];
				}

				s[i][j] = dis + d[i][j];				
			}
		}
		
		cout << "递归累加后的矩阵为\n" << endl;
		for (size_t i = 1; i < d.size(); ++i) {
			for (size_t j = 1; j < d.front().size(); ++j) {
				cout << s[i][j] << "\t";
			}
			cout << endl;
		}

		int index = n;
		int min = s[m][n];
		for(size_t i=1;i<n;++i)
			if (min > s[m][i]) {
				min = s[m][i];
				index = i;
			}

		cout << "\n最小损坏为" << endl;
		cout << min << endl;

		print(s, d, m, index);
	}
	void print(vector<vector<int>>&s,vector<vector<int>>&d, int i, int j) {
		vector<int>stack;
		while (i >= 1) {
			stack.push_back(j);
			int sum = s[i][j] - d[i][j];
			if (j == 1) {
				if (sum == s[i - 1][j + 1])
					j = j + 1;
			}
			else if (j == s.front().size() - 1) {
				if (sum == s[i - 1][j - 1])
					j = j - 1;
			}
			else {
				if (sum == s[i - 1][j + 1])
					j = j + 1;
				else if (sum == s[i - 1][j - 1])
					j = j - 1;
			}
			i -= 1;
		}

		cout << "\n" << endl;
		size_t m = stack.size() - 1;
		for (int i = m; i >=0; --i)
			cout << "（" << m -i+1 << "," << stack[i] << ")" << endl;

		cout << endl;
	}
};

class solution15_9 {
public:
	void operator()() {
		cout << "f[i][j][k][h]=min{f[i][m-1][k][L[m]]+f[m+1][j][L[m]+1][h]+h-k+1 \n"
			<<"0<=i<=m<=j<L.length,1<=k<=L[i],L[j]<=h<=L.length \n"
			<<"从字符串S的k到h位划分点为L[i]--L[j]之间的点，m表示从其中一个点的下标开始\n"

			<<"我看到别的答案的递归式没有考虑原始字符串的长度，可能是我没看懂，所以可能有更简单的方法\n"
			<< endl;

		min_spilt(spilt, 20);
	}
private:
	//vector<int>spilt{ 1,11,14,17,20,25,30 };
	//vector<int>spilt{ 1,10,13,16,19,24,29 };
	vector<int>spilt{ 2,8,10 };
	void min_spilt(vector<int>&spilt, int s) {
		const int n = spilt.size();
		vector<vector<vector<vector<int>>>>f(
			n, vector<vector<vector<int>>>(n, vector<vector<int>>(s + 1, vector<int>(s + 1, INT_MAX)))
		);
		vector<vector<vector<vector<int>>>>r(f);

		for (int i = 0; i < n; ++i)
			for (int j = 1; j <= spilt[i]; ++j)
				for (int k = spilt[i]; k <= s; ++k) {
					f[i][i][j][k] = k - j + 1;
					r[i][i][j][k] = i;
				}//O(L.length*S.length^2)

		for (int len = 1; len <= n; ++len) {//O(L.length*S^3.length^2)
			for (int i = 0; i <= n - len; ++i) {
				int j = i + len - 1;
				for (int k = 1; k <= spilt[i]; ++k) {
					for (int h = spilt[j]; h <= s; ++h) {
						for (int m = i; m <= j; ++m) {
							int cost;
							if (i == j)
								cost = h - k + 1;
							else if (m == i)
								cost = f[i + 1][j][spilt[i]+1][h] + h - k + 1;
							else if (m == j)
								cost = f[i][j - 1][k][spilt[j]] + h - k + 1;
							else
								cost = f[i][m - 1][k][spilt[m]] + f[m + 1][j][spilt[m]+1][h] + h - k + 1;

							if (cost < f[i][j][k][h]) {
								f[i][j][k][h] = cost;
								r[i][j][k][h] = m;
							}
						}
					}
				}
			}
		}


		cout << "最少花费为" << endl;
		cout << f[0][n-1][1][s] << endl;

		cout << "划分顺序为" << endl;
		print(r, 0, n - 1, 1, s);
		cout << endl;
	}

	void print(vector<vector<vector<vector<int>>>>&r, int i, int j, int k, int h) {
		if (i <= j) {
			int m = r[i][j][k][h];
			cout << spilt[m] << "\t";
			if (i != j) {
				if (m == i) {
					print(r, i + 1, j, spilt[i] + 1, h);
				}
				else if (m == j) {
					print(r, i, j - 1, k, spilt[j]);
				}
				else {
					print(r, i, m - 1, k, spilt[m]);
					print(r, m + 1, j, spilt[m] + 1, h);
				}
			}
		}
	}
};
class solution15_10 {
public:
	void operator()() {
		cout << "选择最大回报率的投资"
			<< "d.可能是我对题目理解有误，因为貌似可以使用贪心算法\n"
			<< endl;
	}
};
class solution15_11 {
public:
	void operator()() {
		cout << "s[i][j]代表第i个月已经一共生产了j个机器所花费的最小成本\n"
			<< "s[i][j]=min{s[i-1][k]+max{0,j-k-m}*c+h(j-d[i])}\n"
			<< "其中d[i]<=j<=d[n],d[i-1]<=k<=j  \n"
			<<"运行时间为n*d[n]^2"
			<< endl;
		const int n = 10;
		const int m = 30;
		const int c = 10;
		srand(static_cast<unsigned int>(time(nullptr)));
		vector<int>d(n+1,0);

		cout << "\n" << "每月累计所需个数" << endl;
		for (int i = 1; i <= n; ++i) {
			cout << i << "\t";
			d[i] = rand() % 11 + 25 + d[i - 1];
		}
		cout << endl;
		for (int i = 1; i <= n; ++i)
			cout << d[i] << "\t";

		cout << "\n" << endl;

		min_cost(d, n, m, c);
	}
private:
	int h(int k) {
		return 2*k;
	}
	void min_cost(vector<int>&d,int n,int m,int c) {
		vector<vector<int>>s(n + 1, vector<int>(d[n]+1, INT_MAX));
		vector<vector<int>>r(n + 1, vector<int>(d[n] + 1, 0));

		for (int i = 0; i <= d[n]; ++i)
			s[0][i] = i - m > 0 ? c*(i - m) + h(i) : h(i);

		for (int i = 1; i <= n; ++i) {
			for (int j = d[i]; j <= d[n]; ++j) {
				for (int k = d[i - 1]; k <= d[n]; ++k) {
					if (j > k) {
						int stock = j - d[i] > 0 ? h(j - d[i]) : 0;
						int hire = j - k - m > 0 ? c*(j - k - m) : 0;
						int cost = s[i - 1][k] + stock + hire;
						if (cost < s[i][j]) {
							s[i][j] = cost;
							r[i][j] = k;
						}
					}
					else {//上个月就已经将本月所需生产完毕
						int cost = s[i - 1][k] + h(k - d[i]);
						if (cost < s[i][j]) {
							s[i][j] = cost;
							r[i][j] = k;
						}
					}
				}
			}
		}

		cout << "\n最小成本花费为" << endl;
		cout << s[n][d[n]] << endl;

		cout << "注意是从0月开始的，每月生产个数为\n"
			<< endl;
		print(r, n, d[n]);
		cout << endl;
	}
	void print(vector<vector<int>>&r, int i, int j) {
		if (i >= 0) {
			print(r, i - 1, r[i][j]);
			cout << i << "/"<< j - r[i][j] << "\t";
		}
	}
};

class solution15_12 {
public:
	typedef int vorp;
	typedef int price;
	void operator()() {
		cout << "m[i]为i十万美元能得到的最大vorp，m[i]=m[i-1]+max{r[i-1]+1}\n"
			<< "r[i]表示i十万美元最优化结果买完后剩余的钱，max{moneny}表示用\n"
			<< "money能在未买位置中能得到的最大值\n"
			<<"上面是我自己想到的算法，但第二天发现有一种情况不会得到最优解\n"
			<<"才发现我使用的是类似贪心算法。然后看了别人的递归式重新写了一遍\n"
			<<"For every free-agent player x, let pos(x) denote the player’s position, cost(x) denote \n"
			<< "the amount of money it will cost to sign the player, and vorp(x) denote the\n"
			<< "player’s VORP\n"
			<< "Let f(i, j) denote the maximum total VORP of the players szigned for first i position\n"
			<< "and used j money\n"
			<< "Recursive formulation :\n"
			<< "f(i, j) = max{ f(i - 1, j), f(i - 1, j - cost(k)) + vorp(k) }\n"
			<< "The answer is f(N, X)\n"
			<< "Running time : O(max(N, P) * X)\n"
			<< endl;
		const int x = 50;
		const int n = 15;
		const int p = 5;
		vector<pair<vector<pair<price,vorp>>,bool>>pos;//bool值表示在该位置还能不能买，如果已经买过就不能买了
		srand(static_cast<unsigned int>(time(nullptr)));
		pos.push_back(pair < vector < pair<price, vorp>>,bool>{vector<pair<price,vorp>>(p+1, pair<int, int>{0, 0}), true});
		for (int i = 0; i < n; ++i) {//生成随机人
			pair<vector<pair<int, int>>,bool>peo;
			peo.first.push_back({ 0,0 });

			for (int j = 0; j < p; ++j) {
				peo.first.push_back({ rand() % 18 + 5, rand() % 8 + 3 });
				peo.second = true;
			}
			pos.push_back(peo);
		}
		for(int i=0;i<n;++i)
			sort(pos[i].first.begin()+1,pos[i].first.end(),
				[](pair<int, int>&lhs, pair<int, int>&rhs) {
			return lhs.second > rhs.second;
		}
		);
		
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= p; ++j) 
				cout << pos[i].first[j].first << "|" << pos[i].first[j].second << "\t";
			cout <<"\t"<<i<< endl;
		}
		vorp_max(pos, x, n, p);
		cout << endl;
		vorp_max(pos, x, n, p,true);
	}
private:
	void vorp_max(vector<pair<vector<pair<int, int>>, bool>>&pos,
		int x,int n,int p) {
		vector<int>m(x + 1, 0);
		vector<int>r(x + 1, 0);
		for (int i = 1; i <= x; ++i) {
			int rm = r[i - 1] + 1;
			pair<int, int>index{ 0,0 };//接下来能够买到的人的下标

			for (int k = 1; k <= n; ++k) {
				if(pos[k].second){
					for (int j = 1; j <= p; ++j) {
						if (pos[k].first[j].first < rm) {
							int curr_v = pos[k].first[j].second + m[i - 1];
							if (curr_v > m[i]) {
								m[i] = curr_v;
								index.first = k;
								index.second = j;
							}

						}
					}
				}
			}

			if (index.second) {//条件true表示能够用剩下的钱来买到最优解
				//打印最优解并更新
				cout << index.first << "\t" << index.second <<"\t\t";
				cout << pos[index.first].first[index.second].first << "|"
				<<pos[index.first].first[index.second].second << endl;

				pos[index.first].second = false;//下次改位置不能买
				r[i] = rm - pos[index.first].first[index.second].first;
			}
			else//钱不够剩下的钱加1
				r[i] = r[i - 1] + 1;

		if (!m[i])//钱不够等于上一次能买到的最优解
			m[i] = m[i - 1];
		}
		cout << "贪心算法能够达到的最大vorp值为" << endl;
		cout << m[x] << endl;
	}
	void vorp_max(vector<pair<vector<pair<int, int>>, bool>>&pos,
		int x, int n, int p,bool) {
		vector<vector<int>>m(n + 1, vector<int>(x + 1, 0));
		vector<vector<pair<int, int>>>index(n + 1, vector<pair<int, int>>(x+1,{ 0, 0 }));
		int max = 0;
		for (int i = 1; i <= n; ++i ) {
			for (int j = 1; j <= x; ++j) {

				if (m[i - 1][j] > m[i][j - 1]) {
					m[i][j] = m[i - 1][j];
					index[i][j] = index[i - 1][j];
				}
				else {
					m[i][j] = m[i][j-1];
					index[i][j] = index[i][j-1];
				}
				
				for (int k = 1; k <= p; ++k) {
					int cost = pos[i].first[k].first;
					if (j > cost) {
						int vorp = pos[i].first[k].second;
						if (m[i - 1][j - cost] + vorp > m[i][j]) {
							m[i][j] = m[i - 1][j - cost] + vorp;
							index[i][j] = make_pair(i, k);
						}
					}
				}
			}
		}
		print(pos, index, n, x);
		cout << "动态对话和规划算法最优化结果为" << endl;
		cout << m[n][x] << endl;
	}
	void print(vector<pair<vector<pair<int, int>>, bool>>&pos,
		vector<vector<pair<int,int>>>&index, int i, int j) {
		if (index[i][j].first) {
			cout << index[i][j].first << "\t" << index[i][j].second << "\t\t";
			cout << pos[index[i][j].first].first[index[i][j].second].first << "|"
				<< pos[index[i][j].first].first[index[i][j].second].second << endl;

			print(pos, index, index[i][j].first-1, j - pos[index[i][j].first].first[index[i][j].second].first);
		}
	}
};
#endif 
