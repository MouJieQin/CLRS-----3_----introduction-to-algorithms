#pragma once
#ifndef _SOLUTION_22_H_
#define _SOLUTION_22_H_
#include<iostream>
#include<vector>
#include<memory>
#include<deque>
#include<set>
using namespace std;

class solution22_1_1 {
public:
	void operator()() {
		cout << "如果在节点中维护则两个属性，O(1)，否则出度\n"
			<< "和入度都是O(E+V)\n"
			<< endl;
	}
};

class solution22_1_3 {
public:
	void operator()() {
		cout << "邻接链表O(E+V),邻接矩阵O(V^2)"
			<< endl;
	}
};

class solution22_1_4 {
public:
	void operator()() {
		cout << "扫描"
			<< endl;
	}
};

class solution22_1_5 {
public:
	void operator()() {
		cout << "for每一个顶点\n"
			<< "for没一个和该顶点邻接的顶点\n"
			<< "将这两个顶点加入边\n"
			<< "for每一个与上一个顶点邻接的顶点\n"
			<< "O(E^3)"
			<< endl;
	}
};
class solution22_1_6 {
public:
	void operator()() {
		cout << "维护两个坐标i,j代表当前扫描节点的行列\n"
			<< "为0 j=j+1,为1 i=i+1 \n"
			<< "直到两个坐标超出范围为止，如果是i超出范围检测j\n"
			<< "是否是通用汇点，反之同理，证明如下\n"
			<< "如果画出扫描节点的轨迹，类似于楼梯，结束前所有水平上\n"
			<< "线上的列坐标顶点都不行，因为他们不为1，转折点的行坐标\n"
			<< "不行，因为不为0，\n"
			<< "有如下循环不变式，i,j始终保持有且只有一个表示可能的\n"
			<< "顶点，每当轨迹发生变化时，表示原有可行的不在可行，\n"
			<< "另一个原来不可行的变得可行\n"
			<< "容易证明通用汇点个数不会操过1个，行走的路径不会操过2*|V| \n"
			<< "最后检测也不会操过2*|V|"
			<< endl;
	}
};

////////////////////
struct graphNode;
typedef shared_ptr<graphNode> pt_gh;
struct graphNode {
	graphNode(int k,pt_gh n=nullptr,pt_gh pre=nullptr,int d=INT_MAX,bool v=false):
		key(k),next(n),d(d),pre(pre),visited(v){}
		
	int key;
	pt_gh next;
	pt_gh pre;
	int d;
	bool visited;
};

class queue_ {
public:
	void enqueue(int k) {
		dq.push_back(k);
	}
	int dequeue() {
		int r = dq.front();
		dq.pop_front();
		return r;
	}
	bool empty() {
		return dq.empty();
	}
private:
	deque<int>dq;
};

class BFS {
public:
	BFS(int max, vector<vector<int>>&vt)  {
		for (int i = 0; i <= max; ++i) {
			vect.push_back(shared_ptr<graphNode>(new graphNode(i)));
		}

		for (size_t i = 1; i < vt.size(); ++i) 
			for (size_t j = 0; j < vt[i].size(); ++j) 
				insert(i, vt[i][j]);

	}
	void operator()(int s, int v) {

		print_adj();

		que.enqueue(s);
		vect[s]->d = 0;
		vect[s]->visited = true;

		while (!que.empty()) {
			int vtr = que.dequeue();
			auto curr = vect[vtr]->next;
			
			while (curr) {
				int k = curr->key;
				if (!vect[k]->visited) {
					que.enqueue(k);
					vect[k]->visited = true;
					vect[k]->pre = vect[vtr];
					vect[k]->d = vect[vtr]->d + 1;
				}
				curr = curr->next;
			}
		}

		cout << "The path from " << s << " to " << v << endl;
		print_path(s, v);
		cout << endl;
	}
	void insert(int u, int v) {
		auto ptr = shared_ptr<graphNode>(new graphNode(v));
		ptr->next = vect[u]->next;
		vect[u]->next = ptr;
	}
	void print_path(int s, int v) {
		if (s == v)
			cout << v ;
		else if (!vect[v]->pre)
			cout << "no path from " << s << " to " << v << endl;
		else {
			print_path(s, vect[v]->pre->key);
			cout << "→\t" << v;
		}
	}
	void print_adj() {
		cout << "邻接链表" << endl;
		for (size_t i = 1; i < vect.size(); ++i) {
			cout << vect[i]->key << "→\t";
			auto curr = vect[i]->next;
			while (curr) {
				cout << curr->key << "→\t";
				curr = curr->next;
			}
			cout << endl;
		}
	}
private:
	vector<pt_gh>vect;
	queue_ que;
};
///////////////////////////////////
class solution22_2_1 {
public:
	void operator()() {
		vector<vector<int>>vect{ {0}, { 2,4 }, { 5 }, { 5,6 }, { 2 }, { 4 }, { 6 }};
		BFS bfs(6, vect);
		bfs(3, 2);
	}
};

