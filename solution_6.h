#pragma once
#ifndef _SOLUTION_6_H
#define _SOLUTION_6_H
#include<iostream>
#include<vector>
#include<forward_list>
#include<deque>
using namespace std;
class solution6_1_1 {
public:
	void operator()() {
		cout << "高度为h的二叉树有h+1层，最多有2^(h+1)-1,最少2^h"
			<< endl;
	}
};

class solution6_1_2 {
public:
	void operator()() {
		cout << "高度为┕lgn┙的二叉堆最多有2^(┕lgn┙+1）-1个元素，最少有2^(┕lgn┙)个元素 \n"
			<< "而2^(┕lgn┙)<=n<=2^(┕lgn┙+1）-1,得证"
			<< endl;
	}
};

class solutin6_1_3 {
public:
	void operator()() {
		cout << "这是最大堆的性质"
			<< endl;
	}
};

class solution6_1_4 {
public:
	void operator()() {
		cout << "在叶子上"
			<< endl;
	}
};

class solution6_1_5 {
public:
	void operator()() {
		cout << "是的"
			<< endl;
	}
};

class solution6_1_6 {
public:
	void operator()() {
		cout << "不是，第四位元素的右节点比它大"
			<< endl;
	}
};

class solution6_1_7 {
public:
	void operator()() {
		cout << "因为第一个子叶必然没有子节点，设此子叶的下标为k，2*k>n,等价于k>=┕n/2┙+1,从k开始的后续序列必然也是 \n"
			<< "子节点"
			<< endl;
	}
};


void print_heap(vector<int>&vect) {//打印最大堆
	size_t counter = 1;
	size_t count = 1;
	for (size_t i = 1; i <vect.size(); ++i) {
		cout << vect[i] << "\t";
		if (i == counter) {
			count *= 2;
			counter += count;
			cout << "\n";
		}
	}
	cout << endl;
	cout << endl;
}

