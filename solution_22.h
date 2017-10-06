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
		cout << "����ڽڵ���ά�����������ԣ�O(1)���������\n"
			<< "����ȶ���O(E+V)\n"
			<< endl;
	}
};

class solution22_1_3 {
public:
	void operator()() {
		cout << "�ڽ�����O(E+V),�ڽӾ���O(V^2)"
			<< endl;
	}
};

class solution22_1_4 {
public:
	void operator()() {
		cout << "ɨ��"
			<< endl;
	}
};

class solution22_1_5 {
public:
	void operator()() {
		cout << "forÿһ������\n"
			<< "forûһ���͸ö����ڽӵĶ���\n"
			<< "����������������\n"
			<< "forÿһ������һ�������ڽӵĶ���\n"
			<< "O(E^3)"
			<< endl;
	}
};
class solution22_1_6 {
public:
	void operator()() {
		cout << "ά����������i,j����ǰɨ��ڵ������\n"
			<< "Ϊ0 j=j+1,Ϊ1 i=i+1 \n"
			<< "ֱ���������곬����ΧΪֹ�������i������Χ���j\n"
			<< "�Ƿ���ͨ�û�㣬��֮ͬ��֤������\n"
			<< "�������ɨ��ڵ�Ĺ켣��������¥�ݣ�����ǰ����ˮƽ��\n"
			<< "���ϵ������궥�㶼���У���Ϊ���ǲ�Ϊ1��ת�۵��������\n"
			<< "���У���Ϊ��Ϊ0��\n"
			<< "������ѭ������ʽ��i,jʼ�ձ�������ֻ��һ����ʾ���ܵ�\n"
			<< "���㣬ÿ���켣�����仯ʱ����ʾԭ�п��еĲ��ڿ��У�\n"
			<< "��һ��ԭ�������еı�ÿ���\n"
			<< "����֤��ͨ�û���������ٹ�1�������ߵ�·������ٹ�2*|V| \n"
			<< "�����Ҳ����ٹ�2*|V|"
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
			cout << "��\t" << v;
		}
	}
	void print_adj() {
		cout << "�ڽ�����" << endl;
		for (size_t i = 1; i < vect.size(); ++i) {
			cout << vect[i]->key << "��\t";
			auto curr = vect[i]->next;
			while (curr) {
				cout << curr->key << "��\t";
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
		cout << "�����й���color����䶼�ǵ��ںţ������ںź��\n"
			<< "�޹�black,���Կ���"
			<< endl;
	}
};

class solution22_2_4 {
public:
	void operator()() {
		cout << "����V^2)"
			<< endl;
	}
};

class solution22_2_5 {
public:
	void operator()() {
		cout << "������������Ŀ��ڵ����̵�·��ʱ����˳��Ӱ��\n"
			<< endl;
	}
};

class solution22_2_7 {
public:
	void operator()() {
		cout << "���ڵ�����һ��bool���Ա�ʾ�������͸߸�Ь\n"
			<< "����BFS��Դ�ڵ��ʾΪ����������߸�Ь��\n"
			<< "�������Ԫ�ص��ڽӶ���û�б����ʹ�\n"
			<< "����ɫ��Ϊ�ң������Ը����������Ԫ���÷�\n"
			<< "��������Ѿ����ʹ��������Ը�����������ͬ\n"
			<< "return false"
			<< endl;
	}
};

class solution22_2_8 {
public:
	void operator()(){
		cout << "��������ͼ����ȡһ���ڵ���ΪԴ�ڵ㣬��¼�¶��������\n"
			<< "һ��Ԫ�أ���Ԫ�ؾ���ֱ��·����һ���˵�\n"
			<< "����֤���ýڵ���ֱ��·����\n"
			<< "����ýڵ�w����ֱ���У���ô��ֱ����һ������Դ�ڵ�ϳ�\n"
			<< "��һ���˵�v��w����Ϊһ��������ֱ���������ì��\n"
			<< "��������22.3����֤�����ýڵ�Ϊֱ���Ķ˵�\n"
			<< "��������㷨������������㷨���˵���ΪԴ�ڵ�\n"
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
	pt_gp pre;//Ϊ22.3����13����Ŀ׼��������
	bool visited;
	int d;
	int f;
	////
	int tree=0;//Ϊ22.3����13����Ŀ׼��������
	set<int>vis;//Ϊ22.2-9׼��������
};
class solution22_2_9 {
public:
	void operator()() {
		cout << "���ʾ���last�ڵ�������ǰs�ڵ��last֮��������ڽӽڵ�curr��last�ڵ���Ϊ��󷵻�ʱʹ�á����curr�Ѿ����ʹ�\n"
			<<"˵���������ڵ��ܹ�����curr������һ��������·���������ǰ�ڵ�s�����нڵ㶼�Ѿ��������򷵻���һ���ڵ�\n"
			<<"�ܵ���˵�����ǰ�ڵ㲻����Ϊ�����ڽӽڵ����һ���ڵ㣬�ͽ�����·�����٣�ֻ�������һ������·��"
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
			cout << i << "��\t";
		cout << endl;
	}
	void twice_visited(int s, int last) {//sΪ������һ��last���ʵĵ�ǰ�ڵ�
		path.push_back(s);//ѹ��·��
		adjList[s]->visited = true;//��ǰ�ڵ��Ѿ����ʹ�
		auto curr = adjList[s]->next;

		while (curr) {
			int k = curr->key;
			if (k != last&&adjList[s]->vis.find(k)==adjList[s]->vis.end()) {//�뵱ǰ�ڵ������Ľڵ�curr��Ϊ��һ���ڵ㲢�ҵ�ǰ�ڵ�
				//û�о���curr���ʹ�����һ���ڵ�������󷵻�ʱʹ�ã�
				if (adjList[k]->visited) {//����Ѿ����ʹ��ýڵ㣬˵���ýڵ㲻��Ҫ��ǰ�ڵ�����ͨ����������һ�����ٸ�·��
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

	void dfs_stack() {//ʹ��ջ��dfs
		int time = 0;
		vector<int>stack;

		for (size_t i = 1; i < adjList.size(); ++i) {
			if (!adjList[i]->visited) {
				stack.push_back(i);//����ÿһ����ɫ�ڵ㶼��ջ���Σ�һ�ο�ʼ��һ�ν���
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
		bool mark = true;//�Ƿ��ǵ���ͨ��mark
		int k = 0;//���ڱ����������ı�ţ�
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
			else {//������ǰ�ɫ
				if (adjList[curr->key]->tree == adjList[s]->tree) {//��ͬһ�������������
					if (adjList[curr->key]->f < adjList[s]->d//ǰ���
						||(adjList[curr->key]->f!=0 && time > adjList[curr->key]->f)) {//�����
						mark = false;
						return;
					}
				}
				else {//����ͬһ����������
					if(mp.find(adjList[curr->key]->tree)!=mp.end()){//֮ǰ���������������к����
						mark = false;
							return;
					}
					else {//û�������
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
			cout << i << " |" << adjList[i]->d << "/" << adjList[i]->f << "��\t";
			auto curr = adjList[i]->next;
			while (curr) {
				cout << curr->key << "��\t";
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
		cout << "u���ڵ����űպϺ�ʼv"
			<< endl;
	}
};


class solution22_3_9 {
public:
	void operator()() {
		cout << "��Ҫ���ڽ�������v��������u�ڽӵ�˳��"
			<< endl;
	}
};

class solution22_3_11 {
public:
	void operator()() {
		cout << "�ýڵ�����г������ڵ�ɭ�ֲ������ýڵ㣬����\n"
			<< "�����ýڵ�֮ǰ������ϣ��ýڵ��������ڵĽڵ�\n"
			<< "�ڸýڵ�֮�����"
			<< endl;
	}
};

class solution22_3_12 {
public:
	void operator()() {
		cout << "��dfs_visit(G,u)��Ϊ������һ�����ü�������k\n"
			<< "dfs_visit(G,u,&k),��ʼʱk=1���ڵ�7��֮ǰ����\n"
			<< "k=k+1,�ڵ�10�к������u.cc=k"
			<< endl;
	}
};

class solution22_3_13 {
public:
	void operator()() {
		cout << "�������ǰ������ǵ���ͨ����ͬһ������������д��ں���߲��ǵ���ͨ��\n"
			<< "�ڲ�ͬ�������������������������ָ��ͬһ��������������ǵ���ͨ\n"

			<< "��ע��\n"
			<< endl;
		vector<vector<int>>vect{
			{},{},{1},{4},{2,5},{},{3},{6},{6}
		};

		DFS dfs(8, vect);
		if (dfs.singly_connected())
			cout << "�ǵ���ͨͼ" << endl;
		else
			cout << "���ǵ���ͨͼ" << endl;
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
		cout << "��������Ϊ" << endl;
		while (head) {
			cout << head->key << "��\t";
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
		cout << "һ��ӵ�� " << time << " ��·��"
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
		cout << "�ڽ�����Ϊ" << endl;
		for (size_t i = 1; i < adjList.size(); ++i) {
			cout << i << "��\t";
			auto curr = adjList[i]->next;
			while (curr) {
				cout << curr->key << "��\t";
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
		cout << "����һ���ڵ�����������������¼���ڵ㣬�����ʸ��ڵ㣬�������һ���ڵ��Ѿ����ʹ����л�"
			<< endl;
	}
};

class solution22_4_4 {
public:
	void operator()() {
		cout << "��·���Դ���һ�ڵ㿪ʼ"
			<< endl;
	}
};

class solution22_4_5 {
public:
	void operator()() {
		cout << "top(i)�����Ϊ0�Ķ���i�ķ����������ȼ�1������ö������Ϊ 0 \n"
			<< "�ݹ�,���㷨������ʱ��Ϊ�ҵ����Ϊ0�Ķ���O(v),֮��ݹ������ʱ��Ϊ\n"
			<< "���ж���Ķȣ�O(E),����ΪO(E+V),\n"
			<< "����л������Ͻ�û�ж�������Ϊ0\n"
			<< endl;
	}
};

class solution22_5_1 {
public:
	void operator()(){
		cout << "�����ͬһ��ǿ��ͨ�����в���ı䣬��������ͨ����֮������1"
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
		cout << "ԭʼͼΪ" << endl;
		print_adj(adjList);
		cout <<"\n" << endl;

		transposition_graph();
		cout << "ת��ͼΪ" << endl;
		print_adj(transposition);
		cout << "\n" << endl;

		cout << "ǿ��ͨ����Ϊ" << endl;
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
			cout << i <<" |"<<adjList[i]->d<<"/"<<adjList[i]->f<< "��\t";
			auto curr = adjList[i]->next;
			while(curr) {
				cout << curr->key << "��\t";
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
		cout << "���ܣ�����ͼ22-9��a)���Կ���"
			<< endl;
	}
};


class solution22_5_4 {
public:
	void operator()() {
		cout << "u��v��ת��֮ǰ�ܻ��ൽ�װ��֮��u��v��·�����v��u��·������֮ͬ������ת��֮��\n"
			<< "�ܻ��ൽ�ת��֮ǰ���ܻ��ൽ��Ľڵ�ת��֮��Ҳ���ܻ��ൽ��\n"
			<< endl;
	}
};

class solution22_5_7 {
public:
	void operator()() {
		cout << "�����ԭͼ����ͨ����ͼ����ͼ���������������V(i)û��V(i+1)��·�������ǰ���ͨͼ\n"
			<<"��Ϊֻ�п������ʱ�����ָ�����ʱ�����"
			<< endl;
	}
};
#endif