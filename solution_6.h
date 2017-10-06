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
		cout << "�߶�Ϊh�Ķ�������h+1�㣬�����2^(h+1)-1,����2^h"
			<< endl;
	}
};

class solution6_1_2 {
public:
	void operator()() {
		cout << "�߶�Ϊ��lgn���Ķ���������2^(��lgn��+1��-1��Ԫ�أ�������2^(��lgn��)��Ԫ�� \n"
			<< "��2^(��lgn��)<=n<=2^(��lgn��+1��-1,��֤"
			<< endl;
	}
};

class solutin6_1_3 {
public:
	void operator()() {
		cout << "�������ѵ�����"
			<< endl;
	}
};

class solution6_1_4 {
public:
	void operator()() {
		cout << "��Ҷ����"
			<< endl;
	}
};

class solution6_1_5 {
public:
	void operator()() {
		cout << "�ǵ�"
			<< endl;
	}
};

class solution6_1_6 {
public:
	void operator()() {
		cout << "���ǣ�����λԪ�ص��ҽڵ������"
			<< endl;
	}
};

class solution6_1_7 {
public:
	void operator()() {
		cout << "��Ϊ��һ����Ҷ��Ȼû���ӽڵ㣬�����Ҷ���±�Ϊk��2*k>n,�ȼ���k>=��n/2��+1,��k��ʼ�ĺ������б�ȻҲ�� \n"
			<< "�ӽڵ�"
			<< endl;
	}
};


void print_heap(vector<int>&vect) {//��ӡ����
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

	}//Ϊ��������һ�£��ؼ��ִ��±�1��ʼ
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
		cout << "ʲô������"
			<< endl;
	}
};