class solution6_2_1 {
public:
	void operator()() {
		print_heap(vect);
		max_heapify(3);
	}
private:
	void max_heapify(size_t i) {
		size_t largest=i;
		if (2*i<vect.size()&&vect[i] < vect[2 * i])
			largest = 2 * i;
		if (2 * i+1<vect.size() && vect[largest] < vect[2 * i + 1])
			largest += 1;
		if (largest != i) {
			int temp=vect[largest];
			vect[largest] = vect[i];
			vect[i] = temp;
			print_heap(vect);
			max_heapify(largest);
		}

	}//为了与书上一致，关键字从下标1开始
	vector<int>vect{0,27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
};

class solution6_2_2 {
public:
	void operator()() {
		print_heap(vect);
		min_heapify(2);
	}
private:
	void min_heapify(size_t n) {
		size_t minVauleIndex = n;
		if (2 * n < vect.size() && vect[2 * n] < vect[n])
			minVauleIndex = 2 * n;
		if(2 * n+1 < vect.size() && vect[2 * n+1] < vect[n])
			minVauleIndex = 2 * n+1;
		if (minVauleIndex != n) {
			int temp = vect[minVauleIndex];
			vect[minVauleIndex] = vect[n];
			vect[n] = temp;
			print_heap(vect);
			min_heapify(minVauleIndex);
		}
	}
	vector<int>vect{0,1,11,3,4,5,6,7,8,9,10,2,12,13,14};
};

class solution6_2_3 {
public:
	void operator()() {
		cout << "什么都不做"
			<< endl;
	}
};

class solution6_2_4 {
public:
	void operator()() {
		cout << "什么都不做"
			<< endl;
	}
};

class solution6_2_5 {
public:
	void operator()() {
		print_heap(vect);
		max_heapify(3);
	}
private:
	void max_heapify(size_t i) {
		while(i<=(vect.size()-1)/2){//采用循环结构
			size_t largest = i;
			if ( vect[i] < vect[2 * i])
				largest = 2 * i;
			if (largest <vect.size() && vect[largest] < vect[2 * i + 1])
				largest += 1;
			if (largest != i) {
				int temp = vect[largest];
				vect[largest] = vect[i];
				vect[i] = temp;
				print_heap(vect);
				i = largest;
			}
			else
				break;
		}
	}//为了与书上一致，关键字从下标1开始
	vector<int>vect{ 0,27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0 };
};

class solution6_2_6 {
public:
	void operator()() {
		cout << "该程序的最坏运行情况是从根节点开始一直运行到叶节点，每次调用花费常数时间，一共要调用该数的总高度  \n"
			<< "即lgn次，故Ω(lgn)"
			<< endl;
	}
};
class solution6_3_1 {
public:
	void operator()() {
		build_max_heap();
	}
private:
	void build_max_heap() {
		print_heap(vect);
		for (size_t i = (vect.size() - 1) / 2; i !=0; --i)
			max_heapify(i);
	}
	void max_heapify(size_t i) {
		while (i <= (vect.size()-1) / 2) {//采用循环结构
			size_t largest = i;
			if (vect[i] < vect[2 * i])
				largest = 2 * i;
			if (largest <vect.size()&&vect[largest] < vect[2 * i + 1])
				largest += 1;
			if (largest != i) {
				int temp = vect[largest];
				vect[largest] = vect[i];
				vect[i] = temp;
				print_heap(vect);
				i = largest;
			}
			else
				break;
		}
	}//为了与书上一致，关键字从下标1开始
	vector<int>vect{ 0,5,3,17,10,84,19,6,22,9};
};

class solution6_3_2 {
public:
	void operator()() {
		cout << "在递归调用之前并不能保证该节点的左右子树都是最大堆"
			<< endl;
	}
};

class solution6_3_3 {
public:
	void operator()() {
		cout << "高度为h的节点最少共有2^h个节点，但只能有一个，同高度的节点一共有2^(h+1)-1个节点， \n"
			<<"假设高度为h的节点一共有x个，则有不等式2^h+(2^(h+1)-1)(x-1)<n  \n"
			<<"x<(n-2^h)/(2^(h+1)-1)+1,当n→∞时，x<n-2^h)/2^(h+1)+1=n/2^(h+1)-2^h/2^(h+1)+1<=┍n/2^(h+1)┑"
			<< endl;
	}
};

class solution6_4_1 {
public:
	void operator()() {
		heapSort();
	}
private:
	void max_heapicy(size_t i,size_t end) {
		while (i <=end/2) {//因为i满足这一条件，左子树不用检测越界
			size_t largest = i;
			if (vect[i] < vect[2 * i])//左孩子
				largest = 2 * i;
			if (2*i+1<= end&&vect[largest] < vect[2 * i + 1])//右孩子
				largest = 2 * i + 1;
			if (largest != i) {
				swap(vect[i], vect[largest]);
				i = largest;
			}
			else 
				break;
		}
	}