class solution22_2_3 {
public:
	void operator()() {
		cout << "程序中关于color的语句都是等于号，而等于号后边\n"
			<< "无关black,所以可行"
			<< endl;
	}
};

class solution22_2_4 {
public:
	void operator()() {
		cout << "Θ（V^2)"
			<< endl;
	}
};

class solution22_2_5 {
public:
	void operator()() {
		cout << "当有两条到达目标节点的最短的路径时会受顺序影响\n"
			<< endl;
	}
};

class solution22_2_7 {
public:
	void operator()() {
		cout << "将节点增加一个bool属性表示娃娃脸和高跟鞋\n"
			<< "运用BFS将源节点表示为娃娃脸（或高跟鞋）\n"
			<< "如果出队元素的邻接顶点没有被访问过\n"
			<< "将颜色置为灰，并将性格属性与出队元素置反\n"
			<< "否则如果已经访问过，并且性格属性与其相同\n"
			<< "return false"
			<< endl;
	}
};

class solution22_2_8 {
public:
	void operator()(){
		cout << "对于无向图，任取一个节点作为源节点，记录下队列中最后\n"
			<< "一个元素，该元素就是直径路径的一个端点\n"
			<< "首先证明该节点在直径路径中\n"
			<< "假设该节点w不在直径中，那么该直径中一个距离源节点较长\n"
			<< "的一个端点v和w将成为一个更长的直径，与假设矛盾\n"
			<< "根据引理22.3可以证明，该节点为直径的端点\n"
			<< "根据这个算法在重新用这个算法将端点作为源节点\n"
			<< endl;
	}
};



///////////////////
struct adjNode;
typedef shared_ptr<adjNode> pt_adj;
struct adjNode {
	adjNode(int k,pt_adj n=nullptr):
		key(k),next(n){}
	int key;
	pt_adj next;
};
struct gphNode;
typedef shared_ptr<gphNode> pt_gp;
struct gphNode {
	gphNode(int k,pt_adj n=nullptr,pt_gp p= nullptr,
		bool b=false,int d=0,int f=0):key(k),next(n),
		pre(p),visited(b),d(d),f(f){}

