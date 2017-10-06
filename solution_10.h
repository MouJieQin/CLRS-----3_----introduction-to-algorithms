#pragma once
#ifndef _SOLUTION_10_H_
#define _SOLUTION_10_H_
#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>
using namespace std;
/////////////////////////////////////////////////
class Stack {//ջ������ʵ��
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
		cout << "��A[1]��A[n]�ֱ���Ϊ����ջ��ջ�ף���ߵ�ջpushʱ���ƣ��ұ�ջpushʱ����"
			<< endl;
	}
};
/////////////////////////////////////////////
class Queue {//���е�ʵ��
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
		cout << "������������ʵ��"
			<< endl;
	}
};
////////////////////////////////////////////////
class Deque {//˫����е�ʵ��
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
		cout <<"\n"<< "���δ�β�˲���9,8,7,6����" << endl;
		for (auto i : vect1) {
			deq.tail_enqueue(i);
			deq.print_deque();
		}
		cout << "���δ�ǰ�˲���4,3,2,1����" << endl;
		for (auto i : vect2) {
			deq.head_enqueue(i);
			deq.print_deque();
		}
		cout << "����β�˲���12�����������:" << endl;
		deq.head_enqueue(12);
		cout << "����ǰ�˲���12�����������:" << endl;
		deq.tail_enqueue(12);
		cout << "���Կ��������л���һ��0Ϊ��Ԫ�ز��ܲ��룬��������head==tailΪ�գ���head=tail+1Ϊ����ɵ� \n"
			<< "�����������ж���tailָ����һ������ĵط������Լ�������ᵼ�������Ҫ�ı���һ����Խ�tail����Ϊ \n"
			<< "ָ�����һ��Ԫ��" << endl;
		cout << "���δ��׶˵���4��Ԫ����" << endl;
		for (auto i : vect2) {
			cout << deq.head_dequeue() << "\t" << endl;
		}
		cout << "���δ�β�˵���4��Ԫ����" << endl;
		for (auto i : vect1) {
			cout << deq.tail_dequeue() << "\t" << endl;
		}
		cout << "�����׶˵��������������:" << endl;
		cout << deq.head_dequeue() << endl;
		cout << "����β�˵��������������:" << endl;
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
		cout << "1.��ջs1��Ϊ�洢ջ�����ʱpush��s1,����ʱ��s1������Ԫ��pop��s2��Ȼ��pop s2��Ϊ����Ԫ��,֮�����½�s2������Ԫ��pop��s1,\n"
			<<"���ΪO(1),����Ϊ2cn \n"
			<<"2.���ʱ�����s1��Ϊ����ֱ��push��s1,������s1��Ԫ��pop��s2,���s1Ϊ�����Ƚ�s2 ������Ԫ��pop��s1,Ȼ����ӣ�ͬ������s1��Ԫ��pop��s2 \n"
			<<"����ʱ���s1��Ϊ����ֱ�ӽ�s1 pop��ȥ��Ϊ����s2������Ԫ��pop��s1,Ȼ��pop��ȥ��Ҳ����˵��ĳһʱ��һ����һ������Ϊ�� \n"
			<<"���ʱs1Ϊ��Ϊcn,����O(1��������ʱs2Ϊ��Ϊ��Ϊcn,����O(1��\n"
			<<"3.���ʱֱ��push��s1������ʱ���s2��Ϊ����ֱ�ӽ�s2 pop��ȥ��Ϊ����s1������Ԫ��pop��s2,Ȼ��pop��ȥ \n"
			<<"���ΪO(1),����ΪO(1)��O(n)"
			<< endl;
	}
};

class solution10_1_7 {
public:
	void operator()() {
		cout << "����һ�����ƣ���׸�� ����ʱ��Ϊ��(n)"
			<< endl;
	}
};

class solution10_2_1 {
public:
	void operator()() {
		cout << "insert������O(1)��ʱ����ɣ���Ϊ���������ڱ�ͷ���У����Բ���λ��ǰ������������ָ�붼֪�� \n"
			<< "��delete�������У���Ϊֻ֪��������һ������ָ�����֪����һ�������ָ��"
			<< endl;
	}
};

