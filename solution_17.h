#pragma once
#ifndef _SOLUTION_17_H_
#define _SOLUTION_17_H_
#include<iostream>
#include<vector>
using namespace std;

class solution17_1_1 {
public:
	void operator()() {
		cout << "���ǣ���Ϊ�����Ͽ���һֱִ��multipush��������kn \n"
			<< endl;
	}
};

class solution17_1_2 {
public:
	void operator()() {
		cout << "������an��a<1��ʱ���ڽ�kλ������������Ȼ�������decrement��increment������ÿ�ζ��ķ�k,���Ԧ�(nk)"
			<< endl;
	}
};

class solution17_1_3 {
public:
	void operator()() {
		cout << "���������ģn,�����lgn+1��2���ݣ�2^0+2^1+2^2+....+2^lgn=2n,ʣ�������n���n,����̯������Ϊ1"
			<< endl;
	}
};

class solution17_2_1 {
public:
	void operator()() {
		cout << "push��pop֧��2��Ԫ��ÿ����һ�β�������������1��Ԫ��ʣ�࣬��ΪҪ����k�β�������ܽ��и��Ʋ�������ջ�Ĵ�С�������k,���� \n"
			<< "k�β�����ջ�п϶�������k��Ԫʣ��"
			<< endl;
	}
};

class solution17_2_2 {
public:
	void operator()() {
		cout << "����i�Ƿ�Ϊ2���ݣ�ÿ�β����Ƕ�֧��3��Ԫ�������i�β�������2���ݣ���ôʣ�����û���2�������2���ݣ����ڵ�2^k�β�����\n"
			<< "����ǰһ��������2^(k-1)֮�����2^k������2^k-2^(k-1)������ÿ������ʣ��2��Ԫ������һ����2*2^k-2^k=2^k��Ԫ���պù� \n"
			<< "��λ���ʹ��"
			<< endl;
	}
};

class  solution17_2_3 {
public:
	void operator()() {
		cout << "��ÿһ�������ͷ�ת��λ֧��3,ÿ�μ��ͷ�ת����2�������һ���Ǹ�λ��ÿһλ����������֧����λ�ķ��ã�������Ǹ�λ \n"
			<< "�����ƶ�ÿһ��ÿһλ���и�������\n"
			<< endl;
	}
};

class solution17_3_1 {
public:
	void operator()() {
		cout << "��'(Di)=��(Di)-��(D0),��'(0)=0,��'(Di)��̯������Ϊ��'(Dn)-��'(D0)=��(Dn)-��(D0)���(Di)��̯��������ͬ"
			<< endl;
	}
};

class solution17_3_2 {
public:
	void operator()() {
		cout << "��=2*i-2^(1+��lgi����"//���
			<< endl;
	}
};

class solution17_3_3 {
public:
	void operator()() {
		cout << "��=��[i=1,n] lgi,����nΪ���в�����Ԫ�ظ�����������insert����ʱ����(Di)-��(Di-1)=lgn,ci=lgn+lgn=2lgn, \n"
			<< "������extract_min����ʱ����(Di)-��(Di-1)=-lgn��ci=lgn-lgn=O(1)"
			<< endl;
	}
};

class solution17_3_4 {
public:
	void operator()() {
		cout << "��(Di)Ϊջ��Ԫ�ظ���������push����ci'=c1+1=2,����pop������ci'=c1-1=0,����mulitpop��ci'=k'-k'=0 \n"
			<< "����ʵ�ʲ�����ci<=��2+sn-s0=2n+sn-s0"
			<< endl;
	}
};

class solution17_3_5 {
public:
	void operator()() {
		cout << "n=��(b),��ʾb<=n����������Ĺ�ʽ���ܿ�����"
			<< endl;
	}
};

class solution17_3_6 {
public:
	void operator()() {
		cout << "���ʱֱ��push��s1������ʱ���s2��Ϊ����ֱ�ӽ�s2 pop��ȥ��Ϊ����s1������Ԫ��pop��s2,Ȼ��pop��ȥ \n"
			<< "���֧��3��Ԫ����Ӳ���֧��һ��Ԫ������s2ջ1��Ԫ������������1��Ԫ"
			<< endl;
	}
};

class solution17_3_7 {
public:
	void operator()() {
		cout << "���ȷ���һ���㹻���������У�����ֱ����β�˲��룬֧��5��Ԫ����������ķ�1��Ԫ��ʣ��4��Ԫ������ʱ���ҵ���λ����������λ�� \n"
			<< "��Ϊ����Ԫ��partition,����������ÿ�����������ᳬ��2n��Ԫ��n��Ԫ�صĴ�С��ÿ��Ԫ�ػ�ʣ2��Ԫ \n"
			<< "ɾ��ֻ��Ҫ�ƶ�tail�����л���1��Ԫ����ɾ����һ���Ԫ�ص�Ǯ���ֵ�δɾ��Ԫ�أ���ʱÿ��Ԫ�ؾ�ӵ��4��Ԫ�����Խ����´�ɾ�� \n"
			<< endl;
	}
};

class solution17_4_1 {
public:
	void operator()() {
		cout << "��ת�����ӽӽ�1ʱ������������ѵ�ʱ�俪ʼ���ߵ�����ʱ�䣬��11���Ѿ�����3�ֿ��ŵ�ַ�Ĳ����㷨����Ϊ���ڲ���O(1)�Ĳ�������ƽ̯��O(1)�Ĳ����ϣ��Ӷ�ʹ��ÿ����������O(1)"
			<< endl;
	}
};
class solution17_4_2{
public:
	void operator()() {
		cout << "ci'=ci+��i-��(i-1)=1+2*(num-1)-size-(2*num-size)=-1"
			<< endl;
	}
};

class solution17_4_3 {
public:
	void operator()() {
		cout << "����ɾ��������û������������ \n"
			<< "ci'=1+|2*��num-1)-size|-|2*num-size| \n"
			<< "���ת�����Ӵ���1/2��ci'=-1 \n"
			<< "���ת������С�ڵ���1/2��ci'=3 \n"
			<< "��������˱������ \n"
			<< "ci'=1+1/3*s+|2*(num-1)-2/3*size|-|2*num-size| \n"
			<< "����num=1/3*size,ci'=3 \n"
			<< endl;
	}
};

//˼����
class solution17_1 {
public:


};

#endif