	int key;
	pt_adj next;
	pt_gp pre;//为22.3——13的题目准备的属性
	bool visited;
	int d;
	int f;
	////
	int tree=0;//为22.3——13的题目准备的属性
	set<int>vis;//为22.2-9准备的属性
};
class solution22_2_9 {
public:
	void operator()() {
		cout << "访问经过last节点来到当前s节点除last之外的所有邻接节点curr，last节点作为最后返回时使用。如果curr已经访问过\n"
			<<"说明有其它节点能过到达curr，来回一次消除该路径，如果当前节点s的所有节点都已经访问完则返回上一个节点\n"
			<<"总的来说如果当前节点不能作为与其邻接节点的上一个节点，就将这条路径销毁，只保留最后一条返回路径"
			<< endl;

		/*vector<vector<int>>graph{
			{},{2},{1,3,4},{2,4,6,5},{2,3,7},{3,6},{3,5},{4,8},{7}
		};*/
		vector<vector<int>>graph{
			{},{2,4},{1,3},{2,4,8,9},{1,5,3,7},{4},{7},{4,6,8}, {7,3,9},{3,8,10},{9,11},{10,12},{11}
		};
		const int max = 12;
		for (int i = 0; i <= max; ++i)
			adjList.push_back(shared_ptr<gphNode>(new gphNode(i)));
		for (size_t i = 0; i < graph.size(); ++i)
			for (size_t j = 0; j < graph[i].size(); ++j)
				insert(i, graph[i][j]);

		twice_visited(1, 0);

		for (auto i : path)
			cout << i << "→\t";
		cout << endl;
	}
	void twice_visited(int s, int last) {//s为经过上一个last访问的当前节点
		path.push_back(s);//压入路径
		adjList[s]->visited = true;//当前节点已经访问过
		auto curr = adjList[s]->next;

		while (curr) {
			int k = curr->key;
			if (k != last&&adjList[s]->vis.find(k)==adjList[s]->vis.end()) {//与当前节点相连的节点curr不为上一个节点并且当前节点
				//没有经过curr访问过，上一个节点用做最后返回时使用，
				if (adjList[k]->visited) {//如果已经访问过该节点，说明该节点不需要当前节点来联通，所以来回一次销毁该路径
					adjList[k]->vis.insert(s);
					path.push_back(k);
					path.push_back(s);
				}
				else {
					twice_visited(k, s);
				}
			}
			curr = curr->next;
		}
		if (last)
			path.push_back(last);
	}

	void insert(int i, int j) {
		auto t = shared_ptr<adjNode>(new adjNode(j, adjList[i]->next));
		adjList[i]->next = t;
	}
private:
	vector<pt_gp>adjList;
	vector<int>path;
};

class DFS {
public:
	DFS(int max, vector<vector<int>> &graph):time(0) {
		for (int i = 0; i <= max; ++i)
			adjList.push_back(shared_ptr<gphNode>(new gphNode(i)));
		for (size_t i = 0; i < graph.size(); ++i)
			for (size_t j = 0; j < graph[i].size(); ++j)
				insert(i, graph[i][j]);
	}

	void operator()() {
		print_adjList();

		for (size_t i = 1; i < adjList.size(); ++i)
			if (!adjList[i]->visited)
				dfs_visited(i);
		cout << endl;
	}
	void dfs_visited(int s) {
		cout << "(" << s << " ";

		time += 1;
		adjList[s]->d = time;
		adjList[s]->visited = true;
		auto curr = adjList[s]->next; 

		while (curr) {
			if (!adjList[curr->key]->visited) {
				dfs_visited(curr->key);
			}
			curr = curr->next;
		}

		time = time + 1;
		adjList[s]->f = time;

		cout << s << " )";
	}

	void dfs_stack() {//使用栈的dfs
		int time = 0;
		vector<int>stack;

		for (size_t i = 1; i < adjList.size(); ++i) {
			if (!adjList[i]->visited) {
				stack.push_back(i);//对于每一个白色节点都进栈两次，一次开始，一次结束
				stack.push_back(i);

				while (!stack.empty()) {
					int e = pop(stack);
					
					time += 1;
					if (adjList[e]->visited) {
						adjList[e]->f = time;
						cout << e << " )";
					}
					else {
						adjList[e]->visited = true;
						adjList[e]->d = time;
						cout << "( " << e << " ";

						auto curr = adjList[e]->next;
						while (curr) {
							int k = curr->key;
							if (!adjList[k]->visited) {
								stack.push_back(k);
								stack.push_back(k);
							}
							curr = curr->next;
						}
					}

				}

			}
		}

		cout << endl;
	}