class solution6_2_4 {
public:
	void operator()() {
		cout << "ʲô������"
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
		while(i<=(vect.size()-1)/2){//����ѭ���ṹ
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
	}//Ϊ��������һ�£��ؼ��ִ��±�1��ʼ
	vector<int>vect{ 0,27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0 };
};

class solution6_2_6 {
public:
	void operator()() {
		cout << "�ó�������������ǴӸ��ڵ㿪ʼһֱ���е�Ҷ�ڵ㣬ÿ�ε��û��ѳ���ʱ�䣬һ��Ҫ���ø������ܸ߶�  \n"
			<< "��lgn�Σ��ʦ�(lgn)"
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
		while (i <= (vect.size()-1) / 2) {//����ѭ���ṹ
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
	}//Ϊ��������һ�£��ؼ��ִ��±�1��ʼ
	vector<int>vect{ 0,5,3,17,10,84,19,6,22,9};
};

class solution6_3_2 {
public:
	void operator()() {
		cout << "�ڵݹ����֮ǰ�����ܱ�֤�ýڵ������������������"
			<< endl;
	}
};

class solution6_3_3 {
public:
	void operator()() {
		cout << "�߶�Ϊh�Ľڵ����ٹ���2^h���ڵ㣬��ֻ����һ����ͬ�߶ȵĽڵ�һ����2^(h+1)-1���ڵ㣬 \n"
			<<"����߶�Ϊh�Ľڵ�һ����x�������в���ʽ2^h+(2^(h+1)-1)(x-1)<n  \n"
			<<"x<(n-2^h)/(2^(h+1)-1)+1,��n����ʱ��x<n-2^h)/2^(h+1)+1=n/2^(h+1)-2^h/2^(h+1)+1<=��n/2^(h+1)��"
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
		while (i <=end/2) {//��Ϊi������һ���������������ü��Խ��
			size_t largest = i;
			if (vect[i] < vect[2 * i])//����
				largest = 2 * i;
			if (2*i+1<= end&&vect[largest] < vect[2 * i + 1])//�Һ���
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
		cout << "��ʼ�����ڵ�һ�ε�����ʼ֮ǰ��i=A.length=n,��ȻA[1...i]����������A[1...n]�ĵ�iСԪ�� \n"
			<< "������A[i+1...n]Ϊ�����е�0��Ԫ�� \n"
			<< "���֣���3�н����˵�iС��Ԫ�ص�λ�ڸ��ڵ��A[1]��A[i]��ʹ��iС��Ԫ��λ��λ��i  \n"
			<< "��4�н��������ЧԪ�ظ����ݼ�1 \n"
			<< "�����������õ�i-1С��Ԫ��λ��A[1],����һ�ε�forѭ���ݼ�iά����ѭ������ʽ \n"
			<< "��ֹ��i=1,A[1..1]�ǵ�һС��Ԫ�أ�A[2...n]Ϊ�����е�Ԫ��"
			<< endl;
	}
};

class solution6_4_3 {
public:
	void operator()() {
		cout << "���������򣬵�һ�еĴ��۶�Ϊcn \n"
			<< "���ڽ�����˵����һ�н��ɵĶѻ���ԭ����������ģ�ÿһ�ν������Ὣ��iС��Ԫ�ؽ�����λ��1 \n"
			<< "��ʱmax_heapify�Ὣ���Ԫ�����½�����Ҷ�ӣ�����lgi��ʱ�� ��ʱ��T(n)=lg(n-1)!=��(nlgn) \n"
			<< "����������˵�������ܱ�֤ÿ�ν��������max_heapify���ѳ���ʱ�䣬����ʱ��Ҳ�Ǧ�(nlgn)"
			<< endl;
	}
};

class solution6_4_4 {
public:
	void operator()() {
		cout << "���������鰴�������У������Ѿ�֤��"
			<< endl;
	}
};

class solution6_4_5 {
public:
	void operator()() {
		cout << "ʱ�临�Ӷ�Ӧ�ð����������㣬��һ�������Ѿ�֤��"
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
		cout << "ԭʼ��С����ֻ��һ����Ԫ��0��Ϊ����������ͬ" << endl;
		cout << "���β���15,13,9,5,12,8,7,4,0,6,2,1" << endl;
		for (auto i : vect) {
			min_heap_insert(i);
			print_heap(min_heap);
		}
		cout << "��λ��10�ϵ�12��Ϊ3֮��" << endl;
		heap_decrease_key(10, 3);
		print_heap(min_heap);
		cout << "��ӡ��Сֵ" << endl;
		cout << heap_minimum() << endl;
		cout << "������Сֵ" << endl;
		cout << heap_extract_min() << endl;
		cout << "������Сֵ֮��" << endl;
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
		cout << "������Ϊ����ֱ�Ӹ�ֵA[A.heap-size]=key,��һ��ĳ������ֱ�Ӹ�ֵ,������ĳ���� \n"
			<<"In order to pass the guard clause. Otherwise we have to drop the check if key<A[i]."
			<< endl;
	}
};

class solution6_5_5 {
public:
	void operator()() {
		cout << "��ʼ���������¸�ֵ���A[i]�Ǵ������ĺ��ӵģ���Ϊ����ú���ʱ��Ƚ���ֵ�;�ֵ�Ĵ�С��С�ھ�ֵ \n"
			<< "�ǲ������ѭ���ģ�����ҪôA[1...A.heap-size]������ҪôA[i]>A[parent(i)].  \n"
			<< "���֣����A[i]����A[parent(i)]��������A[i]��A[parent(i)],����ҪôA[1...A.heap-size]������ \n"
			<< "ҪôA[i]>A[parent(i)]. \n"
			<< "��ֹ����ֹ���������i<=1,���޸ĺ��ֵ��A[1]=�޸ĺ��ֵ������A[1...A.heap-size]������ \n"
			<< "������ֹ������A[i]>=A[parent(i)]��ͬ��A[1...A.heap-size]������"
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
			max_heap[i] = max_heap[i / 2];//����һ��
		max_heap[i] = key;
	}
};

class solution6_5_7 {
public:
	void operator()() {
		cout << "���Ҫʵ�����ȶ��У��������ϸ�ʵ���Ƚ��ȳ������ȳ�����Ϊ���ȶ��е������ֵ������ \n"
			<< "Ҫ��ʵ�ֶ��еĵ������������solution6_5_3�Ѿ�ʵ�֣�Ҫʵ��ջ����Ҫ�ѵ���������Ϊ����βԪ�� \n"
			<< "����ɾ���������ⲻ����ϸ����"
			<< endl;
	}
};
void max_heapify(vector<int>&vect, size_t i, int) {//����,����ӡ����
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
		cout << "ԭʽ����" << endl;
		print_heap(max_heap);
		heap_delete(3);
		cout << "ɾ���±�3Ԫ�غ������" << endl;
		print_heap(max_heap);
		heap_delete(9);
		cout << "ɾ���±�9Ԫ�غ������" << endl;
		print_heap(max_heap);
	}
private:
	vector<int>max_heap{ 0,15,13,9,5,12,8,7,4,0,6,2,1 };
	void heap_delete(size_t i) {
		swap(max_heap[i], max_heap.back());//����Ҫɾ����Ԫ�غ����һ��Ԫ��
		max_heap.pop_back();//�������һ��Ԫ��Ҳ����Ҫɾ����Ԫ��
		max_heapify(max_heap, i,0);//����ά���ѵ����ʣ�����ʱ�䦨(lgn)
	}
};

class solution6_5_9 {
public:
	void operator()() {
		cout << "��k���������Ԫ�ع���һ����СΪk����С�ѣ�ÿ�ε�����С�ѵĵ�һ��Ԫ��Ҳ������СԪ�غ�,����λ�� \n"
			<<"λ�ڵ�һ���������һ��Ԫ�ز�����ά����С�ѵ����ʣ����������������ˣ��Ͷ���С�ѵĴ�С��1 \n"
			<<"ֱ����С��Ϊ��Ҳ��������ɣ�ÿ�ε���һ��Ԫ�ز�ά���ķ�lgk��һ��Ҫ����n�Σ����Ի���nlgk \n"
			<<"��������һ��������������n�����Ӻķ�k"
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
	forward_list<int>lst4{ 3,23,33,43,43,43 };//ע�������vect�ĵ�һ��Ԫ����Ϊ�˴����ģ����±��1��ʼ
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

//˼����
class solution6_1 {
public:
	friend void max_heapify(vector<int>&, size_t, int);
	void operator()() {
		cout << "a.��ͬ��������ͬ����9,4,2,1,6,7,3,21,8�����ַ�ʽ�����Ķ�����"
			<< endl;
		built_max_heap_first();
		built_max_heap_second();
		cout << "b.�������£���һ�β���ķ�lg2,�ڶ���lg3,����lg4+lg5...+lg(n-1),T(n)=lg(n-1)!=��(nlgn)"
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
		cout << "a.����5��ѣ��ҵ��Ĺ���Ӧ�ò�ʧһ���� \n"
			<< "�±�Ϊn��Ԫ�ص�parent(n)=(n-2)/d+1,left(n)=d(n-1)+2,right(n)=nd+1  \n"
			<< "b.���ݵȱ����е���͹�ʽ������d�����߶�Ϊh�Ĺ���(d^(h+1)-1)/(d-1)=n \n"
			<< "h=��log(d,n(d-1)+1)������д�ɩ�log(d,n(d-1))�� \n"
			<< "c.T(n)=��(log(d,n(d-1))=��(log(d,n))  \n"
			<<"d.T(n)=��(log(d,n(d-1))=��(log(d,n))  \n"
			<<"e.T(n)=��(log(d,n(d-1))=��(log(d,n))"
			<< endl;
		const size_t d = 3;//�趨d����
		const int insert_value = 89;
		cout << "ԭʼ����" << endl;
		print_d_heap(d);
		built_d_max_heap(d);
		cout << "��" << d << "���" << endl;
		print_d_heap(d);
		cout << "������Ԫ��Ϊ" << endl;
		cout << extract_max(d) << endl;
		cout << "������Ԫ�غ�" << endl;
		print_d_heap(d);
		insert(d, insert_value);
		cout << "����" << insert_value << "��" << endl;
		print_d_heap(d);
		increase_key(d, 21, 82);
		cout << "�����±�21����Ϊ82��" << endl;
		print_d_heap(d);
	}
private:
	void print_d_heap(size_t d);
	vector<int>d_max_heap{ 0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	void d_max_heapify(size_t d,size_t i) {
		while (i <= (d_max_heap.size() - 1 - 2) / d + 1) {//����ʽ�ұ�Ϊһ�����������±����Ľڵ�
			size_t largest = i;
			for (size_t n = d*(i - 1) + 2; n<d_max_heap.size()&&n<= i*d + 1; ++n)//���±�Ϊi�Ľڵ����������������
				if (d_max_heap[largest]< d_max_heap[n])//��Ѱ�����ֵ
					largest = n;//��¼���ֵ�±�
		
			if (largest != i)//���ֵ�±겻��iʱ����
				swap(d_max_heap[largest], d_max_heap[i]);//��һ�����Ż������ʼΪ�˱������û���Ż�
			else
				break;//����ﵽҪ���˳�ѭ��
			i = largest;//����iֵ�����´�ѭ��
		}
	}
	int extract_max(size_t d) {
		int max = d_max_heap[1];//��¼���ֵ
		swap(d_max_heap[1], d_max_heap.back());//������λԪ��
		d_max_heap.pop_back();//ɾ��βԪ��Ҳ�������ֵ
		d_max_heapify(d, 1);//����ά����������
		return max;
	}
	void built_d_max_heap(size_t d) {
		for (size_t i = (d_max_heap.size() - 1 - 2) / 2 + 1; i != 0; --i)//��ʼ����Ϊһ�����������±����Ľڵ�
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
void solution6_2::print_d_heap(size_t d) {//��ӡd���
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
		cout << "a.����young�Ͼ�������ʺ������ƶϳ�Y[1,1]��ֵ��С��Y[n,n]��ֵ���Ȼ������������������ƹ��ɵ�˼�����\n"
			<< "�Ƚ�ԭ��������2��3,4,5,8,9,12,14,16���ȿ�2X2����ȡ���к���ĸ���2,3,4,5������A[1,1]=2,A[2,2]=5 \n"
			<< "2  4 \n"
			<< "3  5 \n"
			<< "Ȼ��3X3����Ϊ��4�����Ѿ������ˣ�����������ȡ�������8,9,12,14,16��A[3,3]=16 \n"
			<< "2  4  12 \n"
			<< "3  5  14 \n"
			<< "8  9  16 \n"
			<< "���4X4������ֱ��ȫ��ޣ�Ҳ����ѡ���ֺ���д \n"
			<< "b.Y[1,1]��ֵ��С,���Y[1,1]=�ޣ������е�ֵΪ�ޣ�Y[n,n]��ֵ���Y[n,n]=ʵ��<�ޣ����е�ֵ��Ϊʵ�� \n"
			<< "����m*n��������1<i<=m,1<=k<=m,Y[1,k]<Y[i,k]&&Y[1,1]<Y[1,k]����֤��Y[1,1]��ֵ��С \n"
			<< "ͬ���֤Y[n,n]��ֵ��� \n"
			<< "c.i+1<=m,j+1<=n,A[i,j]<=A[i,j+1],A[i,j]<=A[i+1,j],���Կ�������������С�ѶԵ����� \n"
			<< "���·�����ע�ͣ�ά��young�������ʵ�young_matrix_heapify(0, 0)�������ֵ���������Ͻ� \n"
			<<"ÿ�ݹ�һ�Σ���ֵ���һ������ƶ�һ����ֱ���Ƶ��ӽ���һ�εݹ����ǰpair_index�д洢���±�ֵʱֹͣ \n"
			<<"��֪���ƶ��Ĳ�������m+n����ÿ�����ѳ���ʱ�䣬T(p)=O(m+n) \n"
			<<"d.����һ��young_matrix_heapify()�Ĳ����෴��ʽ����һ���Ǵ����Ͻ�Ԫ��A[0,0]�������¼�����ġ������� \n"
			<<"��һ���ǽ�Ҫ�����Ԫ���ȸ�ֵ�����Ԫ�غ��棬���һ�������򸳸���һ�е�һ��Ԫ�� \n"
			<< "�������ϼ�����ġ�˫�ס�,ÿ�ݹ�һ�Σ���ֵ����������ƶ�һ����ֱ���ƶ���һ���ʺ��Լ���λ�ã�� \n"
			<<"������˶������Ͻǣ���֪���ƶ��Ĳ�������m+n����ÿ�����ѳ���ʱ�䣬T(p)=O(m+n) \n"
			<<"��д���������ֻ������young�����н������һ�֣�ÿһ�ж������Ĳ��ǡޣ������������һ�У�����ע�͵��� \n"
			<<"�Ǹ�young_matrix�Ͳ����� \n"
			<<"e.�����ڶ�����,������extract_min()���������ÿ�ε�����֮ǰ��֮����СԪ�ض������Ͻǣ�ÿ�ε����� \n"
			<<"����c(m+n)=2cn,֮��ֵ�洢��һ��������,һ����n*n��Ԫ�أ�����Ҫ����n^2�Σ�T(p)=2cn*n^2=O(n^3) \n"
			<<"f.�����ע�ͣ������Ͽ�ʼ��ÿ�ε������һ������н�һ����λֱ��Խ��"
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
			cout << "����" << i << "����" << endl;
			print_young_matrix();
		}
		//f.
		vector<int>vect_{ 9, 6,16,7,3, 2,17, 4, 8, 5, 14, 12 };//���Ҳ�������
		for (auto i : vect_) {
			cout << i;
			find(i) ? cout <<"��" :cout<< "����";
			cout<< "young_matrix��" << endl;
		}
	}
private://�����Ǵ�[0][0]��ʼ
//	vector<vector<int>>young_matrix{ {2,4,12,INT_MAX},{3,5,14,INT_MAX},{8,9,16,INT_MAX},{INT_MAX,INT_MAX,INT_MAX,INT_MAX} };
//	pair<size_t, size_t>pair_index{ 2,2 };//������ֵ���±�
	vector<vector<int>>young_matrix{ {2,3,4,5},{8,9,12,14},{16,INT_MAX ,INT_MAX ,INT_MAX },{ INT_MAX,INT_MAX,INT_MAX,INT_MAX } };
	pair<size_t, size_t>pair_index{ 2,0 };//������ֵ���±�
	void print_young_matrix() {
		for (auto &i : young_matrix) {
			for (auto &j : i)
				j == INT_MAX ? cout << "��" << "      " : cout << j << "\t";
			cout << endl;
		}
	}
	void young_matrix_heapify(size_t i, size_t j) {//���±�[i,j]�ƶ����ʺ�����λ����ά��young_matrix������
		size_t m = i;
		size_t n = j;
		if (i + 1 < young_matrix.size() && young_matrix[i + 1][j] < young_matrix[m][n])
			m = i + 1;
		if (j + 1 < young_matrix[0].size() && young_matrix[i][j + 1] < young_matrix[m][n]) {
			n = j + 1;
			m = i;
		}//��������if�жϣ���young_matrix[i][j]���С��һ������
		if (m != i || n != j) {//���i,j������ȷλ�õݹ����
			swap(young_matrix[i][j], young_matrix[m][n]);
			pair_index = make_pair(m, n);//���´ε���֮ǰ��¼[i,j]�����±�
			young_matrix_heapify(m, n);
		}
		else if (m == 0 && n == 0) 
			pair_index = make_pair(0, -1);
	}
	int extract_min() {
		int min = young_matrix[0][0];
		young_matrix[0][0] = INT_MAX;
		if(pair_index.second!=-1)
			swap(young_matrix[0][0], young_matrix[pair_index.first][pair_index.second]);//�����ֵ����[0,0]
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
		if (key == young_matrix[0][0])//�����׸�Ԫ��
			return true;
		bool flag = false;
		find_(flag,key,0,0);//�������Һ���
		return flag;
	}
	void find_(bool &flag,int key,size_t i,size_t j) {
		if (i + 1 >= young_matrix.size() && j + 1 >= young_matrix[0].size())//�������������Խ��ֱ���˳�
			return;
		pair<int, pair<size_t, size_t>>max;//�����������ֵ�����±꣬����ͬ
		pair<int, pair<size_t, size_t>>min;
		if (i + 1 >= young_matrix.size()&&j+1 < young_matrix[0].size()) {//ֻ��������û��Խ��
			if (key == young_matrix[i][j + 1]) {//��������������
				flag = true;
				return;
			}
			else if (key > young_matrix[i][j + 1]) {//����������������������
				find_(flag, key, i, j + 1);
				return;
			}
			else//С���������˳�
				return;
		}
		else if (j + 1>= young_matrix[0].size() && i + 1 < young_matrix.size() ) {//ֻ��������û��Խ�磬����ͬ��
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
		else {//����������û��Խ��
			if (young_matrix[i + 1][j] < young_matrix[i][j + 1]) {//��¼���ֵ����Сֵ���·�֧ͬ
				max.first = young_matrix[i][j + 1];//���ֵ
				max.second = make_pair(i, j + 1);//���ֵ�±�
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
		if (key < min.first) //����ؼ���С����Сֱֵ���˳�
			return;
		else if(key == min.first || key == max.first) {//���������һ������ȱ����ҵ�
			flag = true;
			return;
		}
		else if (key > max.first) {//�������ֵ�������������������
			find_(flag, key, min.second.first, min.second.second);
			find_(flag, key, max.second.first, max.second.second);
		}
		else {//�ؼ��������ֵ����С֮��ֻ�õ���������Сֵһ������
			find_(flag, key, min.second.first, min.second.second);
		}
	}
};
#endif //_SOLUTION_6_H
