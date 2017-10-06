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
		cout << "��̬�滮����O(n^3)��ע�͵������п��Լ�����һ�����Ž�"
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
		//	cout << activity[6].first << "\t" << activity[6].second << endl;//��6�������֮ǰ�ĵڶ����
		for (int len = 1; len <= n + 1; ++len) {
			for (int i = 0; i <= n - len + 1; ++i) {
				int j = i + len - 1;
				for (int k = i + 1; k < j; ++k) {
					int temp = 0;
					//ȷ��i,j֮���Ƿ��в���ͻ�
					if (activity[k].first >= activity[i].second&&activity[k].second <= activity[j].first)
						temp = c[i][k] + c[k][j] + 1;
					if (temp > c[i][j]) {//c[i][j]ֻ�ܼ�¼����ʹ����ֵ����һ�������Բ��ܼ������п��ܵ����Ž�
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
		cout << "�����е��㷨˵�����ƣ����������ݻ�����һ����������л������ʼ�ģ������������Ļ���������õ����Ž⣬�Դ����� \n"
			<< endl;
		greedy_activity_selector();
	}
private:
	vector<pair<int, int>>activity{ { 0,0 },{ 1,4 },{ 3,5 },{ 0,6 },{ 5,7 },{ 3,9 },{ 5,9 },{ 6,10 },{ 8,11 },{ 8,12 },{ 2,14 },{ 12,16 }};
	void greedy_activity_selector() {
		//����˵����ʼ��ʱ������
		sort(activity.begin(), activity.end(), [](pair<int, int>&lhs, pair<int, int>&rhs) {return lhs.first < rhs.first; });
		deque<int>s;//�洢���Ž��
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
		cout << "������ʱ��Ļ����������ѡ������߲����ҵ������ݼ� \n"
			<< "����Ψһ���ص��Ļ���������������������ص�������һ�����ص��������ҵ����Ž� \n"
			<<"������翪ʼ��������������ҵ����Ž�"
			<< endl;
	}
};

class solution16_1_4 {
public:
	void operator()() {
		cout << "��ʱ��˳��ʹ��̰���㷨������Ŀ�ʼʱ�����򣬻��ʼʱ���Ƿ���֮ǰ�Ļ���������µ��Ѿ�ʹ�ù��Ľ��ң�����оͽ���ý��ң����û��\n"
			<< "�ͷ���һ���½���\n"
			<<"���Կ�����������ÿһ��ѭ�������ᳬ�������n,����ʱ��Ϊcn,��Ҫ����n�Σ���������Ϊcn^2 "
			<< endl;
		least_greedy();
	}
private:
	vector<pair<int, int>>activity{ { 0,0 },{ 1,4 },{ 3,5 },{ 0,6 },{ 5,7 },{ 3,9 },{ 5,9 },{ 6,10 },{ 8,11 },{ 8,12 },{ 2,14 },{ 12,16 } };

	void least_greedy() {
		sort(activity.begin(), activity.end(), [](pair<int, int>&lhs, pair<int, int>&rhs) {return lhs.first < rhs.first; });
		list<int>time_list;//��¼ĳһʱ�����ڽ��еĻ���������ʱ�����������
		vector<int>room(activity.size(), INT_MIN);//��¼ÿһ������õĽ���
		vector<bool>classRoom;//��¼ʹ�ù��Ľ��ң�
		size_t counter = time_list.size();//��¼ʹ�ý��ҵ����ֵ
		for (int i = 0; i != activity.size(); ++i) {
			selector_insert(time_list,room,classRoom, i);
			if (time_list.size() > counter)
				counter = time_list.size();
		}
		cout << "��Ҫ�õ� " << counter << "������\n" << endl;
		for (int i = 0; i != activity.size(); ++i)
			cout << "[" << activity[i].first << "\t" << activity[i].second << ")\t" << room[i] << endl;
	}


	void selector_insert(list<int>&time_list, vector<int>&room, vector<bool>&classRoom, int k) {
		auto iter = time_list.begin();
		for (; iter != time_list.end() && activity[*iter].second <= activity[k].first; iter = time_list.begin()) {
			classRoom[room[*iter]] = false;//k���ʼʱ�޳����д�ʱ�Ѿ������Ļ����ռ�õĽ�����Ϊ����
			time_list.erase(iter);
		}

		auto it = 0;
		for (; it != classRoom.size() &&classRoom[it]; ++it)
			;
		if (it == classRoom.size()) {//����Ѿ�ʹ�ù������н��Ҷ��л���ڽ����򿪱�һ���½���,���������н���
			classRoom.push_back(true);
			room[k] = classRoom.size()-1;
		}
		else {
			room[k] = it;
			classRoom[it] = true;
		}

		int c = 0;
		for (iter = time_list.begin(); iter != time_list.end() && activity[k].second > activity[*iter].second;++c, ++iter)
			;//���k������ʱ������ʵ�λ�ñ����´λ��ɾ��
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
		cout << "��Ϊ���������ܹ�װ���������ڻ���x��Ԫÿ������Ʒg����ѡ����g����y,��x>y,����x���y�ܵõ����õĽ� "
			<< endl;
	}
};

class solution16_2_2 {
public:
	void operator()() {
		cout << "profit[i][j]����ʣ������Ϊj��װ1...i����Ʒ��������� \n"
			<< "profit[n][w]Ϊ���󣬴���������w��1...n����Ʒ�е�������� \n"
			<< "�����i����Ʒ����������ʣ������j,������profit[i][j]=profit[i-1][j]����Ϊ��Ȼ��ʣ������װ���³��ص���Ʒ \n"
			<<"�����i����Ʒ������С�ڵ���ʣ������j,������profit[i][j]=max{profit[i-1][j],i.price+profit[i-1][j-i.weight] \n"
			<<"��Ϊ����ѡ��װ��i����Ʒ����װ��i����Ʒ����ʣ��������ȥװ1...i-1����Ʒ��ѡȡ���нϴ��ֵ�������������Ϊ0"
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
		cout << "����Ʒ�����ĵ��������Ʒ����A���ӵ�һ����Ʒ��ʼֱ����������װ����һ����ƷΪֹΪ���Ž⣬֤���� \n"
			<< "�������Ž������Aj��������Ai������j>i���������Ai����Aj�γ�һ�����Ž� \n"
			<< endl;
	}
};
class solution16_2_4 {
public:
	void operator()() {
		cout << "�����iΪԲ��mΪ�뾶��Բ������������Բ�ڵĲ�ˮ����Ϸ����γ�����ͼ��Ȼ�����ҵ��Ĳ�ˮ��ΪԲ���ظ����ϲ���ֱ������Ŀ�ĵ�j \n"
			<< "�ҵ���ͼ����Ȩ���·������������������ӽṹ��15-3���Ѿ����ˣ�������д����ѧ��ͼʱӦ�û����������� \n"
			<< endl;
	}
};

class solution16_2_5 {
public:
	void operator()() {
		cout << "���ȶԵ㼯�������������ʼ�ĵ�x1Ϊ��λ���ȵ���������㣬�ҵ���һ������x1+1�ĵ�xk,Ȼ����xkΪ����ظ����ϲ��� \n"
			<< "֤����ֻ��֤����һ���ҵ��ļ���f[d]�����Ž��е�ĳ������s[d],f[d]��������s[d]�����Ӽ�����Ϊû�б�x1��С��Ԫ�أ���xk���ܱ����� \n"
			<< "����s[1]...s[d]����f[d]�Ĳ���Ԫ�أ���ô��Ȼ������һ������x1����s[k]��f[d]�����Ӽ�,��Ϊ�����ܴ��ڳ�f[d]��Ԫ��������κ��κ� \n"
			<< "Ԫ������x1��һ������Ϊ1�ļ������棬��ʱ���԰�s[1]...s[d]�е�f[d]�е�Ԫ�س��������s[k]�����f[d]����ʱ���ϵĸ���û�иı� \n"
			<< "����f[d]��Ȼ�����Ž⼯���е�һ��,����ʣ������Ԫ����xk��Ϊx1�ظ��������ۣ���֤ \n"
			<< endl;
	}
};

class solution16_2_6 {
public:
	void operator()() {
		cout << "����װ����ļ�ֵ�ܶ���ߵ���Ʒ��ֱ������,ǰ���Ǳ���������WΪĳһ��Χ�ڳ�������һ�����ѻ���cn,ÿ��ȡ���ֵ���ȡW��\n"
			<<"ÿ��ά��������໨��lgn,cn+cwlgn=O(n) \n"
			<< endl;
	}
};

class solution16_2_7 {
public:
	void operator()() {
		cout << "A,B����������ֻ��֤��a1^b1�����Ž��ĳһ����費�ǣ����Ȼ��a1^by,ax^b1,����a1>ax,b1>by,\n"
			<< "��֤a1^b1*ax^by>=a1^by*ax^by,�����ã�a1/ax)^(b1-by)>=1����Ȼ���� \n"
			<< "���Կ�����a1^b1*ax^by����ԭ�������Ž⣬����a1^b1��Ȼ�����Ž��ĳһ�����ʣ�µ����Դ�����,��֤ \n"
			<<"���򻨷�cnlgn,��˻���cn�������ܻ���cnlgn"
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
	void operator()() {//�й���������������͹��ⲻͬ����֮ǰʹ�õ��Ķ����й������������Ķ���
		cout << "�����κ�һ��ֻ��һ�������Ľڵ㣬������ȥ���ýڵ㽫��������ֲ���ýڵ�λ�ý����������"
			<< endl;
	}
};

class solution16_3_3 {
public:
	void operator()() {
		cout << "��һ����ƫ������Ȼû��������ʣ����ұ�ģ��������ĸ߶ȵ����ڲ��ڵ����������ÿ���ڲ��ڵ����ײ��һ���ⶼ���ҽ���һ��Ҷ�ڵ� \n"
			<< "��������ȫƫ����߻����ұ�\n"
			<< "0,10,110,1110,11110....."
			<< endl;
	}
};

class solution16_3_4 {
public:
	void operator()() {
		cout << "������һ���Ϊd��Ҷ�ڵ�c�������Ϊc.freq*d,��d��c.fred��ӣ����ýڵ���������Ƚڵ�ĺͱ�Ȼ���������Ĵ��ۣ���ֻ������ÿһ��Ҷ�ڵ��\n"
			<< "��Ĵ���"
			<< endl;
	}
};

class solution16_3_5 {
public:
	void operator()() {
		cout << "û̫������Ŀ��˼"
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
		cout << "abcdefgh,a<f<2*a,�����������ʱ��ÿ�ι�����������ᱻ������С�ѵ�ĩβ�����Ի���ÿ�ζ��ܹ�����������Ҷ�ӵ���������ÿ��Ҷ�ӽڵ� \n"
			<< "�ĸ��ڵ㶼������ɺ���γ�(ab)(cd)(ef)(gh)����С�ѣ�ͬ��(ab)<(gh)<2*(ab)����Ϊ256��2���ݣ��������ı�����Ϊ��ȫ������ \n"
			<< "ÿһ��Ҷ�ڵ㶼������ͬ�ĸ߶�lg(256)=8,ÿһλ����8λ����"
			<< endl;
	}
};

class solution16_3_9 {
public:
	void operator()() {
		cout << "������һ�����֤���������"
			<< endl;
	}
};

class solution16_4_1 {
public:
	void operator()() {
		cout << "����3����������֤��"
			<< endl;
	}
};

class solution16_4_2 {
public:
	void operator()() {
		cout << "ͬ��"
			<< endl;//�����������е������޹�
	}
};

class solution16_4_3 {
public:
	void operator()() {
		cout << "���費�ǲ�������ô��Ȼ����һ��xʹ����Ȳ���ǰ�ߵ��������Ӽ�Ҳ���Ǻ��ߵ����Ķ����Ӽ���x��s,������I���Ķ��壬 \n"
			<< "����벻���ں��ߵ��������Ӽ����Ȼ����ǰ�ߣ���֮ͬ�����Լ��費���� \n"
			<< endl;
	}
};

class solution16_4_4 {
public:
	void operator()() {
		cout << "��ΪA������S�Ļ��֣����Ծ��ж�����"
			<< endl;//����֤
	}
};

class solution16_4_5{
public:
	void operator()() {
		cout << "��С����С�����������и���������"
			<< endl;//��С��û̫����
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
		//���ݳͷ�������
		sort(a.begin(), a.end(), [](pair<size_t, size_t>&lhs, pair<size_t, size_t>&rhs) {return lhs.second > rhs.second; });
		vector<size_t>task;
		size_t punishment = 0;
		for (size_t i = 0; i < a.size(); ++i)
			if (a[i].first > task.size())//̰��ѡ����������ĵ�i������Ľ�ֹʱ�䲻������ǰ��������task�����������
				task.push_back(i);
			else
				punishment += a[i].second;
		sort( task.begin(),task.end(), [](size_t lhs, size_t rhs) {return lhs > rhs; });
		cout << "���ŵ���Ϊ" << endl;
		for (auto i : task)
			cout << "a" << 7-i << "\t";//������Ŀ�����жϵ������Ķ�Ӧ��ԭ�������
		
		cout << "\n�ܳͷ�Ϊ " << endl;
		cout << punishment;
		cout << "\n" << endl;
	}
};

class solution16_5_2 {
public:
	void operator()() {
		cout << "k=Ai��k,i=1...|A|,˳��ɨ��Ԫ��" << endl;
	}
};
//˼����
class solution16_1 {
public:
	void operator()() {
		cout << "a/b,������������������Ҫ��һ��С��Ҫ����Ǯ����֤������k=1ʱ��������Ǯa1c+a2>=c�����,a1>=1,���ʹ��̰���㷨���õ�a1+a2 \n"
			<< "�����������Ǯ����c������²�ʹ�����c����õ�a1c+a2��Ӳ�ң���Ȼ̰���㷨�ܵõ����Ž⣬\n"
			<< "����̰��ˣ����c^(k-1)�ϳ������������c^kʱ����g(k,x)��ʾ��̰���㷨�����������c^(k)�������Ǯx�����Ž⣬����ǮΪakc^k+x>c^k��\n"
			<< "��ʹ�����c^k����ô���Ž�Ϊg(k-1,akc^k+x)=ak*c+g(k-1,x),�����ʹ��̰���㷨Ϊg(k,akc^k+x)=ak+g(k-1,x)<ak*c+g(k-1,x),��֤ \n"
			<< "c.12,9,1������27 \n"
			<< "d.ʹ�ö�̬�滮�����忴ע�ͣ�����ѭ��������Ȼ��cnk"
			<< endl;
		get_min();
	}
private:
	vector<int>notes{ 1,2,5,10,20 };
	void get_min(int dollar = 99) {
		vector<int>m(dollar + 1, INT_MAX);// m[i]��ʾҪ����Ǯi����С��
		vector<int>r(m);//r[i]��ʾ��Ǯi��һ���ҵ����
		m[0] = 0;
		//ѭ��֮ǰ��Ҫ�ȶ����������������ʡ��
		for(int i=1;i<=dollar;++i)
			for (size_t j = 0; j < notes.size() && i >= notes[j]; ++j) {
				int temp = 1 + m[i - notes[j]];
				if (temp < m[i]) {//�Աȵ�һ�����ĸ�����ֵ�ܵõ���Сֵ
					m[i] = temp;
					r[i] = notes[j];
				}
			}
		cout << "������ " << m[dollar] << " ��Ӳ��" << endl;
		cout << "���Ϊ" << endl;
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
		cout << "a,ʹ��̰���㷨,ÿ�ζ�ѡȡû����������к�ʱpi����С������ \n"
			<< "֤����С��ʱ������a1Ҫ������ɣ�����ĳ�����Ž�ĵ�һ��������a1����ak,����si=s(i-1)+pi,s��c��ʾ�๫���壬������i��ʾ \n"
			<< "��������ɺ��˳�������ԭʼa1,a2,��˳��a1ǰ����������Ϊg,��ʱc(1)=s(g+1)=sg+p1,ck=s1=pk, \n"
			<< "ak��a1֮����ۼƴ��ۺ�Ϊx,����ǰg+1��Ĵ��ۺ�Ϊpk+x+sg+p1,��������a1��ak,��ʱs1=p1,��Ϊp1<pk������si=s(i-1)+pi���ۼ��� \n"
			<< "ak��a1֮����ۼƴ��ۺ�x'<=x,sg'<=sg,����ǰg+1��Ĵ��ۺ�pk+x'+sg'+p1<=pk+x+sg+p1,����ĳ�����Ž�ĵ�һ�������ȻΪa1,����������� \n"
			<< "������������Դ�����\n"
			<< "b.���Ȱ�����ʱ�����������Ȼ���ͷ�ʱ��������ȶ����򣬵��ͷ�ʱ�䵽��ʱ���е�һ������ֱ����һ��������ͷ�ʱ�䵽���ʱ�Ƚ�\n"
			<< "�������������ʣ��ʱ�����һ�����������ʱ�䣬�����������ռ����ʣ������ʱ�������������ȶ��У������������������񣬲��� \n"
			<< "δ���е�����������ȶ��У�ֱ��������һ�αȽϣ��������Ա�֤�ܹ�������ɵ�����������ɣ�֤����һС����֤�� \n"
			<< "����ĳ�����ΪҪģ��ʱ��ķ�չ�����������ִ�У�����Ҫ����һЩ"
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
		int sum = 0;//ÿ��������ɵ�ʱ���
		int t = tk[0].r;//������������ʼ���е�ʱ�䣬ע�ⱻ�������������������ʱ��ʼ����ʱ��ʱ�䲻���ڵ�һ�����е�ʱ��
		for (size_t i = 0; i < tk.size(); ++i) {
			if (priority.empty()) {
				priority.insert(priority.begin(),tk[i]);//���е�һ��������������
				cout << "���� " << tk[i].index << " ��" << "ʱ�� " << t << " ��ʼ����" << endl;
			}
			else {
				while (!priority.empty() && tk[i].r - t >= priority.front().p) {//��ĳ��������ͷ�ʱ�䵽֮ǰһֱ���п���������
					sum += t + priority.front().p;//��¼���ʱ��
					t += priority.front().p;
					cout << "���� " << priority.front().index << " ��ʱ�� " << t << "�������" << endl;
					priority.erase(priority.begin());//ɾ���Ѿ�������ɵ�����
					cout << "��ͬʱ���� " << priority.front().index << "��ʼ���� " << endl;
				}
				int surplus = priority.front().p - (tk[i].r - t);//�������������ʣ��ʱ��
				if (surplus > tk[i].p) {//����������е������ʣ��ʱ��ȿ��Կ�ʼ����������ͷ�ʱ���
					priority.front().p = surplus;
					t = tk[i].r;
					cout << "���� " << priority.front().index << "��ʱ�� " << t << " ������" << ",ʣ������ʱ�� " << priority.front().p << endl;
					cout << "��ͬʱ���� " << tk[i].index << "��ʼ���� " << endl;
					priority.insert(priority.begin(), tk[i]);
				}
				else {//�������е������ʣ��ʱ����ͷ�ʱ��С,����ִ��ԭ���񣬽���ִ������������λ��
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
			cout << "���� " << priority.front().index << "��ʱ�� " << t << " ���";
			priority.erase(priority.begin());
			if(!priority.empty())
				cout<< "��ͬʱ���� " << priority.front().index << "��ʼ���� " << endl;
		}
		cout << "\n\nƽ������ʱ��Ϊ " << static_cast<double>(sum) / tk.size() << endl;
	}
};

class solution16_3 {
public:
	void operator()() {
		cout << "a.ȱ�����֪ʶ \n"
			<< "b.c.d.e��"
			<< endl;
	}
};

class solution16_5{
public:
	void operator()() {
		cout << "a.�㷨ʱ�������ע��\n"
			<<"b.r1...rn����������ʵ���r1...rk����������ʼ���rk+1...rn����������� \n"
		//	<<"c.r1...rk�����������ӦΪ"
			<< endl;
		cache_hit();
	}
private:
	void cache_hit(int k = 5) {
		vector<int>request;
		list<int>cache;
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 1; i != 71; ++i) {//�������һ����Χ������
			request.push_back(rand() % 10 + 0);
			cout << request.back() << "\t";
		}
		cout << endl;
		int sum = 0;
		vector<list<int>>future(11, list<int>());
		for (size_t i = 0; i < request.size(); ++i) //ɨ��һ�����У�cn,�������߻��������ڶ�ζ�ȡͬһ����
			future[request[i]].push_back(i);//��¼��������ͬԪ�س��ִ���±�,ʵ��Ӧ����Ӧʹ�ù�ϣ��

		for (size_t i = 0; i < request.size(); ++i) {//ģ�����ÿ��Ԫ��
			future[request[i]].erase(future[request[i]].begin());//ɾ���Ѿ����ֹ���Ԫ�ص��±�
			if (!cache.empty()&&request[i] == cache.front()) {//������У���Ϊ���뻺��ķ�ʽ��ģ�⻺�������cache���ǽ����ȳ��ֵ�Ԫ�ط�����λ
				cout << "hit " << request[i] << endl;
				++sum;
				if (!future[cache.front()].empty()) {//������е�Ԫ���´λ������
					auto iter = ++cache.begin();
					for (; iter != cache.end() && future[*iter].front() < future[cache.front()].front(); ++iter)
						;//ck
					if (iter != ++cache.begin()) {
						cache.insert(iter, request[i]);
						cache.erase(cache.begin());
					}
				}
				else {//����Ԫ���´β���������ڻ�����ɾ��Ԫ��
					cache.erase(cache.begin());
				}
			}
			else {//������ڻ����������Ԫ��
				cache_insert(cache,k,future,request[i]);
			}
		}
		cout << "���д���Ϊ " << sum << endl;
	}
	void cache_insert(list<int>&cache, size_t k,vector<list<int>>&future, int key) {
		if (future[key].empty())//���Ҫ�����Ԫ���´β������ֱ�ӷ���
			return;
		auto iter = cache.begin();
		for (; iter != cache.end() && !future[*iter].empty()&&future[*iter].front() < future[key].front(); ++iter)
			;//�ҵ���һ��Ԫ����һ�γ��ֵľ��벻С��Ҫ�����Ԫ�أ�ck

		if (cache.size() < k) {//�������δ�������Ԫ��
			cache.insert(iter, key);
		}
		else if (iter != cache.end()) {//����������˲���Ҫ����Ԫ����һ�γ��ֵľ��벻���������滻
			cache.insert(iter, key);
			cache.erase(--cache.end());
		}

		for (auto i : cache)
			cout << i <<future[i].front()<< "\t";
		cout << "\n" << key << future[key].front() << "\n" << endl;
	}
};
#endif 