	bool singly_connected() {
		print_adjList();
		bool mark = true;//是否是单连通的mark
		int k = 0;//用于标记深度优树的编号，
		for (size_t i = 1; i < adjList.size(); ++i)
			if (mark) {
				if (!adjList[i]->visited) {
					int x = 0;
					map<int, int>mp;
					dfs_v(i, mark, ++k, mp);
				}
			}
			else
				return false;
		return mark;
	}
	void dfs_v(int s,bool &mark,int k,map<int,int>&mp) {

		adjList[s]->tree = k;
		time += 1;
		adjList[s]->d = time;
		adjList[s]->visited = true;
		auto curr = adjList[s]->next;

		while (curr) {
			if (!adjList[curr->key]->visited) {
				adjList[curr->key]->pre = adjList[s];

				dfs_v(curr->key,mark,k,mp);
			}
			else {//如果不是白色
				if (adjList[curr->key]->tree == adjList[s]->tree) {//在同一个深度优先树中
					if (adjList[curr->key]->f < adjList[s]->d//前向边
						||(adjList[curr->key]->f!=0 && time > adjList[curr->key]->f)) {//横向边
						mark = false;
						return;
					}
				}
				else {//不在同一个优先树中
					if(mp.find(adjList[curr->key]->tree)!=mp.end()){//之前已与该深度优先树有横向边
						mark = false;
							return;
					}
					else {//没有则插入
						mp.insert(make_pair(adjList[curr->key]->tree, 1));
					}
				}
			}
			curr = curr->next;
		}

		time = time + 1;
		adjList[s]->f = time;

	}
	pt_gp  topological_sort() {
		print_adjList();
		pt_gp head = nullptr;
		for (size_t i = 1; i < adjList.size(); ++i)
			if (!adjList[i]->visited)
				dfs_top_sort(i, head);
		return head;
	}
	void dfs_top_sort(int s,pt_gp& head) {
		time += 1;
		adjList[s]->d = time;
		adjList[s]->visited = true;

		auto curr = adjList[s]->next;
		while (curr) {
			int k = curr->key;
			if (!adjList[k]->visited) {
				dfs_top_sort(k, head);
			}
			curr = curr->next;
		}

		time = time + 1;
		adjList[s]->f = time;
		top_insert(s, head);
	}
	void top_insert(int s, pt_gp& head) {
		if (head) {
			adjList[s]->pre = head;
			head = adjList[s];
		}
		else {
			head = adjList[s];
		}
	}
	int pop(vector<int>&stack) {
		int re = stack.back();
		stack.pop_back();
		return re;
	}
	void insert(int i, int j) {
		auto t = shared_ptr<adjNode>(new adjNode(j,adjList[i]->next));
		adjList[i]->next = t;
	}
	void print_adjList() {
		for (size_t i = 1; i < adjList.size(); ++i) {
			cout << i << " |" << adjList[i]->d << "/" << adjList[i]->f << "→\t";
			auto curr = adjList[i]->next;
			while (curr) {
				cout << curr->key << "→\t";
				curr = curr->next;
			}
			cout << endl;
		}
	}
private:
	vector<pt_gp>adjList;
	int time;
};
//////////////////////////////////
class solution22_3_2 {
public:
	void operator()() {
		vector<vector<int>>vect{
			{0},{3},{1},{2},{2,3,5},{6,8},{7},{6},{4},{8,10},{8}
		};
		DFS dfs(10, vect);
		dfs();
	}
};

class solution22_3_7 {
public:
	void operator()() {
		/*vector<vector<int>>vect{
			{ 0 },{ 3 },{ 1 },{ 2 },{ 2,3,5 }, { 6,8 },{ 7 },{ 6 },{ 4 },{ 8,10 },{ 8 }
		};*/
		vector<vector<int>>vect{
			{},{ 4,3,7 },{},{ 2 },{},{ 3,6,9 },{ 2 },{ 6,8 },{ 10 },{ 7,10,11 },{ 4,14 },{ 7 },{},{ 9,11,12 },{ 12 }
		};

		DFS dfs(14, vect);
		dfs();
		dfs.print_adjList();
		cout << "\n" << endl;

		DFS stack(14, vect);
		stack.dfs_stack();
		stack.print_adjList();
		cout << "\n" << endl;
	}
};

class solution22_3_8 {
public:
	void operator()() {
		cout << "u所在的括号闭合后开始v"
			<< endl;
	}
};


class solution22_3_9 {
public:
	void operator()() {
		cout << "需要看邻接链表中v和其它与u邻接的顺序"
			<< endl;
	}
};

class solution22_3_11 {
public:
	void operator()() {
		cout << "该节点的所有出边所在的森林不包含该节点，并在\n"
			<< "遍历该节点之前遍历完毕，该节点的入边所在的节点\n"
			<< "在该节点之后遍历"
			<< endl;
	}
};