struct listNode {
	listNode(int k=INT_MAX) :key(k),next(nullptr) {}
	int key;
	listNode *next;
};
///////////////////////////////////////
class Stack_list {//������ʵ��ջ
public:
	Stack_list():head(&headNode){}
	void push(listNode*x) {//���ǰ�push�����Ķ�����ڱ�ͷ
		x->next = head->next;
		head->next = x;
	}
	listNode* pop() {//������ͷ����
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
	~solution10_2_2() {//����
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
class list_queue {//��������ʵ�ֶ���
public:
	list_queue() :head(&headNode) ,tail(head){}
	void enqueue(listNode *key) {//�����������������
		tail->next = key;
		tail = key;
	//	tail->next = nullptr;
	}
	listNode* dequeue() {//�ñ�ͷԪ�س���
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
		cout << "��whileѭ��֮ǰ��L.nil.key=k,ѭ��������ɺ���x==L.nil,�Ƿ���nil�����򷵻�x"
			<< endl;
	}
};
//////////////////////
class singly_circular_list {
public:
	singly_circular_list() :head(&headNode) { headNode.next = head; }//��ʼ��ʱ��ͷָ������
	void insert(listNode *ele) {//�ڱ�ͷԪ�غ�����뻨��O(1)
		ele->next = head->next;
		head->next = ele;
	}
	void Delete(listNode *ele) {//Ҫ�ҵ�Ҫɾ��Ԫ�ص���һ��Ԫ�ػ��Ѧ�(n)
		if (head->next == ele) {//����Ҫɾ����Ԫ���ٱ�ͷ��ע���ʱ��headΪ�ڱ�
			head->next = ele->next;
			delete ele;
			return;
		}
		auto temp = head->next;
		while (temp!=head&&temp->next != ele)//����Ҫɾ����Ԫ�ز��ڱ�ͷ
			temp = temp->next;
		if (temp != head) {
			temp->next = ele->next;
			delete ele;
		}
	}
	listNode* search(int key) {//���������������Ѧ�(n)
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
		cout << "����ʱ�俴����ע��" << endl;
	}
private:
	singly_circular_list list;
};

class solution10_2_6 {
public:
	void operator()() {
		cout << "����" << endl;
	}
};

class solution10_2_7 {
public:
	solution10_2_7():head(&headNode){}
	void operator()() {
		listNode *tail=head;
		for (int i = 1; i != 10; ++i) {//����һ������
			tail->next = new listNode(i);
			tail = tail->next;//ѭ��������tailָ�����һ��Ԫ�أ���������Ѿ����ڵ�һ��������Ҫ����һ���ҵ�
		}//���һ��Ԫ�أ����Ѧ�(n)
		listNode *temp = head->next;
		while (temp) {
			cout << temp->key << "\t";
			temp = temp->next;
		}
		cout << "\n" << endl;
		listNode *tmp_a = head->next->next;//ָ���2��Ԫ�أ��������û�м����Ԫ��Ϊ1��ղ���Ҫ���������
		listNode *tmp_b = tmp_a->next;//����е�3��Ԫ����ָ�������Ԫ�أ�û����Ϊ��

		head->next->next = nullptr;//��¼�õ�2��Ԫ�غ󽫵�1��Ԫ�ص�next�ÿ�
		while (tmp_a) {//ֱ��tmp_aΪ��
			tmp_a->next = head->next;
			head->next = tmp_a;//�����н�tam_aָ���Ԫ�ز��뵽��ͷ����O(1)
			tmp_a = tmp_b;//��tmp_aָ��tmp_b
			if(tmp_b)//���tmp_b��Ϊ���������һ��Ԫ��
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
		cout << "������Ҫ֪���������ʣ�A xor 0=A ,A xor A=0,A xor B xor A=B, A xor A xor B=B \n"
			<< endl;
		cout << "����Ԫ�غ�" << endl;
		for (auto i : vect)
			insert((pt_xor)(new xorNode(i)));
		print();
		cout << "����2" << endl;
		if (search(2))
			cout << "finding " << endl;
		cout << "����21" << endl;
		if (!search(21))
			cout <<"finding nothing "<< endl;
		cout << "��ת" << endl;
		reserve();
		print();
		cout << "ɾ�����йؼ���7�Ľڵ��" << endl;
		del(search(7));
		print();
	}
private:
	vector<int>vect{ 1,3,5,7,9,2,4,6,8,10 };
	pt_xor ptx(pt_xor lhs, pt_xor rhs) { return (pt_xor)((unsigned int)(lhs) ^ (unsigned int)(rhs)); }
	pt_xor head = (pt_xor)(new xorNode(INT_MIN));
	pt_xor tail= (pt_xor)(new xorNode(INT_MIN));
	void insert(pt_xor target) {//����
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

	void print() {//��ӡ��������
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
	pt_xor search(int key) {//����
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
	void del(pt_xor target) {//ɾ��
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
	void reserve() {//��תO(1)
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
		cout << "̫�鷳��ʡ��" << endl;
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
			cout << "Ҫɾ�����±겻��ȷ" << endl;
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
		cout << "�Ű�̫�鷳"
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
	child_sibling_tree(){//��ʼ������left_sibling_tree ��
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
		if (ptr) {//֮����������������Ϊÿһ����Ա�������������͵�ָ������һ����ָ��
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

//˼����
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
		cout << "�����������һ���ն�make_heap���ǳ���ʱ��� \n"
			<< "������С�ѵ����ʣ�minimum��extract-minҲ�ǳ���ʱ�� \n"
			<< "��Ϊ�����������ȡ��Ҫ�ҵ�һ���ڵ�������һЩ����Ҫ�Ľڵ㣬������һ�����ڵ���ӽڵ���Ҫ���� \n"
			<< "cn������ֱ���������insert��union���������ܵ���cn \n"
			<< "��ô���Ա������������Ԫ�ش������飬��������ʵ��insert��������Ҫ����cn \n"
			<< "���ںϲ��������԰����������Ԫ�ش���һ�����飬�����ý��ѻ���cn,���ת�������������������ķǳ� \n"
			<< "��Ц����Ϊ����������ûʲô�ã�������δ���򣬲��뽻Ҳû���õ������Ժܴ������δ�����ߵ���ͼ��� \n"
			<< "�����Ŀ"
			<< endl;
	}
};


#endif //_SOLUTION_10_H_