	void built_heap() {
		for (size_t i = (vect.size() - 1) / 2; i != 0; --i)
			max_heapicy(i,vect.size()-1);
	}
	void heapSort() {
		built_heap();
		print_heap(vect);
		swap(vect[1], vect.back());
		for (size_t i = vect.size() - 2; i !=0; --i) {
			max_heapicy(1,i);
			print_heap(vect);
			swap(vect[1], vect[i]);
		}
	}
	vector<int>vect{0,5,13,2,15,7,17,20,8,4 };
//	vector<int>vect{ 0,1,2,3,4,5,6,7,8,9 };
};

class  solution6_4_2 {
public:
	void operator()() {
		cout << "初始化：在第一次迭代开始之前，i=A.length=n,显然A[1...i]包含了数组A[1...n]的第i小元素 \n"
			<< "子数组A[i+1...n]为以排列的0个元素 \n"
			<< "保持：第3行交换了第i小的元素的位于根节点的A[1]和A[i]，使第i小的元素位于位置i  \n"
			<< "第4行将数组的有效元素个数递减1 \n"
			<< "第五行重新让第i-1小的元素位于A[1],对下一次的for循环递减i维持了循环不变式 \n"
			<< "终止：i=1,A[1..1]是第一小的元素，A[2...n]为以排列的元素"
			<< endl;
	}
};

class solution6_4_3 {
public:
	void operator()() {
		cout << "无论升序降序，第一行的代价都为cn \n"
			<< "对于降序来说，第一行建成的堆还是原来那样降序的，每一次交换都会将第i小的元素交换到位置1 \n"
			<< "这时max_heapify会将这个元素重新交换到叶子，花费lgi的时间 总时间T(n)=lg(n-1)!=Θ(nlgn) \n"
			<< "对于升序来说，并不能保证每次交换后调用max_heapify花费常数时间，所以时间也是Θ(nlgn)"
			<< endl;
	}
};

class solution6_4_4 {
public:
	void operator()() {
		cout << "最坏情况是数组按降序排列，上题已经证明"
			<< endl;
	}
};

class solution6_4_5 {
public:
	void operator()() {
		cout << "时间复杂度应该按最坏的情况来算，这一题上题已经证明"
			<< endl;
	}
};

void max_heapify(vector<int>&vect, size_t i) {
	while (i <= (vect.size() - 1) / 2) {
		size_t largest = i;
		if (vect[i] < vect[2 * i])
			largest = 2 * i;
		if (2 * i + 1 < vect.size() && vect[largest] < vect[2 * i + 1])
			largest = 2 * i + 1;
		if (largest != i)
			swap(vect[i], vect[largest]);
		else
			break;
		i = largest;
		print_heap(vect);
	}
}


class solution6_5_1 {
public:
	friend void max_heapify(vector<int>&,size_t);
	int operator()() {
		return heap_extract_max();
	}
private:
	vector<int>max_heap{ 0,15,13,9,5,12,8,7,4,0,6,2,1 };
	int heap_extract_max() {
		if (max_heap.size()==1) {
			cerr << "heap underflow !!!" << endl;
			return INT_MIN;
		}
		int max = max_heap[1];
		swap(max_heap[1], max_heap.back());
		max_heap.pop_back();
		max_heapify(max_heap, 1);
		return max;
	}
};

class solution6_5_2 {
public:
	void operator()() {
		max_heap_insert(10);
	}
private:
	vector<int>max_heap{ 0,15,13,9,5,12,8,7,4,0,6,2,1 };
	void  max_heap_insert(size_t n) {
		max_heap.push_back(n);
		size_t i = max_heap.size() - 1;
		for (; i > 1 && max_heap[i / 2] < max_heap[i]; i /= 2) {
			swap(max_heap[i / 2], max_heap[i]);
			print_heap(max_heap);
		}
	//	max_heap[i]=max_heap[]
	}
};

void min_heapify(vector<int>&min_heap, size_t i) {
	while (i <= (min_heap.size() - 1) / 2) {
		size_t smallest = i;
		if (min_heap[i] > min_heap[2 * i])
			smallest = 2 * i;
		if (min_heap[smallest] > min_heap[2 * i + 1])
			smallest = 2 * i + 1;
		if (smallest != i)
			swap(min_heap[i], min_heap[smallest]);
		else
			break;
		i = smallest;
	}
}

class solution6_5_3 {
public:
	friend void min_heapify(vector<int>&min_heap, size_t i);
	void operator()() {
		vector<int>vect{ 15,13,9,5,12,8,7,4,0,6,2,1 };
		cout << "原始最小堆中只有一个非元素0，为了与书上相同" << endl;
		cout << "依次插入15,13,9,5,12,8,7,4,0,6,2,1" << endl;
		for (auto i : vect) {
			min_heap_insert(i);
			print_heap(min_heap);
		}
		cout << "将位置10上的12改为3之后" << endl;
		heap_decrease_key(10, 3);
		print_heap(min_heap);
		cout << "打印最小值" << endl;
		cout << heap_minimum() << endl;
		cout << "弹出最小值" << endl;
		cout << heap_extract_min() << endl;
		cout << "弹出最小值之后" << endl;
		print_heap(min_heap);
	}
	int heap_minimum() {
		if (min_heap.size() == 1) {
			cerr << "heap underflow!!! " << endl;
			return INT_MAX;
		}
		return min_heap[1];
	}
	int heap_extract_min() {
		if (min_heap.size() == 1) {
			cerr << "heap underflow!!! " << endl;
			return INT_MAX;
		}
		int min = min_heap[1];
		swap(min_heap[1], min_heap.back());
		min_heap.pop_back();
		min_heapify(min_heap, 1);
		return min;
	}
	void heap_decrease_key(size_t n, int key) {
		if (min_heap[n] < key) {
			cerr<<"new key is bigger than current key !!!" << endl;
			return;
		}
		min_heap[n] = key;
		for (; n > 1 && min_heap[n / 2] > min_heap[n]; n /= 2) 
			swap(min_heap[n / 2], min_heap[n]);
	}
	void min_heap_insert(int key) {
		min_heap.push_back(key);
		heap_decrease_key(min_heap.size() - 1, key);
	}
private:
	vector<int>min_heap{ 0 };
};
class solution6_5_4 {
public:
	void operator()() {
		cout << "个人认为可以直接赋值A[A.heap-size]=key,上一题的程序就是直接赋值,下面是某个答案 \n"
			<<"In order to pass the guard clause. Otherwise we have to drop the check if key<A[i]."
			<< endl;
	}
};

class solution6_5_5 {
public:
	void operator()() {
		cout << "初始化：被重新赋值后的A[i]是大于他的孩子的，因为进入该函数时会比较新值和旧值的大小，小于旧值 \n"
			<< "是不会进入循环的，所以要么A[1...A.heap-size]是最大堆要么A[i]>A[parent(i)].  \n"
			<< "保持：如果A[i]大于A[parent(i)]，将交换A[i]和A[parent(i)],所以要么A[1...A.heap-size]是最大堆 \n"
			<< "要么A[i]>A[parent(i)]. \n"
			<< "终止：终止条件如果是i<=1,即修改后的值，A[1]=修改后的值，所以A[1...A.heap-size]是最大堆 \n"
			<< "或者终止条件是A[i]>=A[parent(i)]，同样A[1...A.heap-size]是最大堆"
			<< endl;
	}
};

class solution6_5_6 {
public:
	void operator()() {
		print_heap(max_heap);
		heap_increase_key(11, 31);
		print_heap(max_heap);
	}
private:
	vector<int>max_heap{ 0,15,13,9,5,12,8,7,4,0,6,2,1 };
	void heap_increase_key(size_t i,int key) {
		if (key < max_heap[i]) {
			cerr<<"new key is smaller than current key !!!" << endl;
			return;
		}
		for (; i > 1 && key > max_heap[i / 2]; i /= 2)
			max_heap[i] = max_heap[i / 2];//交换一次
		max_heap[i] = key;
	}
};

class solution6_5_7 {
public:
	void operator()() {
		cout << "如果要实现优先队列，并不能严格实现先进先出或后进先出，因为优先队列的特殊插值操作， \n"
			<< "要简单实现队列的弹出插入操作，solution6_5_3已经实现，要实现栈，需要把弹出操作改为弹出尾元素 \n"
			<< "至于删除操作本题不做详细讨论"
			<< endl;
	}
};
void max_heapify(vector<int>&vect, size_t i, int) {//重载,不打印过程
	while (i <= (vect.size() - 1) / 2) {
		size_t largest = i;
		if (vect[i] < vect[2 * i])
			largest = 2 * i;
		if (2 * i + 1 < vect.size() && vect[largest] < vect[2 * i + 1])
			largest = 2 * i + 1;
		if (largest != i)
			swap(vect[i], vect[largest]);
		else
			break;
		i = largest;
	}
}

class solution6_5_8 {
public:
	friend void max_heapify(vector<int>&vect, size_t i,int);
	void operator()() {
		cout << "原式最大堆" << endl;
		print_heap(max_heap);
		heap_delete(3);
		cout << "删除下标3元素后的最大堆" << endl;
		print_heap(max_heap);
		heap_delete(9);
		cout << "删除下标9元素后的最大堆" << endl;
		print_heap(max_heap);
	}
private:
	vector<int>max_heap{ 0,15,13,9,5,12,8,7,4,0,6,2,1 };
	void heap_delete(size_t i) {
		swap(max_heap[i], max_heap.back());//交换要删除的元素和最后一个元素
		max_heap.pop_back();//弹出最后一个元素也就是要删除的元素
		max_heapify(max_heap, i,0);//重新维护堆的性质，花费时间Θ(lgn)
	}
};

class solution6_5_9 {
public:
	void operator()() {
		cout << "对k个链表的首元素构成一个大小为k的最小堆，每次弹出最小堆的第一个元素也就是最小元素后,递增位于 \n"
			<<"位于第一个链表的下一个元素并重新维护最小堆的性质，如果该链表遍历完了，就对最小堆的大小减1 \n"
			<<"直到最小堆为空也就排序完成，每次弹出一个元素并维护耗费lgk，一共要弹出n次，所以花费nlgk \n"
			<<"递增到下一个迭代器共花费n，建队耗费k"
			<< endl;
		merge_min_heap();
		for (auto i : order)
			cout << i << "\t";
		cout << endl;
		cout << endl;
	}
private:
	forward_list<int>lst;
	forward_list<int>lst1{ 4,24,34,44,54,64,74 };
	forward_list<int>lst2{ 1,21,31,41,51,61 };
	forward_list<int>lst3{ 2,22,32,42,52,62,72,82, };
	forward_list<int>lst4{ 3,23,33,43,43,43 };//注意下面的vect的第一个元素是为了凑数的，让下标从1开始
	vector < pair<forward_list<int>::iterator, forward_list<int>::iterator>>vect{ {lst.begin(),lst.end()},
	{lst1.begin(),lst1.end()},{lst2.begin(),lst2.end()},{lst3.begin(),lst3.end()},{lst4.begin(),lst4.end()} };
	vector<int>order;
	void min_heapify(size_t i) {
		while (i <=(vect.size() - 1) / 2) {
			size_t smallest = i;
			if (*vect[i].first > *vect[2 * i].first)
				smallest = 2 * i;
			if (2 * i + 1 < vect.size() && *vect[smallest].first > *vect[2 * i + 1].first)
				smallest = 2 * i + 1;
			if (smallest != i) {
				swap(vect[i], vect[smallest]);
				i = smallest;
			}
			else
				break;				
		}
	}
	void built_min_hepa() {
		for (size_t i = (vect.size() - 1) / 2; i != 0; --i)
			min_heapify(i);
	}
	int extract_heap() {
		int min = *vect[1].first;
		if (++vect[1].first == vect[1].second) {
			swap(vect[1], vect.back());
			vect.pop_back();
			min_heapify(1);
		}
		else
			min_heapify(1);
		return min;
	}
	void merge_min_heap() {
		built_min_hepa();
		while (vect.size()!=1)
			order.push_back(extract_heap());
	}
};

//思考题
class solution6_1 {
public:
	friend void max_heapify(vector<int>&, size_t, int);
	void operator()() {
		cout << "a.不同，对于相同输入9,4,2,1,6,7,3,21,8，两种方式产生的堆如下"
			<< endl;
		built_max_heap_first();
		built_max_heap_second();
		cout << "b.在最坏情况下，第一次插入耗费lg2,第二次lg3,依次lg4+lg5...+lg(n-1),T(n)=lg(n-1)!=Θ(nlgn)"
			<< endl;
	}
private:
	vector<int>max_heap{ 0,9,4,2,1,6,7,3,21,8 };
	void built_max_heap_first() {
		vector<int>temp(max_heap);
		for (size_t i = (temp.size() - 1) / 2; i != 0; --i)
			max_heapify(temp, i, 0);
		print_heap(temp);
	}
	void max_heap_insert(vector<int>&heap,int i) {
		int key = heap[i];
		for (; i > 1 && heap[i / 2] < key; i /= 2)
			heap[i] = heap[i / 2];
		heap[i] = key;
	}
	void built_max_heap_second() {
		vector<int>temp(max_heap);
		for (size_t i = 2; i < temp.size(); ++i)
			max_heap_insert(temp, i);
		print_heap(temp);
	}
};

class solution6_2 {
public:
	void operator()() {
		cout << "a.画到5叉堆，找到的规律应该不失一般性 \n"
			<< "下标为n的元素的parent(n)=(n-2)/d+1,left(n)=d(n-1)+2,right(n)=nd+1  \n"
			<< "b.根据等比数列的求和公式对于满d叉树高度为h的共有(d^(h+1)-1)/(d-1)=n \n"
			<< "h=┕log(d,n(d-1)+1)┙，简写成┕log(d,n(d-1))┙ \n"
			<< "c.T(n)=Θ(log(d,n(d-1))=Θ(log(d,n))  \n"
			<<"d.T(n)=Θ(log(d,n(d-1))=Θ(log(d,n))  \n"
			<<"e.T(n)=Θ(log(d,n(d-1))=Θ(log(d,n))"
			<< endl;
		const size_t d = 3;//设定d叉树
		const int insert_value = 89;
		cout << "原始数据" << endl;
		print_d_heap(d);
		built_d_max_heap(d);
		cout << "建" << d << "叉堆" << endl;
		print_d_heap(d);
		cout << "弹出首元素为" << endl;
		cout << extract_max(d) << endl;
		cout << "弹出首元素后" << endl;
		print_d_heap(d);
		insert(d, insert_value);
		cout << "插入" << insert_value << "后" << endl;
		print_d_heap(d);
		increase_key(d, 21, 82);
		cout << "增加下标21数据为82后" << endl;
		print_d_heap(d);
	}
private:
	void print_d_heap(size_t d);
	vector<int>d_max_heap{ 0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	void d_max_heapify(size_t d,size_t i) {
		while (i <= (d_max_heap.size() - 1 - 2) / d + 1) {//不等式右边为一定有子树的下标最大的节点
			size_t largest = i;
			for (size_t n = d*(i - 1) + 2; n<d_max_heap.size()&&n<= i*d + 1; ++n)//在下标为i的节点和其最左最右子树
				if (d_max_heap[largest]< d_max_heap[n])//中寻找最大值
					largest = n;//记录最大值下标
		
			if (largest != i)//最大值下标不是i时交换
				swap(d_max_heap[largest], d_max_heap[i]);//这一步可优化，但最开始为了避免出错没有优化
			else
				break;//如果达到要求退出循环
			i = largest;//更新i值进入下次循环
		}
	}
	int extract_max(size_t d) {
		int max = d_max_heap[1];//记录最大值
		swap(d_max_heap[1], d_max_heap.back());//交换首位元素
		d_max_heap.pop_back();//删除尾元素也就是最大值
		d_max_heapify(d, 1);//重新维护最大堆性质
		return max;
	}
	void built_d_max_heap(size_t d) {
		for (size_t i = (d_max_heap.size() - 1 - 2) / 2 + 1; i != 0; --i)//初始条件为一定有子树的下标最大的节点
			d_max_heapify(d, i);
	}
	void insert(size_t d, int key) {
		d_max_heap.push_back(key);
		size_t n = d_max_heap.size() - 1;
		for (; n > 1 && d_max_heap[(n - 2) / d + 1] < key; n = (n - 2) / d + 1)
			d_max_heap[n] = d_max_heap[(n - 2) / d + 1];
		d_max_heap[n] = key;
	}
	void increase_key(size_t d, size_t i, int key) {
		if (key < d_max_heap[i]) {
			cerr << "new key is smaller than current key" << endl;
			return;
		}
		d_max_heap[i] = key;
		for (; i > 1 && d_max_heap[(i - 2) / d + 1] < key; i = (i - 2) / d + 1)
			d_max_heap[i] = d_max_heap[(i - 2) / d + 1];
		d_max_heap[i] = key;
	}
};
void solution6_2::print_d_heap(size_t d) {//打印d叉堆
	size_t counter = 1;
	size_t count = d;
	for (size_t i = 1; i != d_max_heap.size(); ++i) {
		cout << d_max_heap[i] << "  ";
		if (i == counter) {
			cout << endl;
			counter += count;
			count *= d;
		}
	}
	cout << endl;
	cout << endl;
}

class solution6_3 {
public:
	void operator()() {
		cout << "a.根据young氏矩阵的性质很容易推断出Y[1,1]的值最小，Y[n,n]的值最大，然后运用这个性质用类似归纳的思想求解\n"
			<< "先将原数组排序，2，3,4,5,8,9,12,14,16，先看2X2矩阵，取排列后的四个数2,3,4,5，其中A[1,1]=2,A[2,2]=5 \n"
			<< "2  4 \n"
			<< "3  5 \n"
			<< "然后看3X3，因为有4个数已经排列了，所以我们再取后面的数8,9,12,14,16，A[3,3]=16 \n"
			<< "2  4  12 \n"
			<< "3  5  14 \n"
			<< "8  9  16 \n"
			<< "最后看4X4，可以直接全填∞，也可自选数字后填写 \n"
			<< "b.Y[1,1]的值最小,如果Y[1,1]=∞，则所有的值为∞，Y[n,n]的值最大，Y[n,n]=实数<∞，所有的值都为实数 \n"
			<< "对于m*n矩阵，任意1<i<=m,1<=k<=m,Y[1,k]<Y[i,k]&&Y[1,1]<Y[1,k]可以证明Y[1,1]的值最小 \n"
			<< "同理可证Y[n,n]的值最大 \n"
			<< "c.i+1<=m,j+1<=n,A[i,j]<=A[i,j+1],A[i,j]<=A[i+1,j],可以看出这类似于最小堆对的性质 \n"
			<< "见下方程序注释，维护young矩阵性质的young_matrix_heapify(0, 0)程序将最大值交换到左上角 \n"
			<<"每递归一次，该值向右或向下移动一步，直到移到接近第一次递归调用前pair_index中存储的下标值时停止 \n"
			<<"可知它移动的步数等于m+n步，每步花费常数时间，T(p)=O(m+n) \n"
			<<"d.与上一题young_matrix_heapify()的操作相反格式，上一题是从左上角元素A[0,0]向右向下检测它的‘子树’ \n"
			<<"这一题是将要插入的元素先赋值给最大元素后面，如果一行满了则赋给下一行第一个元素 \n"
			<< "向左向上检测它的‘双亲’,每递归一次，该值向左或向上移动一步，直到移动到一个适合自己的位置，最坏 \n"
			<<"情况是运动到左上角，可知它移动的步数等于m+n步，每步花费常数时间，T(p)=O(m+n) \n"
			<<"我写的这个程序只适用于young矩阵中较特殊的一种，每一行都是满的不是∞，除非是在最后一行，被我注释掉的 \n"
			<<"那个young_matrix就不适用 \n"
			<<"e.类似于堆排序,可以用extract_min()来完成排序，每次调用它之前或之后，最小元素都在左上角，每次调用它 \n"
			<<"花费c(m+n)=2cn,之后将值存储在一个数组里,一共有n*n个元素，所以要调用n^2次，T(p)=2cn*n^2=O(n^3) \n"
			<<"f.具体见注释，从左上开始，每次迭代向右或向下行进一个单位直到越界"
			<< endl;
		print_young_matrix();
		//c.
		while (young_matrix[0][0] != INT_MAX) {
			cout << "value is" << endl;
			cout << extract_min() << endl;
			cout << endl;
			cout << "matrix is" << endl;
			print_young_matrix();
			cout << endl;
		}
		//d.
		vector<int>vect{9, 16, 3, 2, 4, 8, 5, 14, 12};
		for (auto i : vect) {
			insert(i);
			cout << "插入" << i << "后有" << endl;
			print_young_matrix();
		}
		//f.
		vector<int>vect_{ 9, 6,16,7,3, 2,17, 4, 8, 5, 14, 12 };//查找测试样例
		for (auto i : vect_) {
			cout << i;
			find(i) ? cout <<"在" :cout<< "不在";
			cout<< "young_matrix中" << endl;
		}
	}
private://矩阵是从[0][0]开始
//	vector<vector<int>>young_matrix{ {2,4,12,INT_MAX},{3,5,14,INT_MAX},{8,9,16,INT_MAX},{INT_MAX,INT_MAX,INT_MAX,INT_MAX} };
//	pair<size_t, size_t>pair_index{ 2,2 };//存放最大值的下标
	vector<vector<int>>young_matrix{ {2,3,4,5},{8,9,12,14},{16,INT_MAX ,INT_MAX ,INT_MAX },{ INT_MAX,INT_MAX,INT_MAX,INT_MAX } };
	pair<size_t, size_t>pair_index{ 2,0 };//存放最大值的下标
	void print_young_matrix() {
		for (auto &i : young_matrix) {
			for (auto &j : i)
				j == INT_MAX ? cout << "∞" << "      " : cout << j << "\t";
			cout << endl;
		}
	}
	void young_matrix_heapify(size_t i, size_t j) {//将下标[i,j]移动到适合它的位置以维持young_matrix的性质
		size_t m = i;
		size_t n = j;
		if (i + 1 < young_matrix.size() && young_matrix[i + 1][j] < young_matrix[m][n])
			m = i + 1;
		if (j + 1 < young_matrix[0].size() && young_matrix[i][j + 1] < young_matrix[m][n]) {
			n = j + 1;
			m = i;
		}//经过两次if判断，将young_matrix[i][j]与较小的一个交换
		if (m != i || n != j) {//如果i,j不在正确位置递归迭代
			swap(young_matrix[i][j], young_matrix[m][n]);
			pair_index = make_pair(m, n);//在下次迭代之前记录[i,j]所在下标
			young_matrix_heapify(m, n);
		}
		else if (m == 0 && n == 0) 
			pair_index = make_pair(0, -1);
	}
	int extract_min() {
		int min = young_matrix[0][0];
		young_matrix[0][0] = INT_MAX;
		if(pair_index.second!=-1)
			swap(young_matrix[0][0], young_matrix[pair_index.first][pair_index.second]);//将最大值置于[0,0]
		young_matrix_heapify(0, 0);
		return min;
	}
	void insert_f(size_t i, size_t j) {
		size_t m = i;
		size_t n = j;
		if (j != 0 && young_matrix[i][j - 1] > young_matrix[m][n])
			n = j - 1;
		if (i != 0 && young_matrix[i - 1][j] > young_matrix[m][n]) {
			m = i - 1;
			n = j;
		}
		if (m != i || n != j) {
			swap(young_matrix[m][n], young_matrix[i][j]);
			insert_f(m, n);
		}
	}
	void insert(int key) {

		if (pair_index.second + 1 >= young_matrix[0].size()&& pair_index.first + 1< young_matrix.size())
			pair_index = make_pair(pair_index.first+1, -1);

		if (pair_index.second + 1 < young_matrix[0].size()) {
			young_matrix[pair_index.first][pair_index.second + 1] = key;
			size_t temp = pair_index.second + 1;
			pair_index = make_pair(pair_index.first, temp);
			insert_f(pair_index.first, temp);
		}
	}
	bool find(int key) {
		if (key == young_matrix[0][0])//测试首个元素
			return true;
		bool flag = false;
		find_(flag,key,0,0);//真正查找函数
		return flag;
	}
	void find_(bool &flag,int key,size_t i,size_t j) {
		if (i + 1 >= young_matrix.size() && j + 1 >= young_matrix[0].size())//如果下右两子树越界直接退出
			return;
		pair<int, pair<size_t, size_t>>max;//放下右两最大值和其下标，下意同
		pair<int, pair<size_t, size_t>>min;
		if (i + 1 >= young_matrix.size()&&j+1 < young_matrix[0].size()) {//只有右子树没有越界
			if (key == young_matrix[i][j + 1]) {//等于右子树返回
				flag = true;
				return;
			}
			else if (key > young_matrix[i][j + 1]) {//大于右子树继续迭代查找
				find_(flag, key, i, j + 1);
				return;
			}
			else//小于右子树退出
				return;
		}
		else if (j + 1>= young_matrix[0].size() && i + 1 < young_matrix.size() ) {//只有下子树没有越界，意义同上
			if (key == young_matrix[i + 1][j]) {
				flag = true;
				return;
			}
			else if (key > young_matrix[i + 1][j]) {
				find_(flag, key, i + 1, j);
				return;
			}
			else
				return;
		}
		else {//左右子树都没有越界
			if (young_matrix[i + 1][j] < young_matrix[i][j + 1]) {//记录最大值和最小值，下分支同
				max.first = young_matrix[i][j + 1];//最大值
				max.second = make_pair(i, j + 1);//最大值下标
				min.first = young_matrix[i + 1][j];
				min.second = make_pair(i + 1, j);
			}
			else {
				max.first = young_matrix[i + 1][j];
				max.second = make_pair(i + 1, j);
				min.first = young_matrix[i][j + 1];
				min.second = make_pair(i, j + 1);
			}
		}
		if (key < min.first) //如果关键字小于最小值直接退出
			return;
		else if(key == min.first || key == max.first) {//如果与其中一个字相等表明找到
			flag = true;
			return;
		}
		else if (key > max.first) {//大于最大值，向两个方向迭代查找
			find_(flag, key, min.second.first, min.second.second);
			find_(flag, key, max.second.first, max.second.second);
		}
		else {//关键字在最大值和最小之间只用迭代查找最小值一个方向
			find_(flag, key, min.second.first, min.second.second);
		}
	}
};
#endif //_SOLUTION_6_H