class solution22_3_12 {
public:
	void operator()() {
		cout << "将dfs_visit(G,u)改为还加入一个引用计数变量k\n"
			<< "dfs_visit(G,u,&k),初始时k=1，在第7行之前加入\n"
			<< "k=k+1,在第10行后面加入u.cc=k"
			<< endl;
	}
};

class solution22_3_13 {
public:
	void operator()() {
		cout << "如果存在前向边则不是单连通，在同一个深度优先树中存在横向边不是单连通，\n"
			<< "在不同深度优先树中如果有两个横向边指向同一个深度优先树则不是单连通\n"

			<< "看注释\n"
			<< endl;
		vector<vector<int>>vect{
			{},{},{1},{4},{2,5},{},{3},{6},{6}
		};

		DFS dfs(8, vect);
		if (dfs.singly_connected())
			cout << "是单连通图" << endl;
		else
			cout << "不是单连通图" << endl;
	}
};
class solution22_4_1 {
public:
	void operator()() {
		vector<vector<int>>vect{
			{},{2,8},{3,8},{6},{3,5},{6},{},{8},{},{}
		};
		DFS dfs(9, vect);
		pt_gp head=dfs.topological_sort();
		cout << "拓扑排序为" << endl;
		while (head) {
			cout << head->key << "→\t";
			head = head->pre;
		}
		cout << endl;
	}
};

class prime_path {
public:
	prime_path(int max, vector<vector<int>> &graph){
		for (int i = 0; i <= max; ++i)
			adjList.push_back(shared_ptr<gphNode>(new gphNode(i)));
		for (size_t i = 0; i < graph.size(); ++i)
			for (size_t j = 0; j < graph[i].size(); ++j)
				insert(i, graph[i][j]);
	}
	void operator()(int s,int v) {
		print_adjList();
		dfs_visited(s, v);
		cout << "一共拥有 " << time << " 条路径"
			<< endl;
	}
	void dfs_visited(int s,int tar) {
		auto curr = adjList[s]->next;
		while (curr) {
			if (curr->key == tar) {
				time += 1;
				adjList[s]->d = 1;
			}
			else {
				dfs_visited(curr->key, tar);
			}
			curr = curr->next;
		}
	}
	void insert(int i, int j) {
		auto t = shared_ptr<adjNode>(new adjNode(j, adjList[i]->next));
		adjList[i]->next = t;
	}
	void print_adjList() {
		cout << "邻接链表为" << endl;
		for (size_t i = 1; i < adjList.size(); ++i) {
			cout << i << "→\t";
			auto curr = adjList[i]->next;
			while (curr) {
				cout << curr->key << "→\t";
				curr = curr->next;
			}
			cout << endl;
		}
	}
private:
	vector<pt_gp>adjList;
	int time = 0;
};

class solution22_4_2 {
public:
	void operator()() {
		vector<vector<int>>vect{
			{}, {4,3,7},{},{2},{},{3,6,9},{2},{6,8},{10},{7,10,11},{4,14},{7},{},{9,11,12},{12}
		};
		prime_path counter_path(14, vect);
		counter_path(13, 10);
	}
};

class solution22_4_3 {
public:
	void operator()() {
		cout << "对任一个节点进行深度搜索，并记录父节点，不访问父节点，如果访问一个节点已经访问过则有环"
			<< endl;
	}
};

class solution22_4_4 {
public:
	void operator()() {
		cout << "环路可以从任一节点开始"
			<< endl;
	}
};

class solution22_4_5 {
public:
	void operator()() {
		cout << "top(i)将入度为0的顶点i的发出顶点的入度减1，如果该顶点入度为 0 \n"
			<< "递归,该算法的运行时间为找到入度为0的顶点O(v),之后递归的运行时间为\n"
			<< "所有顶点的度，O(E),所以为O(E+V),\n"
			<< "如果有环，环上将没有顶点的入度为0\n"
			<< endl;
	}
};

class solution22_5_1 {
public:
	void operator()(){
		cout << "如果在同一个强联通分量中不会改变，在两个联通分量之间会减少1"
			<< endl;
	}
};

