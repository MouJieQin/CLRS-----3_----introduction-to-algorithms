#pragma once
#ifndef _SOLUTION_10_H_
#define _SOLUTION_10_H_
#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>
using namespace std;
/////////////////////////////////////////////////
class Stack {//栈的数组实现
public:
	Stack(size_t n, initializer_list<int>lst = {}) :vect{ lst }, top(-1) {
		for (auto i = lst.size(); i != n; ++i) {
			vect.push_back(0);
	}
	}
	void push(int key) {
		if (top == vect.size() - 1) {
			cerr << "overflow !!!" << endl;
			return;
		}
		vect[++top] = key;
	}
	int pop() {
		if (empty()) {
			cerr << "underflow !!!" << endl;
			return INT_MIN;
		}
		--top;
		return vect[top + 1];
	}
	bool empty() {
		return top == 0;
	}
	void print_stack() {
		for (size_t i = 0; i != vect.size(); ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	vector<int>vect;
	size_t top;
};
////////////////////////////////////////////////////////
class solution10_1_1 {
public:
	solution10_1_1() :stk(6) {}
	void operator()() {
		stk.push(4);
		stk.print_stack();
		stk.push(1);
		stk.print_stack();
		stk.push(3);
		stk.print_stack();
		cout << stk.pop() <<"\n"<< endl;
		stk.print_stack();
		stk.push(8);
		stk.print_stack();
		cout << stk.pop() << "\n" << endl;
		stk.print_stack();
	}
private:
	Stack stk;
};

class solution10_1_2 {
public:
	void operator()() {
		cout << "将A[1]和A[n]分别作为两个栈的栈底，左边的栈push时右移，右边栈push时左移"
			<< endl;
	}
};
/////////////////////////////////////////////
class Queue {//队列的实现
public:
	Queue(size_t n, initializer_list<int>lst = {}) :vect{ lst }, tail(0), head(0){
		for (size_t i = vect.size(); i != n; ++i)
			vect.push_back(0);
	}
	int dequeue() {
		if (empty()) {
			cerr << "underflow !!!" << endl;
			return INT_MIN;	
		}
		int temp = vect[head];
		head = getIndex(head);
		return temp;
	}
	void enqueue(int key) {
		if (getIndex(tail) == head) {
			cerr << "overflow !!!" << endl;
			return;
		}
		vect[tail]=key;
		tail = getIndex(tail);
	}
	bool empty() {
		return head==tail;
	}
	void print_deque() {
		for (size_t i = 0; i != vect.size(); ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	vector<int>vect;
	size_t head;
	size_t tail;
	size_t getIndex(size_t n) {
		if (n == vect.size()-1)
			return 0;
		return
			++n;
	}
};
/////////////////////////////////////////////////////////
class solution10_1_3 {
public:
	solution10_1_3():que(6){}
	void operator()() {
		que.enqueue(4);
		que.print_deque();
		que.enqueue(1);
		que.print_deque();
		que.enqueue(3);
		que.print_deque();
		cout << que.dequeue() << "\n" << endl;
		que.print_deque();
		que.enqueue(8);
		que.print_deque();
		cout << que.dequeue() << "\n" << endl;
		que.print_deque();
	}
private:
	Queue que;
};
class solution10_1_4 {
public:
	void operator()() {
		cout << "代码已在上面实现"
			<< endl;
	}
};
////////////////////////////////////////////////
class Deque {//双向队列的实现
public:
	Deque(size_t n, initializer_list<int>lst = {}) :vect{ lst }, tail(0), head(0){
		for (size_t i = vect.size(); i != n; ++i)
			vect.push_back(0);
	}
	void tail_enqueue(int key){
		if (getNext(tail)==head) {
			cerr << "overflow !!!" << endl;
			return;
		}
		vect[tail] = key;
		tail = getNext(tail);
	}
	void head_enqueue(int key) {
		if (getLast(head)==tail) {
			cerr << "overflow !!!" << endl;
			return;
		}
		head = getLast(head);
		vect[head] = key;
	}
	int head_dequeue() {
		if (empty()) {
			cerr << "underflow !!!" << endl;
			return INT_MIN;
		}
		int temp = vect[head];
		head = getNext(head);
		return temp;
	}
	int tail_dequeue() {
		if (empty()) {
			cerr << "underflow !!!" << endl;
			return INT_MIN;
		}
		tail = getLast(tail);
		return vect[tail];
	}
	bool empty() {
		return head == tail;
	}
	void print_deque() {
		for (size_t i = 0; i != vect.size(); ++i)
			cout << i << "\t";
		cout << endl;
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	vector<int>vect;
	size_t head;
	size_t tail;
	size_t getNext(size_t n) {
		if (n == vect.size() - 1)
			return 0;
		return ++n;
	}
	size_t getLast(size_t n) {
		if (n == 0)
			return vect.size() - 1;
		return --n;
	}
};
///////////////////////////////////
class solution10_1_5 {
public:
	solution10_1_5():deq(9){}
	void operator()() {
		cout <<"\n"<< "依次从尾端插入9,8,7,6后有" << endl;
		for (auto i : vect1) {
			deq.tail_enqueue(i);
			deq.print_deque();
		}
		cout << "依次从前端插入4,3,2,1后有" << endl;
		for (auto i : vect2) {
			deq.head_enqueue(i);
			deq.print_deque();
		}
		cout << "继续尾端插入12则有溢出警告:" << endl;
		deq.head_enqueue(12);
		cout << "继续前端插入12则有溢出警告:" << endl;
		deq.tail_enqueue(12);
		cout << "可以看到队列中还有一个0为空元素不能插入，这是由于head==tail为空，而head=tail+1为满造成的 \n"
			<< "这里由于书中定义tail指向下一个插入的地方，所以继续插入会导致溢出，要改变这一点可以将tail定义为 \n"
			<< "指向最后一个元素" << endl;
		cout << "依次从首端弹出4个元素有" << endl;
		for (auto i : vect2) {
			cout << deq.head_dequeue() << "\t" << endl;
		}
		cout << "依次从尾端弹出4个元素有" << endl;
		for (auto i : vect1) {
			cout << deq.tail_dequeue() << "\t" << endl;
		}
		cout << "继续首端弹出则有溢出警告:" << endl;
		cout << deq.head_dequeue() << endl;
		cout << "继续尾端弹出则有溢出警告:" << endl;
		cout << deq.tail_dequeue() <<"\t"<< endl;
	}
private:
	vector<int>vect1{ 9,8,7,6 };
	vector<int>vect2{ 4,3,2,1 };
	Deque deq;
};
class solution10_1_6 {
public:
	void operator()() {
		cout << "1.将栈s1作为存储栈，入队时push进s1,出队时将s1的所有元素pop进s2，然后pop s2作为出队元素,之后重新将s2的所有元素pop进s1,\n"
			<<"入队为O(1),出队为2cn \n"
			<<"2.入队时，如果s1不为空则直接push进s1,但不将s1的元素pop进s2,如果s1为空则先将s2 的所有元素pop进s1,然后入队，同样不将s1的元素pop进s2 \n"
			<<"出队时如果s1不为空则直接将s1 pop出去，为空则将s2的所有元素pop进s1,然后pop出去，也就是说在某一时刻一定有一个队列为空 \n"
			<<"入队时s1为空为cn,否则O(1），出队时s2为空为空为cn,否则O(1）\n"
			<<"3.入队时直接push进s1，出队时如果s2不为空则直接将s2 pop出去，为空则将s1的所有元素pop进s2,然后pop出去 \n"
			<<"入队为O(1),出队为O(1)或O(n)"
			<< endl;
	}
};

class solution10_1_7 {
public:
	void operator()() {
		cout << "与上一题类似，不赘述 运行时间为Θ(n)"
			<< endl;
	}
};

class solution10_2_1 {
public:
	void operator()() {
		cout << "insert可以在O(1)的时间完成，因为插入总是在表头进行，所以插入位置前后的两个对象的指针都知道 \n"
			<< "而delete操作不行，因为只知道它的下一额对象的指针而不知道上一个对象的指针"
			<< endl;
	}
};

struct listNode {
	listNode(int k=INT_MAX) :key(k),next(nullptr) {}
	int key;
	listNode *next;
};
///////////////////////////////////////
class Stack_list {//单链表实现栈
public:
	Stack_list():head(&headNode){}
	void push(listNode*x) {//总是把push进来的对象放在表头
		x->next = head->next;
		head->next = x;
	}
	listNode* pop() {//弹出表头对象
		if (empty()) {
	//		cerr << "underflow !!!" << endl;
			return nullptr;
		}
		auto temp = head->next;
		head->next = temp->next;
		return temp;
	}
	bool empty() {
		return head->next == nullptr;
	}
	void print_list() {
		auto temp = head->next;
		while (temp) {
			cout << temp->key << '\t';
			temp = temp->next;
		}
		cout << "\n" << endl;
	}
private:
	listNode headNode;
	listNode *head;
};
///////////////////////////////////////////
class solution10_2_2 {
public:
	void operator()() {
		for (size_t i = 9; i != 0; --i)
			list.push(new listNode(i));
		list.print_list();
		auto temp = list.pop();
		while (temp) {
			cout << temp->key <<"\n";
			delete temp;
			temp = list.pop();
		}
		cout << endl;
	}
	~solution10_2_2() {//析构
		auto temp = list.pop();
		while (temp) {
			delete temp;
			temp = list.pop();
		}		
	}
private:
	Stack_list list;
};
////////////////////////////
class list_queue {//单向链表实现队列
public:
	list_queue() :head(&headNode) ,tail(head){}
	void enqueue(listNode *key) {//将对象插入链表的最后
		tail->next = key;
		tail = key;
	//	tail->next = nullptr;
	}
	listNode* dequeue() {//让表头元素出队
		if (empty())
			return nullptr;
		auto temp = head->next;
		head->next = temp->next;
		return temp;
	}
	bool empty() {
		return head->next==nullptr;
	}
	void print_queue() {
		auto temp = head->next;
		while (temp) {
			cout << temp->key << "\t";
			temp=temp->next;
		}
		cout << "\n" << endl;
	}
private:
	listNode headNode;
	listNode *head;
	listNode *tail;
};
/////////////////////////////
class solution10_2_3 {
public:
	void operator()() {
		for (size_t i = 9; i != 0; --i)
			que.enqueue(new listNode(i));
		que.print_queue();
		auto temp = que.dequeue();
		while (temp) {
			cout << temp->key << "\n";
			delete temp;
			temp = que.dequeue();
		}
		cout << endl;
	}
	~solution10_2_3() {
		auto temp = que.dequeue();
		while (temp) {
			delete temp;
			temp = que.dequeue();
		}
	}
private:
	list_queue que;
};
class solution10_2_4 {
public:
	void operator()() {
		cout << "在while循环之前将L.nil.key=k,循环迭代完成后检测x==L.nil,是返回nil，否则返回x"
			<< endl;
	}
};
//////////////////////
class singly_circular_list {
public:
	singly_circular_list() :head(&headNode) { headNode.next = head; }//初始化时表头指向自身
	void insert(listNode *ele) {//在表头元素后面插入花费O(1)
		ele->next = head->next;
		head->next = ele;
	}
	void Delete(listNode *ele) {//要找到要删除元素的上一个元素花费Θ(n)
		if (head->next == ele) {//处理要删除的元素再表头，注意此时的head为哨兵
			head->next = ele->next;
			delete ele;
			return;
		}
		auto temp = head->next;
		while (temp!=head&&temp->next != ele)//处理要删除的元素不在表头
			temp = temp->next;
		if (temp != head) {
			temp->next = ele->next;
			delete ele;
		}
	}
	listNode* search(int key) {//最坏情况遍历整个表花费Θ(n)
		auto temp = head->next;
		head->key = key;
		while (temp->key != key)
			temp = temp->next;
		if (temp != head)
			return temp;
		return nullptr;
	}
	bool empty() {
		return head->next == head;
	}
	void print_list() {
		auto temp = head->next;
		while (temp != head) {
			cout << temp->key << "\t";
			temp = temp->next;
		}
		cout << "\n" << endl;
	}
private:
	listNode headNode;
	listNode *head;
};
//////////////////////////////////////////////
class solution10_2_5 {
public:
	void operator()() {
		for (int i = 9; i != 0; --i) 
			list.insert(new listNode(i));
		list.print_list();
		list.search(3) ? cout << "finding" << endl : cout << "no finding" << endl;
		list.search(10) ? cout << "finding" << endl : cout << "no finding" << endl;
		for (int i = 11; i != 0; --i) {
			list.Delete(list.search(i));
			list.print_list();
		}
		cout << "运行时间看上面注释" << endl;
	}
private:
	singly_circular_list list;
};

class solution10_2_6 {
public:
	void operator()() {
		cout << "链表" << endl;
	}
};

class solution10_2_7 {
public:
	solution10_2_7():head(&headNode){}
	void operator()() {
		listNode *tail=head;
		for (int i = 1; i != 10; ++i) {//制造一个链表
			tail->next = new listNode(i);
			tail = tail->next;//循环结束后tail指向最后一个元素，如果对于已经存在的一个链表，需要遍历一遍找到
		}//最后一个元素，花费Θ(n)
		listNode *temp = head->next;
		while (temp) {
			cout << temp->key << "\t";
			temp = temp->next;
		}
		cout << "\n" << endl;
		listNode *tmp_a = head->next->next;//指向第2个元素，这个程序并没有检测总元素为1或空不需要交换的情况
		listNode *tmp_b = tmp_a->next;//如果有第3个元素则指向第三个元素，没有则为空

		head->next->next = nullptr;//记录好第2个元素后将第1个元素的next置空
		while (tmp_a) {//直到tmp_a为空
			tmp_a->next = head->next;
			head->next = tmp_a;//这两行将tam_a指向的元素插入到表头花费O(1)
			tmp_a = tmp_b;//将tmp_a指向tmp_b
			if(tmp_b)//如果tmp_b不为空则进入下一个元素
				tmp_b = tmp_b->next;
		}	
		temp = head->next;
		while (temp) {
			cout << temp->key << "\t";
			temp = temp->next;
		}
		cout << "\n" << endl;
	}
private:
	listNode headNode;
	listNode *head;
};
////////////////////////////////
struct xorNode;
typedef xorNode* pt_xor;
struct xorNode {
	xorNode(int k, pt_xor x = nullptr) :key(k), xor (x) {}
	int key;
	pt_xor xor;
};
//////////////////
class solution10_2_8 {
public:
	typedef xorNode* pt_xor;
	void operator()() {
		cout << "这里需要知道异或的性质，A xor 0=A ,A xor A=0,A xor B xor A=B, A xor A xor B=B \n"
			<< endl;
		cout << "插入元素后" << endl;
		for (auto i : vect)
			insert((pt_xor)(new xorNode(i)));
		print();
		cout << "查找2" << endl;
		if (search(2))
			cout << "finding " << endl;
		cout << "查找21" << endl;
		if (!search(21))
			cout <<"finding nothing "<< endl;
		cout << "反转" << endl;
		reserve();
		print();
		cout << "删除具有关键字7的节点后" << endl;
		del(search(7));
		print();
	}
private:
	vector<int>vect{ 1,3,5,7,9,2,4,6,8,10 };
	pt_xor ptx(pt_xor lhs, pt_xor rhs) { return (pt_xor)((unsigned int)(lhs) ^ (unsigned int)(rhs)); }
	pt_xor head = (pt_xor)(new xorNode(INT_MIN));
	pt_xor tail= (pt_xor)(new xorNode(INT_MIN));
	void insert(pt_xor target) {//插入
		if (!head->xor) {
			head->xor = target;
			target->xor= head;
			tail->xor = target;
			return;
		}
		auto next = head->xor;
		next->xor = ptx(ptx(head, next->xor), target);
		target->xor = ptx(head, next);
		head->xor = target;
	}

	void print() {//打印整个链表
		if (!head->xor)
			return;
		auto target = head;
		auto next = target->xor;
		while (next) {
			auto temp = target;
			target = next;
			cout << target->key << "\t";
			next = ptx(next->xor, temp);
		}
		cout << "\n" << endl;
	}	
	pt_xor search(int key) {//查找
		if (!head->xor)
			return nullptr;
		auto target = head;
		auto next = target->xor;
		while (next&&next->key!=key) {
			auto temp = target;
			target = next;
			next = ptx(next->xor, temp);
		}
		return next;
	}
	void del(pt_xor target) {//删除
		if (!head->xor)
			return;
		auto last = head;
		auto tar = last->xor;
		while (tar&&tar != target) {
			auto temp = last;
			last = tar;
			tar = ptx(tar->xor,temp);
		}
		if (tar) {
			auto next = ptx(tar->xor, last);
			last->xor = ptx(ptx(last->xor, tar),next);
			next->xor = ptx(ptx(next->xor, tar), last);
		}
	}
	void reserve() {//反转O(1)
		auto temp = head->xor;
		head->xor = tail->xor;
		head->xor->xor = ptx(head->xor->xor, head);
		tail->xor = temp;
		tail->xor->xor= ptx(tail->xor->xor, head);
	}
};

class solution10_3_1 {
public:
	void operator()() {
		cout <<"L=2 \n"
			<<"\t 1	2	3	4	5	6 \n"
			<< "next	3	6	5	\\	4	1	\n"
			<<"key	8	13	19	11	5	4	\n"
			<< "prev	6	\\	1	5	3	2"
			<< "\n"<<endl;
		cout << "太麻烦了省略" << endl;
	}
};
class link_list_array {
public:
	link_list_array(size_t n):length(n),vect(3*n,-1),free(1),L(3){
		for (size_t i = 1; i - 1 != vect.size()-3; i += 3)
			vect[i] = i + 3;
	}
	size_t allocate_object() {
		if (free ==-1) {
			return -1;
		}
		size_t x = free;
		free = vect[free];
		return x-1;
	}
	void free_object(size_t x) {
		if (x % 3 || x >= vect.size()) {
			cout << "要删除的下标不正确" << endl;
			return;
		}
		vect[x + 1] = free;
		free = x + 1;
	}
	void insert(int key) {
		size_t temp = allocate_object();
		if (temp== -1) {
			cerr << "out of space !!!" << endl;
			return;
		}
		vect[temp] = key;
		vect[temp + 1] = L;
		vect[L + 2] = temp;
		vect[temp + 2] = -1;
		L = temp;
	}
	void print() {
		for (auto i : vect)
			cout << i << "\t";
		cout << "\n" << endl;
	}
private:
	const size_t length;
	vector<int>vect;
	size_t free;
	size_t L;
};
class solution10_3_2 {
public:
	solution10_3_2():list(5){}
	void operator()() {
		for (size_t i = 14; i != 0; --i)
			list.insert(i);
		list.print();
		for (size_t i = 15; i != 0; --i) {
			list.free_object(i);
			list.print();
		}
		for (size_t i = 12; i <= 30; i += 3)
			list.insert(i);
		list.print();
	}
private:
	link_list_array list;
};
/////////////////////////
struct treeNode {
	treeNode(int k, const shared_ptr<treeNode>&pa=nullptr,
		const shared_ptr<treeNode>&lhs = nullptr, const shared_ptr<treeNode>&rhs = nullptr) :
		key(k), p(pa),left(lhs), right(rhs) {}
	int key;
	shared_ptr<treeNode>p;
	shared_ptr<treeNode>left;
	shared_ptr<treeNode>right;
};
class tree {
public:
	tree(){
		for (size_t i = 0; i !=15; ++i) {
			Tree.push_back(shared_ptr<treeNode>(new treeNode(i)));
		}
		for (size_t i = 0; i != 7; ++i) {
			Tree[i]->left = Tree[2 * i + 1];
			Tree[i]->right = Tree[2 * i + 2];
		}
		for (size_t i = 14; i != 0; --i) {
			Tree[i]->p = Tree[(i - 1) / 2];
		}
		root = Tree[0];
	}
	void factory_recurison() {
		print_key_recursion(root);
	}
	void print_key_loop() {
		stack.push_back(root);
		while (!stack.empty()) {
			shared_ptr<treeNode>temp = stack.back();
			if (temp) {
				cout << temp->key << endl;
				stack.pop_back();
				stack.push_back(temp->left);
				stack.push_back(temp->right);
			}
			else
				stack.pop_back();
		}
	}
private:
	void print_key_recursion(shared_ptr<treeNode>&r){
		if (r) {
			cout << r->key << endl;
			print_key_recursion(r->left);
			print_key_recursion(r->right);
		}
	}
	vector<shared_ptr<treeNode>>Tree;
	shared_ptr<treeNode>root;
	vector<shared_ptr<treeNode>>stack;
};
///////////////////////////////
class solution10_4_1 {
public:
	void operator()() {
		cout << "排版太麻烦"
			<< endl;
	}
};
class solution10_4_2 {
public:
	void operator()() {
		tr.factory_recurison();
	}
private:
	tree tr;
};

class solution10_4_3 {
public:
	void operator()() {
		tr.print_key_loop();
	}
private:
	tree tr;
};
//////////////////////////////
struct tree_node {
	tree_node(int k,const shared_ptr<tree_node>&pa=nullptr,const shared_ptr<tree_node>&left=nullptr,
		const shared_ptr<tree_node>&right=nullptr):key(k),p(pa),left_child(left),right_sibling(right){}
	int key;
	shared_ptr<tree_node>p;
	shared_ptr<tree_node>left_child;
	shared_ptr<tree_node>right_sibling;
};

class child_sibling_tree {
public:
	child_sibling_tree(){//初始化生成left_sibling_tree 树
		for (size_t i = 0; i != 8; ++i)
			vect.push_back(shared_ptr<tree_node>(new tree_node(i)));
		root = vect[0];
		vect[0]->left_child = vect[1];
		vect[1]->p = vect[0];
		vect[1]->right_sibling = vect[2];
		vect[2]->p = vect[0];
		vect[2]->right_sibling = vect[3];
		vect[2]->left_child = vect[4];
		vect[4]->p = vect[2];
		vect[5]->p = vect[2];
		vect[6]->p = vect[2];
		vect[7]->p = vect[2];
		vect[4]->right_sibling = vect[5];
		vect[5]->right_sibling = vect[6];
		vect[6]->right_sibling = vect[7];
	}
	void print_child_sibling() {
		print_tree(root);
	}
	void print_tree(shared_ptr<tree_node>&ptr) {
		if (ptr) {//之所以这样可行是因为每一个成员都被这两种类型的指针至少一个所指引
			cout << ptr->key << endl;
			print_tree(ptr->left_child);
			print_tree ( ptr->right_sibling);
		}
	}
private:
	vector<shared_ptr<tree_node>>vect;
	shared_ptr<tree_node>root;
};
//////////////////////////////////
class solution10_4_4 {
public:
	void operator()() {
		tr.print_child_sibling();
	}
private:
	child_sibling_tree tr;
};

//思考题
class solution10_1 {
public:
	void operator()() {
		cout << "1.cn cn cn cn \n"
			<< "2.c cn c cn \n"
			<< "3.cn cn c c \n"
			<< "4.cn c cn c \n"
			<< "5. cn cn cn c \n"
			<< "6. cn c cn c \n"
			<< "7.cn cn cn cn "
			<< endl;
	}
};

class solution10_2 {
public:
	void operator()() {
		cout << "三种情况建立一个空堆make_heap都是常数时间的 \n"
			<< "由于最小堆的性质，minimum和extract-min也是常数时间 \n"
			<< "因为链表不能随机存取，要找到一个节点必须遍历一些不需要的节点，所以找一个父节点或子节点需要花费 \n"
			<< "cn，所以直接用链表的insert和union操作不可能低于cn \n"
			<< "那么可以遍历整个链表把元素存入数组，在数组上实现insert操作，需要花费cn \n"
			<< "至于合并操作可以把两个链表的元素存入一个数组，再利用建堆花费cn,最后转化成链表，这样看起来的非常 \n"
			<< "可笑，因为链表在这里没什么用，已排序，未排序，不想交也没有用到，所以很大可能我未按作者的意图解决 \n"
			<< "这个题目"
			<< endl;
	}
};


#endif //_SOLUTION_10_H_