/////////////////////////////////
class strongly_connected_components {
public:
	strongly_connected_components(vector<vector<int>>&graph, int max):time(0) {
		for (int i = 0; i <= max; ++i)
			adjList.push_back(shared_ptr<gphNode>(new gphNode(i)));

		for (int i = 0; i <= max; ++i)
			transposition.push_back(shared_ptr<gphNode>(new gphNode(i)));

		for (size_t i = 0; i < graph.size(); ++i)
			for (size_t j = 0; j < graph[i].size(); ++j)
				insert(adjList,i, graph[i][j]);
	}
	void operator()() {

		dfs(adjList, true);
		cout << "原始图为" << endl;
		print_adj(adjList);
		cout <<"\n" << endl;

		transposition_graph();
		cout << "转置图为" << endl;
		print_adj(transposition);
		cout << "\n" << endl;

		cout << "强连通分量为" << endl;
		dfs(transposition,false);
		cout << "\n" << endl;
	}
	void transposition_graph() {
		for (size_t i = 0; i < adjList.size(); ++i) {
			auto curr = adjList[i]->next;
			while(curr){
				insert(transposition,curr->key,i);
				curr = curr->next;
			}
		}
	}
	void dfs(vector<pt_gp>&adjList,bool flag=false) {
		time = 0;
		if (flag) {
			for (size_t i = 1; i < adjList.size(); ++i) 
						if (!adjList[i]->visited) 
							dfs_visited(adjList, i, flag);
		}
		else {
			for (auto iter = stack.rbegin(); iter != stack.rend(); ++iter)
				if (!transposition[*iter]->visited) {
					dfs_visited(transposition, *iter, flag);
					cout << endl;
				}
		}
	}
	void dfs_visited(vector<pt_gp>&adjList, int s,bool flag) {
		time += 1;
		adjList[s]->d = time;
		adjList[s]->visited = true;

		auto curr = adjList[s]->next;
		while (curr) {
			if (!adjList[curr->key]->visited) {
				dfs_visited(adjList, curr->key,flag);
			}
			curr = curr->next;
		}

		time += 1;
		adjList[s]->f = time;

		if (flag) {
			stack.push_back(s);
		}
		else {
			cout << s << "\t";
		}
	}

	void insert(vector<pt_gp>&adjList,int i, int j) {
		auto t = shared_ptr<adjNode>(new adjNode(j, adjList[i]->next));
		adjList[i]->next = t;
	}
	void print_adj(vector<pt_gp>&adjList) {
		for (size_t i = 1; i < adjList.size(); ++i) {
			cout << i <<" |"<<adjList[i]->d<<"/"<<adjList[i]->f<< "→\t";
			auto curr = adjList[i]->next;
			while(curr) {
				cout << curr->key << "→\t";
				curr = curr->next;
			}
			cout << endl;
		}
	}

private:
	vector<pt_gp>adjList;
	vector<pt_gp>transposition;
	int time;
	vector<int>stack;
};


class solution22_5_2 {
public:
	void operator()() {
		vector<vector<int>>vect{
			{ 0 },{ 3 },{ 1 },{ 2 },{ 2,3,5 },{ 6,8 },{ 7 },{ 6 },{ 4 },{ 8,10 },{ 8 }
		};
		/*vector<vector<int>>vect{
			{},{2},{3,5,6},{4,7},{3,8},{1,6},{7},{6,8},{8}
		};*/
		strongly_connected_components scc(vect, 10);
		scc();
	}
};

class solution22_5_3 {
public:
	void operator()() {
		cout << "不能，对照图22-9（a)可以看出"
			<< endl;
	}
};


class solution22_5_4 {
public:
	void operator()() {
		cout << "u，v在转置之前能互相到达，装置之后u到v的路径变成v到u的路径，反之同理，所以转置之后\n"
			<< "能互相到达，转置之前不能互相到达的节点转置之后也不能互相到达\n"
			<< endl;
	}
};

class solution22_5_7 {
public:
	void operator()() {
		cout << "先求出原图的连通分量图，对图进行拓扑排序，如果V(i)没到V(i+1)的路径，不是半连通图\n"
			<<"因为只有可能完成时间晚的指向完成时间早的"
			<< endl;
	}
};
#endif